#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"

int main()
{
	TFile *f_in = new TFile("../../data/merged.root");
	TH1D *h_in = (TH1D *) f_in->Get("sb1/merged/combined/h_dNdt");
	//TH1D *h_in = (TH1D *) f_in->Get("ub/merged/45t_56b/h_dsdt");

	TF1 *ff = new TF1("ff", "[0]/x/x + [1] * exp(-[2]*x)", 1E-6, 0.02);

	TCanvas *c = new TCanvas();
	c->SetLogy(1);

	/*
	ff->SetParameter(0, 4E8);
	ff->SetParameter(1, 21.);
	ff->SetParameter(2, 10.);
	ff->SetParameter(3, -22);
	ff->FixParameter(4, 0.);
	ff->FixParameter(5, 0.);
	
	ff->SetParameter(6, 0.48);
	ff->SetParameter(7, 6.66);
	
	ff->SetParameter(8, 8E7);
	ff->SetParameter(9, 6.52);
	*/

	h_in->Fit(ff, "", "", 2.5E-4, 0.02);

	//printf("ff(0) = %f mb / GeV^2\n", ff->Eval(0.));

	TFile *f_out = new TFile("dN_dt_fit.root", "recreate");
	h_in->Write();
	ff->Write();

	delete f_out;

	return 0;
}
