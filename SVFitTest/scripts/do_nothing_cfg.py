import FWCore.ParameterSet.Config as cms
process = cms.Process("MAIN")

process.source = cms.Source("EmptySource", fileNames = cms.untracked.vstring())
