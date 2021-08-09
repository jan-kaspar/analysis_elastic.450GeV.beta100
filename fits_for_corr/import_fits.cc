#include <TDirectory.h>
#include "TFile.h"
#include "TGraph.h"

int main()
{
	TFile *f_out = TFile::Open("imported_fits.root", "recreate");

	{
		TFile *f_in = TFile::Open("/afs/cern.ch/work/j/jkaspar/work/analyses/elastic/450GeV/common/master/data/fits/default/fit_HighBeta.root");
		TGraph *g = (TGraph *) f_in->Get("iteration 2/g_fit_CH");
		gDirectory = f_out;
		g->Write("g_fit_CH_HighBeta");
	}

	{
		TFile *f_in = TFile::Open("/afs/cern.ch/work/j/jkaspar/work/analyses/elastic/450GeV/common/master/data/fits/default/fit_BothBetas.root");
		TGraph *g = (TGraph *) f_in->Get("iteration 2/g_fit_CH");
		gDirectory = f_out;
		g->Write("g_fit_CH_BothBetas");
	}

	delete f_out;

	return 0;
}