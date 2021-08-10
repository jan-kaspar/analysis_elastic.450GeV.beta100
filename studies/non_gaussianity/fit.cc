#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <cstdio>
#include <string>

using namespace std;

int main()
{
	// configuration
	const bool details = false;

	// get input
	TFile *f_in = TFile::Open("../../data/fill7291/Totem1/distributions_45t_56b.root");
	TH1D *h_x_in = (TH1D *) f_in->Get("selected - angles/th_x_diffRL");
	TH1D *h_y_in = (TH1D *) f_in->Get("selected - angles/th_y_diffRL");

	// prepare output
	const string fn_out = (details) ? "fit_details.root" : "fit.root";
	TFile *f_out = TFile::Open(fn_out.c_str(), "recreate");

	// non-gaussian fit function
	TF1 *ff = new TF1("ff", "gaus(0) + gaus(3)");
	ff->SetLineColor(8);

	// run x fits
	if (details)
	{
		printf("\n* dx fit, gauss\n");
		h_x_in->Fit("gaus");
	}

	printf("\n* dx fit, non-gauss\n");
	ff->SetParameters(2.4e8, -3.2e-7, 4.1e-5, 9.5e8, -5.0e-7, 2.7e-5);
	h_x_in->Fit(ff, "+", "", -150E-6, +150E-6);

	ff->Write("ff_x");

	if (details)
		h_x_in->Write("h_x_in");

	// run y fits
	if (details)
	{
		printf("\n* dy fit, gauss\n");
		h_y_in->Fit("gaus");

		printf("\n* dy fit, non-gauss\n");
		ff->SetParameters(4.7e9, -1.1e-6, 7.6e-6, 1e8, 0., 15e-6);
		h_y_in->Fit(ff, "+", "");

		h_y_in->Write("h_y_in");
	}

	// clean up
	delete f_out;

	return 0;
}
