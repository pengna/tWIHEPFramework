/******************************************************************************
 * HistogrammingJetAngular.cpp                                                       *
 *                                                                            *
 * Books and fills histograms                                                 *
 * Used for events passing cuts applied in other classes                      *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    HistogrammingJetAngular()              -- Parameterized Constructor            *
 *    ~HistogrammingJetAngular()             -- Destructor                           *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Fill histograms only (No Cuts)     *
 *    GetCutName()                      -- Returns "HistogrammingJetAngular"         *
 *                                                                            *
 * Private Data Members of this class                                         *
 *    myTH1F* _hMtW                   -- Hist of MtW                          *
 *                                                                            *
 * History                                                                    *
 *      08 Jul 2016 - Created by D. Leggat for CMS IHEP                       *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Histogramming/Recon/HistogrammingJetAngular.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * HistogrammingJetAngular::HistogrammingJetAngular(EventContainer *obj)                     *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Particle class                                                     *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingJetAngular::HistogrammingJetAngular(EventContainer *obj)
{
  SetEventContainer(obj);
} //HistogrammingJetAngular()

/******************************************************************************
 * HistogrammingJetAngular::~HistogrammingJetAngular()                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
HistogrammingJetAngular::~HistogrammingJetAngular()
{
  
} //HistogrammingJetAngular

/******************************************************************************
 * void HistogrammingJetAngular::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void HistogrammingJetAngular::BookHistogram(){
  
  //Histogram of delta R between untagged jets
  _hUntaggedJetDelR = DeclareTH1F("untaggedJetsDelR","#Delta R untagged jets",200,0.,6.);
  _hUntaggedJetDelR->SetXAxisTitle("#Delta R_{j,j}");
  _hUntaggedJetDelR->SetYAxisTitle("Events");
  
  //Histogram of delta R between leading untagged jet and b jet
  _hJet1bJetDelR = DeclareTH1F("bJet1DelR","#Delta R leading untagged jet b-jet",200,0.,6.);
  _hJet1bJetDelR->SetXAxisTitle("#Delta R_{b,j_{1}}");
  _hJet1bJetDelR->SetYAxisTitle("Events");

  //Histogram of delta R between subleading untagged jet and b jet
  _hJet2bJetDelR = DeclareTH1F("bJet2DelR","#Delta R subleading untagged jet b-jet",200,0.,6.);
  _hJet2bJetDelR->SetXAxisTitle("#Delta R_{b,j_{2}}");
  _hJet2bJetDelR->SetYAxisTitle("Events");

  //Histogram of delta R between lepton and b jet
  _hlepJetsDelR = DeclareTH1F("lepJetsDelR","lepton jets delta R",200,0.,6.);
  _hlepJetsDelR->SetXAxisTitle("#Delta R_{l,jj}");
  _hlepJetsDelR->SetYAxisTitle("Events");

  //Histogram of delta R between lepton and b jet
  _hlepbJetDelR = DeclareTH1F("lepbJetDelR","lepton b jet delta R",200,0.,6.);
  _hlepbJetDelR->SetXAxisTitle("#Delta R_{l,b}");
  _hlepbJetDelR->SetYAxisTitle("Events");

  //Histogram of delta R between lepton and leading jet
  _hJet1lepDelR = DeclareTH1F("Jet1lepDelR","lepton leading jet delta R",200,0.,6.);
  _hJet1lepDelR->SetXAxisTitle("#Delta R_{l,j_{1}}");
  _hJet1lepDelR->SetYAxisTitle("Events");

  //Histogram of delta R between lepton and sub-leading jet
  _hJet2lepDelR = DeclareTH1F("Jet2lepDelR","lepton sub-leading jet delta R",200,0.,6.);
  _hJet2lepDelR->SetXAxisTitle("#Delta R_{l,j_{2}}");
  _hJet2lepDelR->SetYAxisTitle("Events");

  //Histogram of delta phi between untagged jets
  _hUntaggedJetDelPhi = DeclareTH1F("untaggedJetsDelPhi","#Delta #Phi untagged jets",200,-3.2,3.2);
  _hUntaggedJetDelPhi->SetXAxisTitle("#Delta #Phi_{j,j}");
  _hUntaggedJetDelPhi->SetYAxisTitle("Events");
  
  //Histogram of delta phi between leading untagged jet and b jet
  _hJet1bJetDelPhi = DeclareTH1F("bJet1DelPhi","#Delta #Phi leading untagged jet b-jet",200,-3.2,3.2);
  _hJet1bJetDelPhi->SetXAxisTitle("#Delta #Phi_{b,j_{1}}");
  _hJet1bJetDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between subleading untagged jet and b jet
  _hJet2bJetDelPhi = DeclareTH1F("bJet2DelPhi","#Delta #Phi subleading untagged jet b-jet",200,-3.2,3.2);
  _hJet2bJetDelPhi->SetXAxisTitle("#Delta #Phi_{b,j_{2}}");
  _hJet2bJetDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between lepton and b jet
  _hlepJetsDelPhi = DeclareTH1F("lepJetsDelPhi","lepton jets delta phi",200,-3.2,3.2);
  _hlepJetsDelPhi->SetXAxisTitle("#Delta #Phi_{l,jj}");
  _hlepJetsDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between lepton and b jet
  _hlepbJetDelPhi = DeclareTH1F("lepbJetDelPhi","lepton b jet delta phi",200,-3.2,3.2);
  _hlepbJetDelPhi->SetXAxisTitle("#Delta #Phi_{l,b}");
  _hlepbJetDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between lepton and leading jet
  _hJet1lepDelPhi = DeclareTH1F("Jet1lepDelPhi","lepton leading jet delta phi",200,-3.2,3.2);
  _hJet1lepDelPhi->SetXAxisTitle("#Delta #Phi_{l,j_{1}}");
  _hJet1lepDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between lepton and sub-leading jet
  _hJet2lepDelPhi = DeclareTH1F("Jet2lepDelPhi","lepton sub-leading jet delta phi",200,-3.2,3.2);
  _hJet2lepDelPhi->SetXAxisTitle("#Delta #Phi_{l,j_{2}}");
  _hJet2lepDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between MET and leading untagged jet
  _hJet1METDelPhi = DeclareTH1F("Jet1METDelPhi","MET leading untagged jet delta phi",200,-3.2,3.2);
  _hJet1METDelPhi->SetXAxisTitle("#Delta #Phi_{MET,j_{1}}");
  _hJet1METDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between MET and sub-leading untagged jet
  _hJet2METDelPhi = DeclareTH1F("Jet1METDelPhi","MET sub-leading untagged jet delta phi",200,-3.2,3.2);
  _hJet2METDelPhi->SetXAxisTitle("#Delta #Phi_{MET,j_{2}}");
  _hJet2METDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between MET and sub-leading untagged jet
  _hbJetMETDelPhi = DeclareTH1F("Jet1METDelPhi","MET b jet delta phi",200,-3.2,3.2);
  _hbJetMETDelPhi->SetXAxisTitle("#Delta #Phi_{MET,b}");
  _hbJetMETDelPhi->SetYAxisTitle("Events");

  //Histogram of delta phi between MET and tagged jets
  _hJetsMETDelPhi = DeclareTH1F("JetsMETDelPhi","MET jets delta phi",200,-3.2,3.2);
  _hJetsMETDelPhi->SetXAxisTitle("#Delta #Phi_{MET,jj}");
  _hJetsMETDelPhi->SetYAxisTitle("Events");

  //cout<<"end of HistogrammingJetAngular::BookHistogram"<<endl;

} //BookHistogram

/******************************************************************************
 * Bool_t HistogrammingJetAngular::Apply()                                         *
 *                                                                            *
 * Fill histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t HistogrammingJetAngular::Apply()
{
  //cout<<"Begin of HistogrammingJetAngular::Apply()"<<endl;
  
  EventContainer *evc = GetEventContainer();
  
  Jet bJet = evc->taggedJets[0];
  int jetCount = 0;
  for (auto const jet : evc->jets){
    if (jet.IsTagged()) continue;
    if (jetCount == 0) leadingJet = jet;
    else subleadingJet = jet;
  }
  Jet firstJet;
  

  //  }
  //cout<<"End of HistogrammingJetAngular::Apply()"<<endl;
  return kTRUE;  
  
} //Apply












