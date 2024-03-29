import FWCore.ParameterSet.Config as cms
import math

#----------------------------------------------------------------------------------------------------

def FiducialCut(points):
  c = cms.VPSet()
  for p in points:
    c.append(cms.PSet(x=cms.double(p[0]), y=cms.double(p[1])))
  return c

#----------------------------------------------------------------------------------------------------

def Contour(fc):
  output = []
  for p in fc:
    output.append([float(p.x.pythonValue()), float(p.y.pythonValue())])
  return output

#----------------------------------------------------------------------------------------------------

class ShrinkSigmas:
  def __init__(self, x, y):
    self.x = x
    self.y = y

shrink_sigmas_def = ShrinkSigmas(13E-6, 4E-6)

def Shrink(points, sigma_x = -1, sigma_y = -1, th_x_low = -100E-6, th_x_high = +100E-6, th_y_low = 50E-6, th_y_high = 100E-6):
  if sigma_x < 0:
    sigma_x = shrink_sigmas_def.x
  if sigma_y < 0:
    sigma_y = shrink_sigmas_def.y

  output = []
  for p in points:
    x = p[0]
    y = p[1]

    if (x < th_x_low):
      x += sigma_x

    if (x > th_x_high):
      x -= sigma_x

    if (y < th_y_low):
      y += sigma_y

    if (y > th_y_high):
      y -= sigma_y

    output.append([x, y])

  return output

#----------------------------------------------------------------------------------------------------

def CutContour(points, x1, y1, x2, y2):
  dx = x2 - x1
  dy = y2 - y1

  nx = -dy
  ny = dx

  output = []

  for i in range(len(points)):
    j = (i + 1) % len(points)

    pi_x = points[i][0]
    pi_y = points[i][1]

    pj_x = points[j][0]
    pj_y = points[j][1]

    pi_proj = (pi_x - x1) * nx + (pi_y - y1) * ny
    pj_proj = (pj_x - x1) * nx + (pj_y - y1) * ny

    pi_in = (pi_proj >= 0)
    pj_in = (pj_proj >= 0)

    if (pi_in and pj_in):
      output.append([pj_x, pj_y])

    if ((pi_in and (not pj_in)) or ((not pi_in) and pj_in)):
      # calculate intersection
      d2x = pj_x - pi_x
      d2y = pj_y - pi_y

      de_a_x = pi_x - x1
      de_a_y = pi_y - y1

      det = - dx * d2y + d2x * dy

      la1 = (-d2y * de_a_x + d2x * de_a_y) / det

      c_x = x1 + la1 * dx
      c_y = y1 + la1 * dy

      if not pi_in:
        output.append([c_x, c_y])
        output.append([pj_x, pj_y])
      else:
        output.append([c_x, c_y])

  return output

#----------------------------------------------------------------------------------------------------

def FormatAlignment(al):
  data = cms.VPSet()
  for rp, pars in al.items():
    data.append(cms.PSet(unit = cms.string(rp), a = cms.double(pars["a"]), b = cms.double(pars["b"]), c = cms.double(pars["c"])))

  return cms.VPSet( cms.PSet(data = data) )

#----------------------------------------------------------------------------------------------------

