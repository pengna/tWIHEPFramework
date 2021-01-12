/******************************************************************************
 * EventContainer.cpp                                                         *
 *                                                                            *
 * Read in variables from EventTree and put them into an Object               *
 *                                                                            *
 * Public Members of EventContainer    class                                  *
 *    EventContainer()                  -- Default Constructor                *
 *    ~EventContainer()                 -- Destructor                         *
 *    GetSourceName()                   -- Get name of source being run on    *
 *    GetSourceNumber()                 -- Get number of source being run on  *
 *    GetTargetTopMass()                -- Get Top Quark Mass                 *
 *    SetSourceName()                   -- Set name of source being run on    *
 *    SetSourceNumber()                 -- Set number of source being run on  *
 *    SetTargetTopMass()                -- Set Top Quark Mass                 *
 *    Initialize()                      -- Initialize class                   *
 *    MakeTopQuarks()                   -- Reconstruct Top in several ways    *
 *    GetNextEvent()                    -- Set up particles for next event    *
 *    SetEventCount()                   -- Set counter for specific event     *
 *    GetCollectionTree()               -- Get the collection tree            *
 *    GetEventTree()                    -- Get the event tree                 *
 *    GetTruthTree()                    -- Get the truth tree                 *
 *    GetTruthAllTree()                    -- Get the truth tree              *
 *    GetTriggerTree()                  -- Get the trigger tree               *
 *    GetFastSimTree()                  -- Get the fastsim tree               *
 *    GetDebugLevel()                   -- Get debug level                    *
 *    SetDebugLevel()                   -- Set debug level                    *
 *    SetDoTrigger()                    -- Set if trigger tree                *
 *    SetDoTruthAll()                   -- Set if TruthAll tree               *
 *    SetDoTruth()                      -- Set if Truth tree                  *
 *    DoTrigger()                       -- If trigger tree                    *
 *    DoTruthAll()                      -- If TruthAll tree                   *
 *    DoTruth()                         -- If Truth tree                      *
 *    GetEventWeight()                  -- Get Event Weight                   *
 *    GetOutputEventWeight()            -- Get Output EventWeight             *
 *    GetTreeEventWeight()              -- Get Tree Event Weight              *
 *    GetGlobalEventWeight()            -- Get Global EventWeight             *
 *    SetGlobalEventWeight()            -- Set global event weight            *
 *    SetOutputEventWeight()            -- Set output event weight            *
 *    GetConfig()                       -- Get Configuration                  *
 *    ApplyJESShift()                   -- scale jet energies                 * 
 *                                                                            *
 *    Int_t ReadEvent()                 -- Create TLorentz Vectors            *
 *    Bool_t CreateFinalState()         -- Create final state particles       *
 *    Int_t runNumber                   -- Run number from the root tree      *
 *    Int_t eventNumber                 -- Event number from the root tree    *
 *    vector<Electron> electrons        -- Electron Vector                    *
 *    vector<Muon>     muons            -- Muon Vector                        *
 *    vector<Muon>     isolatedmuons    -- Isolated Muon Vector               *
 *    vector<Muon>     unisolatedmuons  -- UnIsolated Muon Vector             *
 *    vector<Tau>      taus             -- Tau Vector                         *
 *    vector<Jet>      jets             -- Jet Vector                         *
 *    vector<Jet>      taggedJets       -- taggedJet Vector                   *
 *    vector<Jet>      untaggedJets     -- untaggedJet Vector                 *
 *    vector<Jet>       bLabeledJets    -- jet id'ed with MC B quark          *
 *    vector<Jet>       cLabeledJets    -- jet id'ed with MC C quark          *
 *    vector<Jet>      tauLabeledJets   -- jet id'ed with MC tau              *
 *    vector<Jet> lightQuarkLabeledJets -- jet not id'ed with MC B, C, or tau *
 *    vector<MCParticle> MCParticles    -- MC Particle Vector                 *
 *    vector<MCMuon>   MCmuons          -- MC Muon Vector                     *
 *    vector<MCElectron>   MCElectrons  -- MC Electron Vector                 *
 *    vector<MCTau>   MCTaus            -- MC Tau Vector                      *
 *    vector<MCJet>   MCJets            -- MC Jet Vector                      *
 *    vector<MCJet>   MCBJets           -- MC BJet Vector                     *
 *    vector<MCJet>   MCCJets           -- MC CJet Vector                     *
 *    vector<MCJet>   MCLightQuarkJets  -- MC LightJetJet Vector              *
 *    vector<MCTop>   MCTops            -- MC Top Vector                      *
 *    vector<MCW>     MCWs              -- MC W Vector                        * 
 *    vector<MCAllParticle> MCAllParticles -- MCAllParticle Vector            *
 *    vector<MCAllMuon> MCAllMuons      -- MCAllMuon Vector                   *
 *    vector<MCAllElectron> MCAllElectrons -- MCAll Electron Vector           *
 *    vector<MCAllJet> MCAllJets         -- MCAll Jet Vector                  *
 *    vector<MCAllTau> MCAllTaus         -- MCAll Tau Vector                  *
 *    vector<MCAllChargedPion> MCAllChargedPions -- MCAll Charged Pion Vector *
 *    vector<MCAllChargedK> MCAllChargedKs -- MCAll Charged K Vector          *
 *                                                                            *
 * Protected Members of EventContainer class                                  *
 *    Int_t debugLevel                  -- Debug level                        *
 *    TEnv _config                      -- Used to read configuration         *
 *                                                                            *
 * Private Members of EventContainer class                                    *
 *    Double_t _targetTopMass           -- Target top mass                    *
 *    CollectionTree *_collectionTree   -- Collection tree                    *
 *    EventTree *_eventTree             -- Event tree                         *
 *    TruthTree *_thruthTree            -- Truth tree                         *
 *    Int_t    _eventCount              -- Location in event chain            *
 *    TString  _sourceName              -- Name of source being read          *
 *    TString _sourceNumber             -- Number of source being read        *
 *    Double_t _globalEventWeight       -- Global Event Weight                *
 *    Double_t _treeEventWeight         -- Tree Event Weight                  *
 *    Double_t _outputEventWeight       -- Output Event Weight                *
 *                                                                            *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutJetN"                  *
 *                                                                            *
 * Private Data Members of CutJetN                                            *
 *    myTH1F* _hNJetsBefore              -- Hist of Num of jets before cuts   *
 *    myTH1F* _hNJetsAfter               -- Hist of Num of jets before cuts   *
 *    Int_t _nJetsMin;                   -- Minimum number of jets to require *
 *    Int_t _nJetsMax;                   -- Maximum number of jets allowed    *
 *                                                                            *
 * History                                                                    *
 *      16 June 2015 - Created by Huaqiao ZHANG(zhanghq@ihep.ac.cn) for CMS   *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include <iostream>
#include <string>
#include <fstream>

#include <TLeaf.h>

#include "SingleTopRootAnalysis/Base/Histograms/utils.hpp"

using namespace std;
//using namespace Analysis;
// Integrate classes into the Root system
ClassImp(EventContainer)

//-----------------------------------------------------------------------------------------
// Get the next event.
// It reads in the next event from the current chain and 
// Creates final state particles.
// This method returns -1 when there are no more events.
// It returns the total event count if successful.
//
Int_t EventContainer::GetNextEvent(){

  //cout << "<EventContainer::GetNextEvent Start> " << endl;
  Int_t countOffSet=0;
  if (! DoFastSim()   && _eventTree      == NULL) return -1;
  if (DoTruth()       && _truthTree      == NULL) return -1;
  if (DoFastSim()     && _fastSimTree    == NULL) return -1;

  // now Set things up
  Int_t bytesReadTru;
  Int_t bytesReadEv;

  // ************************
  // FastSim
  // ************************
  if(DoFastSim()) {
    bytesReadEv = _fastSimTree->fChain->GetEntry(_eventCount);
  } else {
    // normal running, get the next eventin the event tree
    bytesReadEv = _eventTree->fChain->GetEntry(_eventCount);
  } 

  if(0 == bytesReadEv) {
    if(DoFastSim()){
      cout << "<EventContainer> Read 0 bytes from fast sim tree." << endl;
      return -1;
    }else  {
      cout << "<EventContainer> Read 0 bytes from event tree." << endl;
      return -1;
    }
  } //if
  // ************************
  // Truth
  // ************************
  if(DoTruth()) {
    Int_t bytesReadTruth = _truthTree->fChain->GetEntry(_eventCount);
    if(0 == bytesReadTruth) {
    cout << "<EventContainer> Read 0 bytes from truth tree." << endl;
    return -1;
    } //if
  } //if
  
  // ************************
  // Skimming
  // ************************
  if(DoSkim()){
    Int_t bytesReadTri =0;
    bytesReadTri = _eventTree->fChain->GetEntry(_eventCount);
    if(0 == bytesReadTri) {
      cout << "<EventContainer> Read 0 bytes from LooseTopInputs tree." << endl;
      return -1;
    }
    if (_truthTree!=NULL){
      bytesReadTri = _truthTree->fChain->GetEntry(_eventCount);
      if(0 == bytesReadTri) {
	cout << "<EventContainer> Read 0 bytes from Truth tree." << endl;
	return -1;
      }
    }

  }

  // Create 4-vectors
  //cout << "<EventContainer::GetNextEvent::ReadEvent Start> " << endl;
  ReadEvent();         //The object selections and corrections are here
  //cout << "<EventContainer::GetNextEvent::CreateFinalState Start> " << endl;
  CreateFinalState();  // the event selections are here
  //cout << "<EventContainer::GetNextEvent::MakeTopQuarks Start> " << endl;
  MakeTopQuarks();
  //cout << "<EventContainer::GetNextEvent::MakeTopQuarks End> " << endl;
  // and finally increment the internal event counter
  _eventCount++;
  if(GetIsFirstEvent() == true) SetIsFirstEvent(false); // not the first event
  return(countOffSet + _eventCount-1);
} // end of GetNextEvent
  
/******************************************************************************
 * EventContainer::EventContainer()                                           *
 *                                                                            *
 * Default Constructor                                                        *
 * Initializes many private data members                                      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
EventContainer::EventContainer(): 
  //_collectionTree(NULL), 
  _eventTree(NULL), _truthTree(NULL), 
  _eventCount(0),   _targetTopMass(175.),
  _debugLevel(0),   _doFastSim(false),_doSkim(false),
  _sourceName("NONE"),
  _globalEventWeight(1.), _treeEventWeight(1.), _outputEventWeight(1.),_EventPileupWeight(-1),
  _EventPileupMinBiasUpWeight(-1),_EventPileupMinBiasDownWeight(-1),
  _config("Configuration"), _JESconfig("JESConfiguration"),_jesError(0.), _jesShift(0), _bTagAlgo("default"), _bTagCut(999), _misTagCut(999), jeteoverlap(kFALSE),closeindex(999),ejordr(999), bestjetdr(999), _isFirstEvent(true), isSimulation(kTRUE), _badJetEvent(kFALSE),  _celloutShift(0),_softjetShift(0),_pileupShift(0),_larShift(0),_metShift(0), _JESconfigread(false),_jesUShift(0),_jesPtShift(0),_jesEtaShift(0),_useUnisolatedLeptons(kFALSE),_trigID(0)
{
 
} //EventContainer()


/******************************************************************************
 * EventContainer::~EventContainer()                                          *
 *                                                                            *
 * Destructor                                                                 *
 * Sets pointers to NULL                                                      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
EventContainer::~EventContainer()
{

  // Event Tree
  if(_eventTree) delete _eventTree;
  _eventTree = NULL;

  // Truth Tree
  if(_truthTree) delete _truthTree;
  _truthTree = NULL;

  // Fast Sim Tree
  // This causes a seg fault - don't know why
  //if(_fastSimTree) delete _fastSimTree;
  //_fastSimTree = NULL;

} //~EventContainer()

/******************************************************************************
 * void EventContainer::Initialize()                                          *
 *                                                                            *
 * Initialize class                                                           *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
//void EventContainer::Initialize(CollectionTree* collectionTree,EventTree* eventTree, TruthTree* truthTree)
//
void EventContainer::Initialize( EventTree* eventTree, TruthTree* truthTree)
{

  _eventTree       = eventTree;
  _truthTree       = truthTree;
//  // now Set up the internal variables:
  SetIsFirstEvent(true);
  actualIntPerXing = 0;
  averageIntPerXing = 0 ;
//  Pvtxall_n = -999;
//  isSimulation = kTRUE;

  _eventCount = 0;
  electrons.clear();
  tightElectrons.clear();
  vetoElectrons.clear();
  ptetaElectrons.clear();
  isolatedElectrons.clear();
  unIsolatedElectrons.clear();
  muons.clear();
  tightMuons.clear();
  tightwoIsoMuons.clear();
  vetoMuons.clear();
  ptetaMuons.clear();
  isolatedMuons.clear();
  unIsolatedMuons.clear();
  taus.clear();
  jets.clear();
  Beforeak8jetcleanjets.clear();
  taggedBeforeak8jetcleanjets.clear();
  untaggedBeforeak8jetcleanjets.clear();
  boostedjets.clear();
  allboostedjets.clear();
  alljets.clear();
  taggedJets.clear();
  unTaggedJets.clear();
  bLabeledJets.clear();
  cLabeledJets.clear();
  tauLabeledJets.clear();
  lightQuarkLabeledJets.clear();
  neutrinos.clear();
  
  // Check for any systematic uncertainties we may be calculating
  _metShift = _config.GetValue("Systs.metShift",0);
  _channelName = _config.GetValue("ChannelName","");

  return;
} //Initialize()

/******************************************************************************
 * void EventContainer::SetupObjectDefinitions(TEnv config)                   *
 *                                                                            *
 * Sets up the different object definitions for each object                   *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void EventContainer::SetupObjectDefinitions(){
  newMuon.SetCuts(GetConfig(),"Tight");
  newMuon.SetCuts(GetConfig(),"PtEtaCut");
  newMuon.SetCuts(GetConfig(),"All");
  newMuon.SetCuts(GetConfig(),"UnIsolated");
  newMuon.SetCuts(GetConfig(),"Veto");

  newElectron.SetCuts(GetConfig(),"Tight");
  newElectron.SetCuts(GetConfig(),"All");
  newElectron.SetCuts(GetConfig(),"Veto");
  newElectron.SetCuts(GetConfig(),"UnIsolated");

  newJet.SetCuts(GetConfig());
  newJet.SetJECUncSource(GetConfig(), _JecSourceName);
  newBoostedJet.SetCuts(GetConfig());
  newBoostedJet.SetJECUncSource(GetConfig(), _JecSourceName);

}

/******************************************************************************
 * void EventContainer::SetUseUnisolatedLeptons(                              *
 *           Bool_t useUnisolatedLeptons, int whichtrig)                      *
 *                                                                            *
 * Used to switch between QCD estimation and non. This is important for       *
 * the jet cleaning algorithm						      *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/

void EventContainer::SetUseUnisolatedLeptons(const Bool_t& useUnisolatedLeptons, int whichtrig){
  _useUnisolatedLeptons = useUnisolatedLeptons;
  _trigID = whichtrig;
  electronsToUsePtr = &tightElectrons;
  electronsToUsePtr2D = &unIsolatedElectrons;
  muonsToUsePtr = &tightMuons;
  muonsToUsePtr2D = &unIsolatedMuons;
  //electronsToUsePtr = &electrons;
 // muonsToUsePtr = &muons;
  boostedjetsToUsePtr = &boostedjets;
  allboostedjetsToUsePtr = &allboostedjets;
  boostedjetsToUsePtrjetaverlap = &basedboostedjets;
  jetsToUsePtr = &alljets;
  //jetsToUsePtr = &taggedJets;
  taggedjetsToUsePtr = &taggedJets;
  taggedjetsToUsePtrBoostedjetoverlap = &taggedBeforeak8jetcleanjets;
  if (_trigID == 0 && _useUnisolatedLeptons){
    electronsToUsePtr = &unIsolatedElectrons;
  }
  else if (_trigID == 1 && useUnisolatedLeptons){
    muonsToUsePtr = &unIsolatedMuons;
  }

mcParticlesPtr = &MCParticles;
mcTopsPtr = &MCTops;
  //For the synch excercise we want it to always be tight leptons, so I'm gonna add here the ability to just make it all tight.
  //  if (GetChannelName() == "ee" || GetChannelName() == "emu" || GetChannelName() == "mumu"){
  // }
} //SetUseUnisolatedLeptons

/******************************************************************************
 * void EventContainer::InitializeFastSim()                                   *
 *                                                                            *
 * Initialize class                                                           *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
//void EventContainer::InitializeFastSim(FastSimTree* fsTree, TruthTree* truthTree)
//{
//  return;
//} //Initialize()


/******************************************************************************
 * Int_t EventContainer::ReadEvent()                                          *
 *                                                                            *
 * Fill objects with event info                                               *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Return 0                                                           *
 ******************************************************************************/
