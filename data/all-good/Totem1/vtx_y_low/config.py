import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
    c.anal.vtx_y_max = -1.5

cfg_45b_56t.anal.L_int = 38575.3
cfg_45t_56b.anal.L_int = 49519.6
