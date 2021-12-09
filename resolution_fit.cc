#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TProfile.h"
#include "TCanvas.h"

#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

void RunOneFit(const vector<pair<double, double>> &fitIntervals, TGraphErrors *g_rms, double unc_th)
{
	// local fit function
	TF1 *ff = new TF1("ff", "1 ++ x");

	// graph of fit results
	TGraph *g_fits = new TGraph();
	g_fits->SetName("g_fits");
	g_fits->SetTitle(";timestamp;RMS");

	// loop intervals
	for (const auto &interval : fitIntervals)
	{
		const double t_min = interval.first;
		const double t_max = interval.second;

		printf("    t_min = %.0f, t_max = %.0f\n", t_min, t_max);

		// copy selected points
		TGraphErrors *g_rms_sel = new TGraphErrors();

		for (int pi = 0; pi < g_rms->GetN(); ++pi)
		{
			double t, rms, rms_u;
			g_rms->GetPoint(pi, t, rms);
			rms_u = g_rms->GetErrorY(pi);

			if (t < t_min || t > t_max)
				continue;

			if (rms_u > unc_th)
				continue;

			int idx = g_rms_sel->GetN();
			g_rms_sel->SetPoint(idx, t, rms);
			g_rms_sel->SetPointError(idx, 0., rms_u);
		}

		printf("    points selected: %i\n", g_rms_sel->GetN());

		// data sufficient?
		if (g_rms_sel->GetN() < 3)
			continue;

		// make fit
		g_rms_sel->Fit(ff, "Q");

		// add points to g_fit
		const double a = ff->GetParameter(1);
		const double b = ff->GetParameter(0);

		int idx = g_fits->GetN();
		g_fits->SetPoint(idx, t_min, a*t_min + b);
		g_fits->SetPoint(idx+1, t_max, a*t_max + b);

		// clean up
		delete g_rms_sel;
	}

	// save output
	g_fits->SetLineColor(2);
	g_fits->Write();

	TCanvas *c = new TCanvas();
	c->SetName("c_cmp_data_fit");
	g_rms->Draw();
	g_fits->Draw("l");
	c->Write();

	// clean up
	delete ff;
}

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>\n");
	printf("OPTIONS:\n");
	printf("    -cfg <file>       config file\n");
	printf("    -dgn <string>     diagonal\n");
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
	if (cfg.diagonal != d45b_56t && cfg.diagonal != d45t_56b)
		return rcIncompatibleDiagonal;

	// print settings
	PrintConfiguration();

	// fit intervals
	vector<pair<double, double>> fitIntervals = {
		{78E3, 90E3},
		{92E3, 102E3},
		{105E3, 116E3},
		{122E3, 125E3},
		{130E3, 144E3},
		{150E3, 155E3},
		{205E3, 219E3},
		{232E3, 245E3},
	};

	// get input
	TFile *f_in = new TFile((string("distributions_") + cfg.diagonal_str + ".root").c_str());

	TGraphErrors *gRMS_diffRL_th_x_vs_time = (TGraphErrors *) f_in->Get("time dependences/gRMS_diffRL_th_x_vs_time");
	TGraphErrors *gRMS_diffRL_th_y_vs_time = (TGraphErrors *) f_in->Get("time dependences/gRMS_diffRL_th_y_vs_time");

	if (!gRMS_diffRL_th_x_vs_time || !gRMS_diffRL_th_y_vs_time)
	{
		printf("ERROR: input not found (%p, %p)\n", gRMS_diffRL_th_x_vs_time, gRMS_diffRL_th_y_vs_time);
		return 1;
	}
	
	// prepare output
	TFile *f_out = new TFile((string("resolution_fit_") + cfg.diagonal_str + ".root").c_str(), "recreate");

	// do fits
	printf("\n\n---------- d_x ----------\n");
	gDirectory = f_out->mkdir("d_x");
	RunOneFit(fitIntervals, gRMS_diffRL_th_x_vs_time, 3E-6);

	printf("\n\n---------- d_y ----------\n");
	gDirectory = f_out->mkdir("d_y");
	RunOneFit(fitIntervals, gRMS_diffRL_th_y_vs_time, 1E-6);

	// clean up
	delete f_out;
	delete f_in;
	return 0;
}
