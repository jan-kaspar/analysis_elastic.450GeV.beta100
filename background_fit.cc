#include <TDirectory.h>
#include <TH1.h>
#include "classes/Config.hh"
#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TGraphErrors.h"

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>\n");
	printf("OPTIONS:\n");
	printf("    -cfg <file>       config file\n");
	printf("    -dgn <string>     diagonal\n");
}

//----------------------------------------------------------------------------------------------------

TF1 *ff = new TF1("ff", "[0] * exp(-[1]*x) * (TMath::Erf( (x - [2]) / [3] ))/2 + [4] + [5]*x");

void FitOne(TGraphErrors *g, const string &tag)
{
	TDirectory *d_top = gDirectory;

	gDirectory = d_top->mkdir(tag.c_str());

	ff->SetRange(0, 0.025);

	ff->SetParameters(0.20, 0., 0., 0., 0., 0.);
	ff->FixParameter(1, 1634.);
	ff->FixParameter(2, 0.0001);
	ff->FixParameter(3, 0.0025);
	ff->FixParameter(4, 0.);
	ff->FixParameter(5, 0.);
	g->Fit(ff, "Q", "", 3E-4, 0.005);

	ff->ReleaseParameter(1);
	ff->ReleaseParameter(2);
	ff->ReleaseParameter(3);
	g->Fit(ff, "Q", "", 3E-4, 0.005);
	g->Fit(ff, "Q", "", 3E-4, 0.015);

	ff->ReleaseParameter(4);
	ff->ReleaseParameter(5);
	g->Fit(ff, "Q", "", 3E-4, 0.015);
	g->Fit(ff, "Q", "", 3E-4, 0.025);

	g->Write("g");
	ff->Write("ff");

	gDirectory = d_top;
}

//----------------------------------------------------------------------------------------------------

void RegulariseUnc(TH1D *h)
{
	for (int bi = 1; bi <= h->GetNbinsX(); ++bi)
	{
		if (h->GetBinError(bi) <= 0.)
		{
			double unc = 1.;
			for (int bj = bi - 1; bj >= 1; --bj)
			{
				if (auto e = h->GetBinError(bj); e > 0)
				{
					unc = e;
					break;
				}
			}

			h->SetBinError(bi, unc);
		}
	}
}

//----------------------------------------------------------------------------------------------------

