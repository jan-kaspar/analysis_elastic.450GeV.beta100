#include "classes/common_init.hh"
#include "classes/Stat.hh"

#include <vector>

#include "TFile.h"
#include "TMath.h"
#include "TGraph2D.h"
#include "TProfile2D.h"
#include "TRandom3.h"
#include "TMatrixDSymEigen.h"

using namespace std;

//----------------------------------------------------------------------------------------------------

struct RPInfo
{
	double p0, p1, p2, p3; 	// central value

	double de_cen, de_sl_x, de_sl_y;  // perturbations

	RPInfo(double _p0, double _p1, double _p2=0., double _p3=1.) : p0(_p0), p1(_p1), p2(_p2), p3(_p3),
		de_cen(0.), de_sl_x(0.), de_sl_y(0.)
	{
	}

	double Evaluate(double th_x, double th_y) const
	{
		const double q = cos(p1) * th_x + sin(p1) * th_y - p2;

		const double de_eff = de_cen + de_sl_x * th_x + de_sl_y * th_y;

		return p0/2. * (1. + TMath::Erf(q / p3)) + de_eff;
	}
};

//----------------------------------------------------------------------------------------------------

struct Point
{
	double th_x, th_y;
};

//----------------------------------------------------------------------------------------------------

vector<RPInfo> GeneratePerturbation(const vector<RPInfo> &input)
{
	vector<RPInfo> result(input);

	for (auto &i : result)
	{
		const double sigma_cen = 0.02;
		const double sigma_sl_x = 0.02 * 2 / 900E-6;
		const double sigma_sl_y = 0.02 * 2 / 150E-6, offset_sl_y = 0.02;

		const double eta_cen = gRandom->Gaus();
		const double eta_sl_x = gRandom->Gaus();
		const double eta_sl_y = gRandom->Gaus();

		i.de_cen = sigma_cen * eta_cen - offset_sl_y * eta_sl_y;
		i.de_sl_x = sigma_sl_x * eta_sl_x;
		i.de_sl_y = sigma_sl_y * eta_sl_y;
	}

	return result;
}

//----------------------------------------------------------------------------------------------------

double Evaluate(const vector<RPInfo> &input, double th_x, double th_y)
{
	double s = 0.;
	for (const auto &i : input)
		s += i.Evaluate(th_x, th_y);

	return s;
}

//----------------------------------------------------------------------------------------------------

