/******************************************************************************
 * HistogrammingEFTau.hpp                                                     *
 *                                                                            *
 * Books and fills histograms                                                 *
 * Used for events passing cuts applied in other classes                      *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingEFTau()              -- Parameterized Constructor          *
 *    ~HistogrammingEFTau()             -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingEFTau"       *
 *                                                                            *
 * Private Data Members of HistogrammingEFTau class                           *
 * - lots of histograms of tau propreties                                     *
 *                                                                            *
 * History                                                                    *
 *      25 Jun 2007 - Created by J. Holzbauer and P. Ryan                     *
 *****************************************************************************/

#ifndef HistogrammingEFTau_h
#define HistogrammingEFTau_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class HistogrammingEFTau : public HistoCut 
{

public:

  // Parameterized Constructor
  HistogrammingEFTau(EventContainer *obj);
  
  // Destructor
  ~HistogrammingEFTau();

  // Get the name describing the cut
  inline std::string GetCutName() { return "HistogrammingEFTau"; };

  // Book Histograms
  void BookHistogram();

  // Fill Histograms
  Bool_t Apply();
  
private:  
  ////////////////////////////////////////////////////////////////
  // Number of Objects
  ////////////////////////////////////////////////////////////////
  myTH1F* _hNObj;     // Histogram of number of taus

  ////////////////////////////////////////////////////////////////
  // Kinematic Quantities - Individual
  ////////////////////////////////////////////////////////////////
  myTH1F* _hPtObj1;   // Tau 1 PT
  myTH1F* _hEtaObj1;  // Tau 1 Eta
  myTH1F* _hPhiObj1;  // Tau 1 Phi

  myTH1F* _hPtObj2;   // Tau 2 PT
  myTH1F* _hEtaObj2;  // Tau 2 Eta
  myTH1F* _hPhiObj2;  // Tau 2 Phi

  myTH1F* _hPtObj3;   // Tau 3 PT
  myTH1F* _hEtaObj3;  // Tau 3 Eta
  myTH1F* _hPhiObj3;  // Tau 3 Phi

  myTH1F* _hPtObj4;   // Tau 4 PT
  myTH1F* _hEtaObj4;  // Tau 4 Eta
  myTH1F* _hPhiObj4;  // Tau 4 Phi

  myTH1F* _hPtObj5;   // Tau 5 PT
  myTH1F* _hEtaObj5;  // Tau 5 Eta
  myTH1F* _hPhiObj5;  // Tau 5 Phi

  myTH1F* _hPtObj6;   // Tau 6 PT
  myTH1F* _hEtaObj6;  // Tau 6 Eta
  myTH1F* _hPhiObj6;  // Tau 6 Phi

  myTH1F* _hPtObj7;   // Tau 7 PT
  myTH1F* _hEtaObj7;  // Tau 7 Eta
  myTH1F* _hPhiObj7;  // Tau 7 Phi

  myTH1F* _hPtObj8;   // Tau 8 PT
  myTH1F* _hEtaObj8;  // Tau 8 Eta
  myTH1F* _hPhiObj8;  // Tau 8 Phi

  ////////////////////////////////////////////////////////////////
  // Delta R - Individual 
  ////////////////////////////////////////////////////////////////
  myTH1F *_hDeltaRTauObj1;             // Tau 1 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj1;           // Tau 1 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj1;        // Tau 1 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj1;              // Tau 1 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj2;             // Tau 2 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj2;           // Tau 2 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj2;        // Tau 2 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj2;              // Tau 2 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj3;             // Tau 3 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj3;           // Tau 3 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj3;        // Tau 3 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj3;              // Tau 3 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj4;             // Tau 4 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj4;           // Tau 4 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj4;        // Tau 4 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj4;              // Tau 4 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj5;             // Tau 5 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj5;           // Tau 5 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj5;        // Tau 5 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj5;              // Tau 5 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj6;             // Tau 6 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj6;           // Tau 6 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj6;        // Tau 6 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj6;              // Tau 6 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj7;             // Tau 7 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj7;           // Tau 7 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj7;        // Tau 7 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj7;              // Tau 7 DeltaR between EF and Recon jets

  myTH1F *_hDeltaRTauObj8;             // Tau 8 DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTauObj8;           // Tau 8 DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2Obj8;        // Tau 8 DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJetObj8;              // Tau 8 DeltaR between EF and Recon jets

  ////////////////////////////////////////////////////////////////
  // Eta-Phi Space - Individual
  ////////////////////////////////////////////////////////////////
  myTH2F *_hEtaPhiObj1;          // Tau 1 2-d eta-phi plot
  myTH2F *_hEtaPhiObj2;          // Tau 2 2-d eta-phi plot
  myTH2F *_hEtaPhiObj3;          // Tau 3 2-d eta-phi plot
  myTH2F *_hEtaPhiObj4;          // Tau 4 2-d eta-phi plot
  myTH2F *_hEtaPhiObj5;          // Tau 5 2-d eta-phi plot
  myTH2F *_hEtaPhiObj6;          // Tau 6 2-d eta-phi plot
  myTH2F *_hEtaPhiObj7;          // Tau 7 2-d eta-phi plot
  myTH2F *_hEtaPhiObj8;          // Tau 8 2-d eta-phi plot

  ////////////////////////////////////////////////////////////////
  // Kinematic Qunatities - All
  ////////////////////////////////////////////////////////////////
  myTH1F *_hPt;       // Pt  of all taus
  myTH1F *_hEta;      // Eta of all taus
  myTH1F *_hPhi;      // Phi of all taus
  myTH1F *_hCharge;   // Charge of all taus 

  ////////////////////////////////////////////////////////////////
  // Delta R - All
  ////////////////////////////////////////////////////////////////
  myTH1F *_hDeltaRTau;             // DeltaR between EF and Reconstructed Taus
  myTH1F *_hDeltaRMCTau;           // DeltaR between EF and MC taus
  myTH1F *_hDeltaRLevel2;        // DeltaR between EF and Level2 taus
  myTH1F *_hDeltaRJet;              // DeltaR between EF and Recon jets

  ////////////////////////////////////////////////////////////////
  // Eta-Phi Space - All
  ////////////////////////////////////////////////////////////////
  myTH2F *_hEtaPhi;          // 2-d eta-phi plot


};


#endif
