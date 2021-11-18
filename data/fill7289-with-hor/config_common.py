import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/../..")
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 206071
  timestamp_max = 218141

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "2018_10_13_fill7289"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (215290 - timestamp_min) / 2.

  c.anal.excl_lsIntervals = cms.VPSet(
    cms.PSet(run=cms.uint32(324532), ls_first=cms.uint32(1), ls_second=cms.uint32(398)) # just the begginning (complement of the main dataset)
  )

UseFiducialCutsForDataWithHorizontals()

#--------------------

cfg_45b_56t.anal.L_int = 10486.0
cfg_45t_56b.anal.L_int = 9630.9
