/******************************************************************************
 * HistogrammingNPvtx.cpp                                                       *
 *                                                                            *
 * Books and fills histograms                                                 *
 * Used for events passing cuts applied in other classes                      *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingNPvtx()              -- Parameterized Constructor            *
 *    ~HistogrammingNPvtx()             -- Destructor                           *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingNPvtx"         *
 *                                                                            *
 * Private Data Members of this class                                         *
 *    myTH1F* _hNPvtx                   -- Hist of MET                          *
 *                                                                            *
 * History                                                                    *
 *      14 Nov 2006 - Created by R. Schwienhorst for ATLAS                    *
 *      20 Nov 2006 - Modified by Bernard Pope                                *
 *      21 Mar 2007 - RS: Fill from event container, add sumET, mex, mey      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Histogramming/Recon/HistogrammingNPvtx.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * HistogrammingNPvtx::HistogrammingNPvtx(EventContainer *obj)                     *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Particle class                                                     *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingNPvtx::HistogrammingNPvtx(EventContainer *obj)
{
  SetEventContainer(obj);
} //HistogrammingNPvtx()

/******************************************************************************
 * HistogrammingNPvtx::~HistogrammingNPvtx()                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingNPvtx::~HistogrammingNPvtx()
{
  
} //HistogrammingNPvtx

/******************************************************************************
 * void HistogrammingNPvtx::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void HistogrammingNPvtx::BookHistogram(){
  
  // Histogram of MET
  _hNPvtx = DeclareTH1F("nPvtx","Number of primary vertex",20,0.,20.);
  _hNPvtx->SetXAxisTitle("nPvtx");
  _hNPvtx->SetYAxisTitle("Events");

  // Histogram of MEX 
  _hNPvtx_nJet = DeclareTH2F("nPvtx_nJet","Number of primary vertex vs number of Jets",20,0.,20., 20,0,20);
  _hNPvtx_nJet->SetXAxisTitle("nPvtx");
  _hNPvtx_nJet->SetYAxisTitle("nJet");

  // Histogram of MET
  _hNPvtx_nElectron = DeclareTH2F("nPvtx_nElectron","Number of primary vertex vs number of Electrons",20,0.,20.,20,0,20);
  _hNPvtx_nElectron->SetXAxisTitle("vPvtx");
  _hNPvtx_nElectron->SetYAxisTitle("nElectron");

  // Histogram of SUM ET
  _hNPvtx_nMuon = DeclareTH2F("nPvtx_nMuon","Number of primary vertex vs number of Muon",20,0.,20.,20,0,20);
  _hNPvtx_nMuon->SetXAxisTitle("vPvtx");
  _hNPvtx_nMuon->SetYAxisTitle("nMuon");


  //cout<<"end of HistogrammingNPvtx::BookHistogram"<<endl;

} //BookHistogram

/******************************************************************************
 * Bool_t HistogrammingNPvtx::Apply()                                         *
 *                                                                            *
 * Fill histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t HistogrammingNPvtx::Apply()
{
  //cout<<"Begin of HistogrammingNPvtx::Apply()"<<endl;
  
  EventContainer *evc = GetEventContainer();
  
  // Fill the histogram before the cut
  //cout<<"missing et is "<<MissingEt<<endl;

  // Fill Histograms
  //  if((evc->tightElectrons.size() >0)||(evc->tightMuons.size() >0)){
  _hNPvtx -> Fill(evc->nPvtx);
  _hNPvtx_nJet -> Fill(evc->nPvtx,evc->jets.size()); // njets
  _hNPvtx_nElectron -> Fill(evc->nPvtx,evc->tightElectrons.size()); // tight electron only

  _hNPvtx_nMuon -> Fill(evc->nPvtx,evc->tightMuons.size()); // tight muon only
  //  }
  //cout<<"End of HistogrammingNPvtx::Apply()"<<endl;
  return kTRUE;  
  
} //Apply












