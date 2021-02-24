/******************************************************************************
 * bstarVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      25 Nov 2016 - Created by D. Leggat
 ******************************************************************************/

#ifndef bstarVars_h
#define bstarVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "TLorentzVector.h"
#include <vector>
#include <TChain.h>

class bstarVars: public VarBase {
  
public:
  bstarVars(bool makeHistos = false);
 void ResetVars();  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
 // bool AddAdditionalVariables(EventContainer * evtObj); 
private:
  std::vector<TLorentzVector> Jet;

  std::vector<TLorentzVector> BJet;
  std::vector<TLorentzVector> BoostedJets;
  std::vector<TLorentzVector> Muon;
  std::vector<TLorentzVector> Electron;

  TLorentzVector sumJet;
  TLorentzVector LeadJet;
  TLorentzVector sumBJet;
  TLorentzVector totalJets;

};

#endif
