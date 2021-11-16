import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

double_arm_contour_45b_56t = Shrink(single_arm_contour_45b_56t, sigma_x = 32E-6, sigma_y = 8E-6, th_x_high=+219E-6, th_y_high=114E-6)
cfg_45b_56t.anal.fc_G = FiducialCut(double_arm_contour_45b_56t)

double_arm_contour_45t_56b = Shrink(single_arm_contour_45t_56b, sigma_x = 32E-6, sigma_y = 8E-6, th_x_low=-219E-6, th_y_high=114E-6)
cfg_45t_56b.anal.fc_G = FiducialCut(double_arm_contour_45t_56b)

#----------

