import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../../"))
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 148551
  timestamp_max = 159046

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "2018_10_12_fill7285"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (timestamp_max - timestamp_min) / 2.

#--------------------

cfg_45b_56t.anal.L_int = 5.9197E+04

#--------------------

cfg_45t_56b.anal.L_int = 6.2482E+04
