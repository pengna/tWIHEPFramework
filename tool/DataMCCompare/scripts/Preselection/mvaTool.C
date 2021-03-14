#define mvaTool_cxx
#include "mvaTool.h"
#include <math.h>
mvaTool::mvaTool(Int_t channel){
  
  _channel = channel;

  regionNames = {""};
  //Start by initialising the list of variables we will base the MVA on


  //I don't understand these guys' implementations, so I'm ignoring them for now.
  baseName = "";

  varList.push_back("M_Pt_W");
  varList.push_back("M_Mass_W");
  varList.push_back("Met_type1PF_phi");
  varList.push_back("M_Mass_Top");
  varList.push_back("M_Mass_Topleadjet");
  varList.push_back("M_Pt_Top");
  varList.push_back("M_Pt_Topleadjet");
  varList.push_back("M_Pt_Lepton");
  varList.push_back("M_Phi_Lepton");
  varList.push_back("M_Eta_Lepton");
  varList.push_back("M_Mass_bstar");
  varList.push_back("M_Pt_bstar");
  varList.push_back("M_Mass_bstarleadjet");
  varList.push_back("M_nBJet");
  varList.push_back("M_Pt_BJet");
  varList.push_back("M_Phi_BJet");
  varList.push_back("M_Mass_BJet");
  varList.push_back("M_Eta_BJet");
  varList.push_back("M_Pt_LeadBJet");
  varList.push_back("M_Mass_LeadBJet");
  varList.push_back("M_Eta_LeadBJet");
  varList.push_back("M_Pt_BoostedJet");
  varList.push_back("M_Phi_BoostedJet");
  varList.push_back("M_Eta_BoostedJet");
  varList.push_back("M_Mass_BoostedJet");
  varList.push_back("M_prunedmass_BoostedJet");
  varList.push_back("M_softdropmass_BoostedJet");
  varList.push_back("M_softdropmasscorr_BoostedJet");
  varList.push_back("M_tau21_BoostedJet");
  varList.push_back("M_tau32_BoostedJet");
  varList.push_back("M_relpt_Jet");
  varList.push_back("M_DeltaRLeptonClostJet");
  varList.push_back("M_DeltaRmin_LeptonBJet");
  varList.push_back("M_DeltaRBLeadJetLepton");
  varList.push_back("M_DeltaRChosedBJetLepton");



  //The list of samples. this is used by the reading, not the training.
  
  //At some point this should be filled out with the names of the systematics so that we can read those too
  systlist.push_back("");
  systlist.push_back("_Toppt_a_up");
  systlist.push_back("_Toppt_b_up");
  systlist.push_back("_Toppt_a_down");
  systlist.push_back("_Toppt_b_down");
  systlist.push_back("_PU_up");
  systlist.push_back("_PU_down");
  systlist.push_back("_LSF_up");
  systlist.push_back("_LSF_down");
  systlist.push_back("_LepIDSF_up");
  systlist.push_back("_LepIDSF_down");
  systlist.push_back("_LepRecoSF_up");
  systlist.push_back("_LepRecoSF_down");
  systlist.push_back("_Trig_up");
  systlist.push_back("_Trig_down");
  systlist.push_back("_bTag_up");
  systlist.push_back("_bTag_bc_up");
  systlist.push_back("_bTag_udsg_up");
  systlist.push_back("_bTag_down");
  systlist.push_back("_bTag_bc_down");
  systlist.push_back("_bTag_udsg_down");
  systlist.push_back("_mistag_up");
  systlist.push_back("_mistag_down");
  systlist.push_back("_PDF_up");
  systlist.push_back("_PDFHess_up");
  systlist.push_back("_PDF_down");
  systlist.push_back("_PDFHess_down");
  systlist.push_back("_WSF_up");
  systlist.push_back("_WSF_down");
 systlist.push_back("_Toptag_up");    
 systlist.push_back("_Toptag_down");
 systlist.push_back("_topsfsemimerged_up");    
 systlist.push_back("_topsfsemimerged_down");
 systlist.push_back("_topsfunmerged_up");    
 systlist.push_back("_topsfunmerged_down");    
 systlist.push_back("_topsfmerged_up");    
 systlist.push_back("_topsfmerged_down");    
  systlist.push_back("_Sys_up");
  systlist.push_back("_Sys_down");
}




void mvaTool::doReading(TString sampleName, TString inDir, TString outDir, bool isData){
  
  std::cout << "Entering reading routine" << std::endl;
  TMVA::Tools::Instance();

  //Get the reader object
  reader = new TMVA::Reader( "!Color:!Silent" );
  unsigned int varsize = varList.size();
  float treevars[varsize];

  std::cout << "Entering variable adding" << std::endl;
  for (unsigned int i=0; i<varsize;i++){
    treevars[i] = 0;
    std::cout << "[Variable loop] Adding variable: " << varList[i].Data() << std::endl;
    reader->AddVariable( varList[i].Data(), &(treevars[i]) );
  }

  reader->BookMVA( "BDT_ttbar", baseName+"loader/weights/tWLepJet_training_BDT_Grad_1000_20_0.1_ttbar.weights.xml" );
  //  reader->BookMVA( "BDT_wJets", baseName+"loader/weights/tWLepJet_training_BDT_Grad_1000_20_0.1_wJets.weights.xml" );

  std::cout << "Finished reading BDT training" << std::endl;

  std::cout << "Processing sample: " << sampleName << std::endl;
  
  processMCSample(sampleName,inDir,outDir,treevars, isData);
  
  std::cout << "Finished processing " << sampleName << std::endl;
  
}

void mvaTool::doReadingNoMVA(TString sampleName, TString inDir, TString outDir, bool isData){
  
  std::cout << "Entering reading routine" << std::endl;

  unsigned int varsize = varList.size();
  float treevars[varsize];

  std::cout << "Entering variable adding" << std::endl;
  for (unsigned int i=0; i<varsize;i++){
    treevars[i] = 0;
    std::cout << "[Variable loop] Adding variable: " << varList[i].Data() << std::endl;
  }


  std::cout << "Finished reading BDT training" << std::endl;

  std::cout << "Processing sample: " << sampleName << std::endl;
  
  processMCSample(sampleName,inDir,outDir,treevars, isData, false);
  
  std::cout << "Finished processing " << sampleName << std::endl;
  
}