cfg = cms.PSet(
  input_files = cms.vstring(),
  distilled_files = cms.vstring("."),

  timestamp0 = cms.double(1539208800),

  timestamp_min = cms.double(0.),
  timestamp_max = cms.double(0.),

  timber_dir = cms.string(""),

  env = cms.PSet(
    optics_version = cms.string("v1"),

    al_x_L = cms.double(0.),
    be_x_L = cms.double(0.),
    al_x_R = cms.double(0.),
    be_x_R = cms.double(0.)
  ),

  anal = cms.PSet(
    excl_timeIntervals = cms.VPSet(
      # fill 7280, high PU prob
      cms.PSet(first=cms.uint32(78680), second=cms.uint32(79259)),
      cms.PSet(first=cms.uint32(79920), second=cms.uint32(79979)),
      cms.PSet(first=cms.uint32(80640), second=cms.uint32(81059)),
      cms.PSet(first=cms.uint32(84840), second=cms.uint32(84964)),

      # fill 7281, high PU prob
      cms.PSet(first=cms.uint32(93360), second=cms.uint32(93479)),
      cms.PSet(first=cms.uint32(94440), second=cms.uint32(94499)),
      cms.PSet(first=cms.uint32(101500), second=cms.uint32(101600)), # tiny end of fill

      # fill 7282
      cms.PSet(first=cms.uint32(105700), second=cms.uint32(105899)), # high PU prob
      cms.PSet(first=cms.uint32(107520), second=cms.uint32(107556)), # high PU prob
      cms.PSet(first=cms.uint32(112100), second=cms.uint32(112400)), # th_y resolution degraded
      cms.PSet(first=cms.uint32(112380), second=cms.uint32(112559)), # high PU prob
      cms.PSet(first=cms.uint32(115000), second=cms.uint32(117000)), # th_y resolution degraded

      # fill 7283, additional 3/4 inefficiency (PU prob >~ 1%)
      cms.PSet(first=cms.uint32(121000), second=cms.uint32(123000)),
      cms.PSet(first=cms.uint32(124400), second=cms.uint32(127000)),

      # fill 7284, high PU prob
      cms.PSet(first=cms.uint32(131220), second=cms.uint32(131339)),
      cms.PSet(first=cms.uint32(133920), second=cms.uint32(134339)),
      cms.PSet(first=cms.uint32(137640), second=cms.uint32(137759)),
      cms.PSet(first=cms.uint32(141420), second=cms.uint32(141659)),

      # fill 7285, high PU prob
      cms.PSet(first=cms.uint32(150480), second=cms.uint32(150634)),
      cms.PSet(first=cms.uint32(152340), second=cms.uint32(152969)),

      # additional 3/4 inefficiency (PU prob >~ 1%)
      cms.PSet(first=cms.uint32(148000), second=cms.uint32(150600)),
      cms.PSet(first=cms.uint32(151600), second=cms.uint32(152600)),
      cms.PSet(first=cms.uint32(154300), second=cms.uint32(160000)),

      # fill 7289, high PU prob
      cms.PSet(first=cms.uint32(206000), second=cms.uint32(206099)),

      # fill 7291, high PU prob
      cms.PSet(first=cms.uint32(233078), second=cms.uint32(233099)),
    ),

    excl_bunches = cms.vuint32(),

    excl_runs = cms.vuint32(324467),

    excl_lsIntervals = cms.VPSet(
      # horizontal RPs inserted - decreased efficiency

      # fill 7281
      cms.PSet(run=cms.uint32(324462), ls_first=cms.uint32( 94), ls_second=cms.uint32(338)),

      # fill 7289
      cms.PSet(run=cms.uint32(324532), ls_first=cms.uint32(399), ls_second=cms.uint32(520)),

      # fill 7291
      cms.PSet(run=cms.uint32(324536), ls_first=cms.uint32(360), ls_second=cms.uint32(509))
    ),

    alignment_sources = cms.VPSet(),

    post_reco_adjustment_L = cms.PSet(
      B = cms.double(0),
      C = cms.double(0),
      E = cms.double(0),
      F = cms.double(0),
    ),

    post_reco_adjustment_R = cms.PSet(
      B = cms.double(0),
      C = cms.double(0),
      E = cms.double(0),
      F = cms.double(0),
    ),

    t_min = cms.double(0.),
    t_max = cms.double(0.03),
    t_min_full = cms.double(0.),
    t_max_full = cms.double(0.045),
    t_min_crop = cms.double(3.1E-4),
    t_max_crop = cms.double(0.025),

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

    vtx_x_min = cms.double(-1.3),
    vtx_x_max = cms.double(+1.3),
    vtx_y_min = cms.double(-1E100),
    vtx_y_max = cms.double(+1E100),

    th_x_default = cms.double(0E-6),
    th_x_safe_max = cms.double(300E-6),

    si_th_x_1arm_L = cms.double(0.),
    si_th_x_1arm_R = cms.double(0.),
    si_th_x_1arm_unc = cms.double(0.),
    si_th_x_2arm = cms.double(0.),
    si_th_x_2arm_unc = cms.double(0.),
    si_th_x_LRdiff = cms.double(0.),
    si_th_x_LRdiff_unc = cms.double(0.),
    si_th_x_LRdiff_adj = cms.double(0.),

    si_th_y_1arm = cms.double(0.),
    si_th_y_1arm_unc = cms.double(0.),
    si_th_y_2arm = cms.double(0.),
    si_th_y_2arm_unc = cms.double(0.),
    si_th_y_LRdiff = cms.double(0.),
    si_th_y_LRdiff_unc = cms.double(0.),
    si_th_y_LRdiff_adj = cms.double(0.),

    use_resolution_fits = cms.bool(True),

    use_3outof4_efficiency_fits = cms.bool(True),
    use_pileup_efficiency_fits = cms.bool(True),
    use_background_fits = cms.bool(True),

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

    binnings = cms.vstring("sb1", "sb2", "sb3"),

    unsmearing_file = cms.string("unfolding_cf_ni_<diagonal>.root"),
    unsmearing_object = cms.string("fit-2/<binning>"),

    alignment_y_ranges = cms.VPSet(
      cms.PSet(unit=cms.string("L_2_F"), bot_min=cms.double(-24.0), bot_max=cms.double(-6.9), top_min=cms.double(7.4), top_max=cms.double(+25.5)),
      cms.PSet(unit=cms.string("L_1_F"), bot_min=cms.double(-21.5), bot_max=cms.double(-6.3), top_min=cms.double(6.6), top_max=cms.double(+22.3)),
      cms.PSet(unit=cms.string("R_1_F"), bot_min=cms.double(-23.0), bot_max=cms.double(-6.6), top_min=cms.double(6.6), top_max=cms.double(+21.5)),
      cms.PSet(unit=cms.string("R_2_F"), bot_min=cms.double(-25.2), bot_max=cms.double(-7.0), top_min=cms.double(7.3), top_max=cms.double(+24.0))
    )
  )
)

