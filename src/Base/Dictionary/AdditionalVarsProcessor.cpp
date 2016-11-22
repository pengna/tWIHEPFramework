#include "SingleTopRootAnalysis/Base/Dictionary/AdditionalVarsProcessor.hpp"

ClassImp(AdditionalVarsProcessor);

AdditionalVarsProcessor::AdditionalVarsProcessor(){
  
}

/****************************************************************************** 
 * void AdditionalVarsProcessor::AddVars(VarBase * variables) 
 *
 * Add the variables to the variable list 
 *                                                                              
 * Input: VarBase * variables
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::AddVars(VarBase* variables){
  _variableList.push_back(variables);
}

/****************************************************************************** 
 * void AdditionalVarsProcessor::BookBranches()                                 
 *                                                                              
 * Books the branches onto the skim tree                                        
 *                                                                              
 * Input: None                                                                  
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::BookBranches(TTree * skimTree){
  for (auto it : _variableList){
    it->BookBranches(skimTree);
  }
}

/****************************************************************************** 
 * void AdditionalVarsProcessor::ResetBranches()                                
 *                                                                              
 * Reset the branches in the skim tree                                          
 *                                                                              
 * Input: None                                                                  
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::ResetBranches(){
  for (auto it : _variableList){
    it->ResetBranches();
  }
}

/****************************************************************************** 
 * void AdditionalVarsProcessor::FillVars(EventContainer *obj)                  
 *                                                                              
 * Fill the variables in each of the variables                                  
 *                                                                              
 * Input: obj is the EventContainer that contains the information of the event  
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::FillBranches(EventContainer *obj){
  for (auto it : _variableList){
    it->FillBranches(obj);
  }

}

/****************************************************************************** 
 * void AdditionalVarsProcessor::TouchBranches()
 *                                                                              
 * Touch all the variables, because this might make it work for some reason.
 *                                                                              
 * Input: None
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::TouchBranches(){
  for (auto it : _variableList){
    it->TouchBranches();
  }
}

/****************************************************************************** 
 * void AdditionalVarsProcessor::OutputBranches()
 *                                                                              
 * Output the values of the branches we've filled
 *                                                                              
 * Input: None
 * Output: None                                                                 
 ******************************************************************************/
void AdditionalVarsProcessor::OutputBranches(){
  for (auto it : _variableList){
    it->OutputBranches();
  }
}
