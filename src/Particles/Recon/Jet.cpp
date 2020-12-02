/******************************************************************************
 * Jet.cpp                                                                    *
 *                                                                            *
 * Store information about final state jets                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Jet class                                       *
 *    Jet()                              -- Default Constructor               *
 *    Jet()                              -- Parameterized Constructor         *
 *    ~Jet()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill jet from event tree          *
 *    FillFastSim                        -- Fill jet from FastSim tree        *
 *    SetEtM0                            -- Set ET for EM layer 0             *
 *    GetEtM0                            -- Set ET for EM layer 0             *
 *    EtEM0                              -- Set ET for EM layer 0             *
 *    ApplyJESCorrection                 -- Shift jet energy by some amount   *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Jet              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Jet class                                          *
 *    Double_t _EtEm0                     -- Et for ME layer 0                *
 *                                                                            *
 * History                                                                    *
 *      16 Nov 2006 - Created by R. Schwienhorst                              *
 *      17 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      20 Mar 2007 - RS: Add filling from fastsim tree                       *
 *      29 Nov 2007 - RS: Add b-tagging choice when filling                   *
 *      11 Jan 2008 - RS: Fill only if object passes ID cuts                  *
 *      14 Jan 2008 - RS: For TRFIP2D, add systematics                        *
 *      08 May 2009 - J. Holzbauer: added quarkFlavorLabel tag                *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/BoostedJet.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Electron.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Muon.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <TRandom3.h>
#include<TString.h>


using namespace std;
//using namespace Analysis;

//
// give me a random number generator.
// put it here and make it static so that I don't create multiple copies
static TRandom3 jet_myran;
static TRandom3 jet_jer_myran;

// Integrate classes into the Root system
ClassImp(Jet)

/******************************************************************************
 * Jet::Jet()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet() : Particle::Particle(),
	_numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _jesUp(false), _jesDown(false), _jerUp(false), _jerDown(false), _hadronFlavour(-1), _tagged(0),
	_JerSF       (1.0),
	_JerSFup       (1.0),
	_JerSFdown       (1.0)
{
} //Jet()

/******************************************************************************
 * Jet::~Jet()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Jet::~Jet()
{
} //~Jet()

/******************************************************************************
 * Jet::Jet(const Jet& other)                                                 *
 *                                                                            *
 * Copy Constructor Jet const                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Jet& other): Particle(other),
_numberOfConstituents		(other.GetnumberOfConstituents()), 
_hadronFlavour		        (other.GethadronFlavour()), 
_tagged				(other.IsTagged()),
_chargedMultiplicity		(other.GetchargedMultiplicity()),  
_bDiscriminator 		(other.GetbDiscriminator()), 
_pileupId 			(other.GetpileupId()), 
_mass 				(other.Getmass()), 
_uncorrPt 			(other.GetuncorrPt()), 
_JerSF 				(other.GetJerSF()), 
_JerSFup 			(other.GetJerSFup()), 
_JerSFdown 			(other.GetJerSFdown()), 
_neutralHadEnergyFraction	(other.GetneutralHadEnergyFraction()), 
_neutralEmEmEnergyFraction 	(other.GetneutralEmEmEnergyFraction()),
 _chargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction()), 
_chargedEmEnergyFraction	(other.GetchargedEmEnergyFraction()), 
_muonEnergyFraction		(other.GetmuonEnergyFraction()), 
_electronEnergy			(other.GetelectronEnergy()), 
_photonEnergy			(other.GetphotonEnergy())
{
} //Jet()

/******************************************************************************
 * Jet::Jet(const Particle& other)                                            *
 *                                                                            *
 * Copy Constructor Particle const                                            *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Particle& other): Particle(other),
				 _numberOfConstituents(0), _hadronFlavour(-1), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _tagged(0),
        _JerSF       (1.0),
        _JerSFup       (1.0),
        _JerSFdown       (1.0)

{
 
} //Jet()


/******************************************************************************
 * Jet& Jet::operator+=(const Jet& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator+=(const Jet& other)
{
  
  Particle::operator+=(other);
  return *this;
} //+=

/******************************************************************************
 * Jet& Jet::operator+(const Jet& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet Jet::operator+(const Jet& other)
{
  Particle particleTemp = Particle::operator+(other);
  Jet jetTemp = particleTemp;
  return jetTemp;

} //+

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Particle& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents(0), 
  SethadronFlavour(-1),
  SetTagged(0),
  SetchargedMultiplicity(0),  
  SetbDiscriminator ( -999.0), 
  SetpileupId ( 0.0), 
  Setmass ( 0.0),
  SetJerSF ( 1.0); 
  SetJerSFup ( 1.0); 
  SetJerSFdown ( 1.0);  
  SetuncorrPt ( 0.0), 
  SetneutralHadEnergyFraction(0.0), 
  SetneutralEmEmEnergyFraction ( 0.0), 
  SetchargedHadronEnergyFraction (0.0), 
  SetchargedEmEnergyFraction(0.0), 
  SetmuonEnergyFraction(0.0), 
  SetelectronEnergy(0.0), 
  SetphotonEnergy(0.0);

  return *this;
} //= Particle

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = const Jet                                                       *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Jet& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SethadronFlavour	         	(other.GethadronFlavour());
  SetTagged				(other.IsTagged());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
   SetJerSF 				(other.GetJerSF());
  SetJerSFup 				(other.GetJerSFup());
  SetJerSFdown 				(other.GetJerSFdown());
  SetuncorrPt 				(other.GetuncorrPt());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= const

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = non-const Jet                                                   *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(Jet& other)
{
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SethadronFlavour	         	(other.GethadronFlavour());
  SetTagged			        (other.IsTagged());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
  SetJerSF 				(other.GetJerSF());
  SetJerSFup 				(other.GetJerSFup());
  SetJerSFdown 				(other.GetJerSFdown());
  SetuncorrPt 				(other.GetuncorrPt());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= non-const

/******************************************************************************         
 * void Jet::SetCuts(TEnv* config)                                            *
 *                                                                            *         
 * Set the cuts to be used on the jet objects                                 *
 *                                                                            *         
 * Input:  TEnv* config                                                       * 
 *         - Contains the cuts to be applied to each jet                      *
 * Output: None                                                               *
 ******************************************************************************/

