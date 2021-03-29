import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  c.anal.excl_bunches = [11, 520, 1019, 1541, 2555]

#----------

cfg_45b_56t.anal.L_int = 64662.4
cfg_45t_56b.anal.L_int = 69161.9
