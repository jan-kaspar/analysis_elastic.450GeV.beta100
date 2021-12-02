#include <cstdio>
#include <string>
#include <vector>

#include "TFile.h"
#include "TDirectory.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Dataset
{
	string tag;
	string file;
};

//----------------------------------------------------------------------------------------------------

string replace(const string &input, const string &fnd, const string &repl)
{
	string output = input;	

	size_t pos = 0;
	while (true)
	{
		pos = output.find(fnd, pos);
		if (pos == string::npos)
			break;

		output.replace(pos, fnd.length(), repl);

		pos += 1 + repl.length() - fnd.length();
	}

	return output;
}

//----------------------------------------------------------------------------------------------------

void AnalyzeCentral(TH2D *h2)
{
	TDirectory *d_top = gDirectory;

	// preparations
	TGraphErrors *g_th_x_mode_vs_vtx_x = new TGraphErrors;
	g_th_x_mode_vs_vtx_x->SetNameTitle("g_th_x_mode_vs_vtx_x", ";vtx_x;mode of th_x");

	unique_ptr<TF1> ff(new TF1("ff", "gaus(0) + pol2(3)"));

	// make slices
	gDirectory = d_top->mkdir("slices");

	for (int bi = 1; bi <= h2->GetXaxis()->GetNbins(); ++bi)
	{
		const double x = h2->GetXaxis()->GetBinCenter(bi);

		if (x < -0.8 || x > +0.8)
			continue;

		// get projection
		TH1D *h_proj = h2->ProjectionY("", bi, bi);

		// get basic parameters
		double p0 = -1, c0 = 0;
		for (int i = 1; i <= h_proj->GetNbinsX(); ++i)
		{
			const double v = h_proj->GetBinContent(i);
			if (v > p0)
			{
				c0 = h_proj->GetBinCenter(i);
				p0 = v;
			}
		}

		const double p1 = h_proj->GetBinContent(h_proj->FindBin(-100E-6));
		const double p2 = h_proj->GetBinContent(h_proj->FindBin(+100E-6));
		const double p3 = (p1 + p2) / 2.;

		// fit projection and extract centre
		ff->SetParameters(p0 - p3, c0, 50E-6, p3, 0., -1.3E8);
		h_proj->Fit(ff.get(), "Q", "", -300E-6, +300E-6);
		h_proj->Fit(ff.get(), "Q", "", -300E-6, +300E-6);

		const double cen = ff->GetParameter(1);
		const double cen_unc = ff->GetParError(1);

		// save fit
		char buf[100];
		sprintf(buf, "x=%.2E", x);
		h_proj->Write(buf);

		// add point to global graph
		int idx = g_th_x_mode_vs_vtx_x->GetN();
		g_th_x_mode_vs_vtx_x->SetPoint(idx, x, cen);
		g_th_x_mode_vs_vtx_x->SetPointError(idx, 0., cen_unc);
	}

	// make global fit
	gDirectory = d_top;

	g_th_x_mode_vs_vtx_x->Fit("pol1", "Q");

	g_th_x_mode_vs_vtx_x->Write();
}

//----------------------------------------------------------------------------------------------------

