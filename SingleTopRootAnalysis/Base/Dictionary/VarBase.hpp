/*************************************
 * Do documentation later!
 */

#ifndef VarBase_h
#define VarBase_h

#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include <map>
#include "TROOT.h"
#include "TBranch.h"

class VarBase : public TNamed
{
public:
  VarBase(); //Not sure what to put in here yet - presumably I will need the skim tree to add branches to it?

  // set name
  virtual void SetName(const char *name);
  
  //Standard set event container method
  inline void SetEventContainer(EventContainer * obj){ _eventContainerObj = obj;};

  //Book the branches
  void BookBranches(TTree * skimTree);

  //Reset the branches
  void ResetBranches();


  //Fill the variables. There are two methods for this - the first is called from the AdditionalVarsProcessor which calls the individual VarBase classes filling routines before filling the branches themselves.
  virtual void FillBranches(EventContainer * evtObj) = 0;

  //Touch the variables.
  void TouchBranches();

  //Output the value of the branches
  void OutputBranches();
  
private:
  EventContainer *_eventContainerObj;
protected:
  std::map<string,int> _intVars;
  std::map<string,float> _floatVars;
  std::map<string,TBranch*> _branchVec;

  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system                                       
  // Must come at end of class definition                                         
  ClassDef (VarBase,1);
  ////////////////////// Do Not Put Anything Below this Line /////////////////////


}; // end class Var Base

#endif
