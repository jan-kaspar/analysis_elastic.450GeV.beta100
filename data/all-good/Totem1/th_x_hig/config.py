import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

cfg_45b_56t.anal.fc_G = FiducialCut([[+99E-6, 80E-6], [+100E-6, 36E-6], [250E-6, 42E-6], [385E-6, 80E-6], [270E-6, 124E-6], [+100E-6, 125E-6]])

cfg_45t_56t.anal.fc_G = FiducialCut([[99E-6, 80E-6], [+100E-6, 131E-6], [250E-6, 132E-6], [355E-6, 95E-6], [375E-6, 43E-6], [330E-6, 32E-6], [+100E-6, 32E-6]])
