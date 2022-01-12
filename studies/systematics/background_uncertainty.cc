#include "TFile.h"
#include "TF1.h"

int main()
{
    TFile *f_in = TFile::Open("../../data/all-good/Totem1/default/background_fit_combined.root");
    TF1 *ff = (TF1 *) f_in->Get("sb1/after_acc_corr/mean/ff");

    TFile *f_out = TFile::Open("background_uncertainty.root", "RECREATE");

    ff->Write("ff_unc");

    delete f_in;
    delete f_out;

    return 0;
}