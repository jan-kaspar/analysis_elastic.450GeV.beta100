import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
    contour = Contour(c.anal.fc_L)
    contour = CutContour(contour, -120E-6, 150E-6, -121E-6, 0E-6)
    contour = CutContour(contour, +120E-6, 0E-6, +121E-6, 150E-6)
    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_low=-115E-6, th_x_high=+115E-6))

#----------

