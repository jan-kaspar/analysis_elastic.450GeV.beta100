import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  c.anal.excl_bunches = [11, 520, 1019, 1541, 2067]

#----------

cfg_45b_56t.anal.L_int = 52017.1
cfg_45t_56b.anal.L_int = 54712.9
