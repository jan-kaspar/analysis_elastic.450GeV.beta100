#include "Environment.hh"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TMatrixDSymEigen.h"
#include "TRandom3.h"

//----------------------------------------------------------------------------------------------------

Environment::Environment() : optics_version("v1"), opt_cov(16), opt_per_gen(16, 16)
{
}

//----------------------------------------------------------------------------------------------------

void Environment::Init()
{
	// beam momentum (GeV)
	p = p_L = p_R = 450.;

	// momentum uncertainty
	si_de_p = 1E-3 * p;

	// beam divergence (rad, for simulation)
	si_th_x_L = si_th_x_R = 6.7E-6;	// beta*_x = 70 m
	si_th_y_L = si_th_y_R = 5.6E-6; // beta*_y = 100 m

	// vertex smearing (mm, for simulation)
	si_vtx_x = 330E-3;
	si_vtx_y = 395E-3;

	// pitch-induced error (mm)
	si_de_P_L = si_de_P_R = 12E-3;

	// alignment uncertainties
	// TODO: check if used, move to python?
	/*
	si_de_x = 0E-3;
	si_de_y_R = 0E-3;
	si_de_y_D = 0E-3;
	si_tilt = 0E-3;
	*/

	// other uncertainties
	// TODO: check if used, move to python?
	//si_th_y_RL_assym_unc = 0.;

	InitOptics();
}

//----------------------------------------------------------------------------------------------------

