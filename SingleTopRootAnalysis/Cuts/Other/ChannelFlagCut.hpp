/******************************************************************************
 * ChannelFlagCut.hpp                                                           *
 *                                                                            *
 * Cuts on Missing Et                                                         *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of ChannelFlagCut class                              *
 *    ChannelFlagCut()                    -- Parameterized Constructor          *
 *    ~ChannelFlagCut()                   -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "ChannelFlagCut"             *
 *                                                                            *
 * Private Data Members of ChannelFlagCut                                       *
 *    myTH1F* _hMissingEtBefore         -- Hist of MissingEt before cuts      *
 *    myTH1F* _hMissingEtAfter          -- Hist of MissingEt after cuts       *
 *    Int_t _missingEtMin;              -- Minimum Missing Et                 *
 *    Int_t _missingEtMin;              -- Minimum Missing Et                 *
 *                                                                            *
 * History                                                                    *
 *      15 Dec 2006 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef ChannelFlagCut_h
#define ChannelFlagCut_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <vector>
#include <sstream>

class ChannelFlagCut : public HistoCut 
{

public:

  // Parameterized Constructor
  ChannelFlagCut(EventContainer *EventContainerObj, Int_t channel);
  
  // Destructor
  ~ChannelFlagCut();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "ChannelFlagCut"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hChannelFlagBefore;    // Histogram Missing Et
  myTH1F* _hChannelFlagAfter;     // Histogram Missing Et

  // Cut parameters
  Int_t _channel;           // Minimum Missing Et

};


#endif







