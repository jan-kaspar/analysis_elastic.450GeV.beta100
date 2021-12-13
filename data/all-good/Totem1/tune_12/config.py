import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../"))
from config_common import *

for c in all_cfg:
  # adjust post-reco corrections
  if c == cfg_45b_56t:
    c.anal.post_reco_adjustment_L.B = +30.7E-6 - 6.0E-6
    c.anal.post_reco_adjustment_L.C = +214
    c.anal.post_reco_adjustment_L.F = +5.5E-3

    c.anal.post_reco_adjustment_R.B = -29.0E-6 + 6.0E-6
    c.anal.post_reco_adjustment_R.C = -150
    c.anal.post_reco_adjustment_R.F = -5.5E-3

  if c == cfg_45t_56b:
    c.anal.post_reco_adjustment_L.B = +33.4E-6 - 8.3E-6
    c.anal.post_reco_adjustment_L.C = +150
    c.anal.post_reco_adjustment_L.F = +8.5E-3

    c.anal.post_reco_adjustment_R.B = -29.3E-6 + 8.3E-6
    c.anal.post_reco_adjustment_R.C = -305
    c.anal.post_reco_adjustment_R.F = -8.5E-3

  # adjust alignment
  if c == cfg_45b_56t:
    alignment_45b_56t["L_1_F"]["b"] += -1.7E-3
    alignment_45b_56t["L_2_F"]["b"] += +1.7E-3
    alignment_45b_56t["R_1_F"]["b"] += -1.7E-3
    alignment_45b_56t["R_2_F"]["b"] += +1.7E-3

    alignment_45b_56t["L_1_F"]["c"] += +36E-3
    alignment_45b_56t["L_2_F"]["c"] += +36E-3
    alignment_45b_56t["R_1_F"]["c"] += +36E-3
    alignment_45b_56t["R_2_F"]["c"] += +36E-3

    c.anal.alignment_sources = FormatAlignment(alignment_45b_56t)

  if c == cfg_45t_56b:
    alignment_45t_56b["L_1_F"]["c"] += -153E-3
    alignment_45t_56b["L_2_F"]["c"] += -153E-3
    alignment_45t_56b["R_1_F"]["c"] += -153E-3
    alignment_45t_56b["R_2_F"]["c"] += -153E-3

    c.anal.alignment_sources = FormatAlignment(alignment_45t_56b)