void Jet::SetCuts(TEnv * config)
{
  _maxEtaCut = 			config -> GetValue("ObjectID.Jet.MaxEta",100.);
  _minPtCut = 			config -> GetValue("ObjectID.Jet.MinPt",0.);
  _bMaxEtaCut = 		config -> GetValue("ObjectID.BJet.MaxEta",100.);
  _bMinPtCut = 			config -> GetValue("ObjectID.BJet.MinPt",0.);
  _bTagCut2016 =                config -> GetValue("ObjectID.BJet.BTagCut.2016",0.0);
  _bTagCut2017 =                config -> GetValue("ObjectID.BJet.BTagCut.2017",0.0);
  _bTagCut2018 =                config -> GetValue("ObjectID.BJet.BTagCut.2018",0.0);
  _closestLeptonCut = 		config -> GetValue("ObjectID.Jet.LepCleanR",0.0);
  _jesUp = 			config -> GetValue("Systs.doJESUp",0);
  _jesDown = 			config -> GetValue("Systs.doJESDown",0);
  _jerUp = 			config -> GetValue("Systs.doJERUp",0);
  _jerDown = 			config -> GetValue("Systs.doJERDown",0);
   _dataEra=             	config -> GetValue("_dataEra",0);
  _bstar = 			config -> GetValue("ifbstar",0);
   _Elechannel =        	config -> GetValue("ifelechannel",0);
  _TT_CR =              	config -> GetValue("TT_CR",0);
  _QCD_CR =             	config -> GetValue("QCD_CR",0);
  _minBoostedJetDetaR = 	config -> GetValue("ObjectID.BJet.BoostedDeltaRMin",-999);
  _MaxLepJetDeltaR    = 	config -> GetValue("ObjectID.BJet.LepJetDeltaRMax",2.0);
}

