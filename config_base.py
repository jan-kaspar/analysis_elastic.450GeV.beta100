import FWCore.ParameterSet.Config as cms
import math

#----------------------------------------------------------------------------------------------------

def FiducialCut(points):
  c = cms.VPSet()
  for p in points:
    c.append(cms.PSet(x=cms.double(p[0]), y=cms.double(p[1])))
  return c

#----------------------------------------------------------------------------------------------------

cfg = cms.PSet(
  input_files = cms.vstring(),
  distilled_files = cms.vstring("."),

  timestamp0 = cms.double(1539208800),

  timestamp_min = cms.double(0.),
  timestamp_max = cms.double(0.),

  timber_dir = cms.string(""),

  env = cms.PSet(
    use_matched_optics = cms.bool(False)
  ),

  anal = cms.PSet(
    excl_timeIntervals = cms.VPSet(
      cms.PSet(first=cms.uint32(112100), second=cms.uint32(112400)),
      cms.PSet(first=cms.uint32(115000), second=cms.uint32(117000))
    ),

    excl_bunches = cms.vuint32(),

    excl_runs = cms.vuint32(324467),

    excl_lsIntervals = cms.VPSet(
      cms.PSet(run=cms.uint32(324462), ls_first=cms.uint32( 94), ls_second=cms.uint32(338)),
      cms.PSet(run=cms.uint32(324532), ls_first=cms.uint32(399), ls_second=cms.uint32(520)),
      cms.PSet(run=cms.uint32(324536), ls_first=cms.uint32(360), ls_second=cms.uint32(509))
    ),

    # FIXME: alignment sources
#	AlignmentSource alSrc;
#	alSrc.SetAlignmentA(atConstant);
#	alSrc.SetAlignmentB(atConstant);
#	alSrc.SetAlignmentC(atConstant);
#
#	alSrc.cnst.a_L_2_F = -7.0E-3; alSrc.cnst.b_L_2_F =    0E-3 - 25E-3; alSrc.cnst.c_L_2_F = +170E-3; // first number: read from alignment.pdf, second number: correction reco-check plots
#	alSrc.cnst.a_L_1_F = -8.5E-3; alSrc.cnst.b_L_1_F = +400E-3 + 25E-3; alSrc.cnst.c_L_1_F =  +30E-3;
#
#	alSrc.cnst.a_R_1_F = +5.0E-3; alSrc.cnst.b_R_1_F = +100E-3 + 25E-3; alSrc.cnst.c_R_1_F = -180E-3;
#	alSrc.cnst.a_R_2_F = +3.5E-3; alSrc.cnst.b_R_2_F = +900E-3 - 25E-3; alSrc.cnst.c_R_2_F =  -20E-3;
    alignment_sources = cms.VPSet(
      cms.PSet(
        # first number: read from alignment.pdf, second number: correction reco-check plots
        data = cms.VPSet(
          cms.PSet(unit=cms.string("L_2_F"), a = cms.double(-7.0E-3), b = cms.double(   0E-3 - 25E-3), c = cms.double(+170E-3)),
          cms.PSet(unit=cms.string("L_1_F"), a = cms.double(-8.5E-3), b = cms.double(+400E-3 + 25E-3), c = cms.double( +30E-3)),
          cms.PSet(unit=cms.string("R_1_F"), a = cms.double(+5.0E-3), b = cms.double(+100E-3 + 25E-3), c = cms.double(-180E-3)),
          cms.PSet(unit=cms.string("R_2_F"), a = cms.double(+3.5E-3), b = cms.double(+900E-3 - 25E-3), c = cms.double( -20E-3))
        )
      )
    ),

    t_min = cms.double(0.),
    t_max = cms.double(0.03),
    t_min_full = cms.double(0.),
    t_max_full = cms.double(0.045),
    t_min_fit = cms.double(0.),

    n_si = cms.double(4.0),

    cut1_a = cms.double(0.), cut1_c = cms.double(0.), cut1_si = cms.double(0.),
    cut2_a = cms.double(0.), cut2_c = cms.double(0.), cut2_si = cms.double(0.),
    cut3_a = cms.double(0.), cut3_c = cms.double(0.), cut3_si = cms.double(0.),
    cut4_a = cms.double(0.), cut4_c = cms.double(0.), cut4_si = cms.double(0.),
    cut5_a = cms.double(0.), cut5_c = cms.double(0.), cut5_si = cms.double(0.),
    cut6_a = cms.double(0.), cut6_c = cms.double(0.), cut6_si = cms.double(0.),
    cut7_a = cms.double(0.), cut7_c = cms.double(0.), cut7_si = cms.double(0.),
    cut8_a = cms.double(0.), cut8_c = cms.double(0.), cut8_si = cms.double(0.),
    cut9_a = cms.double(0.), cut9_c = cms.double(0.), cut9_si = cms.double(0.),
    cut10_a = cms.double(0.), cut10_c = cms.double(0.), cut10_si = cms.double(0.),

    fc_L = FiducialCut([]),
    fc_R = FiducialCut([]),
    fc_G = FiducialCut([]),

	vtx_x_min = cms.double(-1E100),
	vtx_x_max = cms.double(+1E100),
	vtx_y_min = cms.double(-1E100),
	vtx_y_max = cms.double(+1E100),

	si_th_x_1arm_L = cms.double(0.),
	si_th_x_1arm_R = cms.double(0.),
	si_th_x_1arm_unc = cms.double(0.),
	si_th_x_2arm = cms.double(0.),
	si_th_x_2arm_unc = cms.double(0.),
	si_th_x_LRdiff = cms.double(0.),
	si_th_x_LRdiff_unc = cms.double(0.),

	si_th_y_1arm = cms.double(0.),
	si_th_y_1arm_unc = cms.double(0.),
	si_th_y_2arm = cms.double(0.),
	si_th_y_2arm_unc = cms.double(0.),
	si_th_y_LRdiff = cms.double(0.),
	si_th_y_LRdiff_unc = cms.double(0.),

	use_resolution_fits = cms.bool(True),

	use_3outof4_efficiency_fits = cms.bool(False),
	use_pileup_efficiency_fits = cms.bool(False),

	inefficiency_3outof4 = cms.double(0.),
	inefficiency_shower_near = cms.double(0.03),
	inefficiency_pile_up = cms.double(0.),
	inefficiency_trigger = cms.double(0.),
	inefficiency_DAQ = cms.double(0.),

	bckg_corr = cms.double(1.),

    L_int = cms.double(0.),

	eff_3outof4_fixed_point = cms.double(0.),
	eff_3outof4_slope = cms.double(0.),
	eff_3outof4_slope_unc = cms.double(0.),

	norm_corr = cms.double(0.),
	norm_corr_unc = cms.double(0.),

	alignment_t0 = cms.double(0.),
	alignment_ts = cms.double(60*60),

    binnings = cms.vstring("ub", "eb"),

    unsmearing_file = cms.string(""),
    unsmearing_object = cms.string("fit-1/<binning>")

    # FIXME:
	#anal.alignmentYRanges["L_2_F"] = Analysis::AlignmentYRange(-24.0, -6.9, 7.4, +25.5);
	#anal.alignmentYRanges["L_1_F"] = Analysis::AlignmentYRange(-21.5, -6.3, 6.6, +22.3);
	#anal.alignmentYRanges["R_1_F"] = Analysis::AlignmentYRange(-23.0, -6.6, 6.6, +21.5);
	#anal.alignmentYRanges["R_2_F"] = Analysis::AlignmentYRange(-25.2, -7.0, 7.3, +24.0);
  )
)