#----------------------------------------------------------------------------------------------------

def SetResolutions(cfg, si_th_x_1arm, si_th_y_1arm):
  # horizontal resolution
  cfg.anal.si_th_x_1arm_L = si_th_x_1arm
  cfg.anal.si_th_x_1arm_R = si_th_x_1arm
  cfg.anal.si_th_x_1arm_unc = -999.

  cfg.anal.si_th_x_LRdiff = si_th_x_1arm * math.sqrt(2.)
  cfg.anal.si_th_x_LRdiff_unc = -999.

  cfg.anal.si_th_x_2arm = si_th_x_1arm / math.sqrt(2.)
  cfg.anal.si_th_x_2arm_unc = -999.

  # vertical resolution
  cfg.anal.si_th_y_1arm = si_th_y_1arm
  cfg.anal.si_th_y_1arm_unc = -999.

  cfg.anal.si_th_y_LRdiff = si_th_y_1arm * math.sqrt(2.)
  cfg.anal.si_th_y_LRdiff_unc = -999.

  cfg.anal.si_th_y_2arm = si_th_y_1arm / math.sqrt(2.)
  cfg.anal.si_th_y_2arm_unc = -999.

SetResolutions(cfg, 26E-6 / math.sqrt(2), 7.9E-6 / math.sqrt(2))

#----------------------------------------------------------------------------------------------------

# diagonal-independent alignment constants
a_L_2_F, b_L_2_F, c_L_2_F = -6.0E-3,  -16E-3, +158E-3
a_L_1_F, b_L_1_F, c_L_1_F = -6.0E-3, +421E-3,   +8E-3
a_R_1_F, b_R_1_F, c_R_1_F = +6.0E-3, +101E-3, -236E-3
a_R_2_F, b_R_2_F, c_R_2_F = +6.0E-3, +863E-3,   -0E-3

