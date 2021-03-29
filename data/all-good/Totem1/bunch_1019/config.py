import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  c.anal.excl_bunches = [11, 520, 1541, 2067, 2555]

#----------

cfg_45b_56t.anal.L_int = 64251.7
cfg_45t_56b.anal.L_int = 67292.7
