#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"

#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

TObject* GetObject(const string &fn, const string &on)
{
    TFile *f = TFile::Open(fn.c_str());
    if (!f)
    {
        printf("ERROR: file '%s' cannot be opened.\n", fn.c_str());
        return nullptr;
    }

    TObject *obj = f->Get(on.c_str());
    if (!obj)
    {
        printf("ERROR: object '%s' cannot be loaded.\n", on.c_str());
        return nullptr;
    }

    return obj;
}

//----------------------------------------------------------------------------------------------------

int main()
{
    TFile *f_out = TFile::Open("reference.root", "recreate");

    TObject *o;

    for (string dgn : {"45b_56t", "45t_56b"})
    {
        TDirectory *d_dgn = f_out->mkdir(dgn.c_str());

        TDirectory *d_acc_corr = d_dgn->mkdir("acceptance correction");

        TDirectory *d_binning = d_acc_corr->mkdir("eb");

        o = GetObject("../data/fill7291/Totem1/distributions_" + dgn + ".root", "acceptance correction/eb/h_t_after");
        gDirectory = d_binning;
        o->Write("h_t_after");
    }


    delete f_out;

    return 0;
}