si_th_y_1arm = 6E-6
cfg.anal.si_th_y_1arm = si_th_y_1arm
cfg.anal.si_th_y_1arm_unc = -999.

cfg.anal.si_th_y_LRdiff = si_th_y_1arm * math.sqrt(2.)
cfg.anal.si_th_y_LRdiff_unc = -999.

cfg.anal.si_th_y_2arm = si_th_y_1arm / math.sqrt(2.)
cfg.anal.si_th_y_2arm_unc = -999.

si_th_x_1arm = 23E-6
cfg.anal.si_th_x_1arm_L = si_th_x_1arm
cfg.anal.si_th_x_1arm_R = si_th_x_1arm
cfg.anal.si_th_x_1arm_unc = -999.

cfg.anal.si_th_x_LRdiff = si_th_x_1arm * math.sqrt(2.)
cfg.anal.si_th_x_LRdiff_unc = -999.

cfg.anal.si_th_x_2arm = si_th_x_1arm / math.sqrt(2.)
cfg.anal.si_th_x_2arm_unc = -999.

#----------------------------------------------------------------------------------------------------

cfg_45b_56t = cfg.clone(
  anal = dict(
    cut1_a = 1., cut1_c = +4E-6, cut1_si = 35E-6,
    cut2_a = 1., cut2_c = -1.5E-6, cut2_si = 8E-6,

    cut5_a = 0.105, cut5_c = -0.02, cut5_si = 0.08,
    cut6_a = 0.105, cut6_c = +0.03, cut6_si = 0.08,

    cut7_a = 0., cut7_c = -0.02, cut7_si = 0.55,
    cut8_a = 0., cut8_c = +0.30, cut8_si = 2.8,

    cut9_a = -0.28, cut9_c = +0.02, cut9_si = 0.14,
    cut10_a = -0.29, cut10_c = +0.02, cut10_si = 0.14,

    fc_L = FiducialCut([[-350E-6, 31E-6], [50E-6, 31E-6], [250E-6, 40E-6], [390E-6, 80E-6], [270E-6, 126E-6], [-280E-6, 131E-6], [-390E-6, 60E-6]]),
    fc_R = FiducialCut([[-350E-6, 31E-6], [50E-6, 31E-6], [250E-6, 40E-6], [390E-6, 80E-6], [270E-6, 126E-6], [-280E-6, 131E-6], [-390E-6, 60E-6]]),
    fc_G = FiducialCut([[-338E-6, 32E-6], [50E-6, 32E-6], [250E-6, 42E-6], [385E-6, 80E-6], [270E-6, 124E-6], [-280E-6, 129E-6], [-385E-6, 60E-6]]),

    unsmearing_file = "unfolding_cf_ni_45b_56t.root",

    inefficiency_3outof4 = 0.0, # TODO
    inefficiency_pile_up = 0.0 # TODO
  )
)

