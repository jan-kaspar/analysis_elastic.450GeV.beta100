#include "TFile.h"
#include "TH1D.h"

#include <vector>

using namespace std;

//----------------------------------------------------------------------------------------------------

int main()
{
	vector<string> datasets = {
		"DS-fill7280/Totem1",
		"DS-fill7281/Totem1",
		"DS-fill7282/Totem1",
		"DS-fill7283/Totem1",
		"DS-fill7284/Totem1",
		"DS-fill7285/Totem1",
		"DS-fill7286/Totem1",
		"DS-fill7287/Totem1",
		"DS-fill7288/Totem1",
		"DS-fill7289/Totem1",
		"DS-fill7290/Totem1",
		"DS-fill7291/Totem1",
	};

	vector<string> diagonals = {
		"45b_56t",
		"45t_56b",
	};

	double entries_tot = 0.;
	
	printf("%20s", "dataset");
	for (const auto &diagonal : diagonals)
		printf("%10s", diagonal.c_str());
	printf("\n");

	for (const auto &dataset : datasets)
	{
		printf("%20s", dataset.c_str());

		for (const auto &diagonal : diagonals)
		{
			string f_in_name = "../" + dataset + "/distributions_" + diagonal + ".root";
			TFile *f_in = TFile::Open(f_in_name.c_str());

			string h_path = "elastic cuts/cut 1/h_cq1";
			TH1D *h_in = (TH1D *) f_in->Get(h_path.c_str());

			double entries = h_in->GetEntries();

			printf("%10.3E", entries);

			entries_tot += entries;
		}

		printf("\n");
	}

	printf("\n* total: %.3E\n", entries_tot);

	return 0;
}