void ProcessOne(TH1D *h_in_bt, TH1D *h_in_tb, TH1D *h_in_bb, TH1D *h_in_tt)
{
	if (!h_in_bt || !h_in_tb || !h_in_bb || !h_in_tt)
	{
		printf("ERROR: incomplete input to ProcessOne\n");
		return;
	}

	TGraphErrors *g_bb = new TGraphErrors();
	g_bb->SetName("g_bb");
	TGraphErrors *g_tt = new TGraphErrors();
	g_tt->SetName("g_tt");
	TGraphErrors *g_mean = new TGraphErrors();
	g_mean->SetName("g_mean");
	TGraphErrors *g_unc = new TGraphErrors();
	g_unc->SetName("g_unc");

	RegulariseUnc(h_in_bb);
	RegulariseUnc(h_in_tt);

	for (int bi = 1; bi <= h_in_bt->GetNbinsX(); ++bi)
	{
		const double x = h_in_bt->GetBinCenter(bi);
		const double x_unc = h_in_bt->GetBinWidth(bi) / 2.;

		const double v_den = (h_in_bt->GetBinContent(bi) + h_in_tb->GetBinContent(bi) ) / 2.;
		const double v_den_unc = sqrt(pow(h_in_bt->GetBinError(bi), 2) + pow(h_in_tb->GetBinContent(bi), 2)) / 2.;

		if (v_den <= 0.)
			continue;

		const double v_bb = h_in_bb->GetBinContent(bi);
		const double v_bb_unc = h_in_bb->GetBinError(bi);
		const double r_bb = v_bb / v_den;
		const double r_bb_unc = sqrt( pow(v_bb_unc / v_den, 2) + pow(v_bb / v_den * v_den_unc / v_den, 2));

		const double v_tt = h_in_tt->GetBinContent(bi);
		const double v_tt_unc = h_in_tt->GetBinError(bi);
		const double r_tt = v_tt / v_den;
		const double r_tt_unc = sqrt( pow(v_tt_unc / v_den, 2) + pow(v_tt / v_den * v_den_unc / v_den, 2));

		const double v_mean = (v_bb + v_tt) / 2.;
		const double v_mean_unc = sqrt( pow(v_bb_unc, 2) + pow(v_tt_unc, 2)) / 2;
		const double r_mean = v_mean / v_den;
		const double r_mean_unc = sqrt( pow(v_mean_unc / v_den, 2) + pow(v_mean / v_den * v_den_unc / v_den, 2));

		const double v_unc = fabs(v_bb - v_tt) / 2.;
		const double v_unc_unc = sqrt( pow(v_bb_unc, 2) + pow(v_tt_unc, 2)) / 2;
		const double r_unc = v_unc / v_den;
		const double r_unc_unc = sqrt( pow(v_unc_unc / v_den, 2) + pow(v_unc / v_den * v_den_unc / v_den, 2));

		int idx = g_bb->GetN();

		g_bb->SetPoint(idx, x, r_bb);
		g_bb->SetPointError(idx, x_unc, r_bb_unc);

		g_tt->SetPoint(idx, x, r_tt);
		g_tt->SetPointError(idx, x_unc, r_tt_unc);

		g_mean->SetPoint(idx, x, r_mean);
		g_mean->SetPointError(idx, x_unc, r_mean_unc);

		g_unc->SetPoint(idx, x, r_unc);
		g_unc->SetPointError(idx, x_unc, r_unc_unc);
	}

	FitOne(g_bb, "bb");
	FitOne(g_tt, "tt");
	FitOne(g_mean, "mean");
	FitOne(g_unc, "unc");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string cfg_file = "config.py";
	string diagonal_input = "";

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-cfg", cfg_file)) continue;
		if (TestStringParameter(argc, argv, argi, "-dgn", diagonal_input)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// run initialisation
	if (Init(cfg_file, diagonal_input) != 0)
		return 2;

	// compatibility check
	if (cfg.diagonal != dCombined)
		return rcIncompatibleDiagonal;

	// print settings
	PrintConfiguration();

	// settings
	vector<string> binnings = anal.binnings;

	map<string, string> flavours = {
		{ "before_acc_corr", "h_t_before" },
		{ "after_acc_corr", "h_t_after" },
	};

	// get input
	string fn_in = "eff3outof4_" + cfg.diagonal_str + ".root";

	TFile *f_in_bt = TFile::Open("distributions_45b_56t.root");
	TFile *f_in_tb = TFile::Open("distributions_45t_56b.root");
	TFile *f_in_bb = TFile::Open("distributions_anti_45b_56b.root");
	TFile *f_in_tt = TFile::Open("distributions_anti_45t_56t.root");

	if (!f_in_bt || !f_in_tb || !f_in_bb || !f_in_tt)
	{
		printf("ERROR: can't load input files (%p, %p, %p, %p)\n", f_in_bt, f_in_tb, f_in_bb, f_in_tt);
		return 1;
	}

	// prepare output
	TFile *f_out = new TFile(("background_fit_" + cfg.diagonal_str + ".root").c_str(), "recreate");

	// loop over binnings
	for (const auto &binning : binnings)
	{
		TDirectory *d_binning = f_out->mkdir(binning.c_str());

		for (const auto &fp : flavours)
		{
			TDirectory *d_flavour = d_binning->mkdir(fp.first.c_str());

			TH1D* h_in_bt = (TH1D *) f_in_bt->Get(("acceptance correction/" + binning + "/" + fp.second).c_str());
			TH1D* h_in_tb = (TH1D *) f_in_tb->Get(("acceptance correction/" + binning + "/" + fp.second).c_str());
			TH1D* h_in_bb = (TH1D *) f_in_bb->Get(("acceptance correction/" + binning + "/" + fp.second).c_str());
			TH1D* h_in_tt = (TH1D *) f_in_tt->Get(("acceptance correction/" + binning + "/" + fp.second).c_str());

			gDirectory = d_flavour;
			ProcessOne(h_in_bt, h_in_tb, h_in_bb, h_in_tt);
		}
	}

	// clean up
	delete f_out;
	return 0;
}
