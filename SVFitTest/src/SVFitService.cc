#include "ICSVFit/SVFitTest/interface/SVFitService.h"

namespace ic {

  SVFitService::SVFitService() {
    ;
  }
  
  SVFitService::~SVFitService() {
    ;
  }

  std::vector<double> SVFitService::SVFitMassEleHad(Candidate const* lep, Candidate const* had, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToElecDecay, lep->pt(), lep->eta(), lep->phi(), 0.000511));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had->pt(), had->eta(), had->phi(), had->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    delete inputFile_visPtResolution;
    std::vector<double> res;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return res;
  }

  std::vector<double> SVFitService::SVFitMassMuHad(Candidate const* lep, Candidate const* had, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToMuDecay, lep->pt(), lep->eta(), lep->phi(), 0.10566));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had->pt(), had->eta(), had->phi(), had->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    delete inputFile_visPtResolution;
    std::vector<double> res;
    res.push_back(algo.getMass());
    res.push_back(algo.transverseMass());
    return res;
  }

  std::vector<double> SVFitService::SVFitMassHadHad(Candidate const* had1, int decm1, Candidate const* had2, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had1->pt(), had1->eta(), had1->phi(), had1->M(),decm1));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had2->pt(), had2->eta(), had2->phi(), had2->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    std::vector<double> res;
    delete inputFile_visPtResolution;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return res;
  }


  std::vector<double> SVFitService::SVFitMassEleMu(Candidate const* lep1, Candidate const* lep2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToElecDecay, lep1->pt(), lep1->eta(), lep1->phi(), 0.000511));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToMuDecay, lep2->pt(), lep2->eta(), lep2->phi(), 0.10566));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    std::vector<double> res;
    delete inputFile_visPtResolution;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return res;
  }

  std::pair<Candidate, std::vector<double>> SVFitService::SVFitCandidateEleHad(Candidate const* lep, Candidate const* had, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToElecDecay, lep->pt(), lep->eta(), lep->phi(), 0.000511));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had->pt(), had->eta(), had->phi(), had->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(),met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    Candidate fitresult;

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    std::vector<double> res;
    fitresult.set_vector(ROOT::Math::PtEtaPhiEVector(algo.fittedDiTauSystem()));
    delete inputFile_visPtResolution;

    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return std::make_pair(fitresult, res);
  }

  std::pair<Candidate, std::vector<double>> SVFitService::SVFitCandidateMuHad(Candidate const* lep, Candidate const* had, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToMuDecay, lep->pt(), lep->eta(), lep->phi(),0.10566));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had->pt(), had->eta(), had->phi(), had->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    Candidate fitresult;

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    fitresult.set_vector(ROOT::Math::PtEtaPhiEVector(algo.fittedDiTauSystem()));
    delete inputFile_visPtResolution;
    std::vector<double> res;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return std::make_pair(fitresult, res);
  }


  std::pair<Candidate, std::vector<double>> SVFitService::SVFitCandidateEleMu(Candidate const* lep1, Candidate const* lep2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToElecDecay, lep1->pt(),lep1->eta(), lep1->phi(), 0.000511));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToMuDecay, lep2->pt(), lep2->eta(), lep2->phi(), 0.10566));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    Candidate fitresult;

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    fitresult.set_vector(ROOT::Math::PtEtaPhiEVector(algo.fittedDiTauSystem()));
    delete inputFile_visPtResolution;

    std::vector<double> res;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());
    return std::make_pair(fitresult,res);
  }

  std::pair<Candidate, std::vector<double>> SVFitService::SVFitCandidateHadHad(Candidate const* had1, int decm1, Candidate const* had2, int decm2, Met const* met, bool MC) {
    svFitStandalone::Vector met_vec(met->vector().px(), met->vector().py(), met->vector().pz());
    TMatrixD covMET(2, 2);
    covMET(0,0) = met->xx_sig();
    covMET(1,0) = met->yx_sig();
    covMET(0,1) = met->xy_sig();
    covMET(1,1) = met->yy_sig();
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had1->pt(), had1->eta(), had1->phi(), had1->M(),decm1));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(svFitStandalone::kTauToHadDecay, had2->pt(), had2->eta(), had2->phi(), had2->M(),decm2));
    SVfitStandaloneAlgorithm algo(measuredTauLeptons, met->vector().px(), met->vector().py(), covMET, 0);
    algo.addLogM(false);
    TH1::AddDirectory(false);
    TFile *inputFile_visPtResolution = new TFile("SVFitRun2/data/svFitVisMassAndPtResolutionPDF.root");
    algo.shiftVisPt(true, inputFile_visPtResolution);

    Candidate fitresult;

    if(MC) algo.integrateMarkovChain();
    else algo.integrateVEGAS();
    fitresult.set_vector(ROOT::Math::PtEtaPhiEVector(algo.fittedDiTauSystem()));
    delete inputFile_visPtResolution;
    std::vector<double> res;
    res.push_back(algo.getMass());
    if(MC) res.push_back(algo.transverseMass());

    return std::make_pair(fitresult, res);
  }



}
