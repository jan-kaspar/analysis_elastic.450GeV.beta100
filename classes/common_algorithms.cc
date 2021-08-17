#include "common_algorithms.hh"

#include "common_event.hh"
#include "Environment.hh"
#include "Analysis.hh"
#include "Kinematics.hh"

#include <deque>

#include <TFile.h>
#include <TObject.h>
#include <TH1D.h>
#include <TGraph.h>

using namespace std;

//----------------------------------------------------------------------------------------------------

Kinematics DoReconstruction(const HitData &h, const Environment & env)
{
	Kinematics k;

	// ----- single-pot kinematics reconstruction -----

	k.th_x_L_1_F = - h.L_1_F.x / env.L_x_L_1_F;
  	k.th_x_L_2_F = - h.L_2_F.x / env.L_x_L_2_F;

	k.th_x_R_1_F = + h.R_1_F.x / env.L_x_R_1_F;
  	k.th_x_R_2_F = + h.R_2_F.x / env.L_x_R_2_F;

	k.th_y_L_1_F = - h.L_1_F.y / env.L_y_L_1_F;
	k.th_y_L_2_F = - h.L_2_F.y / env.L_y_L_2_F;

	k.th_y_R_1_F = + h.R_1_F.y / env.L_y_R_1_F;
	k.th_y_R_2_F = + h.R_2_F.y / env.L_y_R_2_F;

	// ----- single-arm kinematics reconstruction -----

	const double D_x_L = - env.v_x_L_1_F * env.L_x_L_2_F + env.v_x_L_2_F * env.L_x_L_1_F;
	k.th_x_L = (env.v_x_L_1_F * h.L_2_F.x - env.v_x_L_2_F * h.L_1_F.x) / D_x_L;
	k.vtx_x_L = (- h.L_1_F.x * env.L_x_L_2_F + h.L_2_F.x * env.L_x_L_1_F) / D_x_L;

	const double D_x_R = + env.v_x_R_1_F * env.L_x_R_2_F - env.v_x_R_2_F * env.L_x_R_1_F;
	k.th_x_R = (env.v_x_R_1_F * h.R_2_F.x - env.v_x_R_2_F * h.R_1_F.x) / D_x_R;
	k.vtx_x_R = (+ h.R_1_F.x * env.L_x_R_2_F - h.R_2_F.x * env.L_x_R_1_F) / D_x_R;

	k.th_y_L = (k.th_y_L_1_F + k.th_y_L_2_F) / 2.;
  	k.th_y_R = (k.th_y_R_1_F + k.th_y_R_2_F) / 2.;

	const double D_y_L = - env.v_y_L_1_F * env.L_y_L_2_F + env.v_y_L_2_F * env.L_y_L_1_F;
	//k.th_y_L = (env.v_y_L_1_F * h.L_2_F.y - env.v_y_L_2_F * h.L_1_F.y) / D_y_L;
	k.vtx_y_L = (- h.L_1_F.y * env.L_y_L_2_F + h.L_2_F.y * env.L_y_L_1_F) / D_y_L;

	const double D_y_R = + env.v_y_R_1_F * env.L_y_R_2_F - env.v_y_R_2_F * env.L_y_R_1_F;
	//k.th_y_R = (env.v_y_R_1_F * h.R_2_F.y - env.v_y_R_2_F * h.R_1_F.y) / D_y_R;
	k.vtx_y_R = (+ h.R_1_F.y * env.L_y_R_2_F - h.R_2_F.y * env.L_y_R_1_F) / D_y_R;

	// ----- double-arm kinematics reconstruction -----

	k.th_x = (k.th_x_L + k.th_x_R) / 2.;
	k.th_y = (k.th_y_L + k.th_y_R) / 2.;

	k.vtx_x = (k.vtx_x_L + k.vtx_x_R) / 2.;
	k.vtx_y = (k.vtx_y_L + k.vtx_y_R) / 2.;

	// ----- theta reconstruction -----
	double th_sq = k.th_x*k.th_x + k.th_y*k.th_y;
	k.th = sqrt(th_sq);
	k.phi = atan2(k.th_y, k.th_x);

	// t reconstruction
	k.t_x = env.p*env.p * k.th_x * k.th_x;
	k.t_y = env.p*env.p * k.th_y * k.th_y;
	k.t = k.t_x + k.t_y;

	return k;
}

//----------------------------------------------------------------------------------------------------

