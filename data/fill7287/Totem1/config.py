import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../"))
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324526.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324526.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324526.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324527.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324527.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324527.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324527.3_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324527.4_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324528.0_re_reco_Totem1.root"
  )
