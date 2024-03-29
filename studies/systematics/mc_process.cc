#include "classes/command_line_tools.hh"
#include "classes/common_algorithms.hh"

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

TH1D* GetHistogram(const string &dir, const string &model, const string &scenario, const string &binning, const string &obj)
{
	string file = dir + "/" + model + "/" + scenario + ".root";
	TFile *f_in = TFile::Open(file.c_str());
	if (!f_in)
	{
		printf("ERROR: can't open file '%s'.\n", file.c_str());
		return nullptr;
	}

	string path = binning + "/" + obj;
	TH1D *h_orig = (TH1D *) f_in->Get(path.c_str());
	if (!h_orig)
	{
		printf("ERROR: can't load object '%s'.\n", path.c_str());
		return nullptr;
	}

	gDirectory = nullptr;	// not to associate h_ret with f_in which will be closed in a moment
	TH1D *h_ret = new TH1D(*h_orig);

	delete f_in;

	return h_ret;
}

//----------------------------------------------------------------------------------------------------

double GetNormalisation(TH1D *h)
{
	return 1. / GetNormalizationFactor(h);
}

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: mc_process [option] [option] ...\n");
	printf("OPTIONS:\n");
	printf("    -input <directory>\n");
	printf("    -output <file>\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string inputDirectory = "simu";

	string outFileName = "mc_process.root";

	string ref_scenario = "none";

	string model_base = "fit_2";
	string model_secondary = "fit_3";

	struct Scenario
	{
		string label;
		enum Mode { mDsdt, mUnsmearing } mode;
	};

	vector<Scenario> scenarios = {
		{ "none", Scenario::mDsdt },

		{ "sh-thx", Scenario::mDsdt },
		{ "sh-thx-LRasym", Scenario::mDsdt },

		{ "sh-thy", Scenario::mDsdt },
		{ "sh-thy-LRasym", Scenario::mDsdt },
		{ "sh-thy-TBuncor", Scenario::mDsdt },
		{ "sh-thy-TBuncor-LRasym", Scenario::mDsdt },

		{ "tilt-thx-thy", Scenario::mDsdt },
		{ "tilt-thx-thy-LRasym", Scenario::mDsdt },

		{ "sc-thxy-mode1", Scenario::mDsdt },
		{ "sc-thxy-mode2", Scenario::mDsdt },
		{ "sc-thxy-mode3", Scenario::mDsdt },
		{ "sc-thxy-mode4", Scenario::mDsdt },

		{ "dx-sigma", Scenario::mDsdt },
		{ "dy-sigma", Scenario::mDsdt },
		{ "dx-non-gauss", Scenario::mDsdt },
		/*
		{ "dx-mx-corr", Scenario::mDsdt },
		{ "dy-my-corr", Scenario::mDsdt },
		*/

		{ "eff-mode1", Scenario::mDsdt },
		{ "eff-mode2", Scenario::mDsdt },
		{ "eff-mode3", Scenario::mDsdt },

		{ "beam-mom", Scenario::mDsdt },

		{ "mx-sigma", Scenario::mUnsmearing },
		{ "my-sigma", Scenario::mUnsmearing },

		{ "bckg", Scenario::mDsdt },

		{ "norm", Scenario::mDsdt },
	};

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-input", inputDirectory)) continue;

		if (TestStringParameter(argc, argv, argi, "-output", outFileName)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// list of binnings
	vector<string> binnings;
	binnings.push_back("sb1");
	binnings.push_back("sb2");
	binnings.push_back("sb3");

	// output file	
	TFile *f_out = new TFile(outFileName.c_str(), "recreate");

	// process all scenarios
	for (const auto &scenario : scenarios)
	{
		TDirectory *d_scenario = f_out->mkdir(scenario.label.c_str());

		for (const string &binning : binnings)
		{
			TDirectory *d_binning = d_scenario->mkdir(binning.c_str());

			// get reference histograms
			TH1D *h_t_tr_ref = GetHistogram(inputDirectory, model_base, ref_scenario, binning, "h_t_tr");
			TH1D *h_t_re_ref = GetHistogram(inputDirectory, model_base, ref_scenario, binning, "h_t_re");

			// get histogram with effect
			TH1D *h_t_tr = GetHistogram(inputDirectory, model_base, scenario.label, binning, "h_t_tr");
			TH1D *h_t_re = GetHistogram(inputDirectory, model_base, scenario.label, binning, "h_t_re");

			// validate input
			if (!h_t_tr_ref || !h_t_re_ref || !h_t_re)
				continue;

			// make corrected histograms for scaling
			TH1D *h_t_1 = nullptr;
			TH1D *h_t_0 = nullptr;
			if (scenario.mode == Scenario::mDsdt)
			{
				TH1D *h_unsm_corr = new TH1D(*h_t_tr_ref);
				h_unsm_corr->Divide(h_t_re_ref);

				h_t_1 = new TH1D(*h_t_re);
				h_t_1->Multiply(h_unsm_corr);

				h_t_0 = new TH1D(*h_t_tr_ref);

				delete h_unsm_corr;
			}

			if (scenario.mode == Scenario::mUnsmearing)
			{
				TH1D *h_unsm_corr = new TH1D(*h_t_tr);
				h_unsm_corr->Divide(h_t_re);

				h_t_1 = new TH1D(*h_t_re_ref);
				h_t_1->Multiply(h_unsm_corr);

				h_t_0 = new TH1D(*h_t_tr_ref);

				delete h_unsm_corr;
			}

			// normalise histograms
			double n_0 = GetNormalisation(h_t_0);
			h_t_0->Scale(n_0);

			double n_1 = GetNormalisation(h_t_1);
			h_t_1->Scale(n_1);

			// evaluate effect
			TH1D *h_eff = new TH1D(*h_t_1);
			h_eff->Divide(h_t_0);

			gDirectory = d_binning;
			h_eff->Write("h_eff");

			// clean up
			delete h_t_tr_ref;
			delete h_t_re_ref;
			delete h_t_re;
			delete h_t_1;
			delete h_t_0;
			delete h_eff;
		}
	}

	// estimate uncertainty due to smearing model uncertainty
	TDirectory *d_scenario = f_out->mkdir("unsmearing-model");

	for (const string &binning : binnings)
	{
		TDirectory *d_binning = d_scenario->mkdir(binning.c_str());

		// get histograms
		TH1D *h_t_tr_base = GetHistogram(inputDirectory, model_base, ref_scenario, binning, "h_t_tr");
		TH1D *h_t_re_base = GetHistogram(inputDirectory, model_base, ref_scenario, binning, "h_t_re");

		TH1D *h_t_tr_secondary = GetHistogram(inputDirectory, model_secondary, ref_scenario, binning, "h_t_tr");
		TH1D *h_t_re_secondary = GetHistogram(inputDirectory, model_secondary, ref_scenario, binning, "h_t_re");

		// validate input
		if (!h_t_tr_base || !h_t_re_base || !h_t_tr_secondary || !h_t_re_secondary)
			continue;

		// calculate unsmearing correction (secondary model)
		TH1D *h_unsm_corr = new TH1D(*h_t_tr_secondary);
		h_unsm_corr->Divide(h_t_re_secondary);

		// apply unsmearing correction to base reco histogram
		TH1D *h_t_bias = new TH1D(*h_t_re_base);
		h_t_bias->Multiply(h_unsm_corr);

		// normalise histograms
		double n_base = GetNormalisation(h_t_tr_base);
		h_t_tr_base->Scale(n_base);

		double n_bias = GetNormalisation(h_t_bias);
		h_t_bias->Scale(n_bias);

		// evaluate effect
		TH1D *h_eff = new TH1D(*h_t_bias);
		h_eff->Divide(h_t_tr_base);

		gDirectory = d_binning;
		h_eff->Write("h_eff");

		// clean up
		delete h_unsm_corr;
		delete h_t_bias;
		delete h_eff;
	}

	delete f_out;

	return 0;
}
