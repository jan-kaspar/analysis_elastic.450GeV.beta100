import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/../..")
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 105700
  timestamp_max = 116740

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "2018_10_12_fill7282"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (115000 - timestamp_min) / 2.

#--------------------

cfg_45b_56t.anal.L_int = 69134.6
cfg_45t_56b.anal.L_int = 73195.5