#----------------------------------------------------------------------------------------------------

cfg_45t_56b = cfg.clone(
  anal = dict(
    cut1_a = 1., cut1_c = -7E-6, cut1_si = 34E-6,
    cut2_a = 1., cut2_c = +0.5E-6, cut2_si = 8E-6,

    cut5_a = 0.105, cut5_c = -0.01, cut5_si = 0.08,
    cut6_a = 0.105, cut6_c = -0.06, cut6_si = 0.08,

    cut7_a = 0., cut7_c = -0.04, cut7_si = 0.55,
    cut8_a = 0., cut8_c = -0.20, cut8_si = 2.8,

    cut9_a = -0.28, cut9_c = +0.00, cut9_si = 0.14,
    cut10_a = -0.29, cut10_c = -0.02, cut10_si = 0.14,

    fc_L = FiducialCut([[-50E-6, 31E-6], [-250E-6, 40E-6], [-370E-6, 80E-6], [-270E-6, 132E-6], [250E-6, 134E-6], [360E-6, 95E-6], [380E-6, 42E-6], [330E-6, 31E-6]]),
    fc_R = FiducialCut([[-50E-6, 31E-6], [-250E-6, 40E-6], [-370E-6, 80E-6], [-270E-6, 132E-6], [250E-6, 134E-6], [360E-6, 95E-6], [380E-6, 42E-6], [330E-6, 31E-6]]),
    fc_G = FiducialCut([[-50E-6, 32E-6], [-250E-6, 42E-6], [-365E-6, 80E-6], [-265E-6, 130E-6], [250E-6, 132E-6], [355E-6, 95E-6], [375E-6, 43E-6], [330E-6, 32E-6]]),

    unsmearing_file = "unfolding_cf_ni_45t_56b.root",

    inefficiency_3outof4 = 0.0, # TODO
    inefficiency_pile_up = 0.0 # TODO
  )
)

#----------------------------------------------------------------------------------------------------

cfg_45b_56b = cfg.clone()

#----------------------------------------------------------------------------------------------------

cfg_45t_56t = cfg.clone()

#----------------------------------------------------------------------------------------------------

all_cfg = [cfg, cfg_45b_56t, cfg_45t_56b, cfg_45b_56b, cfg_45t_56t]