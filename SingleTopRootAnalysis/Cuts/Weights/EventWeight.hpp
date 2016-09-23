/******************************************************************************
 * EventWeight.hpp                                                            *
 *                                                                            *
 * Weight events in the histograms                                            *
 *                                                                            *
 * This class is derived from the BaseCut Class and simply                    *
 * cuts on if the event has reconstructed objects                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    EventWeight()                     -- Parameterized Constructor          *
 *    ~EventWeight()                    -- Destructor                         *
 *    BookHistogram()                   -- Book histograms of weights         *
 *    Apply()                           -- Apply weight and fill histograms   *
 *    GetCutName()                      -- Returns "EventWeight"              *
 *                                                                            *
 * Private Data Members of AnalysisMain class                                 *
 *    myTH1F* _hTreeWeight              -- Histogram of Input Tree Weights    *
 *    myTH1F* _hGlobalWeight            -- Histogram of Global Weights        *
 *    myTH1F* _hOutputWeight            -- Histogram of Output Weights        *
 *                                                                            *
 * History                                                                    *
 *     28 Apr 2005 - Created by R. Schwienhorst at D0                         *
 *      7 Nov 2006 - Modified by R. Schwienhorst for ATLAS                    *
 *      9 Nov 2006 - Modified by P. Ryan - cleanup and reorganized            *
 *****************************************************************************/

#ifndef EventWeight_h
#define EventWeight_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/BTagEntry.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/BTagCalibration.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/BTagCalibrationReader.hpp"
//#include "externaltools/pileup/PileupReweighting/TPileupReweighting.h"


class EventWeight : public HistoCut
{

public:

  // Parameterized Constructor
  EventWeight(EventContainer *obj, Double_t TotalMCatNLOEvents = 0,const std::string& MCtype="none", Bool_t pileup = false, Bool_t bWeight = false, Bool_t useLeptonSFs = kFALSE, Bool_t usebTagReshape = kFALSE);
  
  // Default Destructor
  ~EventWeight();

  // Book Histograms
  void BookHistogram(void );
  
  // Apply weight and fill histograms
  Bool_t Apply();

  Double_t PileupAdjust(int eventNumber = 0, int runnumber = 0);

  // methods for weighting for MC generatd with MCatNLO
  void setMCatNLO(Bool_t val=true) { _useMCatNLO=val; };
  void setPileUpWgt(Bool_t val=true) { _usePileUpWgt=val; };
  void setbWeight(Bool_t val=true) { _usebWeight=val; };
  Bool_t isMCatNLO() const { return _useMCatNLO; };
  Bool_t isPileUpWgt() const { return _usePileUpWgt; };
  Bool_t isbWeight() const { return _usebWeight; };

    // methods for weighting for MC generatd with NoWeight
  void setNoWeight(Bool_t val=true) { _useNoWeight=val; };
  Bool_t isNoWeight() const { return _useNoWeight; };
  
  // Get the name describing the cut
  inline std::string GetCutName() { return "EventWeight"; };

 void SetTotalMCatNLOEvents(Double_t evm) { _totalMCatNLOEvents=evm; };
private:
  //  vector<double> vecPileUpWgt;  // vector to store vertex Pile up reweighting weights
  Bool_t _useMCatNLO;  // set to true if this MC is MC@NLO and we need to use the corresponding weight
  Bool_t _usePileUpWgt;  // set to true if this MC is MC@NLO and we need to use the corresponding weight
  Bool_t _usebWeight;  // set to true if using b-tag weights
  Bool_t _useNoWeight;  //No weight except MCatNLO weight
  Bool_t _useLeptonSFs; // Use lepton SFs. Needs to be configured in the overall config file
  Bool_t _usebTagReshape; // Do CSV discriminant reshaping
  // Histograms
  myTH1F* _hTreeWeight;   // Histogram of input tree weights
  myTH1F* _hGlobalWeight; // Histogram of global weights
  myTH1F* _hMCatNLOWeight; // Histogram of MCatNLO weight
  myTH1F* _hPileUpWeight; // Histogram of PileUpWgt weight
  myTH1F* _hbWeight; // Histogram of b weight
  myTH1F* _hLeptonSFWeight; //Histogram of the lepton SF claculated for the event
  myTH1F* _hbTagReshape; //Histogram of the btag reshaping
  myTH1F* _hOutputWeight; // Histogram of output weights
  Double_t _totalMCatNLOEvents;
  BTagCalibration _bTagCalib;
  BTagCalibrationReader _bTagCalibReader;

  //Histograms that are used for applying scale factors to leptons
  //For now we are only using muons as we veto on electrons anyway
  TH2F* _muonIsoSF;
  TH2F* _muonIDSF;

  //Pileup reweighting hisotgrams
  TH1F* _dataPV;
  TH1F* _mcPV;

  Double_t getLeptonWeight(EventContainer * EventContainerObj);
  void setLeptonHistograms(TString muonIDFileName, TString muonIDHistName, TString muonIsoFileName, TString muonIsoHistName);
  Double_t getBTagReshape(EventContainer * EventContainerObj);

 //Root::TPileupReweighting* PileupReweighting;

};


#endif







