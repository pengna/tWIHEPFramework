/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/JESBDTVars.hpp"

#include <iostream>

//Test out a couple of variables, one int and one float I guess
JESBDTVars::JESBDTVars(){

  SetName("JESBDTVars");

  _intVecVars["M_nJet2040_JESShifts"];
  _floatVecVars["M_DeltaRBJetLepton_JESShifts"];
  _floatVecVars["M_DeltaRlightjets_JESShifts"];
  _floatVecVars["M_topMass2_lep_JESShifts"];
  _floatVecVars["M_Pt_Lepton_JESShifts"];
  _floatVecVars["M_Pt_AllJetsLeptonMET_JESShifts"];
  _floatVecVars["M_DeltaRLeptonJet1_JESShifts"];
  _floatVecVars["M_Mass_Jet1Jet2Jet3LeptonMET_JESShifts"];
  _floatVecVars["M_hadronicWmass_JESShifts"];
  _floatVecVars["lightJet1CSV_JESShifts"];

  SetRunAdditionalVariables(true);
}

bool JESBDTVars::AddAdditionalVariables(EventContainer * obj){
  
  for (int i = 0; i < obj->jets[0].GetNumberOfJESCorrections(); i++){

    _intVecVars["M_nJet2040_JESShifts"].push_back(0);
    _floatVecVars["M_DeltaRBJetLepton_JESShifts"].push_back(0);
    _floatVecVars["M_DeltaRlightjets_JESShifts"].push_back(0);
    _floatVecVars["M_topMass2_lep_JESShifts"].push_back(0);
    _floatVecVars["M_Pt_Lepton_JESShifts"].push_back(0);
    _floatVecVars["M_Pt_AllJetsLeptonMET_JESShifts"].push_back(0);
    _floatVecVars["M_DeltaRLeptonJet1_JESShifts"].push_back(0);
    _floatVecVars["M_Mass_Jet1Jet2Jet3LeptonMET_JESShifts"].push_back(0);
    _floatVecVars["M_hadronicWmass_JESShifts"].push_back(0);
    _floatVecVars["lightJet1CSV_JESShifts"].push_back(0);

  }                                                                  


  return true;
}

void JESBDTVars::FillBranches(EventContainer * evtObj){

  //Evaluate each distribution once per JES shift
  for (int i = 0; i < evtObj->jets[0].GetNumberOfJESCorrections(); i++){
    //First let's clear the things we already have
    selectedJet.clear();
    Jet2040.clear();
    BJet.clear();
    UntaggedJet.clear();

    //And make a dummy variable here
    Jet tempJet;
    TLorentzVector tempjet(0,0,0,0);

    //Number of loose jets
    for (auto jet : evtObj->alljets){
      tempJet = jet;
      TLorentzVector tempmet(0,0,0,0);
      tempJet.ShiftPtWithJESCorr(i,&tempmet);
      if (tempJet.Pt() > 20 && tempJet.Pt() < 40) Jet2040.push_back(tempJet);
    }

    for (auto jet : evtObj->jesShiftedJets[i]){
      selectedJet.push_back(jet);
      if (jet.IsTagged()) BJet.push_back(jet);
      else UntaggedJet.push_back(jet);
    }

    //Now set up the lepton and met variables
    TLorentzVector Lepton(00,0,0,0);
    TLorentzVector Miss(00,0,0,0);
    TLorentzVector Wlv(0,0,0,0);
    
    Miss = evtObj->metVecsJESShifted[i];

    if (evtObj->electronsToUsePtr->size() > 0){ // if this number is >0 we're in the electron channel. Otherwise use muons
      Lepton.SetPtEtaPhiE(evtObj->electronsToUsePtr->at(0).Pt(),evtObj->electronsToUsePtr->at(0).Eta(),evtObj->electronsToUsePtr->at(0).Phi(),evtObj->electronsToUsePtr->at(0).E());
    }
    else{
      Lepton.SetPtEtaPhiE(evtObj->muonsToUsePtr->at(0).Pt(),evtObj->muonsToUsePtr->at(0).Eta(),evtObj->muonsToUsePtr->at(0).Phi(),evtObj->muonsToUsePtr->at(0).E());
    }
    Wlv = Lepton+Miss;
   
    TLorentzVector W(0,0,0,0), Top(0,0,0,0);
    for (auto jet : UntaggedJet){
      W = W + jet;
    }

    TLorentzVector totalJets(0,0,0,0);
    for (auto jet : selectedJet){
      totalJets += jet;
    }

    //That should be all of the things we need to make the BDT variables, so let's make the variables now.
    _floatVecVars["M_DeltaRBJetLepton_JESShifts"][i] = fabs(BJet[0].DeltaR(Lepton));
    if (UntaggedJet.size() > 1) _floatVecVars["M_DeltaRlightjets_JESShifts"][i] = UntaggedJet.at(0).DeltaR(UntaggedJet.at(1));
    
    if (BJet[0].DeltaR(Lepton) > BJet[0].DeltaR(W)){
      _floatVecVars["M_topMass2_lep_JESShifts"][i] = -1;
    }
    else{
      Top = W + BJet[0];
      _floatVecVars["M_topMass2_lep_JESShifts"][i] = Top.M();
    }
    _floatVecVars["M_Pt_Lepton_JESShifts"][i] = Lepton.Pt();
  
  _floatVecVars["M_Pt_AllJetsLeptonMET_JESShifts"][i] = (Lepton + Miss + totalJets).Pt();

  _floatVecVars["M_DeltaRLeptonJet1_JESShifts"][i] = fabs(selectedJet.at(0).DeltaR(Lepton));
  
  if (selectedJet.size() > 2) _floatVecVars["M_Mass_Jet1Jet2Jet3LeptonMET_JESShifts"][i] = (selectedJet[0] + selectedJet[1] + selectedJet[2]).M();

  _floatVecVars["M_hadronicWmass_JESShifts"][i] = W.M();

  _floatVecVars["lightJet1CSV_JESShifts"][i] = UntaggedJet[0].GetbDiscriminator();

  }

  


}
