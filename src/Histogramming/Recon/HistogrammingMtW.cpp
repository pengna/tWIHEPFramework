/******************************************************************************
 * HistogrammingMtW.cpp                                                       *
 *                                                                            *
 * Books and fills histograms                                                 *
 * Used for events passing cuts applied in other classes                      *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingMtW()              -- Parameterized Constructor            *
 *    ~HistogrammingMtW()             -- Destructor                           *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingMtW"         *
 *                                                                            *
 * Private Data Members of this class                                         *
 *    myTH1F* _hMtW                   -- Hist of MtW                          *
 *                                                                            *
 * History                                                                    *
 *      08 Jul 2016 - Created by D. Leggat for CMS IHEP                       *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Histogramming/Recon/HistogrammingMtW.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * HistogrammingMtW::HistogrammingMtW(EventContainer *obj)                     *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Particle class                                                     *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingMtW::HistogrammingMtW(EventContainer *obj)
{
  SetEventContainer(obj);
} //HistogrammingMtW()

/******************************************************************************
 * HistogrammingMtW::~HistogrammingMtW()                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingMtW::~HistogrammingMtW()
{
  
} //HistogrammingMtW

/******************************************************************************
 * void HistogrammingMtW::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void HistogrammingMtW::BookHistogram(){
  
  //Histogram of mTW
  _hMtW = DeclareTH1F("mTW", "Transverse W mass",200,0.,200.);
  _hMtW->SetXAxisTitle("m_{T,W} [GeV]");
  _hMtW->SetYAxisTitle("Events");
  //cout<<"end of HistogrammingMtW::BookHistogram"<<endl;

} //BookHistogram

/******************************************************************************
 * Bool_t HistogrammingMtW::Apply()                                         *
 *                                                                            *
 * Fill histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t HistogrammingMtW::Apply()
{
  //cout<<"Begin of HistogrammingMtW::Apply()"<<endl;
  
  EventContainer *evc = GetEventContainer();
  
  if (evc->tightMuons.size() > 0){
    _hMtW -> Fill(TMath::Abs(2*evc->missingEt*evc->tightMuons[0].Pt()*(1-cos(evc->missingPhi - evc->tightMuons[0].Phi()))));
  }
  else if (evc->tightElectrons.size() > 0){
    _hMtW -> Fill(TMath::Abs(2*evc->missingEt*evc->tightElectrons[0].Pt()*(1-cos(evc->missingPhi - evc->tightElectrons[0].Phi()))));
  }

  //  }
  //cout<<"End of HistogrammingMtW::Apply()"<<endl;
  return kTRUE;  
  
} //Apply












