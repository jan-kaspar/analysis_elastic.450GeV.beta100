import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

cfg_45b_56t.anal.fc_G = FiducialCut([[-338E-6, 32E-6], [-100E-6, 32E-6], [-99E-6, 80E-6], [-100E-6, 127E-6], [-280E-6, 129E-6], [-385E-6, 60E-6]])

cfg_45t_56b.anal.fc_G = FiducialCut([[-99E-6, 80E-6], [-100E-6, 36E-6], [-250E-6, 42E-6], [-365E-6, 80E-6], [-265E-6, 130E-6], [-100E-6, 131E-6]])

#----------

cfg_45b_56t.anal.L_int = 0.0
cfg_45t_56b.anal.L_int = 0.0
