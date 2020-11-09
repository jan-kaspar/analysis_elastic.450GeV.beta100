#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"

#include "TFile.h"
#include "TH2D.h"

#include "Fit/Fitter.h"

#include <memory>
#include <vector>
#include <memory>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Point
{
	double x, y, v, e;
};

vector<Point> points;

//----------------------------------------------------------------------------------------------------

class S2_FCN
{
	public:
		S2_FCN() {}

		double operator() (const double *par) const;

		static double f(double x, double y, const double* par);

		TH2D* MakeDiffMap(const TH2D *orig, const double* par);
};

//----------------------------------------------------------------------------------------------------

double S2_FCN::f(double x, double y, const double* par)
{
	const double &A = par[0] * 1E9;
	const double &mu_x = par[1] * 1E-6;
	const double &si_x = par[2] * 1E-6;
	const double &mu_y = par[3] * 1E-6;
	const double &si_y = par[4] * 1E-6;
		
	double de_x = (x - mu_x) / si_x;
	double de_y = (y - mu_y) / si_y;
	double val = A * exp(- (de_x*de_x + de_y*de_y) / 2.);
	
	return val;
}

//----------------------------------------------------------------------------------------------------

double S2_FCN::operator() (const double* par) const
{
	//printf("--------------------------------------------------\n");

	double S2 = 0.;

	for (unsigned int i = 0; i < points.size(); i++)
	{
		const Point &p = points[i];

		double de_f = (p.v - f(p.x, p.y, par)) / p.e;

		S2 += de_f * de_f;
	}

	//printf("S2 = %E\n", S2);

	return S2;
}

//----------------------------------------------------------------------------------------------------

TH2D* S2_FCN::MakeDiffMap(const TH2D *orig, const double* par)
{
	printf(">> MakeDiffMap\n");

	double bs_x = orig->GetXaxis()->GetBinWidth(1);
	double bs_y = orig->GetYaxis()->GetBinWidth(1);

	double lim_x = 110E-6;	int N_x = ceil(lim_x / bs_x);	lim_x = bs_x * N_x;
	double lim_y = 110E-6;	int N_y = ceil(lim_y / bs_y);	lim_y = bs_y * N_y;

	printf("N_x = %u, lim_x = %E\n", N_x, lim_x);
	printf("N_y = %u, lim_y = %E\n", N_y, lim_y);

	TH2D *h = new TH2D("diff map", "", 2*N_x, -lim_x, +lim_x, 2*N_y, -lim_y, +lim_y);

	for (unsigned int i = 0; i < points.size(); i++)
	{
		const Point &p = points[i];

		int bi_x = h->GetXaxis()->FindBin(p.x);
		int bi_y = h->GetXaxis()->FindBin(p.y);

		double de_f = (p.v - f(p.x, p.y, par)) / p.e;

		h->SetBinContent(bi_x, bi_y, de_f*de_f);
	}

	return h;
}

//----------------------------------------------------------------------------------------------------

void MakeFit(TH2D *h_45b, TH2D *h_45t)
{
	printf(">> MakeFit\n");
	printf("%p, %p\n", h_45b, h_45t);

	// select points
	vector<TH2D *> hists;
	hists.push_back(h_45b);
	hists.push_back(h_45t);
	for (unsigned int hi = 0; hi < hists.size(); hi++)
	{
		TH2D *h = hists[hi];
		for (int xi = 1; xi <= h->GetNbinsX(); xi++)
		{
			for (int yi = 1; yi <= h->GetNbinsY(); yi++)
			{
				Point p;
				p.x = h->GetXaxis()->GetBinCenter(xi);
				p.y = h->GetYaxis()->GetBinCenter(yi);
				p.v = h->GetBinContent(xi, yi);
				p.e = h->GetBinError(xi, yi);

				// exclude empty bins
				if (p.v == 0. && p.e == 0.)
					continue;

				// remove partially filled bins at acceptance boundaries
				if (p.x < -150E-6 || p.x > 150E-6 || fabs(p.y) > 98E-6 || (p.y > -15E-6 && p.y < +15E-6))
					continue;

				// theta cut
				double th = sqrt(p.x*p.x + p.y*p.y);
				if (th < 15E-6 || th > 100E-6)
					continue;

				points.push_back(p);

				//printf("th_x = %.0f, th_y = %.0f, v = %.3E, e = %.3E\n", p.x*1E6, p.y*1E6, p.v, p.e);
			}
		}
	}

	printf("number of points: %lu\n", points.size());

	// initialize fitter
	unique_ptr<S2_FCN> s2_fcn(new S2_FCN);
	unique_ptr<ROOT::Fit::Fitter> fitter(new ROOT::Fit::Fitter);

	constexpr unsigned int n_params = 5;
	double pStart[] = {0, 0, 0, 0, 0};
	fitter->SetFCN(n_params, *s2_fcn, pStart, 0, true);

	// set initial parameters
	fitter->Config().ParSettings(0).Set("const", 4., 0.1);	// * 1E9
	fitter->Config().ParSettings(1).Set("mean x", 0., 1.);	// in urad
	fitter->Config().ParSettings(2).Set("sigma x", 40., 1.);
	fitter->Config().ParSettings(3).Set("mean y", 0., 1.);
	fitter->Config().ParSettings(4).Set("sigma y", 40., 1.);

	// run fit
	fitter->FitFCN();
	fitter->FitFCN();

	// get parameters
	const ROOT::Fit::FitResult &result = fitter->Result();
	const double *params = result.GetParams();

	// print results
	printf("\n");

	const double chiSq = (*s2_fcn)(params);
	const unsigned int ndf = points.size() - n_params;
	printf("chiSq = %E, ndf = %i, chiSq/ndf = %.3f\n", chiSq, ndf, chiSq/ndf);

	printf("x: mean = %.3f urad, sigma = %.3f urad\n", params[1], params[2]);
	printf("y: mean = %.3f urad, sigma = %.3f urad\n", params[3], params[4]);

	printf("\n");

	TH2D *m = s2_fcn->MakeDiffMap(h_45b, params);
	m->Write();
}

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>\n");
	printf("OPTIONS:\n");
	printf("    -cfg <file>       config file\n");
	printf("    -dgn <string>     diagonal\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string cfg_file = "config.py";
	string diagonal_input = "";

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-cfg", cfg_file)) continue;
		if (TestStringParameter(argc, argv, argi, "-dgn", diagonal_input)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// run initialisation
	if (Init(cfg_file, diagonal_input) != 0)
		return 2;

	// compatibility check
	if (cfg.diagonal != dCombined)
		return rcIncompatibleDiagonal;

	// print settings
	PrintConfiguration();

	// get input data
	TFile *f_in_45b = new TFile("distributions_45b_56t.root");
	TH2D *h_45b = (TH2D *) f_in_45b->Get("normalization/h2_th_y_vs_th_x_normalized");
	
	TFile *f_in_45t = new TFile("distributions_45t_56b.root");
	TH2D *h_45t = (TH2D *) f_in_45t->Get("normalization/h2_th_y_vs_th_x_normalized");
	
	// prepare output
	TFile *f_out = new TFile("alignment_final.root", "recreate");

	// run fit
	MakeFit(h_45b, h_45t);

	// clean up
	delete f_out;

	return 0;
}
