#include "classes/common_algorithms.hh"
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>\n");
	printf("OPTIONS:\n");
	printf("    -input <string>           input specification\n");
	printf("    -binning <string>         binning\n");

	printf("    -print-details <bool>     print details\n");
	printf("    -print-code <bool>        print results in summary format\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	vector<string> input_specs;

	string binning = "sb1";

	vector<string> diagonals;
	diagonals.push_back("45b_56t");
	diagonals.push_back("45t_56b");

	bool print_details = true;
	bool print_code = false;

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		string input_spec;
		if (TestStringParameter(argc, argv, argi, "-input", input_spec))
		{
			input_specs.push_back(input_spec);
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-binning", binning)) continue;

		if (TestBoolParameter(argc, argv, argi, "-print-details", print_details)) continue;
		if (TestBoolParameter(argc, argv, argi, "-print-code", print_code)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// validate input
	if (input_specs.empty())
	{
		printf("ERROR: input not specified.\n");
		PrintUsage();
		return 2;
	}

	// data structures
	struct Entry
	{
		unsigned int idx_input;
		unsigned int idx_dgn;

		TH1D *h_t, *h_t_no_L;

		double L_int;
		double beta;
	};

	// get per-histogram betas
	vector<Entry> data;
	double s_1 = 0., s_beta = 0.;

	if (print_details)
		printf("* processing input\n");

	for (unsigned int ipti = 0; ipti < input_specs.size(); ++ipti)
	{
		for (unsigned int dgni = 0; dgni < diagonals.size(); dgni++)
		{
			if (print_details)
				printf("    %s, %s\n", input_specs[ipti].c_str(), diagonals[dgni].c_str());

			TFile *f_in = TFile::Open((input_specs[ipti] + "/distributions_" + diagonals[dgni]+".root").c_str());

			Entry e;

			e.idx_input = ipti;
			e.idx_dgn = dgni;

			e.h_t = (TH1D *) f_in->Get(("normalization+unfolding/" + binning + "/h_t_normalized_unsmeared").c_str());
			e.h_t->SetDirectory(nullptr);

			e.h_t_no_L = (TH1D *) f_in->Get(("normalization+unfolding/" + binning + "/h_t_normalized_unsmeared_no_L").c_str());
			e.h_t_no_L->SetDirectory(nullptr);

			const int bi = e.h_t->FindBin(0.008);
			e.L_int = e.h_t_no_L->GetBinContent(bi) / e.h_t->GetBinContent(bi);

			e.beta = 1. / GetRelativeNormalizationFactor(e.h_t, print_details);

			//printf("    L_int = %.1f, raw beta = %.5f\n", e.L_int, e.beta);

			s_1 += 1.;
			s_beta += e.beta;

			delete f_in;

			data.push_back(e);
		}
	}

	// normalise betas
	const double beta_mean = s_beta / s_1;
	if (print_details)
		printf("\n* after beta normalisation\n");
	for (auto &e : data)
	{
		e.beta /= beta_mean;
		if (print_details)
			printf("    %s, %s: beta = %.5f\n", input_specs[e.idx_input].c_str(), diagonals[e.idx_dgn].c_str(), e.beta);
	}

	// build merged histogram
	TH1D *h_merged = new TH1D(* data[0].h_t);
	h_merged->Reset();
	for (int bi = 0; bi < h_merged->GetNbinsX(); ++bi)
	{
		double s_vw = 0., s_w = 0.;
		for (unsigned int ei = 0; ei < data.size(); ei++)
		{
			const double v = data[ei].h_t->GetBinContent(bi) * data[ei].beta;
			const double u = data[ei].h_t->GetBinError(bi) * data[ei].beta;
			const double w = (u > 0.) ? 1./u/u : 0.;

			s_w += w;
			s_vw += v * w;
		}

		const double v = (s_w > 0.) ? s_vw / s_w : 0.;
		const double u = (s_w > 0.) ? 1. / sqrt(s_w) : 0.;

		h_merged->SetBinContent(bi, v);
		h_merged->SetBinError(bi, u);
	}

	// get gamma
	if (print_details)
		printf("\n* calculating gamma:\n");

	const double gamma = 1. / GetNormalizationFactor(h_merged, print_details);

	if (print_details)
		printf("    gamma = %.5f\n", gamma);

	if (print_details)
	{
		printf("\n* results\n");
		for (const auto &e : data)
			printf("    %s, %s: L_int = %.1f\n", input_specs[e.idx_input].c_str(), diagonals[e.idx_dgn].c_str(),
				e.L_int / e.beta / gamma);
	}

	if (print_code)
	{
		for (const auto &e : data)
		{
			printf("file=%s\n", input_specs[e.idx_input].c_str());
			printf("line=cfg_%s.anal.L_int = %.1f\n", diagonals[e.idx_dgn].c_str(), e.L_int / e.beta / gamma);
		}
	}

	return 0;
}