//Do the thing
void mvaTool::processMCSample(TString sampleName, TString inDir, TString outDir, float * treevars,bool isData, bool doMVA){

  //TString dirWithTrees = inDir+sampleName+"/skims/"+sampleName+"*Skim.root";
  int Era =0;
  TString dirWithTrees = inDir+sampleName+"/skims/merge*.root";
 // TString dirWithTrees = inDir+"TTToSemiLeptonic/skims/mergedskimTTToSemiLeptonic0.root";
  if(strstr(inDir,"2016"))Era = 2016;
  else if (strstr(inDir,"2017"))Era = 2017;
  else if (strstr(inDir,"2018"))Era = 2018;
  cout<<"Which year we are running :"<<Era<<endl;
  TString channel ="";
  if (!strstr(inDir,"JE")) {
		  if (strstr(inDir,"Muon")and !strstr(inDir,"TTCR")) channel = "Muon";
		  else if (strstr(inDir,"Muon") and strstr(inDir,"TTCR"))channel = "MuonTTCR";
		  else if (strstr(inDir,"Muon") and strstr(inDir,"QCDCR"))channel = "MuonQCDCR";
		  else if (strstr(inDir,"Electron") and !strstr(inDir,"TTCR"))channel = "Electron";
		  else if (strstr(inDir,"Electron") and strstr(inDir,"TTCR"))channel = "ElectronTTCR";
		  else if (strstr(inDir,"Electron") and strstr(inDir,"QCDCR"))channel = "ElectronQCDCR";
		  }
else {

		  if (strstr(inDir,"Muon")and !strstr(inDir,"TTCR")) channel = "MuonJESR";
		  else if (strstr(inDir,"Muon") and strstr(inDir,"TTCR"))channel = "MuonTTCRJESR";
		  else if (strstr(inDir,"Electron") and !strstr(inDir,"TTCR"))channel = "ElectronJESR";
		  else if (strstr(inDir,"Electron") and strstr(inDir,"TTCR"))channel = "ElectronTTCRJESR";
		  }
  std::vector<TFile*> theoutputfiles;
  for (auto const regionName : regionNames){
    std::cout << "Createing file " << outDir+regionName+"/output_"+sampleName+".root" <<std::endl;
    TFile *theoutputfile = new TFile( (outDir+regionName+"/output_"+sampleName+".root").Data(), "RECREATE");
    theoutputfiles.push_back(theoutputfile);
  }

  std::cout << "Files have been create" << std::endl;
  //  TFile *thetreefile = new TFile( (outDir+"bdtTree_"+sampleName+".root").Data(), "RECREATE");
  //theTreeOutputFileMap[sampleName] = thetreefile;
  
  //------------------------
  // Systematic loop
  //------------------------
  // WIP. This will include the additional files at some point
  

  for (unsigned int j=0; j < systlist.size(); j++){
    if (isData && systlist[j] != "") continue;
  //  createHists(sampleName+systlist[j]);
    TString Histname = systlist[j];
    //cout<<"Histname :"<<Histname<<endl;
    createHists(Histname);
  }

  loopInSample(dirWithTrees,sampleName,treevars,isData,doMVA,Era,channel);
  //makeStatVariationHists(sampleName,theoutputfiles); //We do this in processMCSample so that we have the output file to save the stat variations into.
  
  saveHists(theoutputfiles);
    
  for (auto const outputfile: theoutputfiles){
    outputfile->Close();
    delete outputfile;
  }
}

