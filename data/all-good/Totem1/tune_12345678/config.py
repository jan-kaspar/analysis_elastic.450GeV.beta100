import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  # adjust post-reco corrections
  if c == cfg_45b_56t:
    c.anal.post_reco_adjustment_L.B = +30.7E-6 - 6.0E-6
    c.anal.post_reco_adjustment_L.C = +214
    c.anal.post_reco_adjustment_L.F = +5.5E-3

    c.anal.post_reco_adjustment_R.B = -29.0E-6 + 6.0E-6
    c.anal.post_reco_adjustment_R.C = -150
    c.anal.post_reco_adjustment_R.F = -5.5E-3

  if c == cfg_45t_56b:
    c.anal.post_reco_adjustment_L.B = +33.4E-6 - 8.3E-6
    c.anal.post_reco_adjustment_L.C = +150
    c.anal.post_reco_adjustment_L.F = +8.5E-3

    c.anal.post_reco_adjustment_R.B = -29.3E-6 + 8.3E-6
    c.anal.post_reco_adjustment_R.C = -305
    c.anal.post_reco_adjustment_R.F = -8.5E-3

  # adjust alignment
  if c == cfg_45b_56t:
    alignment_45b_56t["L_1_F"]["b"] += -1.7E-3
    alignment_45b_56t["L_2_F"]["b"] += +1.7E-3
    alignment_45b_56t["R_1_F"]["b"] += -1.7E-3
    alignment_45b_56t["R_2_F"]["b"] += +1.7E-3

    alignment_45b_56t["L_1_F"]["c"] += +36E-3
    alignment_45b_56t["L_2_F"]["c"] += +36E-3
    alignment_45b_56t["R_1_F"]["c"] += +36E-3
    alignment_45b_56t["R_2_F"]["c"] += +36E-3

    c.anal.alignment_sources = FormatAlignment(alignment_45b_56t)

  if c == cfg_45t_56b:
    alignment_45t_56b["L_1_F"]["c"] += -153E-3
    alignment_45t_56b["L_2_F"]["c"] += -153E-3
    alignment_45t_56b["R_1_F"]["c"] += -153E-3
    alignment_45t_56b["R_2_F"]["c"] += -153E-3

    c.anal.alignment_sources = FormatAlignment(alignment_45t_56b)

  # adjust cuts
  c.anal.cut1_si = 29E-6
  c.anal.cut7_si = 0.53

  if c == cfg_45b_56t:
    c.anal.cut1_c = -0.18E-6
    c.anal.cut2_c = +0.09E-6

    c.anal.cut5_c = -0.015
    c.anal.cut6_c = +0.03

    c.anal.cut7_c = +0.00
    c.anal.cut8_c = -0.21

    c.anal.cut9_c = -0.007
    c.anal.cut10_c = +0.001

  if c == cfg_45t_56b:
    c.anal.cut1_c = -0.05E-6
    c.anal.cut2_c = -0.0E-6

    c.anal.cut5_c = +0.03
    c.anal.cut6_c = -0.02

    c.anal.cut7_c = -0.01
    c.anal.cut8_c = +0.13

    c.anal.cut9_c = +0.00
    c.anal.cut10_c = -0.01

  # adjust resolution
  # NB: dx and dy is set from data, time dependent --> sufficient to set only mx and my
  SetResolutions(c, 26E-6 / math.sqrt(2), 7.9E-6 / math.sqrt(2))

  # add th_x cut for safe flag
  c.anal.th_x_safe_max = 300E-6

  # adjust ficucial selection and shrink parameter
  c.anal.vtx_x_min = -1.3
  c.anal.vtx_x_max = +1.3

  shrink_sigmas_def.x = 13E-6

  if c == cfg_45b_56t:
    single_arm_contour_45b_56t = single_arm_contour_45b_56t_full
    single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t, +305E-6, 0E-6, +304E-6, 150E-6)
    single_arm_contour_45b_56t = CutContour(single_arm_contour_45b_56t, -362E-6, 150E-6, -363E-6, 0E-6)
    double_arm_contour_45b_56t = Shrink(single_arm_contour_45b_56t, th_x_high=+219E-6, th_y_high=114E-6)

    c.anal.fc_L = FiducialCut(single_arm_contour_45b_56t)
    c.anal.fc_R = FiducialCut(single_arm_contour_45b_56t)
    c.anal.fc_G = FiducialCut(double_arm_contour_45b_56t)

  if c == cfg_45t_56b:
    single_arm_contour_45t_56b = single_arm_contour_45t_56b_full
    single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b, +363E-6, 0E-6, +362E-6, 150E-6)
    single_arm_contour_45t_56b = CutContour(single_arm_contour_45t_56b, -332E-6, 150E-6, -333E-6, 0E-6)
    double_arm_contour_45t_56b = Shrink(single_arm_contour_45t_56b, th_x_low=-219E-6, th_y_high=114E-6)

    c.anal.fc_L = FiducialCut(single_arm_contour_45t_56b)
    c.anal.fc_R = FiducialCut(single_arm_contour_45t_56b)
    c.anal.fc_G = FiducialCut(double_arm_contour_45t_56b)
