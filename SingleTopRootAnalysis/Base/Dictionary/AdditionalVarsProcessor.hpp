#ifndef __AdditionalVarsProcessor__
#define __AdditionalVarsProcessor__

#include "TTree.h"
#include "TNamed.h"

#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"

class AdditionalVarsProcessor {


public:

  AdditionalVarsProcessor();
 
  //Destructor                                
  inline ~AdditionalVarsProcessor() {};

  //Add variables to the processor
  void AddVars(VarBase* variables);

  // Add variables to skim tree - this is done once before the loop  
  void BookBranches(TTree* skimTree);                                   
                                                                     
  // Reset the variables in the branches. Do this once for each event
  void ResetBranches();                                  
                                                                     
  // Fill the variables                                              
  void FillBranches(EventContainer *obj);                    

  // Touches the branches in case that's somehow helpful?
  void TouchBranches();

  // Output the value of the branches
  void OutputBranches();

private:                                                                 
  static VarBase *_currentVarBase;                                       
  static EventContainer *_currentEventContainer;                         
                                                                         
  //The actual vector that contains the variables we add to the skim tree
  std::vector<VarBase *> _variableList;                                  
                                                                         
  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system                                       
  // Must come at end of class definition                                         
  ClassDef(AdditionalVarsProcessor,1);
  ////////////////////// Do Not Put Anything Below this Line /////////////////////

};

#endif