#----------------------------------------------------------------------------------------------------

alignment_45b_56t = {
  "L_2_F" : { "a": a_L_2_F + 2E-3 - 0.3E-3, "b": b_L_2_F - 17E-3 + 1.7E-3, "c": c_L_2_F - 11E-3 - 90E-3 + 36E-3 },
  "L_1_F" : { "a": a_L_1_F + 2E-3 + 0.3E-3, "b": b_L_1_F + 17E-3 - 1.7E-3, "c": c_L_1_F + 11E-3 - 90E-3 + 36E-3 },
  "R_1_F" : { "a": a_R_1_F - 2E-3 + 1.3E-3, "b": b_R_1_F -  3E-3 - 1.7E-3, "c": c_R_1_F + 30E-3 - 90E-3 + 36E-3 },
  "R_2_F" : { "a": a_R_2_F - 2E-3 - 1.3E-3, "b": b_R_2_F +  3E-3 + 1.7E-3, "c": c_R_2_F - 30E-3 - 90E-3 + 36E-3 },
}

single_arm_contour_45b_56t_full = [[-300E-6, 34E-6], [50E-6, 34E-6], [245E-6, 45E-6], [365E-6, 80E-6], [270E-6, 126E-6], [-280E-6, 131E-6], [-370E-6, 60E-6]]
single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t_full, +305E-6, 0E-6, +304E-6, 150E-6)
single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t, -362E-6, 150E-6, -363E-6, 0E-6)
double_arm_contour_45b_56t = Shrink(single_arm_contour_45b_56t, th_x_high=+219E-6, th_y_high=114E-6)

cfg_45b_56t = cfg.clone(
  anal = dict(
    alignment_sources = FormatAlignment(alignment_45b_56t),

    post_reco_adjustment_L = dict(
      B = +30.7E-6 - 6.0E-6,
      C = +214,
      F = +5.5E-3
    ),

    post_reco_adjustment_R = dict(
      B = -29.0E-6 + 6.0E-6,
      C = -150,
      F = -5.5E-3
    ),

    cut1_a = 1., cut1_c = -0.18E-6, cut1_si = 29E-6,
    cut2_a = 1., cut2_c = +0.09E-6, cut2_si = 8E-6,

    cut5_a = 0.105, cut5_c = -0.015, cut5_si = 0.08,
    cut6_a = 0.105, cut6_c = +0.03, cut6_si = 0.08,

    cut7_a = 0., cut7_c = +0.00, cut7_si = 0.53,
    cut8_a = 0., cut8_c = -0.21, cut8_si = 2.8,

    cut9_a = -0.28, cut9_c = -0.007, cut9_si = 0.14,
    cut10_a = -0.29, cut10_c = +0.001, cut10_si = 0.14,

    fc_L = FiducialCut(single_arm_contour_45b_56t),
    fc_R = FiducialCut(single_arm_contour_45b_56t),
    fc_G = FiducialCut(double_arm_contour_45b_56t),

    inefficiency_3outof4 = 0.0,
    inefficiency_pile_up = 0.0
  )
)

#----------------------------------------------------------------------------------------------------

alignment_45t_56b = {
  "L_2_F" : { "a": a_L_2_F - 0.3E-3 + 1.5E-3, "b": b_L_2_F - 15E-3, "c": c_L_2_F + 15E-3 + 70E-3 - 153E-3},
  "L_1_F" : { "a": a_L_1_F - 0.3E-3 - 1.5E-3, "b": b_L_1_F + 15E-3, "c": c_L_1_F - 15E-3 + 70E-3 - 153E-3},
  "R_1_F" : { "a": a_R_1_F + 0.3E-3 + 1.3E-3, "b": b_R_1_F + 10E-3, "c": c_R_1_F + 20E-3 + 70E-3 - 153E-3},
  "R_2_F" : { "a": a_R_2_F + 0.3E-3 - 1.3E-3, "b": b_R_2_F - 10E-3, "c": c_R_2_F - 20E-3 + 70E-3 - 153E-3},
}

