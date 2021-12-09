import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../../../"))
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 78681.
  timestamp_max = 244931.

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "no_timber_dir"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (timestamp_max - timestamp_min) / 2.

  c.distilled_files = cms.vstring(
    "../../../fill7280/Totem1",
    "../../../fill7281/Totem1",
    "../../../fill7282/Totem1",
    "../../../fill7283/Totem1",
    "../../../fill7284/Totem1",
    "../../../fill7285/Totem1",
    "../../../fill7289/Totem1",
    "../../../fill7291/Totem1"
  )

  c.anal.use_3outof4_efficiency_fits = True # this can possibly change the shape --> True
  c.anal.use_pileup_efficiency_fits = False # this cannot change shape --> False

#--------------------

cfg_45b_56t.anal.L_int = 1.

single_arm_contour_45b_56t = single_arm_contour_45b_56t_full
double_arm_contour_45b_56t = Shrink(single_arm_contour_45b_56t, th_x_high=+219E-6, th_y_high=114E-6)

cfg_45b_56t.anal.fc_L = FiducialCut(single_arm_contour_45b_56t)
cfg_45b_56t.anal.fc_R = FiducialCut(single_arm_contour_45b_56t)
cfg_45b_56t.anal.fc_G = FiducialCut(double_arm_contour_45b_56t)

#--------------------

cfg_45t_56b.anal.L_int = 1.

single_arm_contour_45t_56b = single_arm_contour_45t_56b_full
double_arm_contour_45t_56b = Shrink(single_arm_contour_45t_56b, th_x_low=-219E-6, th_y_high=114E-6)

cfg_45t_56b.anal.fc_L = FiducialCut(single_arm_contour_45t_56b)
cfg_45t_56b.anal.fc_R = FiducialCut(single_arm_contour_45t_56b)
cfg_45t_56b.anal.fc_G = FiducialCut(double_arm_contour_45t_56b)