void Environment::InitOptics()
{
	bool optics_set = false;

	// default/empty optics imperfections
	array<double, n_optical_functions * n_optical_functions> opt_cov_data;
	for (int idx = 0; idx < n_optical_functions * n_optical_functions; ++idx)
		opt_cov_data[idx] = 0;

	// version nominal, sent by Frici on 26 Feb 2020
	// zero uncertainties
	if (optics_version == "nominal")
	{
		v_x_R_1_F = -2.29251110442821; L_x_R_1_F = 35.1828162653735E3; v_y_R_1_F = 0.126220649033512; L_y_R_1_F = 171.911207102938E3; D_x_R_1_F = -0.0864671103458512E3;
		v_x_R_2_F = -1.97644302902099; L_x_R_2_F = 27.2787476702851E3; v_y_R_2_F = 0.100459146707445; L_y_R_2_F = 192.282747401847E3; D_x_R_2_F = -0.0683872276311071E3;

		v_x_L_1_F = -2.24947329593445; L_x_L_1_F = 35.8475945504415E3; v_y_L_1_F = 0.124161170232800; L_y_L_1_F = 173.630053228259E3; D_x_L_1_F = +0.0855111365318488E3;
		v_x_L_2_F = -1.93196310652978; L_x_L_2_F = 27.6759142870506E3; v_y_L_2_F = 0.098769215019425; L_y_L_2_F = 194.499649253117E3; D_x_L_2_F = +0.0672035864182922E3;

		optics_set = true;
	}

	// version v1, sent by Frici on 3 Mar 2021
	// optics imperfections: sent by Frici on 11 June 2021 (labelled as v2 by they belong to the v1 optics)
	if (optics_version == "v1")
	{
		v_x_R_1_F = -2.25830632888932; L_x_R_1_F = 36.5836944494489E3; v_y_R_1_F = -0.01834785764521860; L_y_R_1_F = 167.364428145004E3; D_x_R_1_F = 0E3;
		v_x_R_2_F = -1.94602281958432; L_x_R_2_F = 28.4236464030796E3; v_y_R_2_F = -0.06236909420405130; L_y_R_2_F = 187.213362490210E3; D_x_R_2_F = 0E3;

		v_x_L_1_F = -2.22676133379662; L_x_L_1_F = 36.5451226794256E3; v_y_L_1_F = +0.04076728366855310; L_y_L_1_F = 170.970215192752E3; D_x_L_1_F = 0E3;
		v_x_L_2_F = -1.90985828033614; L_x_L_2_F = 28.2017100011691E3; v_y_L_2_F = +0.00475124530888865; L_y_L_2_F = 191.571488403204E3; D_x_L_2_F = 0E3;

		opt_cov_data = {
			1.41514E-005, 3.81082E-004, -3.51195E-005, -9.34909E-004, 1.29255E-005, 2.93351E-004, -3.95781E-005, -1.02419E-003, 9.40704E-006, 3.99900E-004, -2.34299E-005, -7.11696E-004, 9.12249E-006, 3.14736E-004, -2.63953E-005, -7.75787E-004,
			3.81082E-004, 1.68299E-002, -1.02511E-003, -3.09561E-002, 3.79304E-004, 1.29599E-002, -1.15680E-003, -3.37104E-002, 3.95252E-004, 1.70897E-002, -9.62460E-004, -2.92210E-002, 3.86963E-004, 1.34060E-002, -1.08437E-003, -3.17719E-002,
			-3.51195E-005, -1.02511E-003, 1.85859E-004, 5.20024E-003, -3.36603E-005, -7.53736E-004, 2.09734E-004, 5.79943E-003, -2.58362E-005, -1.06183E-003, 8.47670E-005, 2.56035E-003, -2.51983E-005, -8.28167E-004, 9.55174E-005, 2.81798E-003,
			-9.34909E-004, -3.09561E-002, 5.20024E-003, 1.54581E-001, -9.07848E-004, -2.30387E-002, 5.86984E-003, 1.72711E-001, -7.80723E-004, -3.19943E-002, 2.61080E-003, 7.87306E-002, -7.63535E-004, -2.48997E-002, 2.94203E-003, 8.66761E-002,
			1.29255E-005, 3.79304E-004, -3.36603E-005, -9.07848E-004, 1.20539E-005, 2.89961E-004, -3.79448E-005, -9.93359E-004, 9.30526E-006, 3.99174E-004, -2.31743E-005, -7.07997E-004, 9.02363E-006, 3.14438E-004, -2.61083E-005, -7.72072E-004,
			2.93351E-004, 1.29599E-002, -7.53736E-004, -2.30387E-002, 2.89961E-004, 1.00247E-002, -8.50510E-004, -2.50747E-002, 3.03710E-004, 1.30981E-002, -7.35716E-004, -2.22683E-002, 2.97653E-004, 1.02667E-002, -8.28894E-004, -2.41970E-002,
			-3.95781E-005, -1.15680E-003, 2.09734E-004, 5.86984E-003, -3.79448E-005, -8.50510E-004, 2.36676E-004, 6.54631E-003, -2.91532E-005, -1.19814E-003, 9.56779E-005, 2.88988E-003, -2.84341E-005, -9.34464E-004, 1.07812E-004, 3.18068E-003,
			-1.02419E-003, -3.37104E-002, 5.79943E-003, 1.72711E-001, -9.93359E-004, -2.50747E-002, 6.54631E-003, 1.93087E-001, -8.51499E-004, -3.47923E-002, 2.88322E-003, 8.68475E-002, -8.33190E-004, -2.70567E-002, 3.24903E-003, 9.56390E-002,
			9.40704E-006, 3.95252E-004, -2.58362E-005, -7.80723E-004, 9.30526E-006, 3.03710E-004, -2.91532E-005, -8.51499E-004, 1.50484E-005, 3.98838E-004, -3.44521E-005, -9.01286E-004, 1.36158E-005, 3.12967E-004, -3.87597E-005, -9.85078E-004,
			3.99900E-004, 1.70897E-002, -1.06183E-003, -3.19943E-002, 3.99174E-004, 1.30981E-002, -1.19814E-003, -3.47923E-002, 3.98838E-004, 1.92746E-002, -9.33443E-004, -3.03629E-002, 3.75827E-004, 1.55335E-002, -1.05191E-003, -3.33511E-002,
			-2.34299E-005, -9.62460E-004, 8.47670E-005, 2.61080E-003, -2.31743E-005, -7.35716E-004, 9.56779E-005, 2.88322E-003, -3.44521E-005, -9.33443E-004, 1.95938E-004, 5.48946E-003, -3.34991E-005, -6.78097E-004, 2.20790E-004, 6.11642E-003,
			-7.11696E-004, -2.92210E-002, 2.56035E-003, 7.87306E-002, -7.07997E-004, -2.22683E-002, 2.88988E-003, 8.68475E-002, -9.01286E-004, -3.03629E-002, 5.48946E-003, 1.65231E-001, -8.74912E-004, -2.29122E-002, 6.18771E-003, 1.84824E-001,
			9.12249E-006, 3.86963E-004, -2.51983E-005, -7.63535E-004, 9.02363E-006, 2.97653E-004, -2.84341E-005, -8.33190E-004, 1.36158E-005, 3.75827E-004, -3.34991E-005, -8.74912E-004, 1.27048E-005, 2.88986E-004, -3.76993E-005, -9.52707E-004,
			3.14736E-004, 1.34060E-002, -8.28167E-004, -2.48997E-002, 3.14438E-004, 1.02667E-002, -9.34464E-004, -2.70567E-002, 3.12967E-004, 1.55335E-002, -6.78097E-004, -2.29122E-002, 2.88986E-004, 1.26545E-002, -7.64135E-004, -2.52332E-002,
			-2.63953E-005, -1.08437E-003, 9.55174E-005, 2.94203E-003, -2.61083E-005, -8.28894E-004, 1.07812E-004, 3.24903E-003, -3.87597E-005, -1.05191E-003, 2.20790E-004, 6.18771E-003, -3.76993E-005, -7.64135E-004, 2.48794E-004, 6.89458E-003,
			-7.75787E-004, -3.17719E-002, 2.81798E-003, 8.66761E-002, -7.72072E-004, -2.41970E-002, 3.18068E-003, 9.56390E-002, -9.85078E-004, -3.33511E-002, 6.11642E-003, 1.84824E-001, -9.52707E-004, -2.52332E-002, 6.89458E-003, 2.06915E-001
		};

		optics_set = true;
	}

	// check
	if (!optics_set)
		throw "Optics version not understood";

	// decompose optics uncertainties
	opt_cov.SetMatrixArray(opt_cov_data.data());

	TMatrixDSymEigen eig_decomp(opt_cov);
	TVectorD eig_values(eig_decomp.GetEigenValues());
	TMatrixDSym S(n_optical_functions);
	for (unsigned int i = 0; i < n_optical_functions; i++)
		S(i, i) = (eig_values(i) >= 0.) ? sqrt(eig_values(i)) : 0.;
	opt_per_gen = eig_decomp.GetEigenVectors() * S;
}

