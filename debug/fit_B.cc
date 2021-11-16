#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TGraphErrors.h"

#include <TDirectory.h>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Range
{
    double t_min, t_max;
};

//----------------------------------------------------------------------------------------------------

TF1 *ff = new TF1("ff", "[0] * exp(-[1]*x)");

void FitOneDataSet(TH1D *h_dsdt, const vector<Range> &ranges, vector<TGraphErrors *> &rangePlots, unsigned int x_value)
{
    h_dsdt->Write("h_dsdt");

    for (unsigned int ri = 0; ri < ranges.size(); ++ri)
    {
        const auto &range = ranges[ri];

        ff->SetParameters(230., 16);
		ff->SetRange(range.t_min, range.t_max);
        h_dsdt->Fit(ff, "Q", "", range.t_min, range.t_max);

        char buf[100];
        sprintf(buf, "fit_range_%.3f_%.3f", range.t_min, range.t_max);
        ff->Write(buf);

        auto &rp = rangePlots[ri];
        int idx = rp->GetN();
        rp->SetPoint(idx, x_value, ff->GetParameter(1));
        rp->SetPointError(idx, 0., ff->GetParError(1));
    }
}

//----------------------------------------------------------------------------------------------------

void FitOneR(TH1D *h_dsdt, TGraphErrors *g, double x_value)
{
    // R = v1 / v2
    // v1 = mean ds/dt in Coulomb region (first bins in acceptance)
    // v2 = ds/dt extrapolated to t = 0

    // determine v1
    const int bin_min = h_dsdt->FindBin(3.1E-4);
    const int bin_max = h_dsdt->FindBin(4.9E-4);
    double s_C = 0., s_Cu2 = 0.;
    for (int bi = bin_min; bi <= bin_max; ++bi)
    {
        s_C += h_dsdt->GetBinContent(bi);
        s_Cu2 += pow(h_dsdt->GetBinError(bi), 2);
    }

    const double n = bin_max - bin_min + 1;
    const double v1 = s_C / n;
    const double v1_unc = sqrt(s_Cu2) / n;

    // determine v2
    ff->SetParameters(230., 16);
    h_dsdt->Fit(ff, "Q", "", 0.005, 0.020);
    const double v2 = ff->GetParameter(0), v2_unc = ff->GetParError(0);

    const double R = v1 / v2;
    const double R_unc = R * sqrt( v1_unc*v1_unc/v1/v1 + v2_unc*v2_unc/v2/v2 );

    // fill results
    int idx = g->GetN();
    g->SetPoint(idx, x_value, R);
    g->SetPointError(idx, 0., R_unc);

    // save results
    TGraph *g_R = new TGraph();
    g_R->SetName("g_R");
    g_R->SetPoint(0, R, R_unc);
    g_R->Write();
}

//----------------------------------------------------------------------------------------------------

struct Dataset
{
    string tag;
    string file;
    string path;
    string group = "other";
    unsigned int idx = 0;

    TH1D* GetHist() const
    {
        TFile *f_in = TFile::Open(file.c_str());
        TH1D *h = (TH1D *) f_in->Get(path.c_str());
        h->SetDirectory(nullptr);
        delete f_in;
        return h;
    }
};

//----------------------------------------------------------------------------------------------------

int main()
{
    string binning = "sb1";

    vector<Dataset> datasets;

    {
        unsigned int fill_idx = 0;

        for (const string &fill : {
            "fill7280",
            "fill7281",
            "fill7282",
            "fill7283",
            "fill7284",
            "fill7285",
            "fill7289",
            "fill7291"})
        {
            datasets.push_back({fill + "_combined", "../data/merged.root", "sb1/" + fill + "/combined/h_dsdt", "combined", fill_idx});
            datasets.push_back({fill + "_45b_56t", "../data/merged.root", "sb1/" + fill + "/45b_56t/h_dsdt", "45b_56t", fill_idx});
            datasets.push_back({fill + "_45t_56b", "../data/merged.root", "sb1/" + fill + "/45t_56b/h_dsdt", "45t_56b", fill_idx});

            fill_idx++;
        }
    }

    datasets.push_back({"merged_45b_56t", "../data/merged.root", "sb1/merged/45b_56t/h_dsdt"});
    datasets.push_back({"merged_45t_56b", "../data/merged.root", "sb1/merged/45t_56b/h_dsdt"});

    for (const string &fc : {
            "default", 
            "th_x_hig", "th_x_low", "th_x_mid", "th_y_hig", "th_y_low", "th_y_low_mid",
            "vtx_x_hig", "vtx_x_low", "vtx_x_mid", "vtx_y_hig", "vtx_y_low", "vtx_y_mid",
            "vtx_x_y_mid",
            "opt1", "opt2", "opt3",
            "default_m_x_adj_+1si", "default_m_x_adj_-1si", "default_m_y_adj_+1si", "default_m_y_adj_-1si", "default_m_x_adj_-1si_m_y_adj_+1si"
        })
    {
        for (const string &dgn : {"45b_56t", "45t_56b"})
            datasets.push_back({"all-good_" + fc + "_" + dgn, "../data/all-good/Totem1/" + fc + "/distributions_" + dgn + ".root",
                "normalization+unfolding/sb1/h_t_normalized_unsmeared"});
    }

    vector<Range> ranges = {
        Range{0.005, 0.010},
        Range{0.010, 0.015},
        Range{0.015, 0.020},
        Range{0.020, 0.025},
        Range{0.005, 0.025},
    };

    map<string, vector<TGraphErrors *>> rangePlots;
    map<string, TGraphErrors*> RPlots;

    TFile *f_out = TFile::Open("fit_B.root", "recreate");

    for (const auto &ds : datasets)
    {
        printf("* %s\n", ds.tag.c_str());

        TH1D *h_dsdt = ds.GetHist();

        TDirectory *d_ds = f_out->mkdir(ds.tag.c_str());
        gDirectory = d_ds;

        auto rap = rangePlots.find(ds.group);
        if (rap == rangePlots.end())
        {
            vector<TGraphErrors *> v;
            for (const auto &range : ranges)
            {
                char buf[100];
                sprintf(buf, "g_B_vs_dataset_group_%s_range_%.3f_%.3f", ds.group.c_str(), range.t_min, range.t_max);
                TGraphErrors *g = new TGraphErrors();
                g->SetName(buf);
                v.push_back(g);
            }
            rap = rangePlots.insert({ds.group, v}).first;
        }

        FitOneDataSet(h_dsdt, ranges, rap->second, ds.idx);

        auto rp = RPlots.find(ds.group);
        if (rp == RPlots.end())
        {
            char buf[100];
            sprintf(buf, "g_R_vs_dataset_group_%s", ds.group.c_str());
            TGraphErrors *g = new TGraphErrors();
            g->SetName(buf);

            rp = RPlots.insert({ds.group, g}).first;
        }

        FitOneR(h_dsdt, rp->second, ds.idx);
    }

    gDirectory = f_out;
    
    TF1 *ff_const = new TF1("ff_const", "[0]");

    for (auto &p : rangePlots)
    {
        for (auto *pl : p.second)
        {
            pl->Fit(ff_const, "Q");
            pl->Write();
        }
    }

    for (auto p : RPlots)
    {
        p.second->Fit(ff_const, "Q");
        p.second->Write();
    }

    delete f_out;
}
