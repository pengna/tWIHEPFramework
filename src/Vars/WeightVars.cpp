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
  
  //Systematic variations
  _floatVars["bWeight_SysUp"] = 0.;
  _floatVars["bWeight_SysDown"] = 0.;
  _floatVars["puWeight_SysUp"] = 0.;
  _floatVars["puWeight_SysDown"] = 0.;
  _floatVars["lepSF_SysUp"] = 0.;
  _floatVars["lepSF_SysDown"] = 0.;
  
}

void WeightVars::FillBranches(EventContainer * evtObj){

  //Fill the nominal event weight variables
  _floatVars["EventWeight"] = evtObj->GetOutputEventWeight();
  _floatVars["bWeight"] = evtObj->GetEventbTagReshape();
  _floatVars["puWeight"] = evtObj->GetEventPileupWeight();
  _floatVars["lepSF"] = evtObj->GetEventLepSFWeight();

  //Get the systematic variations
  _floatVars["lepSF_SysUp"] = evtObj->GetEventLepSFWeightUp();
  _floatVars["lepSF_SysDown"] = evtObj->GetEventLepSFWeightDown();

}
