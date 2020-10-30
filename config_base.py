import FWCore.ParameterSet.Config as cms

cfg = cms.PSet(
  input_files = cms.vstring(),
  timestamp0 = cms.double(1539208800),

  env = cms.PSet(
    use_matched_optics = cms.bool(False)
  ),

  anal = cms.PSet(
    L_int = cms.double(0.)
  )
)

cfg_45b_56t = cfg.clone()

cfg_45t_56b = cfg.clone()

cfg_45b_56b = cfg.clone()

cfg_45t_56t = cfg.clone()

all_cfg = [cfg, cfg_45b_56t, cfg_45t_56b, cfg_45b_56b, cfg_45t_56t]