Int_t EventContainer::ReadEvent()
{
  // Set the event weight if there is any
  if(DoFastSim()) {
    // Will have to be updated when we have a fast sim tree
    _treeEventWeight = _fastSimTree -> eventWeight;
    runNumber   = _fastSimTree      -> runNumber;
    eventNumber = _fastSimTree      -> eventNumber;
    larError = 5;
    actualIntPerXing = 0;
    averageIntPerXing = 0 ;
    distns = -999;
    distbunch = -999;
    bcid = -999;
    safejetevent= -999;
    safejeteventup= -999;
    safejeteventdown= -999;
  }  else {
    _treeEventWeight = 1.0;
    runNumber          = _eventTree -> EVENT_run;
    eventNumber        = _eventTree -> EVENT_event;
    actualIntPerXing   = 1;//_eventTree -> 
    averageIntPerXing  = 1;//_eventTree -> 
    bcid               = 1;//_eventTree -> 
    distns = -999;
    distbunch = -999;
    safejetevent= -999;
    safejeteventup= -999;
    safejeteventdown= -999;
  }


cout<<"(Eventcontainer.cpp)Check From Event Container loop : Event number(C) is "<<eventNumber<<"Event Weight = "<<GetEventWeight()<<"Pile Up Weight ="<<GetEventPileupWeight()<<" Top pT Weigth = "<<GetEventTopptreweight()<<endl;
//cout<<"(Eventcontainer.cpp)Check From Event Container loop : Event number(C) is "<<eventNumber<<"Event Weight = "<<EventWeight()<<"Pile Up Weight ="<<EventPileupWeight()<<" Top pT Weigth = "<<EventTopptreweight()<<endl;
  //  isSimulation = kTRUE;
  _badJetEvent = kFALSE;

  // Reset all of the particle vectors
  electrons.clear();
  tightElectrons.clear();
  vetoElectrons.clear();
  ptetaElectrons.clear();
  isolatedElectrons.clear();
  unIsolatedElectrons.clear();

  muons.clear();
  tightMuons.clear();
  tightwoIsoMuons.clear();
  vetoMuons.clear();
  ptetaMuons.clear();
  isolatedMuons.clear();
  unIsolatedMuons.clear();

  taus.clear();

  jets.clear();
  boostedjets.clear();
  basedboostedjets.clear();
  allboostedjets.clear();
  alljets.clear();
  taggedJets.clear();
  unTaggedJets.clear();
  bLabeledJets.clear();
  cLabeledJets.clear();
  tauLabeledJets.clear();
  lightQuarkLabeledJets.clear();
  neutrinos.clear();

 MCParticles.clear();
  MCMuons.clear();
  MCElectrons.clear();
  MCTaus.clear();
  MCJets.clear();
  MCBJets.clear();
  MCCJets.clear();
  MCLightQuarkJets.clear();
  MCLightJets.clear();
  MCTops.clear();
  MCWs.clear();
  MCZs.clear();
  MCPhotons.clear();
  MCNeutrinos.clear();

  ////////////////////////////////////////////////////
  // Fill objects
  ////////////////////////////////////////////////////

  bool useObj;  // decide whether to transfer this into our list of objects 

  //No cuts on MC particles, yet
  if(DoTruth()){
  } //if DoTruth
  // ***************************************************
  // Then from either the reconstruction tree or fast sim
  if(DoFastSim()) {
  } // end of filling from fastsim tree
  // ***************************************************
  // Reconstructed
  else {
    //    isSimulation = _eventTree->isSimulation; // Why is this always set to true?!?
    _badJetEvent = kFALSE;
    //must be done for each event
    // Electrons, Jets, Muons, missingEt
    Electrons_tlv.clear();
    Electrons_tlv_scaled.clear();
    Jets_tlv_scaled.clear();
    Jets_tlv.clear();
    Jets_JESup_tlv.clear();
    Jets_emscale_tlv.clear();
    Muons_tlv_scaled.clear();
    Muons_tlv.clear();
    Muons_ms_tlv_scaled.clear();
    Muons_ms_tlv.clear();
    Muons_track_tlv_scaled.clear();
    Muons_track_tlv.clear();
    missingEt = -888;
    ///////////////////////////////////////////  
    // Number of vertices
    ///////////////////////////////////////////  
    int ncount = 0;

    ///////////////////////////////////////////
    // Fill MET info 
    ///////////////////////////////////////////
    // Should I update this to use PUPPI information?!?
    missingEt = _eventTree->Met_type1PF_pt;
    missingEx = _eventTree->Met_type1PF_px;
    missingPhi = _eventTree->Met_type1PF_phi;
    missingEy = _eventTree->Met_type1PF_py;

    missingEt_xy = _eventTree->Met_type1PF_pt;
    missingEx_xy = _eventTree->Met_type1PF_px;
    missingPhi_xy = _eventTree->Met_type1PF_phi;
    missingEy_xy = _eventTree->Met_type1PF_py;

    passesMETFilters = _eventTree->Flag_METFilters;

    //Fill pvtx information
    nPvtx = _eventTree->nBestVtx;
    trueInteractions = _eventTree->trueInteractions;
    npuVertices = _eventTree->npuVertices;
    
    // Systematic variations on met to be re-calculated here.
    if (_metShift != 0){
      float oldEt = missingEt;
      missingEt = (_metShift == 1) ? _eventTree->Met_type1PF_shiftedPtUp : _eventTree->Met_type1PF_shiftedPtDown;

      float ratioSF = missingEt/oldEt;
      missingEx *= ratioSF;
      missingEy *= ratioSF;

      missingEt_xy *= ratioSF;
      missingEx_xy *= ratioSF;
      missingEy_xy *= ratioSF;
    }

    missingEtVec.SetPtEtaPhiE(missingEt,0.,missingPhi,missingEt);
    missingEtVec_xy.SetPtEtaPhiE(missingEt_xy,0.,missingPhi_xy,missingEt_xy);

   //cout << " In EventContainer isSimulation? "<< isSimulation << endl;

    ///////////////////////////////////////////
    // Muons
    ///////////////////////////////////////////  
    //NOTE: although the missingEt is sent into all the muon loops, it is ONLY shifted in the all muons loop
    // All muon
    for(Int_t io = 0;io < _eventTree -> Muon_pt->size(); io++) {
      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree,*jetsToUsePtr, io,"All", isSimulation);
      if(useObj) {
	muons.push_back(newMuon);
      } // if useObj
      
      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree,*jetsToUsePtr, io,"PtEtaCut", isSimulation);
	if(useObj) {
	 tightwoIsoMuons.push_back(newMuon);
		} // if useObj
    
    //  newMuon.Clear();
    //  useObj = newMuon.Fill(_eventTree,*jetsToUsePtr, io,"Tight", isSimulation);
    //  if(useObj) {
      //  tightMuons.push_back(newMuon);
     // } // if useObj

      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree,*jetsToUsePtr,  io,"Veto", isSimulation);
      if(useObj) {
        vetoMuons.push_back(newMuon);
      } // if useObj

      newMuon.Clear();
      useObj = newMuon.Fill(_eventTree,*jetsToUsePtr,  io,"UnIsolated", isSimulation);
      if(useObj) {
	unIsolatedMuons.push_back(newMuon);
      } // if useObj

    } //for muon loop



    ///////////////////////////////////////////
    // Electrons-->refilled and sorted later in method!!
    ///////////////////////////////////////////

    // All electrons
    for(Int_t io = 0; io < _eventTree->patElectron_pt->size(); io++) {
      newElectron.Clear();
      useObj=newElectron.Fill(_eventTree, io,"All",isSimulation,*muonsToUsePtr2D,*jetsToUsePtr);
      //useObj=newElectron.Fill(_eventTree,  io,"Tight",isSimulation);
      if(useObj) { 
	electrons.push_back(newElectron);
      }  

     // newElectron.Clear();
    // useObj=newElectron.Fill(_eventTree,  io,"Tight",isSimulation,*muonsToUsePtr2D,*jetsToUsePtr);
     // if(useObj) {
      //  tightElectrons.push_back(newElectron);
     // }

      newElectron.Clear();
    useObj=newElectron.Fill(_eventTree,  io,"Veto",isSimulation,*muonsToUsePtr2D,*jetsToUsePtr);
      //useObj=newElectron.Fill(_eventTree,  io,"Tight",isSimulation);
      if(useObj) {
        vetoElectrons.push_back(newElectron);
      }

      newElectron.Clear();
      useObj=newElectron.Fill(_eventTree,  io,"UnIsolated",isSimulation,*muonsToUsePtr2D,*jetsToUsePtr);
    //  useObj=newElectron.Fill(_eventTree,  io,"Tight",isSimulation);
      if(useObj) {
        unIsolatedElectrons.push_back(newElectron);
      }
    } //for Electron loop