//Loop over the events in the desired sample
void mvaTool::loopInSample(TString dirWithTrees, TString sampleName, float* treevars, bool isData, bool doMVA, int Era , TString channel){

  unsigned int varsize = varList.size();

  TChain* theTree = new TChain("TNT/BOOM");
  theTree->Add(dirWithTrees);
  std::cout << "[loopInSample] Added "<<dirWithTrees << " to TChain" << std::endl;
  for (unsigned int ivar=0; ivar<varsize; ivar++) theTree->SetBranchAddress( varList[ivar].Data(), &(treevars[ivar]));

  std::cout << "[loopInSample] Finished assigning variables" << std::endl;
  theweight=0.;
  theTree->SetBranchAddress( "EventWeight", &theweight );
  //Get the systematic weights here. We will then fill hists separately as a result of this.
  float puWeight=0., puWeightUp = 0., puWeightDown = 0.;
  float topptWeight=0., topptWeight_a_Up = 0., topptWeight_a_Down = 0., topptWeight_b_Up = 0., topptWeight_b_Down = 0.;
  float lepSFWeight=0., lepSFWeightUp = 0., lepSFWeightDown = 0.,lepSFSysup=0.,lepSFSysdown=0.;
  float lepIDSFWeight=0., lepIDSFWeightUp = 0., lepIDSFWeightDown = 0.,lepIDSFSysup=0.,lepIDSFSysdown=0.;
  float lepRecoSFWeight=0., lepRecoSFWeightUp = 0., lepRecoSFWeightDown = 0.,lepRecoSFSysup=0.,lepRecoSFSysdown=0.;
  float trigSFWeight=0., trigSFWeightUp = 0., trigSFWeightDown = 0.,trigSysup=0.,trigSysdown=0.,SysUp=0.,SysDown=0.;
 float bWeight=0., bWeightUp = 0., bWeightDown = 0.;
 float bWeight_bc=0., bWeight_bcUp = 0., bWeight_bcDown = 0.;
 float bWeight_udsg=0., bWeight_udsgUp = 0., bWeight_udsgDown = 0.;
 float mistagWeight=0., mistagWeightUp = 0., mistagWeightDown = 0.;
   double pdfUp = 0., pdfDown = 0., pdfDev = 0.,pdfCentral=0.,pdfMean=0.;
  float WSF =0.,WSFUp=0.,WSFDown= 0.; 
  float Toptag=0.,ToptagUp=0.,ToptagDown= 0.; 
  int nbJets3040 = 0., nbJets4000 = 0.,ToptagNmatch=0;

  double met = -100.,metPhi = 100.,genweight=1.;
  float lepPt = -100., lepPhi = 100.,boostedjetPt=-100.,lepEta = 0.,boostedjetPhi=-100.,boostedjetEta = 0.,bstarmass =0.0,bstarpT =0.0,topPt=-100.,jetPt=-100.,jetPhi=0.,jetEta=0.,leadjetPt=-100.,prunedmass=0.,softdropmass=0.,softdropmasscorr=0.,tau21=0.,tau32=0.,topPhi=0.,WPhi=0.,DeltaRminlbjet=0.;
  vector<float>* detaRleptonjet= new std::vector<float>;
  vector<float>* allbjetpT= new std::vector<float>;
  vector<double>* jethadronFlavour= new std::vector<double>;
  vector<float>* allbjetPhi= new std::vector<float>;
  vector<float>* allbjetEta= new std::vector<float>;
  vector<double>* motherpdgid= new std::vector<double>;
  vector<double>* pdgid= new std::vector<double>;
   int eventrun =0;
  int theChannel = -1,nbjet =0.;

  theTree->SetBranchAddress( "Gen_pdg_id",&pdgid);
  theTree->SetBranchAddress( "Gen_motherpdg_id",&motherpdgid);
  theTree->SetBranchAddress( "EVENT_genWeight",&genweight);
  theTree->SetBranchAddress( "M_Pt_Lepton",&lepPt);
  theTree->SetBranchAddress( "EVENT_run",& eventrun);
  theTree->SetBranchAddress( "M_Phi_Lepton",&lepPhi);
  theTree->SetBranchAddress( "M_Eta_Lepton",&lepEta);
  //theTree->SetBranchAddress( "Met_type1PFxy_pt",&met);
 // theTree->SetBranchAddress( "Met_type1PFxy_phi",&metPhi);
  theTree->SetBranchAddress( "M_Mass_bstar",&bstarmass);
  theTree->SetBranchAddress( "M_Pt_bstar",&bstarpT);
  theTree->SetBranchAddress( "Met_type1PF_pt",&met);
  theTree->SetBranchAddress( "Met_type1PF_phi",&metPhi);
  theTree->SetBranchAddress( "M_Pt_BoostedJet",&boostedjetPt); 
  theTree->SetBranchAddress( "M_Phi_BoostedJet",&boostedjetPhi); 
  theTree->SetBranchAddress( "M_Eta_BoostedJet",&boostedjetEta); 
  theTree->SetBranchAddress( "M_prunedmass_BoostedJet",&prunedmass); 
  theTree->SetBranchAddress( "M_softdropmass_BoostedJet",&softdropmass); 
  theTree->SetBranchAddress( "M_softdropmasscorr_BoostedJet",&softdropmasscorr); 
  theTree->SetBranchAddress( "M_tau21_BoostedJet",&tau21); 
  theTree->SetBranchAddress( "M_tau32_BoostedJet",&tau32); 
  theTree->SetBranchAddress( "M_nBJet",&nbjet); 
  theTree->SetBranchAddress( "M_Pt_BJet",&jetPt); 
  theTree->SetBranchAddress( "M_Pt_AllBJet",&allbjetpT); 
  theTree->SetBranchAddress( "Jet_hadronFlavour",&jethadronFlavour); 
  theTree->SetBranchAddress( "M_DeltaRmin_LeptonBJet",&DeltaRminlbjet); 
  theTree->SetBranchAddress( "M_Phi_BJet",&jetPhi); 
  theTree->SetBranchAddress( "M_Phi_AllBJet",&allbjetPhi); 
  theTree->SetBranchAddress( "M_Eta_BJet",&jetEta); 
  theTree->SetBranchAddress( "M_Eta_AllBJet",&allbjetEta); 
  theTree->SetBranchAddress( "M_Pt_LeadBJet",&leadjetPt); 
  theTree->SetBranchAddress( "M_Pt_Top",&topPt); 
  theTree->SetBranchAddress( "M_Phi_Top",&topPhi); 
  theTree->SetBranchAddress( "M_Phi_W",&WPhi); 
  theTree->SetBranchAddress( "M_DeltaRBJetLepton",&detaRleptonjet); 
  
  if (doMVA){
    theTree->SetBranchAddress( "channel",&theChannel);
    theTree->SetBranchAddress( "M_nBJet3040",&nbJets3040);
    theTree->SetBranchAddress( "M_nBJet4000",&nbJets4000);
  }

  if (!isData){
    theTree->SetBranchAddress( "puWeight", &puWeight );
    theTree->SetBranchAddress( "puWeight_SysUp", &puWeightUp );
    theTree->SetBranchAddress( "puWeight_SysDown", &puWeightDown );
    theTree->SetBranchAddress( "Topptreweight", &topptWeight );
    theTree->SetBranchAddress( "Topptreweight_a_SysUp", &topptWeight_a_Up );
    theTree->SetBranchAddress( "Topptreweight_b_SysUp", &topptWeight_b_Up );
    theTree->SetBranchAddress( "Topptreweight_a_SysDown", &topptWeight_a_Down );
    theTree->SetBranchAddress( "Topptreweight_b_SysDown", &topptWeight_b_Down );
    std::cout << "[loopInSample] Finished assigning pileup weights" << std::endl;
    theTree->SetBranchAddress( "WSF", &WSF );
    theTree->SetBranchAddress( "WSF_SysUp", &WSFUp );
    theTree->SetBranchAddress( "WSF_SysDown", &WSFDown );

    theTree->SetBranchAddress( "Toptag", &Toptag );
    theTree->SetBranchAddress( "Toptag_SysUp", &ToptagUp );
    theTree->SetBranchAddress( "Toptag_SysDown", &ToptagDown );
    theTree->SetBranchAddress( "ToptagNmatch", &ToptagNmatch );


    theTree->SetBranchAddress( "lepSF", &lepSFWeight );
    theTree->SetBranchAddress( "lepSF_SysUp", &lepSFWeightUp );
    theTree->SetBranchAddress( "lepSF_SysDown", &lepSFWeightDown );
    theTree->SetBranchAddress( "lepIDSF", &lepIDSFWeight );
    theTree->SetBranchAddress( "lepIDSF_SysUp", &lepIDSFWeightUp );
    theTree->SetBranchAddress( "lepIDSF_SysDown", &lepIDSFWeightDown );

    theTree->SetBranchAddress( "lepRecoSF", &lepRecoSFWeight );
    theTree->SetBranchAddress( "lepRecoSF_SysUp", &lepRecoSFWeightUp );
    theTree->SetBranchAddress( "lepRecoSF_SysDown", &lepRecoSFWeightDown );


    theTree->SetBranchAddress( "trigSF", &trigSFWeight );
    theTree->SetBranchAddress( "trigSF_SysUp", &trigSFWeightUp );
    theTree->SetBranchAddress( "trigSF_SysDown", &trigSFWeightDown );
    
    theTree->SetBranchAddress( "bWeight_central", &bWeight );
    theTree->SetBranchAddress( "bWeight_up", &bWeightUp );
    theTree->SetBranchAddress( "bWeight_down", &bWeightDown );

    theTree->SetBranchAddress( "bWeight_bc_central", &bWeight_bc );
    theTree->SetBranchAddress( "bWeight_bc_up", &bWeight_bcUp );
    theTree->SetBranchAddress( "bWeight_bc_down", &bWeight_bcDown );

    theTree->SetBranchAddress( "bWeight_udsg_central", &bWeight_udsg );
    theTree->SetBranchAddress( "bWeight_udsg_up", &bWeight_udsgUp );
    theTree->SetBranchAddress( "bWeight_udsg_down", &bWeight_udsgDown );


    theTree->SetBranchAddress( "misTagWeight_central", &mistagWeight );
    theTree->SetBranchAddress( "misTagWeight_up", &mistagWeightUp );
    theTree->SetBranchAddress( "misTagWeight_down", &mistagWeightDown );
    
    theTree->SetBranchAddress( "EVENT_PDFv2WeightCentral",&pdfCentral );
    theTree->SetBranchAddress( "EVENT_PDFv2WeightMean",&pdfMean );
    theTree->SetBranchAddress( "EVENT_PDFv2WeightUp",&pdfUp );
    theTree->SetBranchAddress( "EVENT_PDFv2WeightDown",&pdfDown );
    theTree->SetBranchAddress( "EVENT_PDFv2WeightStdDev",&pdfDev );

    std::cout << "[loopInSample] Finished assigning lepton weights" << std::endl;
  }
 
  
  if (theTree ==0) cout << "No TTree found for " << sampleName << "!" << std::endl;

  std::tuple<float,float> bSysts (std::make_pair(1.,1.));
  std::tuple<float,float> mistagSysts (std::make_pair(1.,1.));

  //Loop over the events
   int NFullhadric=0,Nsemilepton=0,Ndelepton=0,Nothercase=0,Nwithcut=0,Ndatainregion2018=0;  
   int N1bjet=0,N2bjet=0,N3bjet=0; 
 std::cout << theTree->GetEntries() << " events in loop for sample " << sampleName << std::endl; 
  for (int i = 0; i < theTree->GetEntries(); i++){
    
    //if (i > 20000) break;
    if (i%500 == 0){
      printf ("Processing event %i\r", i);
      fflush(stdout);
    }
    theTree->GetEntry(i);
    
  //used to identify how ttbar decay
  
   int Ntopdecaytolep=0;
   bool Topleptondecay;
        for(int j =0;j<motherpdgid->size();j++){
        	if(abs(motherpdgid->at(j))==24){
			if (abs(pdgid->at(j))==11||abs(pdgid->at(j))==13||abs(pdgid->at(j))==15)Ntopdecaytolep=Ntopdecaytolep+1;
		}
		
        }
   //cout<<"number of top decay to lepton"<<Ntopdecaytolep<<endl;
   if (Ntopdecaytolep==0)NFullhadric=NFullhadric+1; 
   else if (Ntopdecaytolep==1)Nsemilepton=Nsemilepton+1; 
   else if (Ntopdecaytolep==2)Ndelepton=Ndelepton+1; 
   else if (Ntopdecaytolep>2)Nothercase=Nothercase+1; 
  
   if(nbjet==1)N1bjet=N1bjet+1;
  else if(nbjet==2)N2bjet=N2bjet+1;
  else if(nbjet==3)N3bjet=N3bjet+1;


    if (doMVA)  mvaValue = reader->EvaluateMVA("BDT_ttbar");
    else {
      mvaValue = 0.;
      theChannel = 0;
    }
    mvawJetsValue = 0.;

     for (unsigned int ivar=0; ivar<varsize; ivar++) {
        if(varList[ivar]=="M_Pt_Lepton")treevars[ivar]= lepPt;
	else if(varList[ivar]=="M_Mass_bstar")treevars[ivar]=bstarmass;
	else if(varList[ivar]=="M_Pt_bstar")treevars[ivar]=bstarpT;
        else if(varList[ivar]=="M_Phi_Lepton")treevars[ivar]=lepPhi;
        else if(varList[ivar]=="M_Pt_Lepton")treevars[ivar]=lepPt;
        else if(varList[ivar]=="M_Eta_Lepton")treevars[ivar]=lepEta;
        else if(varList[ivar]=="M_Pt_BJet")treevars[ivar]=jetPt;
        else if(varList[ivar]=="M_Phi_BJet")treevars[ivar]=jetPhi;
        else if(varList[ivar]=="M_Eta_BJet")treevars[ivar]=jetEta;
        else if(varList[ivar]=="M_Phi_Top")treevars[ivar]=topPhi;
        else if(varList[ivar]=="M_Phi_W")treevars[ivar]=WPhi;
        else if(varList[ivar]=="M_nBJet")treevars[ivar]=nbjet;
        else if(varList[ivar]=="M_DeltaRmin_LeptonBJet")treevars[ivar]=DeltaRminlbjet;
        else if(varList[ivar]=="M_Pt_LeadBJet")treevars[ivar]=leadjetPt;
        else if(varList[ivar]=="M_Pt_Top")treevars[ivar]=topPt;
        else if(varList[ivar]=="M_Pt_BoostedJet")treevars[ivar]=boostedjetPt;
        else if(varList[ivar]=="Met_type1PF_phi")treevars[ivar]=metPhi;
        else if(varList[ivar]=="M_Phi_BoostedJet")treevars[ivar]=boostedjetPhi;
        else if(varList[ivar]=="M_Eta_BoostedJet")treevars[ivar]=boostedjetEta;
        else if(varList[ivar]=="M_prunedmass_BoostedJet")treevars[ivar]=prunedmass;
        else if(varList[ivar]=="M_softdropmass_BoostedJet")treevars[ivar]=softdropmass;
        else if(varList[ivar]=="M_softdropmasscorr_BoostedJet")treevars[ivar]=softdropmasscorr;
        else if(varList[ivar]=="M_tau21_BoostedJet")treevars[ivar]=tau21;
        else if(varList[ivar]=="M_tau32_BoostedJet")treevars[ivar]=tau32;
   }
    float MaxDeltaR=0.0;
 //    for (int i =0;i<detaRleptonjet->size();i++){
//	if (detaRleptonjet->at(i)>MaxDeltaR) MaxDeltaR=detaRleptonjet->at(i);
//	}
    
    

      float mtw = std::sqrt(2*met*lepPt*(1-cos(metPhi-lepPhi)));
     float DeltaRPhilv= lepPhi-metPhi;
     float HT= boostedjetPt+jetPt;
     float WOverTop_pT= boostedjetPt/topPt;
     float DeltapTWTop= boostedjetPt-topPt;
     float ST= lepPt+met+jetPt+boostedjetPt;
     float DeltaRPhivboostedjet= boostedjetPhi-metPhi;
     float DeltaRPhitW= boostedjetPhi-topPhi;
      float trueweight = 1;
     float temptweight = 1;


//cout<<"WOverTop_pT ="<<WOverTop_pT<<endl;




  bool lepinregion = false, jetinregion =false, boostedjetinregion = false ,eventruninregion = false;
    if (lepEta<-1.3 && lepPhi >-1.57 && lepPhi <-0.87) lepinregion=true;

     for(int j =0;j<allbjetpT->size();j++){
                        if (allbjetEta->at(j)<-1.3&&allbjetPhi->at(j)>-1.57 && allbjetPhi->at(j)<-0.87)jetinregion=true;
}

   // if (jetEta<-1.3 && jetPhi >-1.57 && jetPhi <-0.87) jetinregion=true;
    if (boostedjetEta<-1.3 && boostedjetPhi >-1.57 && boostedjetPhi <-0.87) boostedjetinregion=true;
    if (eventrun> 319077) eventruninregion =true;
    // cout <<"if btag inf"<< isinf(mistagWeight) <<endl;
  //  if(nbjet==1)temptweight = theweight;else temptweight = 0;
  //   if(boostedjetPt>400 &&tau32<0.65&&softdropmass>105&&softdropmass<220)temptweight = theweight;else temptweight = 0; 
  //if(boostedjetPt>200 &&tau21<0.4&&softdropmasscorr>65&&softdropmasscorr<105)temptweight = theweight;else temptweight = 0; 
  //  if(boostedjetPt>200 &&softdropmasscorr>65&&softdropmasscorr<105)temptweight = theweight;else temptweight = 0; 

  //if( nbjet==1&&met>150&&DeltaRminlbjet<2){temptweight = theweight;Nwithcut=Nwithcut+1;}else temptweight =0;
    if( DeltaRminlbjet<2&&met>0){temptweight = theweight;Nwithcut=Nwithcut+1;}else temptweight =0;

//  if(temptweight<0 ||pdfCentral<0) temptweight =0;  
  if( pdfUp<0 ) pdfUp =pdfCentral ;  
  if( pdfDown<0 ) pdfDown =pdfCentral ;  

  //if(temptweight<0) temptweight =0; 
    //LowCat
    // if(DeltaRminlbjet<2&& met>0&&met<160&&boostedjetPt>200&&boostedjetPt<850){temptweight = theweight;Nwithcut=Nwithcut+1;}else temptweight =0;

    //HighCat
    // if( DeltaRminlbjet<2&&met>160&&boostedjetPt>850){temptweight = theweight;Nwithcut=Nwithcut+1;}else temptweight =0;
    //WJets HT binned correction
    if(sampleName=="WJetHT200To400")temptweight=temptweight*0.978569*1.21;
    else if (sampleName=="WJetHT400To600")temptweight=temptweight*0.928054*1.21;
    else if (sampleName=="WJetHT600To800")temptweight=temptweight*0.856705*1.21;
    else if (sampleName=="WJetHT800To1200")temptweight=temptweight*0.757463*1.21;
    else if (sampleName=="WJetHT1200To2500")temptweight=temptweight*0.608292*1.21;
    else if (sampleName=="WJetHT2500ToInf")temptweight=temptweight*0.454246*1.21;
  /* 
   else if (sampleName=="RH_1200")temptweight=temptweight*(1.98/1.936);
    else if (sampleName=="RH_1400")temptweight=temptweight*(0.81/0.7816);
    else if (sampleName=="RH_1600")temptweight=temptweight*(0.35/0.3416);
    else if (sampleName=="RH_1800")temptweight=temptweight*(0.17/0.1583);
    else if (sampleName=="RH_2000")temptweight=temptweight*(0.081/0.07675);
    else if (sampleName=="RH_2200")temptweight=temptweight*(0.041/0.03864);
    else if (sampleName=="RH_2400")temptweight=temptweight*(0.022/0.02008);
    else if (sampleName=="RH_2600")temptweight=temptweight*(0.012/0.01068);
    else if (sampleName=="RH_2800")temptweight=temptweight*(0.0067/0.005814);
    else if (sampleName=="RH_3000")temptweight=temptweight*(0.0038/0.003224);
    else if (sampleName=="LH_1200")temptweight=temptweight*(1.98/1.944);
    else if (sampleName=="LH_1400")temptweight=temptweight*(0.81/0.7848);
    else if (sampleName=="LH_1600")temptweight=temptweight*(0.35/0.3431);
    else if (sampleName=="LH_1800")temptweight=temptweight*(0.17/0.1588);
    else if (sampleName=="LH_2000")temptweight=temptweight*(0.081/0.07711);
    else if (sampleName=="LH_2200")temptweight=temptweight*(0.041/0.03881);
    else if (sampleName=="LH_2400")temptweight=temptweight*(0.022/0.02015);
    else if (sampleName=="LH_2600")temptweight=temptweight*(0.012/0.01073);
    else if (sampleName=="LH_2800")temptweight=temptweight*(0.0067/0.005829);
    else if (sampleName=="LH_3000")temptweight=temptweight*(0.0038/0.003234);
*/

    //Correction HEM 2018 issue
    if(Era==2018 && isData&& eventrun> 319077 && (boostedjetinregion||lepinregion ||jetinregion)){temptweight = 0;Ndatainregion2018=Ndatainregion2018+1;}
    //Correct this samples crossection in 2018 data.JESR don't need it,don't need it, since rerun the code 
    // if(Era==2018 && !strstr(channel,"JESR") &&sampleName=="WJetHT2500ToInf")temptweight=temptweight*0.248;
    //Correct Lumi missing from Block B 
    if(Era==2017 && !isData )temptweight = 0.88453*temptweight;
    //Rescale of MC samples in 2018 after remove HEM data
    if(Era==2018 &&!isData &&(channel=="Muon"||channel=="MuonJESR")) temptweight = (16333.0/16693.0)*temptweight;
    else if(Era==2018 &&!isData &&(channel=="MuonTTCR" ||channel=="MuonTTCRJESR")) temptweight = (3717.0/3761.0)*temptweight;
    else if(Era==2018 &&!isData &&(channel=="MuonQCDCR"||channel=="MuonQCDCRJESR")) temptweight = (252380.0/255030.0)*temptweight;
    else if(Era==2018 &&!isData &&(channel=="Electron"||channel=="ElectronJESR")) temptweight = (15938.0/17924.0)*temptweight;
    else if(Era==2018 &&!isData &&(channel=="ElectronTTCR"||channel=="ElectronTTCRJESR")) temptweight = (2232.0/2555.0)*temptweight;
    else if(Era==2018 &&!isData &&(channel=="ElectronQCDCR"||channel=="ElectronQCDCRJESR")) temptweight = (19344.0/29547.0)*temptweight;
    //if(isnan(temptweight)||isinf(temptweight))temptweight=0;
    trueweight = temptweight;

    //According to Nmatched number, split toptag weight as merged, semimerge and not merged.
    float topsfmerged=0.0,topsfsemimerged=0.0,topsfunmerged=0.0;
    float topsfmergedUp=0.0,topsfsemimergedUp=0.0,topsfunmergedUp=0.0;
    float topsfmergedDown=0.0,topsfsemimergedDown=0.0,topsfunmergedDown=0.0;
    //cout<<"Toptagmatch="<<ToptagNmatch<<endl;
    if(ToptagNmatch==3)
    {
	    topsfmerged=Toptag;topsfmergedUp=ToptagUp;topsfmergedDown=ToptagDown;
	    topsfsemimerged=1.0;topsfsemimergedUp=1.0;topsfsemimergedDown=1.0;
	    topsfunmerged=1.0;topsfunmergedUp=1.0;topsfunmergedDown=1.0;

    }
    else if(ToptagNmatch==2){
	    topsfsemimerged=Toptag;topsfsemimergedUp=ToptagUp;topsfsemimergedDown=ToptagDown;
	    topsfmerged=1.0;topsfmergedUp=1.0;topsfmergedDown=1.0;
	    topsfunmerged=1.0;topsfunmergedUp=1.0;topsfunmergedDown=1.0;

    }
    else{

	    topsfunmerged=Toptag;topsfunmergedUp=ToptagUp;topsfunmergedDown=ToptagDown;
	    topsfsemimerged=1.0;topsfsemimergedUp=1.0;topsfsemimergedDown=1.0;
	    topsfmerged=1.0;topsfmergedUp=1.0;topsfmergedDown=1.0;

    }
    //cout<<"channel :"<<channel<<endl;    

    // cout <<"genweight is :" <<genweight<<endl; 
    // cout <<"lepSFWeight is :" <<lepSFWeight<<endl; 
    // cout <<"PDF weight is :" <<pdfCentral<<endl; 
    //cout <<"trigSFWeight is :" <<trigSFWeight<<endl; 
    // cout <<"puWeight is :" <<puWeight<<endl; 
    // cout <<"Top tag is :" <<Toptag<<endl; 
    // cout <<"Top pT weight is :" <<topptWeight<<endl; 
    // cout <<"Top tag is :" <<Toptag<<endl; 
    // cout <<"W tag is :" <<WSF<<endl; 
    // cout <<"bWeight_central is :" <<bWeight<<endl; 
    //cout <<"mistagWeight is :" <<mistagWeight<<endl; 
    // cout <<"theweight is :" <<theweight<<endl;
    //cout <<"tureweight is :" <<trueweight<<endl; 
    //cout <<"///////////////////////"<<endl; 
    //







     fillHists("",sampleName,treevars,mvaValue,mvawJetsValue,trueweight,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);

     if (!isData){
	     trigSysup = trigSFWeightUp/trigSFWeight;
	     trigSysdown = trigSFWeightDown/trigSFWeight;      
	     lepSFSysup = lepSFWeightUp/lepSFWeight;
	     lepSFSysdown = lepSFWeightDown/lepSFWeight;      
	     lepIDSFSysup = lepIDSFWeightUp/lepIDSFWeight;              
	     lepIDSFSysdown = lepIDSFWeightDown/lepIDSFWeight;      
	     lepRecoSFSysup = lepRecoSFWeightUp/lepRecoSFWeight;
	     lepRecoSFSysdown = lepRecoSFWeightDown/lepRecoSFWeight;      

	     if(trigSFWeight==0){trigSysup=trigSFWeight;trigSysdown=trigSFWeight;}
	     if(lepSFWeight==0){lepSFSysup=lepSFWeight;lepSFSysdown=lepSFWeight;}
	     if(lepIDSFWeight==0){lepIDSFSysup=lepIDSFWeight;lepIDSFSysdown=lepIDSFWeight;}
	     if(lepRecoSFWeight==0){lepRecoSFSysup=lepRecoSFWeight;lepRecoSFSysdown=lepRecoSFWeight;}
	     //SysUp = trueweight *(1+sqrt((puWeightUp/puWeight-1)*(puWeightUp/puWeight-1)+(WSFUp/WSF-1)*(WSFUp/WSF-1)+(lepSFSysup-1)*(lepSFSysup-1)+(trigSysup-1)*(trigSysup-1)+(bWeightUp/bWeight-1)*(bWeightUp/bWeight-1)+(mistagWeightUp/mistagWeight-1)*(mistagWeightUp/mistagWeight-1)+(pdfDev/pdfMean)*(pdfDev/pdfMean)));
	     SysUp = trueweight *(1+sqrt((puWeightUp/puWeight-1)*(puWeightUp/puWeight-1)+(WSFUp/WSF-1)*(WSFUp/WSF-1)+(lepSFSysup-1)*(lepSFSysup-1)+(trigSysup-1)*(trigSysup-1)+(bWeight_bcUp/bWeight_bc-1)*(bWeight_bcUp/bWeight_bc-1)+(bWeight_udsgUp/bWeight_udsg-1)*(bWeight_udsgUp/bWeight_udsg-1)+(pdfDev/pdfMean)*(pdfDev/pdfMean)));
	     //cout<<"Sys_up="<<SysUp<<endl; 
	     SysDown = trueweight *(1-sqrt((1-puWeightDown/puWeight)*(1-puWeightDown/puWeight)+(1-WSFDown/WSF)*(1-WSFDown/WSF)+(1-lepSFSysdown)*(1-lepSFSysdown)+(1-trigSysdown)*(1-trigSysdown)+(1-bWeight_bcDown/bWeight_bc)*(1-bWeight_bcDown/bWeight_bc)+(1-bWeight_udsgDown/bWeight_udsg)*(1-bWeight_udsgDown/bWeight_udsg)+(pdfDev/pdfMean)*(pdfDev/pdfMean)));
	     //SysDown = trueweight *(1-sqrt((1-puWeightDown/puWeight)*(1-puWeightDown/puWeight)+(1-WSFDown/WSF)*(1-WSFDown/WSF)+(1-lepSFSysdown)*(1-lepSFSysdown)+(1-trigSysdown)*(1-trigSysdown)+(1-bWeightDown/bWeight)*(1-bWeightDown/bWeight)+(1-mistagWeightDown/mistagWeight)*(1-mistagWeightDown/mistagWeight)+(pdfDev/pdfMean)*(pdfDev/pdfMean)));
	     fillHists("_Toppt_a_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topptWeight_a_Up/topptWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
	     fillHists("_Toppt_b_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topptWeight_b_Up/topptWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
	     fillHists("_Toppt_a_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topptWeight_a_Down/topptWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
	     fillHists("_Toppt_b_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topptWeight_b_Down/topptWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
	     fillHists("_PU_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (puWeightUp/puWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
	     fillHists("_PU_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (puWeightDown/puWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_WSF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (WSFUp/WSF),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_WSF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (WSFDown/WSF),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Toptag_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (ToptagUp/Toptag),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Toptag_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (ToptagDown/Toptag),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_topsfsemimerged_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfsemimergedUp/topsfsemimerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_topsfsemimerged_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfsemimergedDown/topsfsemimerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_topsfunmerged_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfunmergedUp/topsfunmerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);        
      fillHists("_topsfunmerged_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfunmergedDown/topsfunmerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_topsfmerged_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfmergedUp/topsfmerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_topsfmerged_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (topsfmergedDown/topsfmerged),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);


      //fillHists("_LSF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepSFWeightUp/lepSFWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      //fillHists("_LSF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepSFWeightDown/lepSFWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LSF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepSFSysup),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LSF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepSFSysdown),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LepIDSF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepIDSFSysup),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LepIDSF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepIDSFSysdown),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LepRecoSF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepRecoSFSysup),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_LepRecoSF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (lepRecoSFSysdown),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      //fillHists("_Trig_up",treevars,mvaValue,mvawJetsValue,trueweight * (trigSFWeightUp/trigSFWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      // fillHists("_Trig_down",treevars,mvaValue,mvawJetsValue,trueweight * (trigSFWeightDown/trigSFWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Trig_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (trigSysup),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Trig_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (trigSysdown),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      //fillHists("_bTag_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight *(bWeightUp/bWeight) ,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      //fillHists("_bTag_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (bWeightDown/bWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
     //cout<<"I'm fine in here"<<endl;
     //cout<<"bWeight_bc"<<bWeight_bc<<endl;
       fillHists("_bTag_bc_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight *(bWeight_bcUp/bWeight_bc) ,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_bTag_bc_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (bWeight_bcDown/bWeight_bc),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_bTag_udsg_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight *(bWeight_udsgUp/bWeight_udsg) ,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_bTag_udsg_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (bWeight_udsgDown/bWeight_udsg),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
     // fillHists("_mistag_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight *(mistagWeightUp/mistagWeight) ,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
     // fillHists("_mistag_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight * (mistagWeightDown/mistagWeight),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_PDFHess_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight*(pdfUp),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_PDFHess_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight*(pdfDown),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_PDF_up",sampleName,treevars,mvaValue,mvawJetsValue,trueweight*(1+pdfDev/pdfMean),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_PDF_down",sampleName,treevars,mvaValue,mvawJetsValue,trueweight*(1-pdfDev/pdfMean),met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Sys_up",sampleName,treevars,mvaValue,mvawJetsValue,SysUp,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
      fillHists("_Sys_down",sampleName,treevars,mvaValue,mvawJetsValue,SysDown,met,mtw,DeltaRPhilv,DeltaRPhivboostedjet,DeltaRPhitW,HT,ST,WOverTop_pT,theChannel);
    }
  }
	cout<<"Fullhadric decay event:"<<NFullhadric<<endl<<"Semilepton decay evnet: "<<Nsemilepton <<endl<<"delepton decay event: "<< Ndelepton<<endl<<"other case: "<<Nothercase<<endl;	
	cout<<"1 btag jet event:"<<N1bjet<<endl<<"2 btag jet event:"<<N2bjet<<endl<<"3 btag jet event:"<<N3bjet<<endl;
	cout<<"Number of event after exta cut :"<<Nwithcut<<endl;
    	cout <<"Ndatainregion2018 : " <<Ndatainregion2018<<endl; 
} 

void mvaTool::createHists(TString sampleName){

  for (unsigned int region = 0; region < regionNames.size(); region++){


    std::vector<TH1F*> histovect;
    std::vector<TH1F*> bdtVect;

    //Make a histogram per variable
    for (unsigned int i = 0; i<varList.size(); i++){
      int nbins = 1;
      double xmin = -1000;
      double xmax = 1000;
      if (varList[i] == "M_Pt_W") {nbins = 20; xmin = 0.; xmax = 600.;};
      if (varList[i] == "M_Pt_Lepton") {nbins = 20; xmin = 50.; xmax = 300.;};
      if (varList[i] == "M_Phi_Lepton") {nbins = 20; xmin = -4.; xmax = 4.;};
      if (varList[i] == "M_Eta_Lepton") {nbins = 20; xmin = -2.5; xmax = 2.5;};
      if (varList[i] == "M_Mass_Top") {nbins = 20; xmin = 80.; xmax = 800.;};
      if (varList[i] == "Met_type1PF_phi") {nbins = 20; xmin = -4.; xmax = 4.;};
      if (varList[i] == "M_Mass_Topleadjet") {nbins = 20; xmin = 80.; xmax = 800.;};
      if (varList[i] == "M_Mass_W") {nbins = 50; xmin = 80.; xmax = 800.;};
      if (varList[i] == "M_Phi_MET") {nbins = 20; xmin = -4.; xmax = 4.;};
      if (varList[i] == "M_Pt_Top") {nbins = 50; xmin = 0.; xmax = 1500.;};
      if (varList[i] == "M_Pt_Topleadjet") {nbins = 50; xmin = 0.; xmax = 1500.;};
      if (varList[i] == "M_Mass_bstar") {nbins = 40; xmin = 0.; xmax = 4000.;};
      //if (varList[i] == "M_Mass_bstar") {nbins = 20; xmin = 0.; xmax = 4000.;};
      //if (varList[i] == "M_Mass_bstar") {nbins = 10; xmin = 0.; xmax = 4000.;};
      if (varList[i] == "M_Pt_bstar") {nbins = 20; xmin = 0.; xmax = 3000.;};
      if (varList[i] == "M_Mass_bstarleadjet") {nbins = 20; xmin = 0.; xmax = 3000.;};
      if (varList[i] == "M_nBJet") {nbins = 6; xmin = 0.; xmax = 6.;};
      if (varList[i] == "M_Pt_BJet") {nbins = 20; xmin = 0.; xmax = 1000.;};
      if (varList[i] == "M_Phi_BJet") {nbins = 20; xmin = -4.; xmax = 4.;};
      if (varList[i] == "M_Pt_LeadBJet") {nbins = 20; xmin = 0.; xmax = 1000.;};
      if (varList[i] == "M_Eta_BJet") {nbins = 20; xmin = -2.5; xmax = 2.5;};
      if (varList[i] == "M_Eta_LeadBJet") {nbins = 20; xmin = -2.5; xmax = 2.5;};
      if (varList[i] == "M_Pt_BoostedJet") {nbins = 20; xmin = 200.; xmax = 1100.;};
      if (varList[i] == "M_Phi_BoostedJet") {nbins = 20; xmin = -4.; xmax = 4.;};
      if (varList[i] == "M_prunedmass_BoostedJet") {nbins = 50; xmin = 0.; xmax = 250.;};
      if (varList[i] == "M_softdropmass_BoostedJet") {nbins = 20; xmin = 100.; xmax = 250.;};
      //if (varList[i] == "M_softdropmass_BoostedJet") {nbins = 50; xmin = 0.; xmax = 250.;};
      if (varList[i] == "M_softdropmasscorr_BoostedJet") {nbins = 20; xmin = 50.; xmax = 120.;};
      if (varList[i] == "M_tau21_BoostedJet") {nbins = 50; xmin = 0.; xmax = 1.2;};
      if (varList[i] == "M_tau32_BoostedJet") {nbins = 50; xmin = 0.; xmax = 1.2;};
      if (varList[i] == "M_Eta_BoostedJet") {nbins = 20; xmin = -2.5; xmax = 2.5;};
      if (varList[i] == "M_Mass_BoostedJet") {nbins = 50; xmin = -400.; xmax = 400.;};
      if (varList[i] == "M_Mass_BJet") {nbins = 50; xmin = -400.; xmax = 400.;};
      if (varList[i] == "M_Mass_LeadBJet") {nbins = 50; xmin = -400.; xmax = 400.;};
      if (varList[i] == "M_relIsoR04") {nbins = 20; xmin = 0.; xmax = 1.;};
      if (varList[i] == "M_relpt_Jet") {nbins = 20; xmin = 0.; xmax = 200.;};
      if (varList[i] ==  "M_dr_Jet") {nbins = 20; xmin = 0; xmax = 0.5;};
      if (varList[i] ==  "M_DeltaRLeptonClostJet") {nbins = 20; xmin = 0; xmax = 4.;};
      if (varList[i] ==  "M_DeltaRmin_LeptonBJet") {nbins = 20; xmin = 0; xmax = 4.;};
      if (varList[i] ==  "M_DeltaRBLeadJetLepton") {nbins = 20; xmin = 0; xmax = 4.;};
      if (varList[i] ==  "M_DeltaRChosedBJetLepton") {nbins = 20; xmin = 0; xmax = 4.;};
      if (varList[i] ==  "M_DeltaRlightjets") {nbins = 20; xmin = 0; xmax = 6.;};
      if (varList[i] == "M_topMass2_lep") {nbins = 20; xmin = 0.; xmax = 600.;};
      if (varList[i] == "M_Pt_AllJets2040") {nbins = 20; xmin = 0; xmax = 160;};
      if (varList[i] == "M_Pt_AllJetsLeptonMET") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_E_Jet1MET") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_Jet1Jet2Jet3_Centrality") {nbins = 20; xmin = 0.; xmax = 1.;};
      if (varList[i] == "M_DeltaRLeptonJet1") {nbins = 20; xmin = 0.; xmax = 6.;};
      if (varList[i] == "M_nJet3040e24") {nbins = 10; xmin = 0.; xmax = 10.;};
      if (varList[i] == "M_nJet2040") {nbins = 10; xmin = 0.; xmax = 10.;};
      if (varList[i] == "M_Mass_Jet1Jet2Jet3LeptonMET") {nbins = 20; xmin = 0.; xmax = 1500.;};
      if (varList[i] == "M_Pt_BJet1_4000") {nbins = 20; xmin = 40.; xmax = 200.;};
      if (varList[i] == "M_Pt_Jet1_2040") {nbins = 20; xmin = 20.; xmax = 40.;};
      if (varList[i] == "M_hadronicWmass") {nbins = 20; xmin = 0.; xmax = 500.;};
      if (varList[i] == "M_hadronicWEta") {nbins = 20; xmin = -6.; xmax = 6.;};
      if (varList[i] == "M_DeltaRBJethadronicW") {nbins = 20; xmin = 0.; xmax = 6.;};
      if (varList[i] == "M_Pt_sys") {nbins = 20; xmin = 0.; xmax = 300.;};
      if (varList[i] == "M_HT") {nbins = 20; xmin = 0.; xmax = 900.;};
      if (varList[i] == "M_TMass_Jet1Jet2Jet3") {nbins = 20; xmin = 0.; xmax = 1400.;};
      if (varList[i] == "M_cosThetaStar") {nbins = 20; xmin = -1.; xmax = 1.;};
      if (varList[i] == "M_cosThetaStar_lepOnly") {nbins = 20; xmin = -1.; xmax = 1.;};
      if (varList[i] == "lightJet1CSV") {nbins = 20; xmin = 0.; xmax = 1.;};
      if (varList[i] == "lightJet2CSV") {nbins = 20; xmin = 0.; xmax = 1.;};


      TH1F* histo = new TH1F((varList[i] +sampleName).Data(), (varList[i] +  sampleName).Data(),nbins,xmin,xmax);
      histo->Sumw2();
      histovect.push_back(histo);
    }
    //Add in some plots for met and mtw for control/fitting
  TH1F* histoWOverTop_pT= new TH1F(("WOverTop_pT" + sampleName).Data(), ("WOverTop_pT" + sampleName).Data(),20,0,4);  
   histoWOverTop_pT->Sumw2();
   histovect.push_back(histoWOverTop_pT);
  TH1F* histoST = new TH1F(("ST" + sampleName).Data(), ("ST" + sampleName).Data(),20,0,3000);
   histoST->Sumw2();
   histovect.push_back(histoST);
 

       TH1F* histoHT = new TH1F(("HT" + sampleName).Data(), ("HT" + sampleName).Data(),20,0,1500);
    histoHT->Sumw2();
    histovect.push_back(histoHT);
 
  
  
    TH1F* histoDeltaRPhitW = new TH1F(("DeltaRPhitW" + sampleName).Data(), ("DeltaRPhitW" + sampleName).Data(),20,-4,4);
    histoDeltaRPhitW->Sumw2();
    histovect.push_back(histoDeltaRPhitW);
    TH1F* histoDeltaRPhivboostedjet = new TH1F(("DeltaRPhivboostedjet" + sampleName).Data(), ("DeltaRPhivboostedjet" + sampleName).Data(),20,-4,4);
    histoDeltaRPhivboostedjet->Sumw2();
    histovect.push_back(histoDeltaRPhivboostedjet);
    TH1F* histoDeltaRPhilv = new TH1F(("DeltaRPhilv" + sampleName).Data(), ("DeltaRPhilv" + sampleName).Data(),20,-4,4);
    histoDeltaRPhilv->Sumw2();
    histovect.push_back(histoDeltaRPhilv);
    TH1F* histomtw = new TH1F(("mTW" + sampleName).Data(), ("mTW" + sampleName).Data(),20,0.,200.);
    histomtw->Sumw2();
    histovect.push_back(histomtw);
    TH1F* histomet = new TH1F(("met" + sampleName).Data(), ("met" + sampleName).Data(),50,0.,400.);
   // TH1F* histomet = new TH1F(("met" + sampleName).Data(), ("met" + sampleName).Data(),20,0.,200.);
    histomet->Sumw2();
    histovect.push_back(histomet);
  
    theHistoMap[sampleName].push_back(histovect);
  }
  std::cout << "hist maps are this long: " << the2DHistoMap[sampleName].size() << " " << theHistoMap[sampleName].size() << " " << bdtHistoMap[sampleName].size() << std::endl;
}

void mvaTool::fillHists(TString sysName,TString sampleName, float* treevars, double mvaValue, double mvawJetsValue, double theweight, float met, float mtw,float DeltaRPhilv, float DeltaRPhivboostedjet, float DeltaRPhitW,float HT,float ST,float WOverTop_pT,int theChannel){

  std::vector<std::vector<TH1F*> > histovect = theHistoMap[sysName];
  std::vector<std::vector<TH1F*> > histovecttemp = theHistoMap[sysName];

  
//  for (unsigned int i=0; i < varList.size(); i++) histovect[theChannel][i]->Fill(treevars[i],theweight);
  for (unsigned int i=0; i < varList.size(); i++){
	 histovect[theChannel][i]->Fill(treevars[i],theweight);

	}
  histovect[theChannel][histovect[theChannel].size() - 8]->Fill(WOverTop_pT,theweight);
  histovect[theChannel][histovect[theChannel].size() - 7]->Fill(ST,theweight);
  histovect[theChannel][histovect[theChannel].size() - 6]->Fill(HT,theweight);
  histovect[theChannel][histovect[theChannel].size() - 5]->Fill(DeltaRPhitW,theweight);
  histovect[theChannel][histovect[theChannel].size() - 4]->Fill(DeltaRPhivboostedjet,theweight);
  histovect[theChannel][histovect[theChannel].size() - 3]->Fill(DeltaRPhilv,theweight);
  histovect[theChannel][histovect[theChannel].size() - 2]->Fill(mtw,theweight);
  histovect[theChannel][histovect[theChannel].size() - 1]->Fill(met,theweight);



}

void mvaTool::saveHists(std::vector<TFile*> outFile){
  for (unsigned int i = 0; i < regionNames.size(); i++){
    outFile[i]->cd();
    for (auto histoMapElement: theHistoMap){
      for (auto hist: (histoMapElement.second)[i]){
		 SetOverflowbin(hist);
		 hist->Write();
	}
    		}
 
 
 
  }
}


void mvaTool::SetOverflowbin(TH1F* h){

	h->SetBinContent(1,h->GetBinContent(1)+h->GetBinContent(0));
	float overflowbin= h->GetBinContent(h->GetNbinsX()+1);
//	if(overflowbin<=0)overflowbin=0;
//	cout<<"overflowbin is "<<overflowbin<<"last bin is "<<h->GetBinContent(h->GetNbinsX())<<endl;	
	h->SetBinContent(h->GetNbinsX(),h->GetBinContent(h->GetNbinsX())+overflowbin);
//	cout<<"last bin is:"<<h->GetBinContent(h->GetNbinsX())<<"OverFlowbin is :"<<h->GetBinContent(h->GetNbinsX()+1)<<endl;



}








void mvaTool::setbTagVars(TChain * theTree){
  std::cout << "[setbTagVars] Entered setbTagVars" << std::endl;
  //  std::vector<TString> bTagSystNames = {"cferr1","cferr2","hfstats1","hfstats2","jes","lf"};
  //  std::vector<TString> bTagSystNames = {"cferr1","cferr2","hfstats2"};
  std::vector<TString> bTagSystNames = {"jes","hfstats1","lf","hfstats2","cferr1"};
  std::vector<TString> upDown = {"up","down"};
  bTagSysts.push_back(0.);
  std::cout << "[setbTagVars] Assigned central variable " << std::endl;
  theTree->SetBranchAddress( "bWeight_central", &(bTagSysts[0]) );
  std::cout << "[setbTagVars] Assigned central variable to tree " << std::endl;
  int i = 1;
  for (auto bName: bTagSystNames){
    std::cout << "[setbTageVars] Booking " << bName << " variable: " << std::endl;
    for (auto ud: upDown){
      bTagSysts.push_back(0.);
      std::cout << ("     [setbTageVars] bWeight_"+ud+"_"+bName).Data() << std::endl;
      theTree->SetBranchAddress( ("bWeight_"+ud+"_"+bName).Data(), &(bTagSysts[i]));
      i++;
    }
  }
}

std::tuple<float,float> mvaTool::calculatebTagSyst(float bCentral, std::vector<float> bWeightsSyst){
  float systUp = 0., systDown = 0.;
  for (unsigned int i = 1; i < bWeightsSyst.size(); i++){
      if (i%2 == 0){//Down systs
	systDown += pow((bWeightsSyst[i]/bCentral)-1,2);
	//	std::cout << (bWeightsSyst[i]/bCentral)-1 << ",";
      }
      else{
	systUp += pow((bWeightsSyst[i]/bCentral)-1,2);
	//std::cout << (bWeightsSyst[i]/bCentral)-1 << ",";
      }
    }
  //  std::cout << std::endl;
  return std::make_tuple(1+sqrt(systUp),1-sqrt(systDown));
}





  
void mvaTool::makeStatVariationHists(TString sampleName, std::vector<TFile *> outputFile){
  for (unsigned int i = 0; i < regionNames.size(); i++){
    TH1F * theDefaultMVA = theHistoMap[sampleName][i].back(); //We only need to do this to nominal.
    outputFile[i]->cd();
    std::ostringstream histNameStream;
    std::string histName;             
    
    for (int i = 1; i <= theDefaultMVA->GetXaxis()->GetNbins();i++){
      histNameStream.str("");
      histNameStream << "MVA_" << sampleName << "_statbin"<<i<<"_up";
      histName = histNameStream.str();
      TH1F* tempMVAUp = (TH1F*)theDefaultMVA->Clone(histName.c_str());
      histNameStream.str("");
      histNameStream << "MVA_" << sampleName << "_statbin"<<i<<"_down";
      histName = histNameStream.str();
      TH1F* tempMVADown = (TH1F*)theDefaultMVA->Clone(histName.c_str());
      float binToChange = theDefaultMVA->GetBinContent(i);
      //This is the bit I'm not sure of, but can edit later with any luck.
      float uncert = sqrt(binToChange);
      tempMVAUp->SetBinContent(i,binToChange+uncert);
      tempMVADown->SetBinContent(i,binToChange-uncert);
      tempMVAUp->Write();
      tempMVADown->Write();
    }
  }
}