//----------------------------------------------------------------------------------------------------

void Environment::Load(const edm::ParameterSet &ps)
{
	optics_version = ps.getParameter<string>("optics_version");

	Init();
}

//----------------------------------------------------------------------------------------------------

void Environment::Print() const
{
	printf("p=%E, p_L=%E, p_R=%E\n", p, p_L, p_R);
	printf("\n");
	printf("si_th_x_L=%E, si_th_y_L=%E\n", si_th_x_L, si_th_y_L);
	printf("si_th_x_R=%E, si_th_y_R=%E\n", si_th_x_R, si_th_y_R);
	printf("si_vtx_x=%E, si_vtx_y=%E\n", si_vtx_x, si_vtx_y);
	printf("si_de_P_L=%E, si_de_P_R=%E\n", si_de_P_L, si_de_P_R);

	printf("\n");
	printf("optics:\n");
	printf("version = %s\n", optics_version.c_str());
	printf("L_x_L_1_F = %E, v_x_L_1_F = %E, L_y_L_1_F = %E, v_y_L_1_F = %E\n", L_x_L_1_F, v_x_L_1_F, L_y_L_1_F, v_y_L_1_F);
	printf("L_x_L_2_F = %E, v_x_L_2_F = %E, L_y_L_2_F = %E, v_y_L_2_F = %E\n", L_x_L_2_F, v_x_L_2_F, L_y_L_2_F, v_y_L_2_F);
	printf("L_x_R_1_F = %E, v_x_R_1_F = %E, L_y_R_1_F = %E, v_y_R_1_F = %E\n", L_x_R_1_F, v_x_R_1_F, L_y_R_1_F, v_y_R_1_F);
	printf("L_x_R_2_F = %E, v_x_R_2_F = %E, L_y_R_2_F = %E, v_y_R_2_F = %E\n", L_x_R_2_F, v_x_R_2_F, L_y_R_2_F, v_y_R_2_F);

	// TODO
	/*
	printf("\n");
	printf("si_de_x=%E, si_de_y_R=%E, si_de_y_D=%E, si_tilt=%E\n", si_de_x, si_de_y_R, si_de_y_D, si_tilt);
	printf("\n");
	printf("de_x_L_N=%E, de_y_L_N=%E, tilt_L_N=%E\n", de_x_L_N, de_y_L_N, tilt_L_N);
	printf("de_x_L_F=%E, de_y_L_F=%E, tilt_L_F=%E\n", de_x_L_F, de_y_L_F, tilt_L_F);
	printf("de_x_R_N=%E, de_y_R_N=%E, tilt_R_N=%E\n", de_x_R_N, de_y_R_N, tilt_R_N);
	printf("de_x_R_F=%E, de_y_R_F=%E, tilt_R_F=%E\n", de_x_R_F, de_y_R_F, tilt_R_F);
	printf("\n");
	printf("si_th_y_RL_assym_unc=%E\n", si_th_y_RL_assym_unc);
	*/

	printf("optics uncertainties: left arm\n");
	printf("\tv_x_N: %.4f\n", sqrt(opt_cov(0, 0)));
	printf("\tL_x_N: %.4f m\n", sqrt(opt_cov(1, 1)));
	printf("\tv_y_N: %.4f\n", sqrt(opt_cov(2, 2)));
	printf("\tL_y_N: %.4f m\n", sqrt(opt_cov(3, 3)));
	printf("\tv_x_F: %.4f\n", sqrt(opt_cov(4, 4)));
	printf("\tL_x_F: %.4f m\n", sqrt(opt_cov(5, 5)));
	printf("\tv_y_F: %.4f\n", sqrt(opt_cov(6, 6)));
	printf("\tL_y_F: %.4f m\n", sqrt(opt_cov(7, 7)));

	printf("optics uncertainties: right arm\n");
	printf("\tv_x_N: %.4f\n", sqrt(opt_cov(8, 8)));
	printf("\tL_x_N: %.4f m\n", sqrt(opt_cov(9, 9)));
	printf("\tv_y_N: %.4f\n", sqrt(opt_cov(10, 10)));
	printf("\tL_y_N: %.4f m\n", sqrt(opt_cov(11, 11)));
	printf("\tv_x_F: %.4f\n", sqrt(opt_cov(12, 12)));
	printf("\tL_x_F: %.4f m\n", sqrt(opt_cov(13, 13)));
	printf("\tv_y_F: %.4f\n", sqrt(opt_cov(14, 14)));
	printf("\tL_y_F: %.4f m\n", sqrt(opt_cov(15, 15)));
}

