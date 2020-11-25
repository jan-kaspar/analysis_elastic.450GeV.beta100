import FWCore.ParameterSet.Config as cms

input_files = cms.vstring(
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.0_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.1_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.2_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.3_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.4_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.5_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.6_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.7_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.8_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324467.9_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.0_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.10_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.11_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.12_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.13_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.14_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.15_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.16_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.17_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.18_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.19_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.1_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.20_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.21_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.22_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.23_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.2_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.3_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.4_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.5_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.6_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.7_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.8_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324469.9_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.0_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.10_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.11_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.12_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.13_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.14_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.15_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.16_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.17_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.18_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.19_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.1_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.20_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.21_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.22_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.23_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.24_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.25_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.26_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.27_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.28_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.29_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.2_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.30_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.31_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.32_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.33_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.34_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.35_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.36_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.37_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.38_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.39_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.3_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.40_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.41_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.42_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.43_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.44_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.45_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.4_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.5_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.6_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.7_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.8_re_reco_ZeroBias.root",
  "root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/ZeroBias/version5/run_324471.9_re_reco_ZeroBias.root"
)
