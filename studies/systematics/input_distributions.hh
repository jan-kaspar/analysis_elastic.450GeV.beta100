#ifndef _input_distributions_hh_
#define _input_distributions_hh_

#include "TSpline.h"
#include "TFile.h"
#include "TGraph.h"

#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

TGraph* CropTDistribution(TGraph *input, double cut_off = 0.5)
{
	TGraph *g = new TGraph();
	for (int i = 0; i < input->GetN(); i++)
	{
		double t, v;
		input->GetPoint(i, t, v);

		if (t > cut_off)
			break;

		int idx = g->GetN();
		g->SetPoint(idx, t, v);
	}

	return g;
}

//----------------------------------------------------------------------------------------------------

TSpline* BuildSpline(TGraph *g)
{
	TSpline3 *s = new TSpline3("", g->GetX(), g->GetY(), g->GetN());
	s->SetName(g->GetName());
	return s;
}

//----------------------------------------------------------------------------------------------------

TObject* GetObject(const string &file, const string &path)
{
	TFile *f = TFile::Open(file.c_str());
	if (!f)
	{
		printf("ERROR: can't load file `%s'.\n", file.c_str());
		return nullptr;
	}

	TObject *o = f->Get(path.c_str());
	if (!o)
	{
		printf("ERROR: can't load object `%s' from file `%s'.\n", path.c_str(), file.c_str());
		return nullptr;
	}

	return o;
}

//----------------------------------------------------------------------------------------------------

struct InputTDistribution
{
	string label;
	TGraph *g_dsdt;
	TSpline *s_dsdt;
};

vector<InputTDistribution> inputTDistributions;

//----------------------------------------------------------------------------------------------------

int LoadTDistributions()
{
	// define input t-distributions
	// TODO: update
	inputTDistributions.push_back({
		"fitN-2",
		(TGraph *) GetObject("/afs/cern.ch/work/j/jkaspar/analyses/elastic/6500GeV/combined/first_fits/2/do_fit.root", "variant 2/g_dsdt_CH"),
		nullptr
	});

	// preprocess t-distributions
	for (auto &itd : inputTDistributions)
	{
		itd.g_dsdt = CropTDistribution(itd.g_dsdt);
		itd.s_dsdt = BuildSpline(itd.g_dsdt);
	}

	return 0;
}

#endif