void BuildBinning(const Analysis &anal, const string &type, double* &binEdges, unsigned int &bins)
{
	bool verbose = false;

	if (verbose)
		printf(">> BuildBinning(%s)\n", type.c_str());

	std::vector<double> be;

	if (type.find("sb") == 0)
	{
		const double t_low = 0.002, t_high = 0.02;

		double w_low = 1., w_high = 2.;
		if (type == "sb1") { w_low = 1.0E-4; w_high = 0.5E-3; }
		if (type == "sb2") { w_low = 2.0E-4; w_high = 1.0E-3; }
		if (type == "sb3") { w_low = 3.0E-4; w_high = 2.0E-3; }

		const double a = (w_high - w_low) / (t_high - t_low);

		double t = anal.t_min;
		const double t_max = 0.1;
		while (true)
		{
			be.push_back(t);

			if (t > t_max)
				break;

			double w = w_low;
			if (t >= t_low) w = w_low + a * (t - t_low);
			if (t >= t_high) w = w_high;

			t += w;
		}
	}

	bins = be.size() - 1;
	binEdges = new double[be.size()];
	for (unsigned int i = 0; i < be.size(); i++)
	{
		binEdges[i] = be[i];
		if (verbose)
			printf("\tbi = %4u: %.4E\n", i, binEdges[i]);
	}
}

//----------------------------------------------------------------------------------------------------

HitData ProtonTransport(const Kinematics & k, const Environment & env)
{
	HitData h;

	h.L_2_F.x = -env.L_x_L_2_F*k.th_x_L + env.v_x_L_2_F*k.vtx_x;
	h.L_2_F.y = -env.L_y_L_2_F*k.th_y_L + env.v_y_L_2_F*k.vtx_y;

	h.L_1_F.x = -env.L_x_L_1_F*k.th_x_L + env.v_x_L_1_F*k.vtx_x;
	h.L_1_F.y = -env.L_y_L_1_F*k.th_y_L + env.v_y_L_1_F*k.vtx_y;

	h.R_1_F.x = +env.L_x_R_1_F*k.th_x_R + env.v_x_R_1_F*k.vtx_x;
	h.R_1_F.y = +env.L_y_R_1_F*k.th_y_R + env.v_y_R_1_F*k.vtx_y;

	h.R_2_F.x = +env.L_x_R_2_F*k.th_x_R + env.v_x_R_2_F*k.vtx_x;
	h.R_2_F.y = +env.L_y_R_2_F*k.th_y_R + env.v_y_R_2_F*k.vtx_y;

	return h;
}

//----------------------------------------------------------------------------------------------------

double *th_x_binning_edges_1d=nullptr, *th_y_binning_edges_1d=nullptr;
double *th_x_binning_edges_2d=nullptr, *th_y_binning_edges_2d=nullptr;
double *th_x_binning_edges_2d_coarse=nullptr, *th_y_binning_edges_2d_coarse=nullptr;

int th_x_binning_n_1d=0, th_y_binning_n_1d=0;
int th_x_binning_n_2d=0, th_y_binning_n_2d=0;
int th_x_binning_n_2d_coarse=0, th_y_binning_n_2d_coarse=0;

//----------------------------------------------------------------------------------------------------

void BuildThBinning()
{
	deque<double> edges;

	// ----- th_x, 1D -----
	edges.clear();
	for (double x = 0E-6; ; )
	{
		edges.push_back(x);
		if (x != 0E-6)
			edges.push_front(-x);

		if (x > 480E-6)
			break;

		x += 20E-6;
	}

	th_x_binning_edges_1d = new double[edges.size()];
	th_x_binning_n_1d = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
		th_x_binning_edges_1d[i] = edges[i];

	// ----- th_y, 1D -----
	edges.clear();
	for (double y = 0E-6; ; )
	{
		edges.push_back(y);
		if (y > 160E-6)
			break;

		y += (y > 30E-6) ? 10./120 * (y - 30E-6) + 5E-6 : 5E-6;
	}

	th_y_binning_edges_1d = new double[edges.size()];
	th_y_binning_n_1d = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
		th_y_binning_edges_1d[i] = edges[i];

	// ----- th_x, 2D -----
	edges.clear();
	for (double x = 0E-6; ; )
	{
		edges.push_back(x);
		if (x != 0E-6)
			edges.push_front(-x);

		if (x > 480E-6)
			break;

		x += 50E-6;
	}

	th_x_binning_edges_2d = new double[edges.size()];
	th_x_binning_n_2d = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		th_x_binning_edges_2d[i] = edges[i];
		printf("  %i --> edge x = %E\n", i, edges[i]);
	}

	// ----- th_y, 2D -----
	edges.clear();
	for (double y = 0E-6; ; )
	{
		edges.push_back(y);
		if (y > 160E-6)
			break;

		y += (y > 30E-6) ? 10./120 * (y - 30E-6) + 5E-6 : 5E-6;
	}

	printf("\n");

	th_y_binning_edges_2d = new double[edges.size()];
	th_y_binning_n_2d = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		th_y_binning_edges_2d[i] = edges[i];
		printf("  %i --> edge y = %E\n", i, edges[i]);
	}

	// ----- th_x, 2D, coarse -----
	edges = { -400E-6, -300E-6, -200E-6, -150E-6, -100E-6, 100E-6, 150E-6, 200E-6, 300E-6, 400E-6 };

	th_x_binning_edges_2d_coarse = new double[edges.size()];
	th_x_binning_n_2d_coarse = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
		th_x_binning_edges_2d_coarse[i] = edges[i];

	// ----- th_y, 2D, coarse -----
	edges = { 30E-6, 50E-6, 70E-6, 100E-6, 130E-6 };

	th_y_binning_edges_2d_coarse = new double[edges.size()];
	th_y_binning_n_2d_coarse = edges.size() - 1;
	for (unsigned int i = 0; i < edges.size(); i++)
		th_y_binning_edges_2d_coarse[i] = edges[i];

	printf(">> BuildThBinning\n");
	printf("\n1D, th_x: %i, %p\n", th_x_binning_n_1d, th_x_binning_edges_1d);
	printf("\n1D, th_y: %i, %p\n", th_y_binning_n_1d, th_y_binning_edges_1d);
	printf("\n2D, th_x: %i, %p\n", th_x_binning_n_2d, th_x_binning_edges_2d);
	printf("\n2D, th_y: %i, %p\n", th_y_binning_n_2d, th_y_binning_edges_2d);
	printf("\n2D coarse, th_x: %i, %p\n", th_x_binning_n_2d_coarse, th_x_binning_edges_2d_coarse);
	printf("\n2D coarse, th_y: %i, %p\n", th_y_binning_n_2d_coarse, th_y_binning_edges_2d_coarse);
}

