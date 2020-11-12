import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/..")
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324517.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324518.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324518.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324518.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324518.3_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324519.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324519.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324519.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324519.3_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324519.4_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324520.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324520.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324520.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324520.3_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324520.4_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324524.0_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324524.1_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324524.2_re_reco_Totem1.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324524.3_re_reco_Totem1.root"
  )
