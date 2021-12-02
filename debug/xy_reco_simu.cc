#include "xy_reco_base.hh"

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

TSpline* GetSpline(double th_min, double th_max)
{
	TGraph *g_cdf = new TGraph();

	const double w = 1E-6;

	double v = 0.;
	for (double th_x = th_min; th_x <= th_max; th_x += w)
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
	
	TSpline *s_icdf = BuildSpline(g_icdf);

	delete g_cdf;
	delete g_icdf;

	return s_icdf;
}

//----------------------------------------------------------------------------------------------------

struct HistSet
{
	TH2D *h2_th_y_vs_th_x;
	TH2D *h2_th_x_RLdiff_vs_th_y;
	TH2D *h2_th_y_RLdiff_vs_th_x;

	HistSet() :
		h2_th_y_vs_th_x(new TH2D("", ";th_x;th_y", 100, -400E-6, +400E-6, 100, -10E-6, +150E-6)),
		h2_th_x_RLdiff_vs_th_y(new TH2D("", ";th_y;th_x_RLdiff", 100, 0E-6, 150E-6, 100, -130E-6, +130E-6)),
		h2_th_y_RLdiff_vs_th_x(new TH2D("", ";th_x;th_y_RLdiff", 100, -400E-6, +400E-6, 100, -25E-6, +25E-6))
	{
	}

	void Write() const
	{
		h2_th_y_vs_th_x->Write("h2_th_y_vs_th_x");
		h2_th_x_RLdiff_vs_th_y->Write("h2_th_x_RLdiff_vs_th_y");
		h2_th_y_RLdiff_vs_th_x->Write("h2_th_y_RLdiff_vs_th_x");
	}
};

//----------------------------------------------------------------------------------------------------

int main()
{
	// config
	const unsigned int n_events = 1E6;

	const double si_bd_x = 23E-6;
	const double si_bd_y = 6E-6;

	Environment env;
	env.Init();

	struct LambdaSet
	{
		double la_xy_sym, la_xy_asym, la_yx_sym, la_yx_asym;
	};

	vector<LambdaSet> lambdaSets;
	
	for (double la_xy_sym : {0., 2., 4.})
		for (double la_xy_asym : {0., 0.5, 1.})
			lambdaSets.push_back({la_xy_sym * 1E3, la_xy_asym * 1E3, 0., 0.});

	for (double la_yx_sym : {0., 2., 4.})
		for (double la_yx_asym : {0., 2., 4.})
			lambdaSets.push_back({0., 0., la_yx_sym * 1E3, la_yx_asym * 1E3});

	//lambdaSets.emplace_back(LambdaSet{0., 0., 0., 0.});
	//lambdaSets.emplace_back(LambdaSet{0., 0., 1E3, 0.});
	
	// prepare output
	TFile *f_out = TFile::Open("xy_reco_simu.root", "recreate");

	// prepare generation
	TSpline *s_icdf_x = GetSpline(-500E-6, +500E-6);
	TSpline *s_icdf_y = GetSpline(0E-6, 150E-6);

	// prepare data structures
	vector<Environment> envs;
	vector<HistSet> hists;
	for (const auto &p : lambdaSets)
	{
		envs.emplace_back(GetBiasedEnvironment(env, p.la_xy_sym, p.la_xy_asym, p.la_yx_sym, p.la_yx_asym));
		hists.emplace_back(HistSet());
	}

	for (unsigned int idx = 0; idx < lambdaSets.size(); ++idx)
	{
		const auto &env = envs[idx];
		printf("idx %u: %.1E, %.1E, %.1E, %.1E\n", idx, env.la_xy_N, env.la_xy_F, env.la_yx_N, env.la_yx_F);
	}

	// run simulation
	for (unsigned int ev_idx = 0; ev_idx < n_events; ++ev_idx)
	{
		// generate true kinematics
		Kinematics k_true;
		k_true.th_x = s_icdf_x->Eval(gRandom->Rndm());
		k_true.th_y = s_icdf_y->Eval(gRandom->Rndm());
		k_true.vtx_x = gRandom->Gaus(0., 0.5);

		const double bd_x_L = gRandom->Gaus(0., si_bd_x);
		const double bd_x_R = gRandom->Gaus(0., si_bd_x);
		const double bd_y_L = gRandom->Gaus(0., si_bd_y);
		const double bd_y_R = gRandom->Gaus(0., si_bd_y);

		//printf("%.1f, %.1f\n", k_true.th_x * 1E6, k_true.th_y * 1E6);

		// calculate hit and reconstruct and fill hist
		for (unsigned int idx = 0; idx < lambdaSets.size(); ++idx)
		{
			Event ev = Propagate(k_true, envs[idx]);
			Kinematics k_reco = Reconstruct(ev, envs[idx]);
			//printf("    %.1f, %.1f\n", k_reco.th_x * 1E6, k_reco.th_y * 1E6);

			const double th_x_L = k_reco.th_x + bd_x_L, th_x_R = k_true.th_x + bd_x_R;
			const double th_y_L = k_reco.th_y + bd_y_L, th_y_R = k_true.th_y + bd_y_R;

			const double th_x_G = (th_x_L + th_x_R) / 2.;
			const double th_y_G = (th_y_L + th_y_R) / 2.;

			auto &h = hists[idx];
			h.h2_th_y_vs_th_x->Fill(k_reco.th_x, k_reco.th_y);
			h.h2_th_y_RLdiff_vs_th_x->Fill(th_x_G, th_y_R - th_y_L);
			h.h2_th_x_RLdiff_vs_th_y->Fill(th_y_G, th_x_R - th_x_L);
		}
	}

	// save histograms
	for (unsigned int idx = 0; idx < lambdaSets.size(); ++idx)
	{
		const auto &ls = lambdaSets[idx];

		char buf[100];
		sprintf(buf, "%+.3f,%+.3f,%+.3f,%+.3f", ls.la_xy_sym, ls.la_xy_asym, ls.la_yx_sym, ls.la_yx_asym);
		gDirectory = f_out->mkdir(buf);

		hists[idx].Write();
	}

	// clean up
	delete f_out;

	return 0;
}