/******************************************************************************         
 * void Jet::Fill(EventTree *evtr, Int_t iE,const TString& tagName)           *         
 *                                                                            *         
 * Fill jet vector from tree                                                  *         
 *                                                                            *         
 * Input:  Event Tree pointer                                                 *         
 *         - which jet                                                        *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/

Bool_t Jet::Fill( double myJESCorr, double myJERCorr, std::vector<BoostedJet>& selectedboostedjets,std::vector<Muon>& selectedMuons, std::vector<Electron>& selectedElectrons, EventTree *evtr, Int_t iE, TLorentzVector * met, bool isMC,TString jetType)
{
  int eventNumber = evtr -> EVENT_event;  

  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge, jetM, jetpx, jetpy, jetpz,jetUncorrE,jet_Uncorr_pt,jet_JesSF,jerSF,pt,energy,jet_DeepJet;
  jetPt     			= evtr -> Jet_pt     -> operator[](iE);
  jetEta    			= evtr -> Jet_eta    -> operator[](iE);
  jetPhi    			= evtr -> Jet_phi    -> operator[](iE);
  jetE      			= evtr -> Jet_energy -> operator[](iE);
  jetpx     			= evtr -> Jet_px     -> operator[](iE);
  jetpy     			= evtr -> Jet_py     -> operator[](iE);
  jetpz     			= evtr -> Jet_pz     -> operator[](iE);
  jet_Uncorr_pt			= evtr -> Jet_Uncorr_pt     -> operator[](iE);
  jetUncorrE = (evtr -> Jet_energy -> operator[](iE))/(evtr -> Jet_pt -> operator[](iE))*jet_Uncorr_pt;
  jet_JesSF  			= evtr -> Jet_JesSF-> operator[](iE);
  jerSF				= evtr -> Jet_JerSF     -> operator[](iE);
  jet_DeepJet 			= evtr ->Jet_pfDeepFlavourBJetTags-> operator[](iE);
  SetJerSF(jerSF);
  SetJerSFup(evtr->Jet_JerSFup->operator[](iE));
  SetJerSFdown(evtr->Jet_JerSFdown->operator[](iE));
  SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  if(jerSF == 1.0){
	  //>99% of jerSF > 1.1 is due to the bug in stochastic method , recalculation here
	  float rho = evtr->EVENT_rhopog;
	  TLorentzVector genJet={0,0,0,0}; 
	  float JerScaleFactor(1.), JerScaleFactorUP(1.), JerScaleFactorDOWN(1.);
	  Getjer(rho, false, genJet, JerScaleFactor, JerScaleFactorUP, JerScaleFactorDOWN, eventNumber);
	  SetJerSF(JerScaleFactor);
	  SetJerSFup(JerScaleFactorUP);
	  SetJerSFdown(JerScaleFactorDOWN);
  }
//cout<<"After correction jet pt from eventtree is : "<<jetPt<<"corresponding jerSF is : "<<JerSF()<<endl;

  TVector3 Jet(jetpx,jetpy,jetpz); 
//  pt = jet_Uncorr_pt*jet_JesSF*jerSF;
 // energy=(jet_Uncorr_pt/jetPt)*jetE*jet_JesSF*jerSF; 
 // SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  SetPtEtaPhiE(jet_Uncorr_pt,jetEta,jetPhi,jetUncorrE);



  SetnumberOfConstituents		(evtr -> Jet_numberOfConstituents     	-> operator[](iE));
  SetchargedMultiplicity		(evtr -> Jet_chargedMultiplicity     	-> operator[](iE)); 
  SetbDiscriminator 			(evtr -> Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags     	-> operator[](iE));
  SetpileupId 				(evtr -> Jet_pileupId     		-> operator[](iE));
  Setmass 				(evtr -> Jet_mass     			-> operator[](iE));
  SetuncorrPt 				(evtr -> Jet_Uncorr_pt     		-> operator[](iE));
  SetneutralHadEnergyFraction		(evtr -> Jet_neutralHadEnergyFraction	-> operator[](iE));
  SetneutralEmEmEnergyFraction 		(evtr -> Jet_neutralEmEnergyFraction  -> operator[](iE));
  SetchargedHadronEnergyFraction 	(evtr -> Jet_chargedHadronEnergyFraction-> operator[](iE));
  SetchargedEmEnergyFraction		(evtr -> Jet_chargedEmEnergyFraction    -> operator[](iE));
  SetmuonEnergyFraction			(evtr -> Jet_muonEnergyFraction     	-> operator[](iE));
  SetelectronEnergy			(evtr -> Jet_electronEnergy     	-> operator[](iE));
  SetphotonEnergy			(evtr -> Jet_photonEnergy     		-> operator[](iE));
  if (isMC)  SethadronFlavour           (evtr -> Jet_hadronFlavour              -> operator[](iE));


  /////////////////////////////////////////////////////////////////////////
  // Jet Cleaning
  /////////////////////////////////////////////////////////////////////////
//  cout<<"we are going to jet cleaning "<<endl;
  Bool_t passesCleaningfor2Dcut= kTRUE;
  Double_t closestLepton = 999.;
  TLorentzVector jet(0,0,0,0);
  TLorentzVector closedmuon(0,0,0,0);
  jet.SetPtEtaPhiE(Pt(),Eta(),Phi(),E());
  for (auto const & ele : selectedElectrons){
	  if (ele.patElectron_index() == evtr->Jet_ele_indices -> operator[](iE)){
		  jet = jet-ele;
	  }
  }
  for (auto const & mu : selectedMuons){
	  if (mu.index() == evtr->Jet_mu_indices -> operator[](iE)) { 
		  jet=jet-mu;
	  }
  }
 if(jet.E()>0){
       SetPtEtaPhiE(jet.Pt()*jet_JesSF*jerSF,jet.Eta(),jet.Phi(),jet.E()*jet_JesSF*jerSF);
 }
 else {
       SetPtEtaPhiE(1,1,1,3);
 }
  SetClosestLep(closestLepton);

  //cout<<"jet pt is : "<<jet.Pt()<<"jet Eta is : "<<jet.Eta()<<endl;
  if (_jesUp || _jesDown || _jerUp || _jerDown) SystematicPtShift(evtr, iE, met);  

  /////////////////////////////////////////////////////////////////////////
  // Jet ID
  /////////////////////////////////////////////////////////////////////////
  
  Bool_t LowEtaID =kTRUE;
  Bool_t MediumEtaID= kTRUE;
  Bool_t HighEtaID = kTRUE;

 if(_dataEra==2016){
    LowEtaID = (neutralHadEnergyFraction()<0.99 && neutralEmEmEnergyFraction()<0.99 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0 && chargedEmEnergyFraction() < 0.99) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()>0.01 && neutralHadEnergyFraction()<0.98 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 );
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 );

//LowEtaID = (neutralHadEnergyFraction()<0.90 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0 && chargedEmEnergyFraction() < 0.99) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
//MediumEtaID = (neutralEmEmEnergyFraction()>0.01 && neutralHadEnergyFraction()<0.98 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 );
//HighEtaID = (neutralEmEmEnergyFraction()<0.90 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 );

  }else if(_dataEra==2017){
    LowEtaID = (neutralHadEnergyFraction()<0.90 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()<0.99 && neutralEmEmEnergyFraction()>0.02 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 );
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 && neutralHadEnergyFraction()>0.02 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 );
  }else if(_dataEra==2018){
    LowEtaID = (neutralHadEnergyFraction()<0.90 && chargedMultiplicity()>0 ) && ((TMath::Abs(Eta())<=2.6 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1 && chargedHadronEnergyFraction()>0 ) || (TMath::Abs(Eta())>2.6 && neutralEmEmEnergyFraction()<0.99)) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()<0.99 && neutralEmEmEnergyFraction()>0.02 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 );
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 && neutralHadEnergyFraction()>0.2 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 );
  }else{
    std::cout<<"ERROR in Jet dataEra must be 2016/2017/2018 " << std::endl;
  }

    Bool_t passesJetID = LowEtaID || MediumEtaID || HighEtaID;








  /////////////////////////////////////////////////////////////////////////////
  // Jet Pt and Eta Cuts
  /////////////////////////////////////////////////////////////////////////////
  Bool_t passPt = Pt() > _minPtCut;
  Bool_t passEta = TMath::Abs(Eta()) < _maxEtaCut;
  Bool_t pass2Dcut = Pt()>30&&TMath::Abs(Eta())<3.0;

////////////////////////////////////////////////////////////////////////////
//Deta R related cut : with boostedjet Pt and Lepton
/////////////////////////////////////////////////////////////////////////////

 Double_t closestBoostJet= 999.;
 Bool_t passBoostedJet = kTRUE;
for (auto const & boostedjet :selectedboostedjets ){
	    if (boostedjet.DeltaR(*this) < closestBoostJet) closestBoostJet= boostedjet.DeltaR(*this);
	      }
//if(closestBoostJet<_minBoostedJetDetaR)passBoostedJet = kFALSE ;
if(closestBoostJet<0.8)passBoostedJet = kFALSE ;

Bool_t passDetaRleptonJet = kTRUE;
for (auto const & mu : selectedMuons){
	if (mu.DeltaR(*this) >_MaxLepJetDeltaR) passDetaRleptonJet = kFALSE; 
	//cout <<"DeltaR Lep Jet = "<<mu.DeltaR(*this)<<endl;
	}
for (auto const & ele : selectedElectrons){
	if (ele.DeltaR(*this) >_MaxLepJetDeltaR) passDetaRleptonJet = kFALSE;
        }

  /////////////////////////////////////////////////////////////////////////
  // B-tag related cuts
  /////////////////////////////////////////////////////////////////////////
  Bool_t passbPt = Pt() > _bMinPtCut;
  Bool_t passbEta = TMath::Abs(Eta()) < _bMaxEtaCut;
  Bool_t passTagCut = kTRUE;
  if(_dataEra==2016){passTagCut = jet_DeepJet> _bTagCut2016;}
  if(_dataEra==2017){passTagCut = jet_DeepJet> _bTagCut2017;}
  if(_dataEra==2018){passTagCut = jet_DeepJet> _bTagCut2018;}




  if(_bstar){
		  if("jetleptonclean"== jetType) return pass2Dcut;
		  else {
		  if (passTagCut) {SetTagged(1);}//cout<<"btag number: "<<jet_DeepJet<<endl;}
		  else SetTagged(0);
		  //else if ("beforejetoverlap"== jetType)return (passPt && passEta&& passesJetID);
		  //else {if (passPt && passEta&& passesJetID && passBoostedJet && passDetaRleptonJet) return kTRUE;} 
		  if (passPt && passEta&& passesJetID && passBoostedJet&& passDetaRleptonJet) return kTRUE;
} 
 }
else{
	if (passbPt && passbEta && passTagCut) SetTagged(1);
	else SetTagged(0);
	if (passPt && passEta && passesJetID ) return kTRUE;
}
 return kFALSE;
} //Fill()


/******************************************************************************         
 * void Jet::FillFastSim(FastSimTree *tr, Int_t iE,const TString& tagName )   *         
 *                                                                            *         
 * Fill jet vector from fastsim tree                                          *         
 *                                                                            *         
 * Input:  - FastSim tree pointer                                             *         
 *         - which jet                                                        *
 *         - tagName, either default or IP2D                                  *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/
Bool_t Jet::FillFastSim( std::vector<MCJet>& MCBJets, std::vector<MCJet>& MCCJets, std::vector<MCTau>& MCTaus, std::vector<Electron>& electrons, FastSimTree *tr,Int_t iE,TEnv* config,const TString& tagName, Double_t btagCut, Double_t mistagCut, Double_t eshift)
{ 
  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge;
  jetPt     = tr -> PJet_p_T    -> operator[](iE);
  jetEta    = tr -> PJet_eta    -> operator[](iE);
  jetPhi    = tr -> PJet_phi    -> operator[](iE);
  jetE      = tr -> PJet_E      -> operator[](iE);
  jetCharge = tr -> PJet_charge -> operator[](iE); 
  
  SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  SetCharge(jetCharge);

  if(eshift != 0){
    
    Double_t diffx,diffy,diffz,diffe;
    
    
    diffx = eshift * Px();
    diffy = eshift * Py();
    diffz = eshift * Pz();
    diffe = eshift * E();
    SetPxPyPzE(diffx + Px(),
	       diffy + Py(),
	       diffz + Pz(),
	       diffe + E());
    
    
    // if met pointers have been provided, update those also
    
   
  }
  //##########################################################################
  //b-tagging.  Insert info when available, based on reco tree.
  //##########################################################################



  //##########################################################################
  //PdgId()
  //
  //identifies jet with a MC quark.  5=bquark, 4=cquark, 15=tau(mc), 0=lightquark or gluon, etc
  //
  //This section identifies the MC particle (b, c, tau, or other (light quark)
  //that the jet is closest to and labels it as that, by pdgid, where light quark
  //is 0.  Jets are labeled starting with b, then c, then tau, and then, if none
  //of these match, as light quark.  This follows proceedure in b-tagging csc note.
  //Jet must be within deltaR of 0.3 of particle to be matched, and mc particle
  //must have Pt > 5 GeV, also per the csc note.
  //
  //Currently modified to use the Jet_Truth_Label variable from tree
  //Currently no charge information carried in this label
  //
  //NOTE: This PDGId() method returns the flavor of the MC particle associated
  //with the jet (wrt position).  It is NOT nessesarily the jet's flavor, but
  //a reasonable assumption BASED ON MC AND RECO INFORMATION
  //##########################################################################

  Double_t DeltaRCurrent = 0;
  Double_t EtaCurrent  = 0;
  Double_t PhiCurrent  = 0;
  Double_t PtCurrent   = 0;
  //SetPdgId(999);//not set yet
  
  //SetPdgId(tr -> Jet_Truth_Label -> operator[](iE));//not set yet
  
  
  //////////////////////////////////////////////////
  // Overlap with Electron
  //////////////////////////////////////////////////
  // Get Minimum separation between the electron and jet from the config file
  Double_t electronDeltaRMin = config -> GetValue("ObjectID.Jet.ElectronDeltaRMin", 0.0);
  Double_t electronDeltaR = 0.0;
  std::vector<Electron>::iterator electronIterator;
  for(electronIterator = electrons.begin(); electronIterator != electrons.end(); electronIterator++){
    electronDeltaR = electronIterator->DeltaR(*this);
    // If jet is too close to any electron set overlap to 1 and break
   if(electronDeltaR < electronDeltaRMin ){
      //SetOverlapWithElectron(1);
      break;
    } //if
  } //for
 




 
  
  // now check jet object ID cuts
  double maxEta=config->GetValue("ObjectID.Jet.MaxEta",100.);
  double minPt=config->GetValue("ObjectID.Jet.MinPt",0.);
  
  
  //if(jetPt<minPt) return kFALSE;
  //if(TMath::Abs(jetEta)>maxEta) return kFALSE;

  // Set to false if jet fails pT requirement, eta reqiurement, is overlapped with electron
  //if( jetPt <= minPt || TMath::Abs(jetEta) >= maxEta  || GetOverlapWithElectron() ) return kFALSE;
  //else return kTRUE;
  return kTRUE;
  
} //FillFastSim()

/******************************************************************************         
 *  * void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
 *   *                                                                            *         
 *    * Calculate JEC uncertainty source                                           *
 *     *                                                                            *         
 *      * Input:  - SourceName, SystUp, txtfilenmame                                 # 
 *       * Output: -                                                                  *
 *        ******************************************************************************/