void AnalyzeBand(TH2D *h2)
{
	TDirectory *d_top = gDirectory;

	// preparations
	TGraphErrors *g_vtx_x_mode_vs_th_x = new TGraphErrors;
	g_vtx_x_mode_vs_th_x->SetNameTitle("g_vtx_x_mode_vs_th_x", ";th_x;mode of vtx_x");

	unique_ptr<TF1> ff(new TF1("ff", "gaus(0)"));

	// make slices
	gDirectory = d_top->mkdir("slices");

	for (int bi = 1; bi <= h2->GetYaxis()->GetNbins(); ++bi)
	{
		const double y = h2->GetYaxis()->GetBinCenter(bi);

		if (y < -300E-6 || fabs(y) < 100E-6 || y > +300E-6)
			continue;

		// get projection
		TH1D *h_proj = h2->ProjectionX("", bi, bi);

		// get basic parameters
		const double p0 = h_proj->GetBinContent(h_proj->FindBin(0));

		// fit projection and extract centre
		ff->SetParameters(p0, 0, 0.5);
		h_proj->Fit(ff.get(), "Q", "", -1.5, +1.5);
		h_proj->Fit(ff.get(), "Q", "", -1.5, +1.5);

		const double cen = ff->GetParameter(1);
		const double cen_unc = ff->GetParError(1);

		// save fit
		char buf[100];
		sprintf(buf, "y=%.2E", y);
		h_proj->Write(buf);

		// add point to global graph
		int idx = g_vtx_x_mode_vs_th_x->GetN();
		g_vtx_x_mode_vs_th_x->SetPoint(idx, y, cen);
		g_vtx_x_mode_vs_th_x->SetPointError(idx, 0., cen_unc);
	}

	// make global fit
	gDirectory = d_top;

	g_vtx_x_mode_vs_th_x->Fit("pol1", "Q");

	g_vtx_x_mode_vs_th_x->Write();
}

//----------------------------------------------------------------------------------------------------

void AnalyzeOne(TH2D *h2)
{
	h2->Write("h2");

	TDirectory *d_top = gDirectory;

	gDirectory = d_top->mkdir("central");
	AnalyzeCentral(h2);

	gDirectory = d_top->mkdir("band");
	AnalyzeBand(h2);
}

//----------------------------------------------------------------------------------------------------

void AnalyzeOneXY(TH2D *h2)
{
	h2->Write("h2");

	TDirectory *d_top = gDirectory;

	// preparations
	TGraphErrors *g_mode_vs_th_x = new TGraphErrors;
	g_mode_vs_th_x->SetNameTitle("g_mode_vs_th_x", ";th_x;mode of RLdiff of th_y");

	unique_ptr<TF1> ff(new TF1("ff", "gaus(0)"));

	// make slices
	gDirectory = d_top->mkdir("slices");

	for (int bi = 1; bi <= h2->GetXaxis()->GetNbins(); ++bi)
	{
		const double x = h2->GetXaxis()->GetBinCenter(bi);

		if (x < -300E-6 || x > +300E-6)
			continue;

		// get projection
		TH1D *h_proj = h2->ProjectionY("", bi, bi);

		// get basic parameters
		const double p0 = h_proj->GetMean();
		const double p1 = h_proj->GetBinContent(h_proj->FindBin(p0));

		// fit projection and extract centre
		ff->SetParameters(p1, p0, 7E-6);
		const double fit_min = p0 - 15E-6, fit_max = p0 + 15E-6;
		h_proj->Fit(ff.get(), "Q", "", fit_min, fit_max);
		h_proj->Fit(ff.get(), "Q", "", fit_min, fit_max);

		const double cen = ff->GetParameter(1);
		const double cen_unc = ff->GetParError(1);

		// save fit
		char buf[100];
		sprintf(buf, "x=%.2E", x);
		h_proj->Write(buf);

		// add point to global graph
		int idx = g_mode_vs_th_x->GetN();
		g_mode_vs_th_x->SetPoint(idx, x, cen);
		g_mode_vs_th_x->SetPointError(idx, 0., cen_unc);
	}

	// make global fit
	gDirectory = d_top;

	g_mode_vs_th_x->Fit("pol1", "Q");

	g_mode_vs_th_x->Write();
}

//----------------------------------------------------------------------------------------------------

