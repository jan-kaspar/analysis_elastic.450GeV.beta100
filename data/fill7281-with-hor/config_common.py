import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/../..")
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 92934
  timestamp_max = 101598

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "2018_10_11_fill7281"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (timestamp_max - timestamp_min)

  c.anal.excl_lsIntervals = cms.VPSet(
    cms.PSet(run=cms.uint32(324461), ls_first=cms.uint32(1), ls_second=cms.uint32(100)), # full run
    cms.PSet(run=cms.uint32(324462), ls_first=cms.uint32(1), ls_second=cms.uint32(93)) # just the begginning (complement of the main dataset)
  )

UseFiducialCutsForDataWithHorizontals()

#--------------------

cfg_45b_56t.anal.L_int = 58293.7
cfg_45t_56b.anal.L_int = 55139.6
