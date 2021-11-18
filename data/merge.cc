#include <TDirectory.h>
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TH1D.h"

#include <cstdio>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct SHist
{
	TH1D *hist;
	double scale;
	SHist(TH1D *_h, double _s) : hist(_h), scale(_s) {}
};

//----------------------------------------------------------------------------------------------------

TH1D* Merge(const vector<SHist> &hists, bool sumBins)
{
	// prepare merged histogram
	TH1D *m = new TH1D(*hists[0].hist);

	// merge number of entries
	unsigned int entries = 0;
	for (unsigned int hi = 0; hi < hists.size(); hi++)
		entries += hists[hi].hist->GetEntries();

	m->SetEntries(entries);

	// merge bins
	for (int bi = 1; bi <= m->GetNbinsX(); bi++)
	{
		if (sumBins)
		{
			// sum bins
			double Sv = 0., Su2 = 0.;
			for (unsigned int hi = 0; hi < hists.size(); hi++)
			{
				const double v = hists[hi].hist->GetBinContent(bi);
				const double u = hists[hi].hist->GetBinError(bi) * hists[hi].scale;

				Sv += v;
				Su2 += u * u;
			}

			const double v = Sv;
			const double u = sqrt(Su2);

			m->SetBinContent(bi, v);
			m->SetBinError(bi, u);
		} else {
			// average bins
			double Svw = 0., Sw = 0.;
			for (unsigned int hi = 0; hi < hists.size(); hi++)
			{
				const double v = hists[hi].hist->GetBinContent(bi);
				const double u = hists[hi].hist->GetBinError(bi) * hists[hi].scale;
				const double w = (u > 0.) ? 1./u/u : 0.;

				Sw += w;
				Svw += v * w;
			}

			const double avg = (Sw > 0.) ? Svw / Sw : 0.;
			const double avg_unc = (Sw > 0.) ? 1. / sqrt(Sw) : 0.;

			m->SetBinContent(bi, avg);
			m->SetBinError(bi, avg_unc);
		}
	}

	return m;
}

//----------------------------------------------------------------------------------------------------

struct Entry
{
	string input;
	double stat_unc_scale;
	string tag;

