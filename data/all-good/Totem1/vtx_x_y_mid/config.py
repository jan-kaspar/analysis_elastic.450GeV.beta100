import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
    c.anal.vtx_x_min = -0.4
    c.anal.vtx_x_max = +0.4
    c.anal.vtx_y_min = -1.5
    c.anal.vtx_y_max = +1.5

#----------

cfg_45b_56t.anal.L_int = 187857.3
cfg_45t_56b.anal.L_int = 196367.5
