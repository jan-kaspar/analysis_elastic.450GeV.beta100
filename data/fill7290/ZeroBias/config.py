import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../"))
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.28_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324534.9_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.28_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.29_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.30_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.31_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.32_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.33_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.34_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.35_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.36_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.37_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.38_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.39_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.40_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.41_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.42_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.43_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.44_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.45_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.46_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.47_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.48_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.49_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.50_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.51_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.52_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.53_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.54_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.55_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.56_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.57_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.58_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.59_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.60_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.61_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.62_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.63_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.64_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.65_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.66_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.67_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.68_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.69_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.70_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.71_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.72_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.73_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.74_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.75_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.76_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.77_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.78_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.79_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.80_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.81_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.82_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.83_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.84_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324535.9_re_reco_ZeroBias.root"
  )