//----------------------------------------------------------------------------------------------------

extern double GetNormalizationFactor(const TObject *obj, bool print_details)
{
	// range
	const double t_min_goal = 3.1E-4, t_max_goal = 4.5E-4;

	// reference cross-section ( a / t^2 )
	const double a_ref = 0.000260508;

	if (obj->InheritsFrom("TH1D"))
	{
		const TH1D *h = (TH1D *) obj;

		// determine limits
		const int bi_min = h->GetXaxis()->FindBin(t_min_goal);
		const int bi_max = h->GetXaxis()->FindBin(t_max_goal);

		const double t_min = h->GetXaxis()->GetBinLowEdge(bi_min);
		const double t_max = h->GetXaxis()->GetBinLowEdge(bi_max) + h->GetXaxis()->GetBinWidth(bi_max);

		if (print_details)
			printf("    summing from bin %i (left edge %.1E) to bin %i (right edge %.1E)\n", bi_min, t_min, bi_max, t_max);

		// sum bin content
		double n_hist = 0.;
		for (int bi = bi_min; bi <= bi_max; ++bi)
		{
			n_hist += h->GetBinContent(bi) * h->GetBinWidth(bi);

			//printf("%i, %.2E, %.2E\n", bi, h->GetBinContent(bi), h->GetBinWidth(bi));
		}

		const double si_ref = a_ref * (1./t_min - 1./t_max);

		return n_hist / si_ref;
	}

	if (obj->InheritsFrom("TGraph"))
	{
		const TGraph *g = (TGraph *) obj;

		double s_gra = 0., s_ref = 0.;
		for (int i = 0; i < g->GetN(); ++i)
		{
			const double x = g->GetX()[i];
			const double y = g->GetY()[i];

			if (x < t_min_goal || x > t_max_goal)
				continue;

			const double y_ref = a_ref / (x*x);

			s_gra += y;
			s_ref += y_ref;
		}

		return (s_ref > 0) ? s_gra / s_ref : 0.;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------

extern double GetRelativeNormalizationFactor(const TObject *obj, bool print_details)
{
	// range
	const double t_min_goal = 3.1E-4, t_max_goal = 0.02;

	if (obj->InheritsFrom("TH1D"))
	{
		const TH1D *h = (TH1D *) obj;

		// determine limits
		const int bi_min = h->GetXaxis()->FindBin(t_min_goal);
		const int bi_max = h->GetXaxis()->FindBin(t_max_goal);

		const double t_min = h->GetXaxis()->GetBinLowEdge(bi_min);
		const double t_max = h->GetXaxis()->GetBinLowEdge(bi_max) + h->GetXaxis()->GetBinWidth(bi_max);

		if (print_details)
			printf("    summing from bin %i (left edge %.1E) to bin %i (right edge %.1E)\n", bi_min, t_min, bi_max, t_max);

		// sum bin content
		double n_hist = 0.;
		for (int bi = bi_min; bi <= bi_max; ++bi)
			n_hist += h->GetBinContent(bi) * h->GetBinWidth(bi);

		return n_hist;
	}

	return 0;
}
