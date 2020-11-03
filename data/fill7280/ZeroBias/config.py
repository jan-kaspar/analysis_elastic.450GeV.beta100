import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../"))
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.28_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.29_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.30_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.31_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.32_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.33_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.34_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.35_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.36_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.37_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.38_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.39_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.40_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.41_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.42_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.43_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.44_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.45_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.46_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.47_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.48_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.49_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.50_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.51_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.52_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.53_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.54_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.55_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.56_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.57_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.58_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.59_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.60_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.61_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.62_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.63_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.64_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.65_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.66_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.67_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.68_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.69_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.70_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.71_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.72_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.73_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.74_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.75_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.76_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.77_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.78_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324458.9_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.28_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.29_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.30_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.31_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.32_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.33_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.34_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.35_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.36_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.37_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.38_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.39_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.40_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.41_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.42_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.43_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.44_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.45_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.46_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.47_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.48_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324460.9_re_reco_ZeroBias.root"
  )