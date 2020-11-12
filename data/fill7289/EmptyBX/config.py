import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/..")
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.0_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.1_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.2_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.3_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.4_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.5_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.6_re_reco_EmptyBX.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/EmptyBX/version1/run_324532.7_re_reco_EmptyBX.root"
  )
