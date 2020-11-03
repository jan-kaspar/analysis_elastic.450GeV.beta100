import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../"))
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.0_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.10_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.1_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.2_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.3_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.4_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.5_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.6_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.7_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.8_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324485.9_re_reco_EmptyBX.root"
  )