//Fill BoostedJet without remove jetoverlap
for(Int_t io = 0;io < _eventTree -> BoostedJet_pt->size(); io++) {
        newBoostedJet.Clear();
      allboostedjets.push_back(newBoostedJet); 
        useObj = newBoostedJet.Fill(1.0,1.0, *muonsToUsePtr2D, *electronsToUsePtr2D,*taggedjetsToUsePtrBoostedjetoverlap, _eventTree, io, &missingEtVec, isSimulation,"Baseline");
       if(useObj){basedboostedjets.push_back(newBoostedJet);}
   newBoostedJet.Clear();
 useObj = newBoostedJet.Fill(1.0,1.0, *muonsToUsePtr2D, *electronsToUsePtr2D,*taggedjetsToUsePtr, _eventTree, io, &missingEtVec, isSimulation,"skim");
       if(useObj){boostedjets.push_back(newBoostedJet);}        
}



    ///////////////////////////////////////////
    // Jets
    ///////////////////////////////////////////
    //cout <<"EVENT"<<endl;
	int Nalljets=0;
	for(Int_t io = 0;io < _eventTree -> Jet_pt->size(); io++) {
		newJet.Clear();

		missingEt = TMath::Sqrt(pow(missingEx,2) + pow(missingEy,2));//so MET gets JES adjustment toogEx=top_met.MET_ExMiss();
		/////////////////////////////////////
		useObj = newJet.Fill(1.0,1.0, *boostedjetsToUsePtrjetaverlap,*muonsToUsePtr2D, *electronsToUsePtr2D, _eventTree, io, &missingEtVec, isSimulation,"jetleptonclean");
		if(useObj) {alljets.push_back(newJet);Nalljets++;}
/*
		newJet.Clear();
	useObj = newJet.Fill(1.0,1.0, *boostedjetsToUsePtrjetaverlap,*muonsToUsePtr2D, *electronsToUsePtr2D, _eventTree, io, &missingEtVec, isSimulation,"beforejetoverlap");
		if(useObj) {
			Beforeak8jetcleanjets.push_back(newJet);
			if(newJet.IsTagged()) taggedBeforeak8jetcleanjets.push_back(newJet);
			else untaggedBeforeak8jetcleanjets.push_back(newJet);
}
*/
	 newJet.Clear();
	 useObj = newJet.Fill(1.0,1.0, *boostedjetsToUsePtrjetaverlap,*muonsToUsePtr2D, *electronsToUsePtr2D, _eventTree, io, &missingEtVec, isSimulation,"skim");
	 if(useObj) {
  		 jets.push_back(newJet);
  		 if(newJet.IsTagged()) taggedJets.push_back(newJet);
		  else unTaggedJets.push_back(newJet);

		} // if useObj
	} //jets





