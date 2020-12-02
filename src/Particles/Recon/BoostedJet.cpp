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
#include "SingleTopRootAnalysis/Particles/Recon/BoostedJet.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
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
static TRandom3 boostedjet_myran;
static TRandom3 boostedjet_jer_myran;

// Integrate classes into the Root system
ClassImp(BoostedJet)

/******************************************************************************
 * Jet::Jet()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
BoostedJet::BoostedJet() : Particle::Particle(),
	_prunedmass(0.0),_softdropmass(0.0),_softdropmasscorr(0.0),_tau1(0.0),_tau2(0.0),_tau3(0.0),_numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _jesUp(false), _jesDown(false), _jerUp(false), _jerDown(false), _hadronFlavour(-1), _tagged(0),
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
 BoostedJet::~BoostedJet()
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
BoostedJet::BoostedJet(const BoostedJet& other): Particle(other),
_prunedmass			(other.Getprunedmass()),
_softdropmass			(other.Getsoftdropmass()),
_softdropmasscorr			(other.Getsoftdropmasscorr()),
_tau1				(other.Gettau1()),
_tau2				(other.Gettau2()),
_tau3				(other.Gettau3()),
_numberOfConstituents		(other.GetnumberOfConstituents()), 
_hadronFlavour		        (other.GethadronFlavour()), 
_tagged				(other.IsTagged()),
_chargedMultiplicity		(other.GetchargedMultiplicity()),  
_bDiscriminator 		(other.GetbDiscriminator()), 
_mass 				(other.Getmass()), 
_uncorrPt 			(other.GetuncorrPt()), 
_JerSF                          (other.GetJerSF()),
_JerSFup                        (other.GetJerSFup()),
_JerSFdown                      (other.GetJerSFdown()),
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
BoostedJet::BoostedJet(const Particle& other): Particle(other),
				 _prunedmass(0.0),_softdropmass(0.0),_softdropmasscorr(0.0),_tau1(0.0),_tau2(0.0),_tau3(0.0),_numberOfConstituents(0), _hadronFlavour(-1), _chargedMultiplicity(0),  _bDiscriminator ( -999.0),  _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _tagged(0),
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
BoostedJet& BoostedJet::operator+=(const BoostedJet& other)
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
BoostedJet BoostedJet::operator+(const BoostedJet& other)
{
  Particle particleTemp = Particle::operator+(other);
  BoostedJet boostedjetTemp = particleTemp;
  return boostedjetTemp;

} //+

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Jet                                                                *
 ******************************************************************************/
