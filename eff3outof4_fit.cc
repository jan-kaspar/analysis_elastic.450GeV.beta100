#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

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

	// prepare output
	TFile *f_out = new TFile("eff3outof4_fit.root", "recreate");

	// combinations
	vector<string> diagonals;
	diagonals.push_back("45b_56t");
	diagonals.push_back("45t_56b");

	vector<string> units;
	units.push_back("L_2_F");
	units.push_back("L_1_F");
	units.push_back("R_1_F");
	units.push_back("R_2_F");

	// fit function
	TF1 *pol0 = new TF1("pol0", "[0]", -120E-6, +120E-6);	pol0->SetLineColor(2);
	TF1 *pol1 = new TF1("pol1", "[0] + [1]*x", -120E-6, +120E-6);	pol1->SetLineColor(8);

	for (unsigned int dgni = 0; dgni < diagonals.size(); dgni++)
	{
		printf("\n\n------------------------------ %s ------------------------------\n", diagonals[dgni].c_str());
	
		// FIXME: this is left after migration - check
		// diagonal settings
		//Init(diagonals[dgni]);
		
		//double th_y_min = max(anal.th_y_lcut_L, anal.th_y_lcut_R) + 5E-6;
		//double th_y_max = min(anal.th_y_hcut_L, anal.th_y_hcut_R) - 3E-6;
		const double th_y_min = 40E-6;
		const double th_y_max = 110E-6;
		
		printf("th_y_min = %E\n", th_y_min);
		printf("th_y_max = %E\n", th_y_max);

		printf("\n\n");

		// get input
		string fn_in = "eff3outof4_" + diagonals[dgni] + ".root";
		TFile *f_in = new TFile(fn_in.c_str());
		if (f_in->IsZombie())
		{
			printf("ERROR: can't load file '%s'\n", fn_in.c_str());
			continue;
		}

		TDirectory *dgnDir = f_out->mkdir(diagonals[dgni].c_str());

		for (unsigned int ui = 0; ui < units.size(); ui++)
		{
			printf("\n\n>> %s\n", units[ui].c_str());

			TDirectory *unitDir = dgnDir->mkdir(units[ui].c_str());
			gDirectory = unitDir;

			TH1D *h_eff = (TH1D *) f_in->Get(("excluded RPs "+units[ui]+"/n_si 3.0/th_y dependence with th_x cut/h_refined_ratio.th_y").c_str());
			if (h_eff == nullptr)
			{
				printf("ERROR: can't load h_eff for unit '%s'.\n", units[ui].c_str());
				continue;
			}
			
			h_eff->Write();

			h_eff->Fit(pol0, "", "", th_y_min, th_y_max);
			pol0->SetRange(th_y_min, th_y_max);
			pol0->Write();

			h_eff->Fit(pol1, "", "", th_y_min, th_y_max);
			pol1->SetRange(th_y_min, th_y_max);
			pol1->Write();
		}
	}

	delete f_out;
	return 0;
}
