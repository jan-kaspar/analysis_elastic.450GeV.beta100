#include <string>
#include <vector>
#include <map>
#include <cmath>

double timestamp0 = 1539208800;

vector<string> distilledNtuples;

vector<AlignmentSource> alignmentSources;
Analysis anal;
Environment env;

string unsmearing_file;
string unsmearing_object;

string luminosity_data_file;

//----------------------------------------------------------------------------------------------------

void Init_global()
{
	// list of (sub-)directories with distilled ntuples
	distilledNtuples.push_back(".");

	// selection of bunches
	keepAllBunches = true;

	// environment settings
	env.InitNominal();

	// crude alignment
	AlignmentSource alSrc;
	alSrc.SetAlignmentA(atConstant);
	alSrc.SetAlignmentB(atConstant);
	alSrc.SetAlignmentC(atConstant);

	alSrc.cnst.a_L_2_F =  -8E-3; alSrc.cnst.b_L_2_F =    0E-3 - 25E-3; alSrc.cnst.c_L_2_F = +150E-3;
	alSrc.cnst.a_L_1_F = -13E-3; alSrc.cnst.b_L_1_F = +400E-3 + 25E-3; alSrc.cnst.c_L_1_F =    0E-3;

	alSrc.cnst.a_R_1_F =  +2E-3; alSrc.cnst.b_R_1_F = +100E-3 + 25E-3; alSrc.cnst.c_R_1_F = -200E-3;
	alSrc.cnst.a_R_2_F =  +2E-3; alSrc.cnst.b_R_2_F = +900E-3 - 25E-3; alSrc.cnst.c_R_2_F =    0E-3;

	alignmentSources.push_back(alSrc);

	// binning
	// TODO
	anal.t_min = 0.; anal.t_max = 0.05;
	anal.t_min_full = 0.; anal.t_max_full = 0.09;

	// approximate (time independent) resolutions
	anal.si_th_y_1arm = 6E-6;
	anal.si_th_y_1arm_unc = -999.;

	anal.si_th_y_LRdiff = anal.si_th_y_1arm * sqrt(2.);
	anal.si_th_y_LRdiff_unc = -999.;

	anal.si_th_y_2arm = -999.;
	anal.si_th_y_2arm_unc = -999.;

	anal.si_th_x_1arm_L = 26E-6;
	anal.si_th_x_1arm_R = anal.si_th_x_1arm_L;
	anal.si_th_x_1arm_unc = -999.;

	anal.si_th_x_LRdiff = anal.si_th_x_1arm_L * sqrt(2.);
	anal.si_th_x_LRdiff_unc = -999.;

	anal.si_th_x_2arm = -999.;
	anal.si_th_x_2arm_unc = -999.;

	// analysis settings
	anal.use_resolution_fits = true;

	anal.use_3outof4_efficiency_fits = false;
	anal.use_pileup_efficiency_fits = false;
	anal.inefficiency_3outof4 = 0.;				// diagonal dependent
	anal.inefficiency_shower_near = 0.03;
	anal.inefficiency_pile_up = 0.;				// diagonal dependent
	anal.inefficiency_trigger = 0.;

	anal.bckg_corr = 1.;

	anal.L_int = 0.;	// mb^-1, diagonal dependent

	anal.t_min_fit = 0.; // TODO

	anal.alignment_t0 = 0.;	// beginning of the first time-slice
	anal.alignment_ts = 60.*60.;		// time-slice in s

	anal.alignmentYRanges["L_2_F"] = Analysis::AlignmentYRange(-24.0, -6.9, 7.4, +25.5);
	anal.alignmentYRanges["L_1_F"] = Analysis::AlignmentYRange(-21.5, -6.3, 6.6, +22.3);
	anal.alignmentYRanges["R_1_F"] = Analysis::AlignmentYRange(-23.0, -6.6, 6.6, +21.5);
	anal.alignmentYRanges["R_2_F"] = Analysis::AlignmentYRange(-25.2, -7.0, 7.3, +24.0);

#if 0
	// TODO
	unsmearing_file = "";	// diagonal dependent
	//unsmearing_object = "cf,<binning>/exp3/corr_final";
	//unsmearing_object = "cf,<binning>/exp3+exp4/corr_final";
	unsmearing_object = "ff";

	// TODO
	luminosity_data_file = "../fill_3549_lumiCalc2.py_V04-02-04_lumibylsXing.csv";
#endif
}