	Entry(const string &_i, double _sus, const string &_tag) : input(_i), stat_unc_scale(_sus), tag(_tag) {}
};

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: merge <option> <option> ...\n");
	printf("OPTIONS:\n");
	printf("    -output <file>     set output file\n");
	printf("    -entry <string>    add entry in format 'directory,scale,label,merge'\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	vector<string> input_entries;
	string output_file_name = "merged.root";

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-output", output_file_name)) continue;

		if (strcmp(argv[argi], "-entry") == 0)
		{
			input_entries.push_back(argv[++argi]);
			continue;
		}

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// build list of entries and collections
	vector<Entry> entries;
	map<string, vector<string>> collections;

	if (! input_entries.empty())
	{
		for (const auto &ie : input_entries)
		{
			istringstream iss(ie);
			string dir; getline(iss, dir, ',');
			string scale; getline(iss, scale, ',');
			string tag; getline(iss, tag, ',');

			entries.emplace_back(dir, atof(scale.c_str()), tag);

			collections["merged"].push_back(tag);
		}

	} else {
		printf("* using default list of entries\n");

		entries.push_back(Entry("fill7280/Totem1", 1., "fill7280"));

		entries.push_back(Entry("fill7281/Totem1", 1., "fill7281"));
		entries.push_back(Entry("fill7281-with-hor/Totem1", 1., "fill7281-with-hor"));

		entries.push_back(Entry("fill7282/Totem1", 1., "fill7282"));
		entries.push_back(Entry("fill7283/Totem1", 1., "fill7283"));
		entries.push_back(Entry("fill7284/Totem1", 1., "fill7284"));
		entries.push_back(Entry("fill7285/Totem1", 1., "fill7285"));

		entries.push_back(Entry("fill7289/Totem1", 1., "fill7289"));
		entries.push_back(Entry("fill7289-with-hor/Totem1", 1., "fill7289-with-hor"));

		entries.push_back(Entry("fill7291/Totem1", 1., "fill7291"));
		entries.push_back(Entry("fill7291-with-hor/Totem1", 1., "fill7291-with-hor"));

		for (const auto &e : entries)
		{
			collections[e.tag] = {e.tag};

			collections["merged-also-with-hor"].push_back(e.tag);

			bool withHor = e.tag.find("-with-hor") != string::npos;

			if (!withHor)
				collections["merged"].push_back(e.tag);

			if (withHor)
			{
				collections["merged-only-with-hor"].push_back(e.tag);
			}
		}
	}

	vector<string> diagonals;
	diagonals.push_back("45b_56t");
	diagonals.push_back("45t_56b");

	vector<string> binnings;
	binnings.push_back("sb1");
	binnings.push_back("sb2");
	binnings.push_back("sb3");

	// print info
	printf("* %lu entries:\n", entries.size());
	for (const auto& e : entries)
		printf("  %s, %.3f, %s\n", e.input.c_str(), e.stat_unc_scale, e.tag.c_str());

	printf("* %lu collections:\n", collections.size());
	for (const auto &p : collections)
	{
		printf("  %s: ", p.first.c_str());
		for (const auto &e : p.second)
			printf("%s, ", e.c_str());
		printf("\n");
	}

	// prepare output
	TFile *f_out = new TFile(output_file_name.c_str(), "recreate");

	// loop over binnings
	for (unsigned int bi = 0; bi < binnings.size(); bi++)
	{
		printf("\t%s\n", binnings[bi].c_str());

		TDirectory *d_binning = f_out->mkdir(binnings[bi].c_str());

		// input from a single entry and diagonal
		struct InputHists {
			SHist h_L, h_no_L;
			InputHists(const SHist &_L, const SHist &_no_L) : h_L(_L), h_no_L(_no_L) {}
		};

		// load entries
		vector<vector<InputHists>> hists; // e_hist[entry index][diagonal index]

		for (unsigned int ei = 0; ei < entries.size(); ei++)
		{
			vector<InputHists> temp;

			for (unsigned int dgni = 0; dgni < diagonals.size(); dgni++)
			{
				string fn = entries[ei].input + "/distributions_"+diagonals[dgni]+".root";
				TFile *f_in = TFile::Open(fn.c_str());
				if (!f_in)
				{
					printf("ERROR: File `%s' cannot be opened.\n", fn.c_str());
					return 1;
				}

				string on = "normalization+unfolding/"+binnings[bi]+"/h_t_normalized_unsmeared";
				TH1D *h_norm_L = (TH1D *) f_in->Get(on.c_str());
				if (!h_norm_L)
				{
					printf("ERROR: Object `%s' cannot be loaded from file `%s'.\n", on.c_str(), fn.c_str());
					return 2;
				}

				on = "normalization+unfolding/"+binnings[bi]+"/h_t_normalized_unsmeared_no_L";
				TH1D *h_norm_no_L = (TH1D *) f_in->Get(on.c_str());
				if (!h_norm_no_L)
				{
					printf("ERROR: Object `%s' cannot be loaded from file `%s'.\n", on.c_str(), fn.c_str());
					return 2;
				}

				h_norm_L->SetName("h_dsdt");
				h_norm_L->SetDirectory(nullptr);

				h_norm_no_L->SetName("h_dNdt");
				h_norm_no_L->SetDirectory(nullptr);

				temp.emplace_back(SHist(h_norm_L, entries[ei].stat_unc_scale), SHist(h_norm_no_L, entries[ei].stat_unc_scale));

				delete f_in;
			}

			hists.emplace_back(temp);
		}

		// process all collections
		for (const auto &p : collections)
		{
			TDirectory *d_collection = d_binning->mkdir(p.first.c_str());

			vector<unsigned int> entry_indices;
			for (const auto &tag : p.second)
			{
				signed int idx = -1;
				for (unsigned int e_idx = 0; e_idx < entries.size(); ++e_idx)
				{
					if (tag == entries[e_idx].tag)
						idx = e_idx;
				}

				if (idx < 0)
				{
					printf("ERROR: entry with tag '%s' not found. Skipping.", tag.c_str());
				} else {
					entry_indices.push_back(idx);
				}
			}

			vector<SHist> combined_list_L, combined_list_no_L;

			for (unsigned int dgni = 0; dgni < diagonals.size(); ++dgni)
			{
				gDirectory = d_collection->mkdir(diagonals[dgni].c_str());

				vector<SHist> dgn_list_L, dgn_list_no_L;

				for (const auto &e_idx : entry_indices)
				{
					dgn_list_L.push_back(hists[e_idx][dgni].h_L);
					dgn_list_no_L.push_back(hists[e_idx][dgni].h_no_L);

					combined_list_L.push_back(hists[e_idx][dgni].h_L);
					combined_list_no_L.push_back(hists[e_idx][dgni].h_no_L);
				}

				Merge(dgn_list_L, false)->Write();
				Merge(dgn_list_no_L, true)->Write();
			}

			{
				gDirectory = d_collection->mkdir("combined");

				Merge(combined_list_L, false)->Write();
				Merge(combined_list_no_L, true)->Write();
			}
		}
	}

	delete f_out;

	return 0;
}