//----------------------------------------------------------------------------------------------------

void Environment::ApplyRandomOpticsPerturbations(TVectorD & de)
{
	TVectorD r(n_optical_functions);
	for (unsigned int i = 0; i < n_optical_functions; i++)
		r(i) = gRandom->Gaus();
	de = opt_per_gen * r;

	v_x_L_1_F += de(0) * 1E0;
	L_x_L_1_F += de(1) * 1E3;
	v_y_L_1_F += de(2) * 1E0;
	L_y_L_1_F += de(3) * 1E3;
	v_x_L_2_F += de(4) * 1E0;
	L_x_L_2_F += de(5) * 1E3;
	v_y_L_2_F += de(6) * 1E0;
	L_y_L_2_F += de(7) * 1E3;

	v_x_R_1_F += de(8) * 1E0;
	L_x_R_1_F += de(9) * 1E3;
	v_y_R_1_F += de(10) * 1E0;
	L_y_R_1_F += de(11) * 1E3;
	v_x_R_2_F += de(12) * 1E0;
	L_x_R_2_F += de(13) * 1E3;
	v_y_R_2_F += de(14) * 1E0;
	L_y_R_2_F += de(15) * 1E3;
}

//----------------------------------------------------------------------------------------------------

void Environment::ApplyOpticsPerturbationMode(int mode, double coef)
{
	printf(">> Environment::ApplyOpticsPerturbationMode\n");

	// prepare correlation matrix
	TMatrixDSym cor(opt_cov);
	TMatrixDSym Sigma(opt_cov);
	for (int i = 0; i < opt_cov.GetNrows(); i++)
		for (int j = 0; j < opt_cov.GetNcols(); j++)
		{
			cor(i, j) /= sqrt( opt_cov(i, i) * opt_cov(j, j) );
			Sigma(i, j) = (i == j) ? sqrt( opt_cov(i, i) ) : 0.;
		}

	// eigen decomposition
	TMatrixDSymEigen eig_decomp(cor);
	TVectorD eig_values(eig_decomp.GetEigenValues());

	// construct mode
	TVectorD vm(opt_cov.GetNrows());
	for (int i = 0; i < opt_cov.GetNrows(); i++)
	{
		double l = eig_values(i);
		double sl = (l > 0.) ? sqrt(l) : 0.;
		vm(i) = (i == mode) ? sl * coef : 0.;
	}

	vm = Sigma * eig_decomp.GetEigenVectors() * vm;

	printf("\tleft arm: mode %u, coefficient %+.3f\n", mode, coef);
	vm.Print();

	v_x_L_1_F += vm(0) * 1E0;
	L_x_L_1_F += vm(1) * 1E3;
	v_y_L_1_F += vm(2) * 1E0;
	L_y_L_1_F += vm(3) * 1E3;
	v_x_L_2_F += vm(4) * 1E0;
	L_x_L_2_F += vm(5) * 1E3;
	v_y_L_2_F += vm(6) * 1E0;
	L_y_L_2_F += vm(7) * 1E3;

	v_x_R_1_F += vm(8) * 1E0;
	L_x_R_1_F += vm(9) * 1E3;
	v_y_R_1_F += vm(10) * 1E0;
	L_y_R_1_F += vm(11) * 1E3;
	v_x_R_2_F += vm(12) * 1E0;
	L_x_R_2_F += vm(13) * 1E3;
	v_y_R_2_F += vm(14) * 1E0;
	L_y_R_2_F += vm(15) * 1E3;
}

