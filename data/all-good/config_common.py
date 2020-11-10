import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../../../"))
from config_base import *

#--------------------

for c in all_cfg:
  timestamp_min = 78681.
  timestamp_max = 244931.

  c.timestamp_min = timestamp_min
  c.timestamp_max = timestamp_max
  c.timber_dir = "no_timber_dir"

  c.anal.alignment_t0 = timestamp_min
  c.anal.alignment_ts = (timestamp_max - timestamp_min) / 2.

  c.distilled_files = cms.vstring(
    "../../../fill7280/Totem1",
    "../../../fill7281/Totem1",
    "../../../fill7282/Totem1",
    "../../../fill7283/Totem1",
    "../../../fill7284/Totem1",
    "../../../fill7285/Totem1",
    "../../../fill7289/Totem1",
    "../../../fill7291/Totem1"
  )

#--------------------

cfg_45b_56t.anal.L_int = 1.

#--------------------

cfg_45t_56b.anal.L_int = 1.
