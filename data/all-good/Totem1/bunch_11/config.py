import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  c.anal.excl_bunches = [520, 1019, 1541, 2067, 2555]

#----------

cfg_45b_56t.anal.L_int = 59510.5
cfg_45t_56b.anal.L_int = 62788.9