single_arm_contour_45t_56b_full = [[-50E-6, 34E-6], [-240E-6, 45E-6], [-360E-6, 80E-6], [-270E-6, 132E-6], [250E-6, 134E-6], [360E-6, 95E-6], [370E-6, 42E-6], [330E-6, 34E-6]]
single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b_full, +363E-6, 0E-6, +362E-6, 150E-6)
single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b, -332E-6, 150E-6, -333E-6, 0E-6)
double_arm_contour_45t_56b = Shrink(single_arm_contour_45t_56b, th_x_low=-219E-6, th_y_high=114E-6)

cfg_45t_56b = cfg.clone(
  anal = dict(
    alignment_sources = FormatAlignment(alignment_45t_56b),

    post_reco_adjustment_L = dict(
      B = +33.4E-6 - 8.3E-6,
      C = +150,
      F = +8.5E-3
    ),

    post_reco_adjustment_R = dict(
      B = -29.3E-6 + 8.3E-6,
      C = -305,
      F = -8.5E-3
    ),

    cut1_a = 1., cut1_c = -0.05E-6, cut1_si = 29E-6,
    cut2_a = 1., cut2_c = -0.00E-6, cut2_si = 8E-6,

    cut5_a = 0.105, cut5_c = +0.03, cut5_si = 0.08,
    cut6_a = 0.105, cut6_c = -0.02, cut6_si = 0.08,

    cut7_a = 0., cut7_c = -0.01, cut7_si = 0.53,
    cut8_a = 0., cut8_c = +0.13, cut8_si = 2.8,

    cut9_a = -0.28, cut9_c = +0.00, cut9_si = 0.14,
    cut10_a = -0.29, cut10_c = -0.01, cut10_si = 0.14,

    fc_L = FiducialCut(single_arm_contour_45t_56b),
    fc_R = FiducialCut(single_arm_contour_45t_56b),
    fc_G = FiducialCut(double_arm_contour_45t_56b),

    inefficiency_3outof4 = 0.0,
    inefficiency_pile_up = 0.0
  )
)

#----------------------------------------------------------------------------------------------------

cfg_45b_56b = cfg_45t_56b.clone()

#----------------------------------------------------------------------------------------------------

cfg_45t_56t = cfg_45b_56t.clone()

#----------------------------------------------------------------------------------------------------

all_cfg = [cfg, cfg_45b_56t, cfg_45t_56b, cfg_45b_56b, cfg_45t_56t]

#----------------------------------------------------------------------------------------------------

def UseFiducialCutsForDataWithHorizontals():
  global single_arm_contour_45b_56t
  global cfg_45b_56t
  single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t, +166E-6, 0E-6, +165E-6, 150E-6)
  single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t, -215E-6, 150E-6, -216E-6, 0E-6)
  double_arm_contour_45b_56t = Shrink(single_arm_contour_45b_56t, th_x_low=-210E-6, th_x_high=+160E-6, th_y_high=114E-6)
  cfg_45b_56t.anal.fc_L = FiducialCut(single_arm_contour_45b_56t)
  cfg_45b_56t.anal.fc_R = FiducialCut(single_arm_contour_45b_56t)
  cfg_45b_56t.anal.fc_G = FiducialCut(double_arm_contour_45b_56t)

  global single_arm_contour_45t_56b
  global cfg_45t_56b
  single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b, +166E-6, 0E-6, +165E-6, 150E-6)
  single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b, -215E-6, 150E-6, -216E-6, 0E-6)
  double_arm_contour_45t_56b = Shrink(single_arm_contour_45t_56b, th_x_low=-210E-6, th_x_high=+160E-6, th_y_high=114E-6)
  cfg_45t_56b.anal.fc_L = FiducialCut(single_arm_contour_45t_56b)
  cfg_45t_56b.anal.fc_R = FiducialCut(single_arm_contour_45t_56b)
  cfg_45t_56b.anal.fc_G = FiducialCut(double_arm_contour_45t_56b)