float Jet::CalculateUncSource(Double_t jesSF, bool jesup, int eventNumber ){
	float jecvar = 1.;
	if(jesSF == 1 )return jecvar;
	jecAK4PFchsMCUncSource_->setJetEta( Eta() );
	jecAK4PFchsMCUncSource_->setJetPt( Pt() );
	float corrUpAK4PFchs_up = jesSF * (1 + fabs(jecAK4PFchsMCUncSource_->getUncertainty(1)));
	jecAK4PFchsMCUncSource_->setJetEta( Eta() );
	jecAK4PFchsMCUncSource_->setJetPt( Pt() );
	float corrUpAK4PFchs_down = jesSF * (1 - fabs(jecAK4PFchsMCUncSource_->getUncertainty(-1)));
	//std::cout << "_jecsource "<< _jecsourceName <<" jet Pt  " << Pt() << " jet eta "  << Eta() << " jesSF " << jesSF << " jesFlavorQCDup " << corrUpAK4PFchs_up << " jesFlavorQCDdown " << corrUpAK4PFchs_down << std::endl;
	if(jesup)jecvar = corrUpAK4PFchs_up;
	else jecvar = corrUpAK4PFchs_down;
	return jecvar;
};

void Jet::SetJECUncSource(TEnv * config, TString jecsourceName){
	_sourcefilename = config->GetValue("Systs.JecSourceFile","config/weights/2018data/Regrouped_Autumn18_V19_MC_UncertaintySources_AK4PFchs.txt");
         resolution = JME::JetResolution(config->GetValue("Systs.JerResFile","config/weights/2018data/Autumn18_V7_MC_PtResolution_AK4PFchs.txt"));
        //cout<<"resolution config name :"<<config->GetValue("Systs.JerResFile","config/weights/data2018/Autumn18_V7_MC_PtResolution_AK4PFchs.txt")<<endl; 
	res_sf = JME::JetResolutionScaleFactor(config->GetValue("Systs.JerSFFile","config/weights/2018data/Autumn18_V7_MC_SF_AK4PFchs.txt"));
	_jecsourceName = jecsourceName;
	std::cout<< " set jecsource " << jecsourceName << " _jecsource " << _jecsourceName << std::endl;
	//_sourcename = config->GetValue("FlavorQCD");
	if(_jecsourceName != "NONE"){
		jecAK4PFchsMCUncSource_   =  new JetCorrectionUncertainty(*(new JetCorrectorParameters(_sourcefilename.Data(), _jecsourceName.Data())));
	}
};

