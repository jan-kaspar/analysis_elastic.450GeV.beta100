import sys
import os
import FWCore.ParameterSet.Config as cms

tfd = os.path.dirname(os.path.abspath(__file__))
sys.path.append(tfd + "/..")
from config_common import *

for c in all_cfg:
  c.input_files = cms.vstring(
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324464.9_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.0_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.100_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.101_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.102_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.103_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.104_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.105_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.106_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.107_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.10_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.11_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.12_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.13_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.14_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.15_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.16_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.17_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.18_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.19_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.1_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.20_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.21_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.22_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.23_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.24_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.25_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.26_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.27_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.28_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.29_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.2_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.30_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.31_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.32_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.33_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.34_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.35_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.36_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.37_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.38_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.39_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.3_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.40_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.41_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.42_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.43_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.44_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.45_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.46_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.47_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.48_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.49_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.4_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.50_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.51_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.52_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.53_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.54_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.55_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.56_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.57_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.58_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.59_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.5_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.60_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.61_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.62_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.63_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.64_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.65_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.66_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.67_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.68_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.69_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.6_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.70_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.71_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.72_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.73_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.74_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.75_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.76_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.77_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.78_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.79_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.7_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.80_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.81_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.82_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.83_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.84_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.85_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.86_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.87_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.88_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.89_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.8_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.90_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.91_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.92_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.93_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.94_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.95_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.96_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.97_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.98_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.99_re_reco_ZeroBias.root",
    "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version2/run_324465.9_re_reco_ZeroBias.root"
  )
