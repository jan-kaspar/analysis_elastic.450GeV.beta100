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

//----------------------------------------------------------------------------------------------------

void Init_global()
{
	// list of (sub-)directories with distilled ntuples
	distilledNtuples.push_back(".");

	// input selection
	anal.excl_runs.push_back(324467);

	anal.excl_lsIntervals[324462] = { {94, 338} };
	anal.excl_lsIntervals[324532] = { {399, 520} };
	anal.excl_lsIntervals[324536] = { {360, 509} };

	anal.excl_timeIntervals.push_back({112100, 112400});
	anal.excl_timeIntervals.push_back({115000, 117000});

	// environment settings
	env.InitNominal();

	// crude alignment
	AlignmentSource alSrc;
	alSrc.SetAlignmentA(atConstant);
	alSrc.SetAlignmentB(atConstant);
	alSrc.SetAlignmentC(atConstant);

	alSrc.cnst.a_L_2_F = -7.0E-3; alSrc.cnst.b_L_2_F =    0E-3 - 25E-3; alSrc.cnst.c_L_2_F = +170E-3; // first number: read from alignment.pdf, second number: correction reco-check plots
	alSrc.cnst.a_L_1_F = -8.5E-3; alSrc.cnst.b_L_1_F = +400E-3 + 25E-3; alSrc.cnst.c_L_1_F =  +30E-3;

	alSrc.cnst.a_R_1_F = +5.0E-3; alSrc.cnst.b_R_1_F = +100E-3 + 25E-3; alSrc.cnst.c_R_1_F = -180E-3;
	alSrc.cnst.a_R_2_F = +3.5E-3; alSrc.cnst.b_R_2_F = +900E-3 - 25E-3; alSrc.cnst.c_R_2_F =  -20E-3;

	alignmentSources.push_back(alSrc);

	// binning
	anal.t_min = 0.; anal.t_max = 0.03;
	anal.t_min_full = 0.; anal.t_max_full = 0.045;

	// approximate (time independent) resolutions
	anal.si_th_y_1arm = 6E-6;
	anal.si_th_y_1arm_unc = -999.;

	anal.si_th_y_LRdiff = anal.si_th_y_1arm * sqrt(2.);
	anal.si_th_y_LRdiff_unc = -999.;

	anal.si_th_y_2arm = anal.si_th_y_1arm / sqrt(2.);
	anal.si_th_y_2arm_unc = -999.;

	anal.si_th_x_1arm_L = 23E-6;
	anal.si_th_x_1arm_R = anal.si_th_x_1arm_L;
	anal.si_th_x_1arm_unc = -999.;

	anal.si_th_x_LRdiff = anal.si_th_x_1arm_L * sqrt(2.);
	anal.si_th_x_LRdiff_unc = -999.;

	anal.si_th_x_2arm = anal.si_th_x_1arm_L / sqrt(2.);
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

	unsmearing_file = "";	// diagonal dependent
	unsmearing_object = "fit-1/<binning>";
}

//----------------------------------------------------------------------------------------------------

void Init_global_45b_56t()
{
	// analysis settings
	anal.cut1_a = 1.; anal.cut1_c = +4E-6; anal.cut1_si = 35E-6;
	anal.cut2_a = 1.; anal.cut2_c = -1.5E-6; anal.cut2_si = 8E-6;

	anal.cut5_a = 0.105; anal.cut5_c = -0.02; anal.cut5_si = 0.08;
	anal.cut6_a = 0.105; anal.cut6_c = +0.03; anal.cut6_si = 0.08;

	anal.cut7_a = 0.; anal.cut7_c = -0.02; anal.cut7_si = 0.55;
	anal.cut8_a = 0.; anal.cut8_c = +0.30; anal.cut8_si = 2.8;

	anal.cut9_a = -0.28; anal.cut9_c = +0.02; anal.cut9_si = 0.14;
	anal.cut10_a = -0.29; anal.cut10_c = +0.02; anal.cut10_si = 0.14;

	anal.fc_L = FiducialCut({{-350E-6, 31E-6}, {50E-6, 31E-6}, {250E-6, 40E-6}, {350E-6, 80E-6}, {270E-6, 126E-6}, {-280E-6, 126E-6}, {-390E-6, 60E-6}});
	anal.fc_R = FiducialCut({{-350E-6, 31E-6}, {50E-6, 31E-6}, {250E-6, 40E-6}, {350E-6, 80E-6}, {270E-6, 126E-6}, {-280E-6, 126E-6}, {-390E-6, 60E-6}});
	anal.fc_G = FiducialCut({{-338E-6, 32E-6}, {50E-6, 32E-6}, {250E-6, 42E-6}, {345E-6, 80E-6}, {270E-6, 124E-6}, {-280E-6, 124E-6}, {-385E-6, 60E-6}});

	unsmearing_file = "unfolding_cf_ni_45b_56t.root";

	anal.inefficiency_3outof4 = 0.0; // TODO
	anal.inefficiency_pile_up = 0.0; // TODO
}

//----------------------------------------------------------------------------------------------------

void Init_global_45t_56b()
{
	// analysis settings
	anal.cut1_a = 1.; anal.cut1_c = -7E-6; anal.cut1_si = 34E-6;
	anal.cut2_a = 1.; anal.cut2_c = +0.5E-6; anal.cut2_si = 8E-6;

	anal.cut5_a = 0.105; anal.cut5_c = -0.01; anal.cut5_si = 0.08;
	anal.cut6_a = 0.105; anal.cut6_c = -0.06; anal.cut6_si = 0.08;

	anal.cut7_a = 0.; anal.cut7_c = -0.04; anal.cut7_si = 0.55;
	anal.cut8_a = 0.; anal.cut8_c = -0.20; anal.cut8_si = 2.8;

	anal.cut9_a = -0.28; anal.cut9_c = +0.00; anal.cut9_si = 0.14;
	anal.cut10_a = -0.29; anal.cut10_c = -0.02; anal.cut10_si = 0.14;

	anal.fc_L = FiducialCut({{-50E-6, 31E-6}, {-250E-6, 40E-6}, {-370E-6, 80E-6}, {-270E-6, 132E-6}, {250E-6, 134E-6}, {360E-6, 95E-6}, {380E-6, 42E-6}, {330E-6, 31E-6}});
	anal.fc_R = FiducialCut({{-50E-6, 31E-6}, {-250E-6, 40E-6}, {-370E-6, 80E-6}, {-270E-6, 132E-6}, {250E-6, 134E-6}, {360E-6, 95E-6}, {380E-6, 42E-6}, {330E-6, 31E-6}});
	anal.fc_G = FiducialCut({{-50E-6, 32E-6}, {-250E-6, 42E-6}, {-365E-6, 80E-6}, {-265E-6, 130E-6}, {250E-6, 132E-6}, {355E-6, 95E-6}, {375E-6, 43E-6}, {330E-6, 32E-6}});

	unsmearing_file = "unfolding_cf_ni_45t_56b.root";

	anal.inefficiency_3outof4 = 0.0; // TODO
	anal.inefficiency_pile_up = 0.0; // TODO
}