/******************************************************************************         
* void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
*                                                                            *         
* Calculate JEC uncertainty source                                           *
*                                                                            *         
* Input:  - SourceName, SystUp, txtfilenmame                                 # 
* Output: -                                                                  *
******************************************************************************/
void Jet::Getjer(float rhoJER, bool isgenmatch, TLorentzVector genjet, float &JERScaleFactor, float &JERScaleFactorUP, float &JERScaleFactorDOWN, int nEvent){
	double cFactorJER = 1.0; 
	double cFactorJERdown = 1.0;
	double cFactorJERup = 1.0;
	double recoJetPt = Pt();
        JME::JetParameters parameters;
	parameters.setJetPt(Pt());
	parameters.setJetEta(Eta());
	parameters.setRho(rhoJER);
	float relpterr = resolution.getResolution(parameters);
	cFactorJER = res_sf.getScaleFactor(parameters);
	cFactorJERup = res_sf.getScaleFactor(parameters, Variation::UP);
	cFactorJERdown = res_sf.getScaleFactor(parameters, Variation::DOWN);
	if(isgenmatch){
		double genJetPt = genjet.Pt();
		double diffPt    = recoJetPt - genJetPt;
		double conesize = 0.4;
		if(genJetPt>0. && genjet.DeltaR(*this)<conesize/2
				&& (abs(recoJetPt-genjet.Pt())<3*relpterr*recoJetPt)) {
			JERScaleFactor     = (std::max(0., genJetPt + cFactorJER*diffPt))/recoJetPt;
			JERScaleFactorUP   = (std::max(0., genJetPt + cFactorJERup*diffPt))/recoJetPt;
			JERScaleFactorDOWN = (std::max(0., genJetPt + cFactorJERdown*diffPt))/recoJetPt;
		} else {
			JERScaleFactor     = 1.;
			JERScaleFactorUP   = 1.;
			JERScaleFactorDOWN = 1.;
		}
	}else{
		if(cFactorJER>1){
			double sigma = relpterr * std::sqrt(cFactorJER*cFactorJER-1);
			JERScaleFactor = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
		}else{
			JERScaleFactor = 1.;
		}
		if(cFactorJERup>1){
			double sigma = relpterr * std::sqrt(cFactorJERup*cFactorJERup-1);
			JERScaleFactorUP = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
		}else{
			JERScaleFactorUP = 1.;
		}
		if(cFactorJERdown>1){
			double sigma = relpterr * std::sqrt(cFactorJERdown*cFactorJERdown-1);
			JERScaleFactorDOWN = (std::max(0., 1. + jet_jer_myran.Gaus(0,sigma)));
		}else{
			JERScaleFactorDOWN = 1.;
		}
	}
};






