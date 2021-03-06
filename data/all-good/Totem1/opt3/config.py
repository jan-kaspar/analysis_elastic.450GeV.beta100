import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in [cfg_45b_56t]:
    contour = Contour(c.anal.fc_L)
    contour = CutContour(contour, +220E-6, 0E-6, +221E-6, 150E-6)
    contour = CutContour(contour, 1., 115E-6, -1., 115E-6)
    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_high=+219E-6, th_y_high=114E-6))
    c.anal.vtx_x_min = -0.4
    c.anal.vtx_x_max = +0.4

for c in [cfg_45t_56b]:
    contour = Contour(c.anal.fc_L)
    contour = CutContour(contour, -220E-6, 150E-6, -221E-6, 0E-6)
    contour = CutContour(contour, 1., 115E-6, -1., 115E-6)
    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_low=-219E-6, th_y_high=114E-6))
    c.anal.vtx_x_min = -0.4
    c.anal.vtx_x_max = +0.4

#----------