/*
 ///////////////////////////////////////////
 // //  BoostedJets
 ///////////////////////////////////////////////
    //std::cout << "Before newBoostedJet Loop" << _eventTree -> BoostedJet_pt->size()<<std::endl;
 for(Int_t io = 0;io < _eventTree -> BoostedJet_pt->size(); io++) {
        newBoostedJet.Clear();
        //useObj = newBoostedJet.Fill(1.0,1.0, *muonsToUsePtr2D, *electronsToUsePtr2D,*taggedjetsToUsePtrBoostedjetoverlap, _eventTree, io, &missingEtVec, isSimulation,"skim");
        useObj = newBoostedJet.Fill(1.0,1.0, *muonsToUsePtr2D, *electronsToUsePtr2D,*taggedjetsToUsePtr, _eventTree, io, &missingEtVec, isSimulation,"skim");
       if(useObj){boostedjets.push_back(newBoostedJet);}
        
}


*/

////////////////////////////////////////////
//Lepton defined for preselection
////////////////////////////////////
for(Int_t io = 0;io < _eventTree -> Muon_pt->size(); io++) {

	newMuon.Clear();
	useObj = newMuon.Fill(_eventTree,*jetsToUsePtr, io,"Tight", isSimulation);
	if(useObj) {
		tightMuons.push_back(newMuon);
	} // if useObj


		}
