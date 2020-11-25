import FWCore.ParameterSet.Config as cms

input_files = cms.vstring(
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.0_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.10_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.11_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.12_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.13_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.14_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.15_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.16_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.17_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.1_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.2_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.3_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.4_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.5_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.6_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.7_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.8_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324461.9_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.0_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.10_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.11_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.12_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.13_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.14_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.15_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.16_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.17_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.18_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.19_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.1_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.20_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.21_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.22_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.23_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.24_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.25_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.26_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.27_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.28_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.29_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.2_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.30_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.31_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.32_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.33_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.34_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.35_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.36_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.37_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.38_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.39_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.3_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.40_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.41_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.42_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.43_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.44_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.45_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.46_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.47_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.48_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.49_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.4_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.50_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.51_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.52_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.53_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.54_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.55_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.56_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.57_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.58_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.59_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.5_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.60_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.61_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.62_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.63_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.64_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.65_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.66_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.67_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.68_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.69_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.6_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.70_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.71_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.72_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.73_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.74_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.75_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.76_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.77_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.78_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.79_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.7_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.80_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.81_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.82_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.83_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.84_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.85_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.86_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.87_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.88_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.8_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324462.9_re_reco_ZeroBias.root"
)