/******************************************************************************         
 * void Jet::SystematicPtShift(EventTree * evtr)                         *
 *                                                                            *         
 * Apply systematic shifts in jet pt                                          *
 *                                                                            *         
 * Input:  - the event tree (to access systematic SFs and MET info)      *
 * Output: -                                                                  *
 ******************************************************************************/
void Jet::SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met){


  float ptSF = 1.0;
  float jecvar = 1.0;
  float jesSF = evtr->Jet_JesSF -> operator[](iE);
  int evtNumber = evtr -> EVENT_event; 

  if (TMath::Abs(Eta())>3.0){ptSF=1.0;}
  else {

	  if (_jesUp){
		  //   ptSF = evtr->Jet_JesSFup->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
		  if(_jecsourceName != "NONE"){
			  jecvar = CalculateUncSource(jesSF, true, evtNumber);
			  ptSF = jecvar/jesSF;
		  }else{
			  ptSF = evtr->Jet_JesSFup->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
		  }


	  }
	  if (_jesDown){
		  // ptSF = evtr->Jet_JesSFdown->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
		  if(_jecsourceName != "NONE"){
			  jecvar = CalculateUncSource(jesSF, false, evtNumber);
			  ptSF = jecvar/jesSF;
		  }else{
			  ptSF = evtr->Jet_JesSFdown->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
		  } 
	  }
	  if (_jerUp){
		  ptSF = evtr->Jet_JerSFup->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
	  }
	  if (_jerDown){
		  ptSF = evtr->Jet_JerSFdown->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
	  }
  }  
//  float ptBefore = Pt();
  //Remove jet from MET
  met->SetPx(met->Px() + Px());
  met->SetPy(met->Py() + Py());
  //Apply the correction
  SetPx(Px()*ptSF);
  SetPy(Py()*ptSF);
  SetPz(Pz()*ptSF);
  
  //Propagate to MET
  met->SetPx(met->Px() - Px());
  met->SetPy(met->Py() - Py());







}