for(Int_t io = 0; io < _eventTree->patElectron_pt->size(); io++) {
	   newElectron.Clear();
	        useObj=newElectron.Fill(_eventTree,  io,"Tight",isSimulation,*muonsToUsePtr,*jetsToUsePtr);
	             if(useObj) {
	                  tightElectrons.push_back(newElectron);
	                       }
	                       }
  
  


//Fill Gen event
 if(isSimulation){
  int motherIndex =0;
  int daughtIndex =0;
  // Gen particles 
  for(Int_t io = 0;io < _eventTree -> Gen_pt->size(); io++) {
	  newMCParticle.Clear();
	  newMCParticle.Fill(_eventTree, io, motherIndex, daughtIndex);
	  MCParticles.push_back(newMCParticle);
	  if(newMCParticle.isTop()){
		  MCTops.push_back(newMCParticle);
	  }
	  if(newMCParticle.isW()){
		  MCWs.push_back(newMCParticle);
	  } 

  }
}



  
  
  } // end of else: filling from reco tree
  
  //
  // Create a neutrino, including nu_pzn calculation
  Neutrino newNeutrino;
  newNeutrino.Fill(tightMuons, tightElectrons,missingEx,missingEy);
  neutrinos.push_back(newNeutrino);
  



  return 0;
} //ReadEvent

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * Bool_t EventContainer::CreateFinalState()                                  *
 *                                                                            *
 * Create final state particles                                               *
 * Require at least 2 jets and 1 isolated lepton.  Make cuts if necessary.    *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTRUE if requirements fulfilled                                    *
 ******************************************************************************/
 Bool_t EventContainer::CreateFinalState()
{

  ///////////////////////////////////////
  // Prepare final state particles
  //////////////////////////////////////
  // There should only be one lepton.  If this is the case use that lepton
  if(      1 == tightMuons.size() && 0 == tightElectrons.size()){
    finalLepton = tightMuons[0];
    finalLeptonPDGID = 13;
  }
  else if( 0 == tightMuons.size() && 1 == tightElectrons.size()){
    finalLepton = tightElectrons[0];
    finalLeptonPDGID = 11;
  }
  // If it is the case where there is more than 1 lepton 
  // If more than 1 muon and no electron use leading muon. If more than 1 electron and no muons use leading electron
  else if( tightMuons.size()     > 0 && 0 == tightElectrons.size()){
    finalLepton = tightMuons[0];
    finalLeptonPDGID = 13;
  }
  else if( tightElectrons.size() > 0 && 0 == tightMuons.size()){
     finalLepton = tightElectrons[0];
     finalLeptonPDGID = 11;
  }
  // If there is 1 or more muon and 1 or more electron use lepton with highest pT
  else if( tightMuons.size() > 0 && tightElectrons.size() > 0 ){
    if( tightMuons[0].Pt() > tightElectrons[0].Pt() ){
      finalLepton = tightMuons[0];
      finalLeptonPDGID = 13;
    }
    else{
      finalLepton = tightElectrons[0];
      finalLeptonPDGID = 11;
    }
  } //if
  // If there are no leptons set finalLepton to 0
  else if( 0 == tightMuons.size() && 0 == tightElectrons.size()){
    finalLepton = TLorentzVector(0.0,0.0,0.0,0.0);
    finalLeptonPDGID = 0;
    //    std::cout << "WARNING: <EventContainer::CreateFinalState>" << " O Muons and 0 Electrons in Final State." << std::endl;
  } //else
  // Default (just in case) is to set finalLepton to 0
  else{
    finalLepton = TLorentzVector(0.0,0.0,0.0,0.0);
    finalLeptonPDGID = 0;
  }

  ///////////////////////////////////////////////////////////
  // Reconstruct Neutrino (Pretend that momentum is unknown)
  //NEED TO USE MET, MEX, MEY information to get top eta, etc.
  ///////////////////////////////////////////////////////////
  // Initialize neutrino with negative px and negative py from lepton
  Double_t finalNeutrino_Px = -finalLepton.Px();
  Double_t finalNeutrino_Py = -finalLepton.Py();

  // Truth neutrino pz
  Double_t truthNeutrino_Pz;
  if(MCNeutrinos.size() > 0) truthNeutrino_Pz = MCNeutrinos[0].Pz();
  else truthNeutrino_Pz = 0.0;
			
  // Loop over jets and add negative of jet px and py
  finalJetVector = jets;
  for(Int_t i = 0; i < finalJetVector.size(); i++){
    finalNeutrino_Px += -finalJetVector[i].Px();
    finalNeutrino_Py += -finalJetVector[i].Py();
  } //for

  // Calculate Neutrino pz   
  // 6th parameter: Large negative scale factor means that no scale factor is used
  // 7th parameter: Truth neutrino - not needed for pz calculation (does nothing in Neutrino_Pz())
  Double_t scaleFactor = -999999.0;
  // Double_t finalNeutrino_Pz = Neutrino_Pz(finalNeutrino_Px, finalNeutrino_Py, finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(), scaleFactor, truthNeutrino_Pz);
 Double_t finalNeutrino_Pz = Neutrino_Pz(missingEx, missingEy, finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(), scaleFactor, truthNeutrino_Pz);
  // Calculate final Neutrino Energy
  //Double_t finalNeutrino_E = sqrt(finalNeutrino_Px * finalNeutrino_Px + finalNeutrino_Py * finalNeutrino_Py + finalNeutrino_Pz * finalNeutrino_Pz);
 Double_t finalNeutrino_E = sqrt((missingEx*missingEx) + (missingEy*missingEy) + (finalNeutrino_Pz * finalNeutrino_Pz));
  // Set 4 vector and Id
  // finalNeutrino.SetPxPyPzE(finalNeutrino_Px, finalNeutrino_Py, finalNeutrino_Pz, finalNeutrino_E);
 finalNeutrino.SetPxPyPzE(missingEx,missingEy, finalNeutrino_Pz, finalNeutrino_E);
  // finalNeutrino.SetPdgId(-12); // Not implemented for reconstructed particles

  //  nu_pz=Neutrino_Pz(missingEx, missingEy,leadlep_px,leadlep_py,leadlep_pz,leadlep_e,scf,1.0);
  //  nu_e=sqrt(missingEx*missingEx + missingEy*missingEy + nu_pz*nu_pz);
  //  SetPxPyPzE(missingEx,missingEy,nu_pz,nu_e);
  
  ///////////////////////////////////////////////////////////
  // Reconstruct W 
  ///////////////////////////////////////////////////////////
  finalW = finalNeutrino;
  finalW += finalLepton;
  
  ///////////////////////////////////////////////////////////
  // Reconstruct CM system (add lepton, neutrino, and jets)
  ///////////////////////////////////////////////////////////
  finalCM = finalLepton + finalNeutrino;
  for(Int_t i = 0; i < finalJetVector.size(); i++){
    finalCM = finalCM + finalJetVector[i];
  } //for

  return kTRUE;

} //CreateFinalState() 

