import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/../..")
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 233085
  timestamp_max = 244931

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "2018_10_13_fill7291"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (241454 - timestamp_min) / 2.

#--------------------

cfg_45b_56t.anal.L_int = 97638.0
cfg_45t_56b.anal.L_int = 98017.6