//----------------------------------------------------------------------------------------------------

void Init_global_45b_56t()
{
	// analysis settings
	anal.cut1_a = 1.; anal.cut1_c = -4E-6; anal.cut1_si = 35E-6;
	anal.cut2_a = 1.; anal.cut2_c = -1.5E-6; anal.cut2_si = 8E-6;

	anal.cut5_a = 0.105; anal.cut5_c = +0.01; anal.cut5_si = 0.08;
	anal.cut6_a = 0.105; anal.cut6_c = +0.04; anal.cut6_si = 0.08;

	anal.cut7_a = 0.; anal.cut7_c = -0.20; anal.cut7_si = 0.55;
	anal.cut8_a = 0.; anal.cut8_c = -0.43; anal.cut8_si = 2.8;

	anal.cut9_a = -0.28; anal.cut9_c = +0.03; anal.cut9_si = 0.14;
	anal.cut10_a = -0.29; anal.cut10_c = -0.02; anal.cut10_si = 0.14;

	anal.fc_L_l = FiducialCut( 35E-6, -330E-6, -1.05,  +75E-6, +0.15);
	anal.fc_L_h = FiducialCut(135E-6, -250E-6, +0.56, +305E-6, -0.75);

	anal.fc_R_l = FiducialCut( 35E-6, -330E-6, -1.05,  +75E-6, +0.15);
	anal.fc_R_h = FiducialCut(135E-6, -250E-6, +0.56, +305E-6, -0.75);

	anal.fc_G_l = FiducialCut( 37E-6, -325E-6, -1.10,  +70E-6, +0.15);
	anal.fc_G_h = FiducialCut(130E-6, -245E-6, +0.56, +300E-6, -0.65);

	// TODO
	//unsmearing_file = "unfolding_fit_45b_56t_old.root";

	anal.inefficiency_3outof4 = 0.0; // TODO
	anal.inefficiency_pile_up = 0.0; // TODO

	anal.L_int = 1.;	// TODO	
}

//----------------------------------------------------------------------------------------------------

void Init_global_45t_56b()
{
	// analysis settings
	anal.cut1_a = 1.; anal.cut1_c = +0.8E-6; anal.cut1_si = 33E-6;
	anal.cut2_a = 1.; anal.cut2_c = +0.5E-6; anal.cut2_si = 8E-6;

	anal.cut5_a = 0.105; anal.cut5_c = +0.03; anal.cut5_si = 0.08;
	anal.cut6_a = 0.105; anal.cut6_c = -0.04; anal.cut6_si = 0.08;

	anal.cut7_a = 0.; anal.cut7_c = +0.15; anal.cut7_si = 0.55;
	anal.cut8_a = 0.; anal.cut8_c = -0.9; anal.cut8_si = 2.8;

	anal.cut9_a = -0.28; anal.cut9_c = -0.01; anal.cut9_si = 0.14;
	anal.cut10_a = -0.29; anal.cut10_c = +0.02; anal.cut10_si = 0.14;

	anal.fc_L_l = FiducialCut( 35E-6,  -75E-6, -0.20, +330E-6, +0.50);
	anal.fc_L_h = FiducialCut(142E-6, -250E-6, +0.50, +250E-6, -0.56);

	anal.fc_R_l = FiducialCut( 35E-6,  -75E-6, -0.20, +330E-6, +0.50);
	anal.fc_R_h = FiducialCut(142E-6, -250E-6, +0.50, +250E-6, -0.56);

	anal.fc_G_l = FiducialCut( 37E-6,  -70E-6, -0.20, +325E-6, +0.50);
	anal.fc_G_h = FiducialCut(140E-6, -245E-6, +0.50, +245E-6, -0.56);

	// TODO
	//unsmearing_file = "unfolding_fit_45b_56t_old.root";

	anal.inefficiency_3outof4 = 0.0; // TODO
	anal.inefficiency_pile_up = 0.0; // TODO

	anal.L_int = 1.;	// TODO	
}
