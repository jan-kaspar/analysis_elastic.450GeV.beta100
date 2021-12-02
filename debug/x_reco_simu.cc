#include <TDirectory.h>
#include "x_reco_base.hh"

#include "TFile.h"
#include "TDirectory.h"
#include "TH2D.h"
#include "TRandom3.h"
#include "TSpline.h"
#include "TGraph.h"

#include <cstdio>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------------------------------

double dist_th_x(double th_x)
{
	const double a_1 = 900.;
	const double si_1 = 30E-6;

	const double a_2 = 500.;
	const double si_2 = 300E-6;

	const double c_1 = a_1 * exp(-th_x*th_x / 2. / si_1 / si_1);
	const double c_2 = a_2 * exp(-th_x*th_x / 2. / si_2 / si_2);

	return c_1 + c_2;
}

//----------------------------------------------------------------------------------------------------

TSpline* BuildSpline(TGraph *g)
{
	TSpline3 *s = new TSpline3("", g->GetX(), g->GetY(), g->GetN());
	s->SetName(g->GetName());
	return s;
}

//----------------------------------------------------------------------------------------------------

int main()
{
	// config
	unsigned int n_events = 1E6;

	Environment env;
	env.Init();

	struct AlBePair
	{
		double al, be;
	};

	vector<AlBePair> al_be_pairs = {
		{ -0.005, -0.05},
		{ -0.005, +0.00},
		{ -0.005, +0.02},

		{ -0.000, -0.05},
		{ -0.000, +0.00},
		{ -0.000, +0.02},

		{ +0.005, -0.05},
		{ +0.005, +0.00},
		{ +0.005, +0.02},
	};

	// prepare output
	TFile *f_out = TFile::Open("x_reco_simu.root", "recreate");

	// prepare generation
	TSpline *s_icdf;
	{
		TGraph *g_cdf = new TGraph();

		const double w = 1E-6;

		double v = 0.;
		for (double th_x = -500E-6; th_x <= +500E-6 + w; th_x += w)
		{
			int idx = g_cdf->GetN();
			g_cdf->SetPoint(idx, th_x, v);

			v += dist_th_x(th_x) * w;
		}

		const double v_max = g_cdf->GetY()[g_cdf->GetN() - 1];

		TGraph *g_icdf = new TGraph();
		for (int idx = 0; idx < g_cdf->GetN(); ++idx)
		{
			double x, y;
			g_cdf->GetPoint(idx, x, y);
			g_icdf->SetPoint(idx, y/v_max, x);
		}

		s_icdf = BuildSpline(g_icdf);

		delete g_cdf;
		delete g_icdf;
	}

	// prepare data structures
	vector<Environment> envs;
	vector<TH2D*> h2s;
	for (const auto &p : al_be_pairs)
	{
		envs.emplace_back(GetBiasedEnvironment(env, p.al, p.be));
		h2s.push_back(new TH2D("", ";vtx_x;th_x", 100, -2., +2., 100, -400E-6, +400E-6));
	}

	// run simulation
	for (unsigned int ev_idx = 0; ev_idx < n_events; ++ev_idx)
	{
		// generate true kinematics
		Kinematics k_true;
		k_true.th = s_icdf->Eval(gRandom->Rndm());
		k_true.vtx = gRandom->Gaus(0., 0.5);

		// calculate hit
		Event ev = Propagate(k_true, env);

		// reconstruct and fill hist
		for (unsigned int idx = 0; idx < al_be_pairs.size(); ++idx)
		{
			Kinematics k_reco = Reconstruct(ev, envs[idx]);
			h2s[idx]->Fill(k_reco.vtx, k_reco.th);
		}
	}

	// save histograms
	for (unsigned int idx = 0; idx < al_be_pairs.size(); ++idx)
	{
		char buf[100];
		sprintf(buf, "al=%+.3f,be=%+.3f", al_be_pairs[idx].al, al_be_pairs[idx].be);
		gDirectory = f_out->mkdir(buf);

		h2s[idx]->Write("h2_th_x_vs_vtx_x");
	}

	// clean up
	delete f_out;

	return 0;
}