/******************************************************************************
 * void EventContainer::MakeTopQuarks()                                       *
 *                                                                            *
 * Make top quarks from W and several jets                                    *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void EventContainer::MakeTopQuarks()
{
  //  std::cout<<"MAKING TOP QUARKS"<<endl;

  ///////////////////////////////////////////////////////////
  // Set everything related to Top Quark jets to 0 
  ///////////////////////////////////////////////////////////
  finalTop_leadingJet.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0);
  finalTop_bestJet.SetPxPyPzE(    0.0, 0.0, 0.0, 0.0);
  finalTop_bestJet12.SetPxPyPzE(  0.0, 0.0, 0.0, 0.0);
  finalTop_bgJet.SetPxPyPzE(      0.0, 0.0, 0.0, 0.0);

  bgJet.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);

  bestJet12Ptr      = NULL;
  nonBestJet12Ptr   = NULL;
  bestJetPtr        = NULL;
  bgJetbJetPtr      = NULL;
  nonBgJetPtr       = NULL;
  bgJetGluonPtr     = NULL;
  taggedJetPtr      = NULL;
  untaggedPtJetPtr  = NULL;
  untaggedEtaJetPtr = NULL;
  forwardJetPtr     = NULL;
  leadingJetPtr     = NULL;

  ///////////////////////////////////////////////////////////
  // Set Jet pointers
  ///////////////////////////////////////////////////////////
  // Set tagger Jet ptr to leading b-tagged jet 
  if(taggedJets.size() > 0) taggedJetPtr = &(taggedJets[0]);
  // Set untaggedPtJetPtr to the leading un-tagged jet ordered in pT (is this correct?)
  if(unTaggedJets.size() > 0) untaggedPtJetPtr = &(unTaggedJets[0]);


  ///////////////////////////////////////////////////////////
  // Create Several Top Quarks
  // Make top quarks from the W and several possible jets. 
  ///////////////////////////////////////////////////////////
  iBestJet = 0;  // index of best jet
  
  // The leading jet from the Top is the W plus the leading jet
  if( finalJetVector.size() > 0){
    finalTop_leadingJet = finalW + finalJetVector[0];
  } //if
  else{
    //std::cout<<"No Jets in this event, particle reconstruction unclear"<<endl;
  } //else

  // Determine Best Jet (one which reconstructs closest to Target Top Mass )
  // findBestJet returns 0 if there are no jets in the event.  But in this case, finalJetVector is empty.  So check number of jets first.
  iBestJet = findBestJet(finalJetVector.size(), finalJetVector, finalW, _targetTopMass);
  if(finalJetVector.size() > 0){
    bestJetPtr = &(finalJetVector[iBestJet]);
    finalTop_bestJet = finalW + *bestJetPtr;
  }
  
  // Determine Best Jet from only the 2 leading jets
  Int_t nJets12 = finalJetVector.size() > 2 ? 2: finalJetVector.size();
  iBestJet = findBestJet(nJets12, finalJetVector, finalW, _targetTopMass);
  if(finalJetVector.size() > 0){
     bestJet12Ptr = &(finalJetVector[iBestJet]);
     finalTop_bestJet12 = finalW + *(bestJet12Ptr);
   }
 
  if(finalJetVector.size() >= 2) nonBestJet12Ptr = &(finalJetVector[1-iBestJet]);  // What if iBestJet > 1 ?
  else nonBestJet12Ptr = NULL;

  // Leading Jet
  if(finalJetVector.size() > 0) leadingJetPtr = &(finalJetVector[0]);


  //   //cout<<"add in a possible gluon"<<endl;
//   // add in the gluon if it is close to this jet
//   // and then determine the best jet

  std::vector<Jet> tmpJetVector;
  // Add gluon if it is close to the jet and then determine the best jet
  // If 2 or less jets use the bestJet12
  if((finalJetVector.size() <= 2)&&(finalJetVector.size() > 0)) {
    finalTop_bgJet = finalTop_bestJet12;
    bgJet          = *bestJet12Ptr;
    bgJetbJetPtr   = bestJet12Ptr;
    nonBgJetPtr    = nonBestJet12Ptr;
  } //if
  
  // For 3 or more jets, pair each of the leading 2 jets with the gluon and then find the best jet
  // Gluon is finalJetVector[2] (how do we know this)
  else if (finalJetVector.size() > 2){
    tmpJetVector = finalJetVector;
  
    // Not sure if this is correct
    // Old version used a 4-element array even if 4th jet did not exist
    // This version only fills 4th element if 4th jet exists
    for(Int_t i = 0; i < 2 ;i++) {
      tmpJetVector[i]   =  finalJetVector[i];
      if( tmpJetVector.size() > i+2 ) tmpJetVector[i+2] =  finalJetVector[i] + finalJetVector[2];
    } // for over jets 1,2

    // Find best jet out of 4
    // Replaced 4 by tmpJetVector.size()
    
    iBestJet       = findBestJet(tmpJetVector.size(), tmpJetVector, finalW, _targetTopMass);
    finalTop_bgJet = tmpJetVector[iBestJet] + finalW;
    bgJet          = tmpJetVector[iBestJet];
    
    // Determine if gluon needs to be included

    if(iBestJet >= 2) {
      bgJetbJetPtr  = &(finalJetVector[iBestJet-2]);
      nonBgJetPtr   = &(finalJetVector[1-(iBestJet-2)]);
      bgJetGluonPtr = &(finalJetVector[2]);
    }  //if
    else {
      bgJetbJetPtr  = &(finalJetVector[iBestJet]);
      nonBgJetPtr   = &(finalJetVector[1-(iBestJet)]);
      bgJetGluonPtr = 0;
    }
    
  } // else: try to include the gluon


  // Final top from tagged jet and W
  if(taggedJetPtr != NULL) {
    finalTop_taggedJet = *taggedJetPtr + finalW;
    
    // and the W using a top mass constraint:
    // the neutrino from the top mass constraint
    // also use a constraint on the top mass rather than the smaller of the two
    // solutions.

    // cout<<"True Top mass is "<<tlt.M()<<" e= "<<tlt.E()<<", px= "<<tlt.Px()<<", py= "<<tlt.Py()<<", pz= "<<tlt.Pz()<<endl;

    // Truth neutrino pz
    Double_t truthNeutrino_Pz;
    if(MCNeutrinos.size() > 0) truthNeutrino_Pz = MCNeutrinos[0].Pz();
    else truthNeutrino_Pz = 0.0;

    Double_t finalNeutrino_Pz = Neutrino_Pz_Top(finalNeutrino.Px(), finalNeutrino.Py(),
						finalLepton.Px(), finalLepton.Py(), finalLepton.Pz(), finalLepton.E(),
						taggedJetPtr -> Px(), taggedJetPtr -> Py(), taggedJetPtr -> Pz(), taggedJetPtr -> E(),
						truthNeutrino_Pz );
    
    
     Double_t finalNeutrino_E = sqrt( pow(finalNeutrino.Px(),2) + pow(finalNeutrino.Py(),2) + finalNeutrino_Pz*finalNeutrino_Pz);
     finalNeutrinoTopC.SetPxPyPzE(finalNeutrino.Px(), finalNeutrino.Py(), finalNeutrino_Pz, finalNeutrino_E);
     //     finalNeutrinoTopC.SetPdgId(-12);  // Does not work at the moment
    
     // The final lepton from top constraint on neutrino
     finalWTopC = finalNeutrinoTopC + finalLepton;
     finalTop_taggedJetTopC = *taggedJetPtr + finalWTopC;
  } //if

   else{
     finalTop_taggedJet.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);
     finalTop_taggedJetTopC.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);

   } //else

  return;
} //MakeTopQuark