BoostedJet& BoostedJet::operator=(const Particle& other)
{
  
  Particle::operator=(other);
  Setprunedmass(0.0),
  Setsoftdropmass(0.0),
  Setsoftdropmasscorr(0.0),
  Settau1(0.0),
  Settau2(0.0),
  Settau3(0.0),
  SetnumberOfConstituents(0), 
  SethadronFlavour(-1),
  SetTagged(0),
  SetchargedMultiplicity(0),  
  SetbDiscriminator ( -999.0), 
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
BoostedJet& BoostedJet::operator=(const BoostedJet& other)
{
  
  Particle::operator=(other);
  Setprunedmass				(other.Getprunedmass());
  Setsoftdropmass				(other.Getsoftdropmass());
  Setsoftdropmasscorr				(other.Getsoftdropmasscorr());
  Settau1				(other.Gettau1());
  Settau2				(other.Gettau2());
  Settau3				(other.Gettau3());
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SethadronFlavour	         	(other.GethadronFlavour());
  SetTagged				(other.IsTagged());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  Setmass 				(other.Getmass());
  SetJerSF                             (other.GetJerSF());
  SetJerSFup                            (other.GetJerSFup());
  SetJerSFdown                          (other.GetJerSFdown());

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
BoostedJet& BoostedJet::operator=(BoostedJet& other)
{
  Particle::operator=(other);
  Setprunedmass                         (other.Getprunedmass());
  Setsoftdropmass                         (other.Getsoftdropmass());
  Setsoftdropmasscorr                         (other.Getsoftdropmasscorr());
  Settau1                               (other.Gettau1());
  Settau2                               (other.Gettau2());
  Settau3                               (other.Gettau3());

  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SethadronFlavour	         	(other.GethadronFlavour());
  SetTagged			        (other.IsTagged());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  Setmass 				(other.Getmass());
   SetJerSF                              (other.GetJerSF());
  SetJerSFup                            (other.GetJerSFup());
  SetJerSFdown                          (other.GetJerSFdown());
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

void BoostedJet::SetCuts(TEnv * config)
{
  _maxEtaCut = 			config -> GetValue("ObjectID.BoostedJet.MaxEta",100.);
  _minPtCut = 			config -> GetValue("ObjectID.BoostedJet.MinPt",0.);
  _minCRPtCut = 		config -> GetValue("ObjectID.BoostedJet.CR.MinPt",0.);
  _closestLeptonCut = 		config -> GetValue("ObjectID.BoostedJet.LepCleanR",0.0);
  _jesUp = 			config -> GetValue("Systs.doJESUp",0);
  _jesDown = 			config -> GetValue("Systs.doJESDown",0);
  _jerUp = 			config -> GetValue("Systs.doJERUp",0);
  _jerDown = 			config -> GetValue("Systs.doJERDown",0);
  _bstar = 			config -> GetValue("ifbstar",0);
   _dataEra=                    config -> GetValue("_dataEra",0);
  _Elechannel = 		config -> GetValue("ifelechannel",0);
  _TT_CR = 			config -> GetValue("TT_CR",0);
  _QCD_CR = 			config -> GetValue("QCD_CR",0);
  _minMuonBoostedJetDetaR =     config -> GetValue("ObjectID.BoostedJet.MuonDeltaRMin",0.0);
  _minprunedmass = 		config -> GetValue("ObjectID.BoostedJet.MinPrunedMass",0.0);
  _maxprunedmass = 		config -> GetValue("ObjectID.BoostedJet.MaxPrunedMass",999.9);
  _minpuppisoftdropmass= 	config -> GetValue("ObjectID.BoostedJet.MinPuppiSofeDropMass",0.0);
  _maxpuppisoftdropmass= 	config -> GetValue("ObjectID.BoostedJet.MaxPuppiSofeDropMass",0.0);
  _minsoftdropmass = 		config -> GetValue("ObjectID.BoostedJet.MinSoftdropMass",0.0);
  _maxsoftdropmass = 		config -> GetValue("ObjectID.BoostedJet.MaxSoftdropMass",999.9);
  _tau21_2016 = 			config -> GetValue("ObjectID.BoostedJet.Tau21.2016",0.0);
  _tau21_2017 = 			config -> GetValue("ObjectID.BoostedJet.Tau21.2017",0.0);
  _tau21_2018 = 			config -> GetValue("ObjectID.BoostedJet.Tau21.2017",0.0);
  _tau32 = 			config -> GetValue("ObjectID.BoostedJet.Tau32",0.0);
  _minBJetDetaR=    	     config -> GetValue("ObjectID.BoostedJet.BoostedDeltaRMin",-999.0);

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

Bool_t BoostedJet::Fill( double myJESCorr, double myJERCorr, std::vector<Muon>& selectedMuons, std::vector<Electron>& selectedElectrons, std::vector<Jet>& selectedBjets, EventTree *evtr, Int_t iE, TLorentzVector * met, bool isMC,TString BoostedjetType)
{
   int eventNumber = evtr -> EVENT_event;
  Double_t boostedjetPt, boostedjetEta,boostedjetPhi,boostedjetE, boostedjetCharge, boostedjetM,prunedmass,softdropmass,tau1,tau2,tau3,boostedjet_Uncorr_pt,boostedjet_Uncorr_E,boostedjet_JesSF,boostedjet_JerSF,boostedjet_pt,energy,jerSF,boostedjet_puppi_softdrop_masscorr;
  boostedjetPt     = evtr -> BoostedJet_pt     -> operator[](iE);
  boostedjetEta    = evtr -> BoostedJet_eta    -> operator[](iE);
  boostedjetPhi    = evtr -> BoostedJet_phi    -> operator[](iE);
  boostedjetE      = evtr -> BoostedJet_energy -> operator[](iE);
  prunedmass       = evtr -> BoostedJet_pruned_mass -> operator[](iE);  
  softdropmass     = evtr -> BoostedJet_puppi_softdrop_mass-> operator[](iE);
  //softdropmass     = evtr -> BoostedJet_softdrop_mass-> operator[](iE);
   tau1     	   = evtr -> BoostedJet_puppi_tau1-> operator[](iE);
   tau2     	   = evtr -> BoostedJet_puppi_tau2-> operator[](iE);
  tau3     	   = evtr -> BoostedJet_puppi_tau3-> operator[](iE);
 
// tau1     	   = evtr -> BoostedJet_tau1-> operator[](iE);
//tau2     	   = evtr -> BoostedJet_tau2-> operator[](iE);
 // tau3     	   = evtr -> BoostedJet_tau3-> operator[](iE);

  boostedjet_Uncorr_pt     = evtr -> BoostedJet_Uncorr_pt     -> operator[](iE);
  boostedjet_Uncorr_E      = (evtr -> BoostedJet_energy -> operator[](iE))/(evtr -> BoostedJet_pt -> operator[](iE))*boostedjet_Uncorr_pt;
  boostedjet_JesSF     = evtr -> BoostedJet_JesSF     -> operator[](iE);
  jerSF     = evtr -> BoostedJet_JerSF     -> operator[](iE);
  boostedjet_pt = boostedjet_Uncorr_pt*boostedjet_JesSF*boostedjet_JerSF;
  energy = (boostedjet_Uncorr_pt/boostedjetPt)*boostedjetE*boostedjet_JesSF*boostedjet_JerSF;
  boostedjet_puppi_softdrop_masscorr=evtr -> BoostedJet_puppi_softdrop_masscorr -> operator[](iE);
  SetJerSF(jerSF);
  SetJerSFup(evtr->BoostedJet_JerSFup->operator[](iE));
  SetJerSFdown(evtr->BoostedJet_JerSFdown->operator[](iE));
  SetPtEtaPhiE(boostedjetPt,boostedjetEta,boostedjetPhi,boostedjetE);

  Setprunedmass                         (evtr -> BoostedJet_pruned_mass -> operator[](iE));
  Setsoftdropmass                         (evtr -> BoostedJet_puppi_softdrop_mass -> operator[](iE));
  Setsoftdropmasscorr                         (evtr -> BoostedJet_puppi_softdrop_masscorr -> operator[](iE));
  Settau1				(evtr -> BoostedJet_puppi_tau1-> operator[](iE));
  Settau2				(evtr -> BoostedJet_puppi_tau2-> operator[](iE));
  Settau3				(evtr -> BoostedJet_puppi_tau3-> operator[](iE));
// Settau1				(evtr -> BoostedJet_tau1-> operator[](iE));
// Settau2				(evtr -> BoostedJet_tau2-> operator[](iE));
 // Settau3				(evtr -> BoostedJet_tau3-> operator[](iE));


  SetnumberOfConstituents		(evtr -> BoostedJet_numberOfConstituents     	-> operator[](iE));
  SetchargedMultiplicity		(evtr -> BoostedJet_chargedMultiplicity     	-> operator[](iE)); 
  SetbDiscriminator 			(evtr -> BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags     	-> operator[](iE));
  Setmass 				(evtr -> BoostedJet_mass     			-> operator[](iE));
  SetuncorrPt 				(evtr -> BoostedJet_Uncorr_pt     		-> operator[](iE));
  SetneutralHadEnergyFraction		(evtr -> BoostedJet_neutralHadEnergyFraction	-> operator[](iE));
  SetchargedHadronEnergyFraction 	(evtr -> BoostedJet_chargedHadronEnergyFraction-> operator[](iE));
  SetchargedEmEnergyFraction		(evtr -> BoostedJet_chargedEmEnergyFraction    -> operator[](iE));
  SetmuonEnergyFraction			(evtr -> BoostedJet_muonEnergyFraction     	-> operator[](iE));
  SetelectronEnergy			(evtr -> BoostedJet_electronEnergy     	-> operator[](iE));
  SetphotonEnergy			(evtr -> BoostedJet_photonEnergy     		-> operator[](iE));
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




  // Now we want to do the JER and JES systematic adjustments to the jet. This also requires correcting the MET.




  /////////////////////////////////////////////////////////////////////////
  //  // Jet Cleaning
  //    /////////////////////////////////////////////////////////////////////////
  //    //  cout<<"we are going to jet cleaning "<<endl;
  //
  Bool_t passesCleaning = kTRUE;
  Bool_t selectMuon = kFALSE;
  Double_t closestLepton = 999.;
  TLorentzVector closedmuon(0,0,0,0);
  TLorentzVector tempjet(0,0,0,0);
  TLorentzVector jet(0,0,0,0);
  jet.SetPtEtaPhiE(boostedjet_Uncorr_pt,Eta(),Phi(),boostedjet_Uncorr_E);  
  for (auto const & ele : selectedElectrons){
	  if (ele.DeltaR(*this) < _minMuonBoostedJetDetaR)
	  {
		  jet=jet-ele;
	  }
  }
  for (auto const & mu : selectedMuons){
	  selectMuon = kTRUE;
	  if (mu.DeltaR(*this) < _minMuonBoostedJetDetaR) 
	  {
		  jet=jet-mu;
	  }
  }
  SetPtEtaPhiE(jet.Pt()*boostedjet_JesSF*jerSF,jet.Eta(),jet.Phi(),jet.E()*boostedjet_JesSF*jerSF);  
  SetClosestLep(closestLepton);

  if (_jesUp || _jesDown || _jerUp || _jerDown) SystematicPtShift(evtr, iE, met);  
  /////////////////////////////////////////////////////////////////////////
  // Jet ID
  /////////////////////////////////////////////////////////////////////////
  
  Bool_t LowEtaID =kTRUE;
  Bool_t MediumEtaID= kTRUE;
  Bool_t HighEtaID = kTRUE;

 if(_dataEra==2016){
    LowEtaID = (neutralHadEnergyFraction()<0.99 && neutralEmEmEnergyFraction()<0.99 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0 && chargedEmEnergyFraction() < 0.99) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
   // LowEtaID = (neutralHadEnergyFraction()<0.90 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0 && chargedEmEnergyFraction() < 0.99) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
    MediumEtaID = (neutralEmEmEnergyFraction()>0.01 && neutralHadEnergyFraction()<0.98 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 );
    HighEtaID = (neutralEmEmEnergyFraction()<0.90 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 );
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




Double_t closestBJet= 999.;
 Bool_t passBJetOverlap = kTRUE;
for (auto const & bjet :selectedBjets ){
            if (bjet.DeltaR(*this) < closestBJet) closestBJet= bjet.DeltaR(*this);
              }
if(closestBJet<_minBJetDetaR)passBJetOverlap= kFALSE ;
//if(closestBJet< 0.8)passBJetOverlap= kFALSE ;






  //cout<<"softdropmass from boostedjet: "<<softdropmass<<endl;
  Double_t tau21 = tau2/tau1;
  Double_t tau32 = tau3/tau2;
  //cout<<"tau21 = "<<tau21 <<endl;
  Bool_t passmasswindow=kTRUE;
  if(_TT_CR){
	  passmasswindow =_minsoftdropmass<softdropmass&& softdropmass< _maxsoftdropmass;}
  else{	
	  passmasswindow =_minpuppisoftdropmass <boostedjet_puppi_softdrop_masscorr && boostedjet_puppi_softdrop_masscorr< _maxpuppisoftdropmass;}
  Bool_t passtau = kTRUE;
  if(_TT_CR){
	  passtau = tau32<_tau32;}
  else if(_QCD_CR){
	  if(_dataEra==2016){passtau =tau21>_tau21_2016;}
	  if(_dataEra==2017){passtau =tau21>_tau21_2017;}
	  if(_dataEra==2018){passtau =tau21>_tau21_2018;}
  }
  else{
	  if(_dataEra==2016){   passtau	= tau21<_tau21_2016;}
	  if(_dataEra==2017){   passtau	= tau21<_tau21_2017;}
	  if(_dataEra==2018){   passtau	= tau21<_tau21_2018;}
  }

  //if (passPt && passEta  && passmasswindow && passtau &&passesJetID &&passBJetOverlap) return kTRUE;
   if("Baseline"== BoostedjetType) return (passPt && passEta  && passesJetID);
   else return (passPt && passEta  && passmasswindow && passtau &&passesJetID &&passBJetOverlap);
  return kFALSE;

} //Fill()




/******************************************************************************         
 *  *  * void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
 *   *   *                                                                            *         
 *    *    * Calculate JEC uncertainty source                                           *
 *     *     *                                                                            *         
 *      *      * Input:  - SourceName, SystUp, txtfilenmame                                 # 
 *       *       * Output: -                                                                  *
 *        *        ******************************************************************************/
float BoostedJet::CalculateUncSource(Double_t jesSF, bool jesup, int eventNumber ){
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



void BoostedJet::SetJECUncSource(TEnv * config, TString jecsourceName){
	_sourcefilename = config->GetValue("Systs.JecSourceFile","config/weights/2018data/Regrouped_Autumn18_V19_MC_UncertaintySources_AK4PFchs.txt");
	resolution = JME::JetResolution(config->GetValue("Systs.AK8JerResFile","config/weights/2018data/Autumn18_V7_MC_PtResolution_AK8PFchs.txt"));
	//cout<<"resolution config name :"<<config->GetValue("Systs.JerResFile","config/weights/data2018/Autumn18_V7_MC_PtResolution_AK4PFchs.txt")<<endl; 
	res_sf = JME::JetResolutionScaleFactor(config->GetValue("Systs.AK8JerSFFile","config/weights/2018data/Autumn18_V7_MC_SF_AK8PFchs.txt"));
	_jecsourceName = jecsourceName;
	std::cout<< " set jecsource " << jecsourceName << " _jecsource " << _jecsourceName << std::endl;
	//_sourcename = config->GetValue("FlavorQCD");
	if(_jecsourceName != "NONE"){
		jecAK4PFchsMCUncSource_   =  new JetCorrectionUncertainty(*(new JetCorrectorParameters(_sourcefilename.Data(), _jecsourceName.Data())));
	}
};



/******************************************************************************         
 * * void Jet::CalculateUncSource(TString JECfile, TString SourceName, Bool_t SystUp)*
 * *                                                                            *         
 * * Calculate JEC uncertainty source                                           *
 * *                                                                            *         
 * * Input:  - SourceName, SystUp, txtfilenmame                                 # 
 * * Output: -                                                                  *
 * ******************************************************************************/
void BoostedJet::Getjer(float rhoJER, bool isgenmatch, TLorentzVector genjet, float &JERScaleFactor, float &JERScaleFactorUP, float &JERScaleFactorDOWN, int nEvent){
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
                double conesize = 0.8;
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
                        JERScaleFactor = (std::max(0., 1. + boostedjet_jer_myran.Gaus(0,sigma)));
                }else{
                        JERScaleFactor = 1.;
                }
                if(cFactorJERup>1){
                        double sigma = relpterr * std::sqrt(cFactorJERup*cFactorJERup-1);
                        JERScaleFactorUP = (std::max(0., 1. + boostedjet_jer_myran.Gaus(0,sigma)));
                }else{
                        JERScaleFactorUP = 1.;
                }
                if(cFactorJERdown>1){
                        double sigma = relpterr * std::sqrt(cFactorJERdown*cFactorJERdown-1);
                        JERScaleFactorDOWN = (std::max(0., 1. + boostedjet_jer_myran.Gaus(0,sigma)));
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
void BoostedJet::SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met){


  //  std::cout << "syst correct" << std::endl;
  float ptSF = 1.0;
 float jecvar = 1.0;
  float jesSF = evtr->BoostedJet_JesSF -> operator[](iE);
  int evtNumber = evtr -> EVENT_event;
  if (TMath::Abs(Eta())>3.0){ptSF=1.0;}
  else {

	  if (_jesUp){
		  if(_jecsourceName != "NONE"){
			  jecvar = CalculateUncSource(jesSF, true, evtNumber);
			  ptSF = jecvar/jesSF;
		  }else{
			  ptSF = evtr->BoostedJet_JesSFup->operator[](iE)/evtr->BoostedJet_JesSF->operator[](iE);
		  }


	  }
	  if (_jesDown){
		  if(_jecsourceName != "NONE"){
			  jecvar = CalculateUncSource(jesSF, false, evtNumber);
			  ptSF = jecvar/jesSF;
		  }else{
			  ptSF = evtr->BoostedJet_JesSFdown->operator[](iE)/evtr->BoostedJet_JesSF->operator[](iE);
		  }
	  }
	  if (_jerUp){
		  ptSF = evtr->BoostedJet_JerSFup->operator[](iE)/evtr->BoostedJet_JerSF->operator[](iE);
	  }
	  if (_jerDown){
		  ptSF = evtr->BoostedJet_JerSFdown->operator[](iE)/evtr->BoostedJet_JerSF->operator[](iE);
	  }
  }






  //  float ptBefore = Pt();
  //Remove jet from MET
  met->SetPx(met->Px() + Px());
  met->SetPy(met->Py() + Py());
  //Apply the correction
  //  std::cout << Px() << " " << Py() << " " << Pt() << std::endl;
  SetPx(Px()*ptSF);
  SetPy(Py()*ptSF);
  SetPz(Pz()*ptSF);
  //std::cout << Px() << " " << Py() << " " << Pt() << std::endl << std::endl;
  
  //Propagate to MET
  met->SetPx(met->Px() - Px());
  met->SetPy(met->Py() - Py());

}
