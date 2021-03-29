import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
    c.anal.vtx_x_min = +0.4

#----------

cfg_45b_56t.anal.L_int = 52760.0
cfg_45t_56b.anal.L_int = 59257.0
