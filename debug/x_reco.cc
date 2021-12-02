#include "x_reco_base.hh"

#include "TGraph.h"
#include "TFile.h"
#include "TDirectory.h"

#include <cstdio>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------------------------------

tuple<double, double, double, double> GetCoefficients(const Environment env, double al, double be)
{
    Environment env_p = GetBiasedEnvironment(env, al, be);

    Kinematics k_th; k_th.th = 100E-6; k_th.vtx = 0.;
    Kinematics k_vtx; k_vtx.th = 0E-6; k_vtx.vtx = 1.;

    const Event ev_th = Propagate(k_th, env);
    const Event ev_vtx = Propagate(k_vtx, env);

    Kinematics k_reco_th = Reconstruct(ev_th, env_p);
    Kinematics k_reco_vtx = Reconstruct(ev_vtx, env_p);

    const double A = k_reco_th.th / k_th.th;
    const double B = k_reco_vtx.th / k_vtx.vtx;
    const double C = k_reco_th.vtx / k_th.th;
    const double D = k_reco_vtx.vtx / k_vtx.vtx;

    return {A, B, C, D};
}

//----------------------------------------------------------------------------------------------------

int main()
{
    // configuration
    Environment env;
    env.Init();

    vector<double> al_values = { -0.010, -0.005, 0.000, +0.005, +0.010 };

    // prepare output
    TFile *f_out = TFile::Open("x_reco.root", "recreate");

    // evaluation
    for (const auto &al : al_values)
    {
        char buf[100];
        sprintf(buf, "al=%+.3f", al);
        gDirectory = f_out->mkdir(buf);

        TGraph *g_A = new TGraph(); g_A->SetName("g_A");
        TGraph *g_B = new TGraph(); g_B->SetName("g_B");
        TGraph *g_C = new TGraph(); g_C->SetName("g_C");
        TGraph *g_D = new TGraph(); g_D->SetName("g_D");

        for (double be = -0.100; be <= +0.050; be += 0.001)
        {
            auto [A, B, C, D] = GetCoefficients(env, al, be);

            int idx = g_A->GetN();
            g_A->SetPoint(idx, be, A);
            g_B->SetPoint(idx, be, B);
            g_C->SetPoint(idx, be, C);
            g_D->SetPoint(idx, be, D);
        }

        g_A->Write();
        g_B->Write();
        g_C->Write();
        g_D->Write();
    }

    // cleaning
    delete f_out;    

    return 0;
}