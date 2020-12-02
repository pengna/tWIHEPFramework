/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/WeightVars.hpp"

#include <iostream>

//Test out a couple of variables, one int and one float I guess
WeightVars::WeightVars(){
  _floatVars["EventWeight"] = 0.;
  _floatVars["bWeight"] = 0.;
  _floatVars["puWeight"] = 0.;
  _floatVars["lepSF"] = 0.;
  _floatVars["trigSF"] = 0.;
   _floatVars["WSF"] = 0.;
   _floatVars["Toptag"] = 0.;
   _floatVars["Topptreweight"] = 0.;
  //_bTagSystNames = {"central","up_jes","down_jes","up_lf","down_lf","up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_cferr1","down_cferr1","up_cferr2","down_cferr2"};
  _bTagSystNames = {"central","up","down"};

  //Systematic variations
  for (auto const bSystName: _bTagSystNames) {
    _floatVars["bWeight_"+bSystName] = 0.;
    _floatVars["misTagWeight_"+bSystName] = 0.;
  }
  _floatVars["puWeight_SysUp"] = 0.;
  _floatVars["puWeight_SysDown"] = 0.;
  _floatVars["lepSF_SysUp"] = 0.;
  _floatVars["lepSF_SysDown"] = 0.;
  _floatVars["trigSF_SysUp"] = 0.;
  _floatVars["trigSF_SysDown"] = 0.;
  _floatVars["WSF_SysUp"] = 0.;
  _floatVars["WSF_SysDown"] = 0.;
  _floatVars["Toptag_SysUp"] = 0.;
  _floatVars["Toptag_SysDown"] = 0.;
 _floatVars["Topptreweight_a_SysUp"] = 0.;
 _floatVars["Topptreweight_b_SysUp"] = 0.;
  _floatVars["Topptreweight_a_SysDown"] = 0.;
  _floatVars["Topptreweight_b_SysDown"] = 0.;
}

void WeightVars::FillBranches(EventContainer * evtObj){

  //Fill the nominal event weight variables
  _floatVars["EventWeight"] = evtObj->GetOutputEventWeight();
  _floatVars["bWeight"] = evtObj->GetEventbTagReshape();
  _floatVars["puWeight"] = evtObj->GetEventPileupWeight();
  _floatVars["lepSF"] = evtObj->GetEventLepSFWeight();
  _floatVars["trigSF"] = evtObj->GetEventTrigSFWeight();
   _floatVars["WSF"] = evtObj->GetEventWSF();
   _floatVars["Toptag"] = evtObj->GetEventToptagging();
   _floatVars["Topptreweight"] = evtObj->GetEventTopptreweight();
  //Get the systematic variations
  _floatVars["lepSF_SysUp"] = evtObj->GetEventLepSFWeightUp();
  _floatVars["lepSF_SysDown"] = evtObj->GetEventLepSFWeightDown();
  _floatVars["trigSF_SysUp"] = evtObj->GetEventTrigSFWeightUp();
  _floatVars["trigSF_SysDown"] = evtObj->GetEventTrigSFWeightDown();
   _floatVars["WSF_SysUp"] = evtObj->GetEventWSFUp();
     _floatVars["WSF_SysDown"] = evtObj->GetEventWSFDown();
   _floatVars["Toptag_SysUp"] = evtObj->GetEventToptaggingUp();
     _floatVars["Toptag_SysDown"] = evtObj->GetEventToptaggingDown();
  _floatVars["Topptreweight_a_SysUp"] = evtObj->GetEventTopptreweight_a_Up();
  _floatVars["Topptreweight_b_SysUp"] = evtObj->GetEventTopptreweight_b_Up();
     _floatVars["Topptreweight_a_SysDown"] = evtObj->GetEventTopptreweight_a_Down();
     _floatVars["Topptreweight_b_SysDown"] = evtObj->GetEventTopptreweight_b_Down();
  //Pileup variations
  _floatVars["puWeight_SysUp"] = evtObj->GetEventPileupMinBiasUpWeight();
  _floatVars["puWeight_SysDown"] = evtObj->GetEventPileupMinBiasDownWeight();

  for (auto const bSystName: _bTagSystNames) {
    _floatVars["bWeight_"+bSystName] = evtObj->GetEventbTagReshape(bSystName);
    _floatVars["misTagWeight_"+bSystName] = evtObj->GetEventMisTagReshape(bSystName);
  }

}
