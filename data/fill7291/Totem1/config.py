import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../"))
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version3/run_324536.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version3/run_324536.1_re_reco_Totem1.root"
  )
