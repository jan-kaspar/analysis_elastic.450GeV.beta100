#include "classes/Environment.hh"
#include "classes/Analysis.hh"
#include "classes/Kinematics.hh"
#include "classes/common_algorithms.hh"
#include "classes/AcceptanceCalculator.hh"
#include "classes/command_line_tools.hh"
#include "classes/common_init.hh"

#include "scenarios.hh"
#include "input_distributions.hh"

#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"

#include "TMatrixD.h"
#include "TVectorD.h"
#include "TMatrixDSymEigen.h"

#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

TMatrixD BuildGeneratorMatrix(const TMatrixDSym &m_cov)
{
	unsigned int dim = m_cov.GetNrows();

	TMatrixDSymEigen eig_decomp(m_cov);
	TVectorD eig_values(eig_decomp.GetEigenValues());
	TMatrixDSym S(dim);
	for (unsigned int i = 0; i < dim; i++)
		S(i, i) = (eig_values(i) >= 0.) ? sqrt(eig_values(i)) : 0.;

	TMatrixD m_gen = eig_decomp.GetEigenVectors() * S;
	return m_gen;
}

//----------------------------------------------------------------------------------------------------

TVectorD GenerateRandomVector(const TMatrixD m_gen)
{
	unsigned int dim = m_gen.GetNrows();
	TVectorD g(dim);
	for (unsigned int i = 0; i < dim; i++)
		g(i) = gRandom->Gaus();

	return m_gen * g;
}

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: mc_simu [option] [option] ...\n");
	printf("OPTIONS:\n");
	printf("    -diagonal <str>\n");
	printf("    -scenario <str>     systematic scenario\n");
	printf("    -model <str>        dsigma/dt model\n");
	printf("    -events <int>\n");
	printf("    -seed <int>\n");
	printf("    -output <file>\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string cfg_file = "config.py";
	string diagonal_input = "";
	string scenario = "none";
	string model = "fit_2";

	unsigned int n_events = (unsigned int) 1E5;
	unsigned int seed = 1;

	string outFileName = "ouput.root";

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

		if (TestStringParameter(argc, argv, argi, "-scenario", scenario)) continue;
		if (TestStringParameter(argc, argv, argi, "-model", model)) continue;

		if (TestUIntParameter(argc, argv, argi, "-events", n_events)) continue;
		if (TestUIntParameter(argc, argv, argi, "-seed", seed)) continue;

		if (TestStringParameter(argc, argv, argi, "-output", outFileName)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// print input
	printf(">> input parameters:\n");
	printf("    diagonal = %s\n", diagonal_input.c_str());
	printf("    scenario = %s\n", scenario.c_str());
	printf("    model = %s\n", model.c_str());
	printf("    n_events = %u (%.1E)\n", n_events, double(n_events));
	printf("    seed = %u\n", seed);
	printf("    outFileName = %s\n", outFileName.c_str());

	// run initialisation
	if (Init(cfg_file, diagonal_input) != 0)
		return 2;

	// compatibility check
	if (cfg.diagonal == dCombined || cfg.diagonal == ad45b_56b || cfg.diagonal == ad45t_56t)
		return rcIncompatibleDiagonal;

	// set scenario
	Environment env_sim = env;
	Environment env_rec = env;
	Analysis anal_sim = anal;
	Analysis anal_rec = anal;

	Biases biases;

	if (SetScenario(scenario, biases, env_sim, anal_sim, env_rec, anal_rec) != 0)
	{
		printf("ERROR: unknown scenario '%s'.\n", scenario.c_str());
		return 2;
	}

	// print configuration
	printf(">> biases:\n");
	biases.Print();

	printf("\n\n>> env_sim:\n");
	env_sim.Print();

	printf("\n\n>> anal_sim:\n");
	anal_sim.Print();

	printf("\n\n>> anal_rec:\n");
	anal_rec.Print();

	// load non-gaussian distributions
	LoadNonGaussianDistributions(anal_sim.si_th_x_LRdiff, anal_sim.si_th_y_LRdiff);

	// load uncertainty of the background-subtraction correction
	LoadBackgroundUncertainty();

	// random seed
	gRandom->SetSeed(seed);

	// initialise acceptance calculation
	AcceptanceCalculator accCalc;
	accCalc.Init(cfg.th_y_sign, anal_rec);

	// build generating matrices for d and m
	TMatrixDSym m_cov_dx_mx(2);
	m_cov_dx_mx(0, 0) = anal_sim.si_th_x_LRdiff * anal_sim.si_th_x_LRdiff;
	m_cov_dx_mx(0, 1) = m_cov_dx_mx(1, 0) = anal_sim.si_th_x_LRdiff * anal_sim.si_th_x_2arm * biases.d_m_corr_coef_x;
	m_cov_dx_mx(1, 1) = anal_sim.si_th_x_2arm * anal_sim.si_th_x_2arm;
	const TMatrixD &m_gen_dx_mx = BuildGeneratorMatrix(m_cov_dx_mx);

	TMatrixDSym m_cov_dy_my(2);
	m_cov_dy_my(0, 0) = anal_sim.si_th_y_LRdiff * anal_sim.si_th_y_LRdiff;
	m_cov_dy_my(0, 1) = m_cov_dy_my(1, 0) = anal_sim.si_th_y_LRdiff * anal_sim.si_th_y_2arm * biases.d_m_corr_coef_y;
	m_cov_dy_my(1, 1) = anal_sim.si_th_y_2arm * anal_sim.si_th_y_2arm;
	const TMatrixD &m_gen_dy_my = BuildGeneratorMatrix(m_cov_dy_my);

	// output file	
	TFile *f_out = new TFile(outFileName.c_str(), "recreate");

	// load input dsigma/dt distribution
	if (LoadTDistributions() != 0)
		return 1;

	TSpline *s_dsdt = nullptr;
	TGraph *g_dsdt = nullptr;
   	for (const auto &itd : inputTDistributions)
	{
		if (itd.label == model)
		{
			s_dsdt = itd.s_dsdt;
			g_dsdt = itd.g_dsdt;
		}
	}

	if (s_dsdt == nullptr)
	{
		printf("ERROR: dsigma/dt model '%s' not available.\n", model.c_str());
		return 5;
	}

	gDirectory = f_out;
	g_dsdt->Write("g_dsdt");

	// list of binnings
	vector<string> binnings;
	binnings.push_back("sb1");
	binnings.push_back("sb2");
	binnings.push_back("sb3");

	// book histograms
	vector<TH1D*> bh_t_tr, bh_t_re;
	for (unsigned int bi = 0; bi < binnings.size(); ++bi)
	{
		unsigned int N_bins;
		double *bin_edges;
		BuildBinning(anal_sim, binnings[bi], bin_edges, N_bins);

		bh_t_tr.push_back(new TH1D("", ";|t|;events per bin", N_bins, bin_edges)); bh_t_tr[bi]->Sumw2();
		bh_t_re.push_back(new TH1D("", ";|t|;events per bin", N_bins, bin_edges)); bh_t_re[bi]->Sumw2();
	}

	TH1D *h_m_x = new TH1D("h_m_x", ";d_x", 200, -120E-6, +120E-6);
	TH1D *h_m_y = new TH1D("h_m_y", ";d_y", 200, -120E-6, +120E-6);

	TH1D *h_d_x = new TH1D("h_d_x", ";d_x", 200, -120E-6, +120E-6);
	TH1D *h_d_y = new TH1D("h_d_y", ";d_y", 200, -20E-6, +20E-6);

	// simulation settings
	const double be = 6.;
	const double ga = 1. - exp(-be * anal_sim.t_max_full);

	// event loop
	for (unsigned int ev = 0; ev < n_events; ev++)
	{
		// ----- true event -----

		Kinematics k_tr;

		const double u = gRandom->Rndm();
		k_tr.t = - log(1. - ga * u) / be;
		double w = s_dsdt->Eval(k_tr.t) / exp(-be * k_tr.t);

		k_tr.phi = cfg.th_y_sign * gRandom->Rndm() * M_PI; // just one hemisphere

		k_tr.th = sqrt(k_tr.t) / env_sim.p;
		k_tr.th_x = k_tr.th_x_L = k_tr.th_x_R = k_tr.th * cos(k_tr.phi);
		k_tr.th_y = k_tr.th_y_L = k_tr.th_y_R = k_tr.th * sin(k_tr.phi);

		for (unsigned int bi = 0; bi < binnings.size(); ++bi)
			bh_t_tr[bi]->Fill(k_tr.t, w);

		// ----- smearing -----

		const TVectorD &vec_dx_mx = GenerateRandomVector(m_gen_dx_mx);
		const double d_x = vec_dx_mx(0), m_x = vec_dx_mx(1);

		const TVectorD &vec_dy_my = GenerateRandomVector(m_gen_dy_my);
		const double d_y = vec_dy_my(0), m_y = vec_dy_my(1);

		double d_x_reweight = 1.;
		if (biases.use_non_gaussian_d_x)
		{
			const double w_des = NonGauassianDistribution_d_x(d_x);
			const double &si = anal_sim.si_th_x_LRdiff;
			const double w_gen = 1./sqrt(2.*M_PI) / si * exp(-d_x*d_x / 2. / si / si);

			d_x_reweight = w_des / w_gen;
			w *= d_x_reweight;
		}

		h_m_x->Fill(m_x);
		h_m_y->Fill(m_y);

		h_d_x->Fill(d_x, d_x_reweight);
		h_d_y->Fill(d_y);

		Kinematics k_sm;

		k_sm.th_x_R = k_tr.th_x + m_x + d_x/2.;
		k_sm.th_x_L = k_tr.th_x + m_x - d_x/2.;

		k_sm.th_y_R = k_tr.th_y + m_y + d_y/2.;
		k_sm.th_y_L = k_tr.th_y + m_y - d_y/2.;

		k_sm.th_x = (k_sm.th_x_L + k_sm.th_x_R) / 2.;
		k_sm.th_y = (k_sm.th_y_L + k_sm.th_y_R) / 2.;
		k_sm.th = sqrt(k_sm.th_x*k_sm.th_x + k_sm.th_y*k_sm.th_y);

		// ----- reconstruction bias -----

		Kinematics k_re;

		k_re.th_x_L = biases.L.sc_th_x * k_sm.th_x_L + biases.L.sh_th_x + biases.L.tilt_th_x_eff_prop_to_th_y * k_sm.th_y_L;
		k_re.th_x_R = biases.R.sc_th_x * k_sm.th_x_R + biases.R.sh_th_x + biases.R.tilt_th_x_eff_prop_to_th_y * k_sm.th_y_R;

		k_re.th_y_L = biases.L.sc_th_y * k_sm.th_y_L + biases.L.sh_th_y + biases.L.tilt_th_y_eff_prop_to_th_x * k_sm.th_x_L;
		k_re.th_y_R = biases.R.sc_th_y * k_sm.th_y_R + biases.R.sh_th_y + biases.R.tilt_th_y_eff_prop_to_th_x * k_sm.th_x_R;

		k_re.th_x = (k_re.th_x_L + k_re.th_x_R) / 2.;
		k_re.th_y = (k_re.th_y_L + k_re.th_y_R) / 2.;
		k_re.th = sqrt(k_re.th_x*k_re.th_x + k_re.th_y*k_re.th_y);
		k_re.t = env_rec.p*env_rec.p * k_re.th*k_re.th;

		// ----- fiducial cuts and acceptance correction -----

		double phi_corr = 0., div_corr = 0.;
		bool skip = accCalc.Calculate(k_re, phi_corr, div_corr);

		// ----- inefficiency and its correction -----

		const double eff = 1.;
		const double eff_corr = (biases.eff_perturbation) ? 1. / (1. - biases.eff_perturbation->Interpolate(k_sm.th_x, fabs(k_sm.th_y))) : 1.;

		const double norm_adjustment = eff * eff_corr * (1. + biases.norm);

		// ----- background subtraction uncertainty -----

		const double bckg_adjustment = (1. + biases.bckg * f_bckg_unc->Eval(k_re.t));

		// fill plots
		if (!skip)
		{
			for (unsigned int bi = 0; bi < binnings.size(); ++bi)
				bh_t_re[bi]->Fill(k_re.t, w * norm_adjustment * bckg_adjustment * phi_corr * div_corr / 2.);
		}
	}

	// save
	gDirectory = f_out;

	h_m_x->Write();
	h_m_y->Write();

	h_d_x->Write();
	h_d_y->Write();

	for (unsigned int bi = 0; bi < binnings.size(); ++bi)
	{
		gDirectory = f_out->mkdir(binnings[bi].c_str());

		bh_t_tr[bi]->Scale(1., "width");
		bh_t_tr[bi]->Write("h_t_tr");

		bh_t_re[bi]->Scale(1., "width");
		bh_t_re[bi]->Write("h_t_re");
	}

	delete f_out;

	return 0;
}