//----------------------------------------------------------------------------------------------------

void Environment::ApplyEffectiveLengthPerturbationMode(int mode, double coef)
{
	printf(">> Environment::ApplyEffectiveLengthPerturbationMode\n");

	// prepare reduced covariance matrix
	TMatrixDSym cov_red(8);
	for (unsigned int i = 0; i < 8; i++)
		for (unsigned int j = 0; j < 8; j++)
			cov_red(i, j) = opt_cov(2*i+1, 2*j+1);

	// eigen decomposition
	TMatrixDSymEigen eig_decomp(cov_red);
	TVectorD eig_values(eig_decomp.GetEigenValues());

	// construct mode
	TVectorD vm(cov_red.GetNrows());
	for (int i = 0; i < cov_red.GetNrows(); i++)
	{
		double l = eig_values(i);
		double sl = (l > 0.) ? sqrt(l) : 0.;
		vm(i) = (i == mode) ? sl * coef : 0.;
	}

	vm = eig_decomp.GetEigenVectors() * vm;

	printf("\tmode %u, coefficient %+.3f\n", mode, coef);
	//vm.Print();

	L_x_L_1_F += vm(0) * 1E3;
	L_y_L_1_F += vm(1) * 1E3;
	L_x_L_2_F += vm(2) * 1E3;
	L_y_L_2_F += vm(3) * 1E3;

	L_x_R_1_F += vm(4) * 1E3;
	L_y_R_1_F += vm(5) * 1E3;
	L_x_R_2_F += vm(6) * 1E3;
	L_y_R_2_F += vm(7) * 1E3;
}
