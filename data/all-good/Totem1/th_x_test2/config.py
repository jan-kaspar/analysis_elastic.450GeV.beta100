import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in [cfg_45b_56t]:
    contour = Contour(c.anal.fc_L)
    contour = CutContour(contour, 305E-6, 0E-6, 304E-6, 150E-6)
    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour, th_x_high=300E-6))

for c in [cfg_45t_56b]:
    contour = Contour(c.anal.fc_L)

    contour = CutContour(contour, 280E-6, 30E-6, 350E-6, 80E-6)

    c.anal.fc_L = FiducialCut(contour)
    c.anal.fc_R = FiducialCut(contour)
    c.anal.fc_G = FiducialCut(Shrink(contour))

#----------

