#include "TFile.h"
#include "TH1D.h"

#include <cstdio>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------------------------------

double GetEventsInRange(const TH1D *h, double t_min, double t_max)
{
	double sum = 0.;
	for (int bi = 1; bi <= h->GetNbinsX(); ++bi)
	{
		const double t = h->GetBinCenter(bi);
		if (t_min <= t && t < t_max)
			sum += h->GetBinContent(bi);
	}

	return sum;
}

//----------------------------------------------------------------------------------------------------

void PrintStats(const vector<string> &datasets, const vector<string> &diagonals, const string &type, double t_min, double t_max)
{
	string obj_path = "";
	if (type == "tagged") obj_path = "acceptance correction/sb1/h_t_Nev_before";
	if (type == "accepted") obj_path = "acceptance correction/sb1/h_t_Nev_after_no_corr";

	if (obj_path.empty())
	{
		printf("ERROR: type '%s' not recognized.\n", type.c_str());
		return;
	}

	printf("\n\n* %s events in |t| range from %.3E to %.3E\n", type.c_str(), t_min, t_max);
	
	printf("%30s", "dataset");
	for (const auto &diagonal : diagonals)
		printf("%13s", diagonal.c_str());
	printf("\n");

	double entries_tot = 0.;

	for (const auto &dataset : datasets)
	{
		printf("%30s", dataset.c_str());

		for (const auto &diagonal : diagonals)
		{
			const string f_in_name = "../data/" + dataset + "/distributions_" + diagonal + ".root";
			TFile *f_in = TFile::Open(f_in_name.c_str());

			TH1D *h_in = (TH1D *) f_in->Get(obj_path.c_str());

			// remove
			//const double entries = h_in->GetEntries();
			const double entries = GetEventsInRange(h_in, t_min, t_max);

			printf("%13.3E", entries);

			entries_tot += entries;

			delete f_in;
		}

		printf("\n");
	}

	printf("%30s\n", "----------");
	printf("%30s%13.3E\n", "total (datasets, diagonals)", entries_tot);
}

//----------------------------------------------------------------------------------------------------

int main()
{
	vector<string> datasets = {
		"fill7280/Totem1",
		"fill7281/Totem1",
		"fill7281-with-hor/Totem1",
		"fill7282/Totem1",
		"fill7283/Totem1",
		"fill7284/Totem1",
		"fill7285/Totem1",
		//"fill7286/Totem1",
		//"fill7287/Totem1",
		//"fill7288/Totem1",
		"fill7289/Totem1",
		"fill7289-with-hor/Totem1",
		//"fill7290/Totem1",
		"fill7291/Totem1",
		"fill7291-with-hor/Totem1",
	};

	vector<string> diagonals = {
		"45b_56t",
		"45t_56b",
	};

	PrintStats(datasets, diagonals, "tagged", 0., 1E4);

	PrintStats(datasets, diagonals, "accepted", 3E-4, 0.005);
	PrintStats(datasets, diagonals, "accepted", 0.005, 0.010);
	PrintStats(datasets, diagonals, "accepted", 0.010, 1E4);

	return 0;
}