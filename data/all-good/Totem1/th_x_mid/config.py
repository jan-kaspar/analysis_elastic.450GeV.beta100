import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

cfg_45b_56t.anal.fc_G = FiducialCut([[-101E-6, 80E-6], [-100E-6, 32E-6], [+100E-6, 36E-6], [+101E-6, 80E-6], [+100E-6, 125E-6], [-100E-6, 127E-6]])

cfg_45t_56b.anal.fc_G = FiducialCut([[-50E-6, 32E-6], [-100E-6, 36E-6], [-101E-6, 80E-6], [-100E-6, 131E-6], [+100E-6, 131E-6], [+101E-6, 80E-6], [+100E-6, 32E-6]])

#----------

cfg_45b_56t.anal.L_int = 320184.0
cfg_45t_56b.anal.L_int = 377459.0