void AnalyzeOneY(TH2D *h2)
{
	h2->Write("h2");

	TDirectory *d_top = gDirectory;

	// preparations
	TGraphErrors *g_mode_vs_th_y = new TGraphErrors;
	g_mode_vs_th_y->SetNameTitle("g_mode_vs_th_y", ";th_y;mode of RLdiff of th_y");

	unique_ptr<TF1> ff(new TF1("ff", "gaus(0)"));

	// make slices
	gDirectory = d_top->mkdir("slices");

	for (int bi = 1; bi <= h2->GetXaxis()->GetNbins(); ++bi)
	{
		const double x = h2->GetXaxis()->GetBinCenter(bi);

		if (fabs(x) < 40E-6 || fabs(x) > 120E-6)
			continue;

		// get projection
		TH1D *h_proj = h2->ProjectionY("", bi, bi);

		// get basic parameters
		const double p0 = 0.;
		const double p1 = h_proj->GetBinContent(h_proj->FindBin(p0));

		// fit projection and extract centre
		ff->SetParameters(p1, p0, 7.5E-6);
		const double fit_min = p0 - 15E-6, fit_max = p0 + 15E-6;
		h_proj->Fit(ff.get(), "Q", "", fit_min, fit_max);
		h_proj->Fit(ff.get(), "Q", "", fit_min, fit_max);

		const double cen = ff->GetParameter(1);
		const double cen_unc = ff->GetParError(1);

		// save fit
		char buf[100];
		sprintf(buf, "x=%.2E", x);
		h_proj->Write(buf);

		// add point to global graph
		int idx = g_mode_vs_th_y->GetN();
		g_mode_vs_th_y->SetPoint(idx, x, cen);
		g_mode_vs_th_y->SetPointError(idx, 0., cen_unc);
	}

	// make global fit
	gDirectory = d_top;

	g_mode_vs_th_y->Fit("pol1", "Q");

	g_mode_vs_th_y->Write();
}

//----------------------------------------------------------------------------------------------------

int main()
{
	// config
	vector<Dataset> datasets = {
		{ "fill7291", "../data/fill7291/Totem1/distributions_<diagonal>.root" },
		{ "fill7291-test", "../data/fill7291-debug/test/distributions_<diagonal>.root" },

		{ "all-good:default", "../data/all-good/Totem1/default/distributions_<diagonal>.root" },
		{ "all-good:tune", "../data/all-good/Totem1/tune/distributions_<diagonal>.root" }
	};

	vector<string> diagonals = {
		"45b_56t",
		"45t_56b",
	};

	// prepare output
	unique_ptr<TFile> f_out(TFile::Open("analyze_tilts.root", "recreate"));

	// process
	for (const auto &ds : datasets)
	{
		TDirectory *d_dataset = f_out->mkdir(ds.tag.c_str());

		for (const auto &dgn : diagonals)
		{
			TDirectory *d_dgn = d_dataset->mkdir(dgn.c_str());

			const string f = replace(ds.file, "<diagonal>", dgn);
			unique_ptr<TFile> f_in(TFile::Open(f.c_str()));

			// x part
			TDirectory *d_part_x = d_dgn->mkdir("x");

			TH2D *h2_L = (TH2D *) f_in->Get("selected - angles/h2_th_x_L_vs_vtx_x_L");
			TH2D *h2_R = (TH2D *) f_in->Get("selected - angles/h2_th_x_R_vs_vtx_x_R");

			gDirectory = d_part_x->mkdir("L");
			AnalyzeOne(h2_L);

			gDirectory = d_part_x->mkdir("R");
			AnalyzeOne(h2_R);

			// xy part
			TDirectory *d_part_xy = d_dgn->mkdir("xy");

			TH2D *h2_xy = (TH2D *) f_in->Get("selected - angles/h2_th_y_diffRL_vs_th_x_G");

			gDirectory = d_part_xy;
			AnalyzeOneXY(h2_xy);

			// y part
			TDirectory *d_part_y = d_dgn->mkdir("y");

			TH2D *h2_y = (TH2D *) f_in->Get("selected - angles/h2_th_y_diffRL_vs_th_y_G");

			gDirectory = d_part_y;
			AnalyzeOneY(h2_y);
		}
	}

	return 0;
}