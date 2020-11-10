import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

cfg_45b_56t.anal.fc_G = FiducialCut([[-350E-6, 80E-6], [385E-6, 80E-6], [270E-6, 124E-6], [-280E-6, 129E-6]])

cfg_45t_56b.anal.fc_G = FiducialCut([[-365E-6, 80E-6], [-265E-6, 130E-6], [250E-6, 132E-6], [355E-6, 95E-6], [357E-6, 80E-6]])