int main()
{
	// run initialisation
	if (Init("config.py", "45b_56t") != 0)
		return 1;

	// RP info
	vector<RPInfo> rpInfo_nom = {
		RPInfo(0.99, M_PI/2.),

		//RPInfo(0.98, M_PI/2.),
		RPInfo(0.98, 1.666, -20E-6, 51E-6),

		RPInfo(0.97, M_PI/2.),
		RPInfo(0.96, M_PI/2.)
	};

	// config
	const unsigned int n_events = 10000;

	const bool debug = false;

	// book histogram
	TProfile2D *p_eff_vs_th_x_th_y = new TProfile2D("p_eff_vs_th_x_th_y", ";theta_x;theta_y", 50, -450E-6, +450E-6, 50, 0E-6, 150E-6, "S");
	TH2D *h2_rms_eff_vs_th_x_th_y = new TH2D("h2_rms_eff_vs_th_x_th_y", ";theta_x;theta_y", 50, -450E-6, +450E-6, 50, 0E-6, 150E-6);

	// build list of sampling points
	const unsigned int n_samples_x = 15;
	const unsigned int n_samples_y = 15;
	const unsigned int n_samples_tot = n_samples_x * n_samples_y;

	vector<Point> samplingPoints;
	samplingPoints.reserve(n_samples_tot);
	for (unsigned int ix = 0; ix < n_samples_x; ++ix)
	{
		for (unsigned int iy = 0; iy < n_samples_y; ++iy)
		{
			const double th_x = -450E-6 + ix * 900E-6 / (n_samples_x - 1);
			const double th_y = iy * 150E-6 / (n_samples_y - 1);

			samplingPoints.push_back({th_x, th_y});

			//printf("sp %lu: %.3E, %.3E\n", samplingPoints.size() - 1, th_x, th_y);
		}
	}

	// book statistics data
	Stat st(n_samples_tot);

	for (unsigned int ev = 0; ev < n_events; ev++)
	{
		// generate efficiency error
		auto rpInfo_per = GeneratePerturbation(rpInfo_nom);

		// fill profile
		for (int bx = 1; bx <= p_eff_vs_th_x_th_y->GetXaxis()->GetNbins(); ++bx)
		{
			for (int by = 1; by <= p_eff_vs_th_x_th_y->GetYaxis()->GetNbins(); ++by)
			{
				const double th_x = p_eff_vs_th_x_th_y->GetXaxis()->GetBinCenter(bx);
				const double th_y = p_eff_vs_th_x_th_y->GetYaxis()->GetBinCenter(by);

				const double eff_nom = Evaluate(rpInfo_nom, th_x, th_y);
				const double eff_per = Evaluate(rpInfo_per, th_x, th_y);

				p_eff_vs_th_x_th_y->Fill(th_x, th_y, eff_per - eff_nom);
			}
		}

		// fill stat
		vector<double> samples(n_samples_tot);

		for (unsigned int pi = 0; pi < samplingPoints.size(); ++pi)
		{
			const auto &p = samplingPoints[pi];

			const double eff_nom = Evaluate(rpInfo_nom, p.th_x, p.th_y);
			const double eff_per = Evaluate(rpInfo_per, p.th_x, p.th_y);

			samples[pi] = eff_per - eff_nom;
		}

		st.Fill(samples);
	}

	// build modes
	TMatrixDSym V(n_samples_tot);
	for (unsigned int i = 0; i < n_samples_tot; ++i)
	{
		for (unsigned int j = 0; j < n_samples_tot; ++j)
			V(i, j) = st.GetCovariance(i, j);
	}

	TMatrixDSymEigen eig_decomp(V);
	TVectorD eig_values(eig_decomp.GetEigenValues());
	TMatrixDSym S(n_samples_tot);
	for (unsigned int i = 0; i < n_samples_tot; i++)
		S(i, i) = (eig_values(i) >= 0.) ? sqrt(eig_values(i)) : 0.;

	TMatrixD m_gen = eig_decomp.GetEigenVectors() * S;

	printf("\n");
	printf("* eigenvalues greater than 1E-10:\n");
	for (unsigned int m = 0; m < n_samples_tot; ++m)
	{
		if (eig_values(m) > 1E-10)
			printf("    %u: %.2E\n", m, eig_values(m));
	}

	vector<TGraph2D *> modeGraphs;

	printf("\n");
	for (unsigned int m = 0; m < n_samples_tot; ++m)
	{
		if (eig_values(m) < 1E-5)
			continue;

		TGraph2D *g = new TGraph2D();
		g->SetName(("g2_mode_" + to_string(m+1)).c_str());

		for (unsigned int j = 0; j < n_samples_tot; ++j)
		{
			const auto &p = samplingPoints[j];
			g->SetPoint(g->GetN(), p.th_x, p.th_y, m_gen(j, m));
		}

		modeGraphs.push_back(g);
	}

	printf("* %lu modes built\n", modeGraphs.size());

	/// save output
	TFile *f_out = TFile::Open("effect_efficiency_mc.root", "recreate");

	for (int bx = 1; bx <= p_eff_vs_th_x_th_y->GetXaxis()->GetNbins(); ++bx)
		for (int by = 1; by <= p_eff_vs_th_x_th_y->GetYaxis()->GetNbins(); ++by)
			h2_rms_eff_vs_th_x_th_y->SetBinContent(bx, by, p_eff_vs_th_x_th_y->GetBinError(bx, by));


	if (debug)
		h2_rms_eff_vs_th_x_th_y->Write();

	for (auto *g : modeGraphs)
		g->Write();

	TH2 *h2_rms_eff_vs_th_x_th_y_modes = new TH2D(*h2_rms_eff_vs_th_x_th_y);
	h2_rms_eff_vs_th_x_th_y_modes->SetName("h2_rms_eff_vs_th_x_th_y_modes");
	h2_rms_eff_vs_th_x_th_y_modes->Reset();

	TH2 *h2_rms_eff_vs_th_x_th_y_diff = new TH2D(*h2_rms_eff_vs_th_x_th_y);
	h2_rms_eff_vs_th_x_th_y_diff->SetName("h2_rms_eff_vs_th_x_th_y_diff");
	h2_rms_eff_vs_th_x_th_y_diff->Reset();

	for (int bx = 1; bx <= h2_rms_eff_vs_th_x_th_y->GetXaxis()->GetNbins(); ++bx)
	{
		for (int by = 1; by <= h2_rms_eff_vs_th_x_th_y->GetYaxis()->GetNbins(); ++by)
		{
			const double th_x = h2_rms_eff_vs_th_x_th_y->GetXaxis()->GetBinCenter(bx);
			const double th_y = h2_rms_eff_vs_th_x_th_y->GetYaxis()->GetBinCenter(by);

			const double rms = h2_rms_eff_vs_th_x_th_y->GetBinContent(bx, by);

			double s2 = 0.;
			for (auto *g : modeGraphs)
				s2 += pow(g->Interpolate(th_x, th_y), 2.);
			const double rms_modes = sqrt(s2);

			h2_rms_eff_vs_th_x_th_y_modes->SetBinContent(bx, by, rms_modes);
			h2_rms_eff_vs_th_x_th_y_diff->SetBinContent(bx, by, rms_modes - rms);
		}
	}

	if (debug)
	{
		h2_rms_eff_vs_th_x_th_y_modes->Write();
		h2_rms_eff_vs_th_x_th_y_diff->Write();
	}

	delete f_out;

	return 0;
}
