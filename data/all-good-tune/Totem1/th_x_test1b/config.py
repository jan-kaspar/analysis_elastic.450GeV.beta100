import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in [cfg_45b_56t]:
    contour = Contour(c.anal.fc_L)
    contour = CutContour(contour, 295E-6, 0E-6, 294E-6, 150E-6)
    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_high=219E-6))

for c in [cfg_45t_56b]:
    contour = Contour(c.anal.fc_L)

    contour = CutContour(contour, -255E-6, 150E-6, -254E-6, 0E-6)

    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_low=-250E-6))

#----------

