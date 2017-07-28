#define mvaTool_cxx
#include "mvaTool.h"

mvaTool::mvaTool(){
  
  //Start by initialising the list of variables we will base the MVA on

    //varList.push_back("M_Pt_Jet1_2040e24");

    //    varList.push_back("largestCSV");varList.push_back("M_nJet2040");
    //  varList.push_back("M_firstJetPt");
  //I don't understand these guys' implementations, so I'm ignoring them for now.
  //  varList.push_back("likelihood_BJet2040");
  //varList.push_back("likelihood_BJet4000");    varList.push_back("M_HT");
    //varList.push_back("M_nJet3040");
    //  varList.push_back("M_nJet2040e24");
    //    varList.push_back("M_hadronicWPt");
    //    varList.push_back("M_hadronicWPhi");

  baseName = "";

    varList.push_back("M_nJet2040");
    varList.push_back("M_HT");
    varList.push_back("M_DeltaRBJetLepton");
    varList.push_back("M_DeltaRlightjets");
    varList.push_back("M_topMass2_lep");
    //varList.push_back("M_Pt_AllJets2040");
    varList.push_back("M_Pt_Lepton");
    varList.push_back("M_Pt_AllJetsLeptonMET");
    varList.push_back("M_E_Jet1MET");
    varList.push_back("M_Jet1Jet2Jet3_Centrality");
    varList.push_back("M_DeltaRLeptonJet1");
    varList.push_back("M_nJet3040e24");

    varList.push_back("M_Mass_Jet1Jet2Jet3LeptonMET");
    //varList.push_back("M_Pt_BJet1_4000");
    varList.push_back("M_Pt_Jet1_2040");
    varList.push_back("M_hadronicWmass");
    
    //varList.push_back("M_hadronicWEta");
    //varList.push_back("M_DeltaRBJethadronicW");
    //varList.push_back("M_Pt_sys");
    varList.push_back("M_TMass_Jet1Jet2Jet3");
    //varList.push_back("M_cosThetaStar");
    //varList.push_back("M_cosThetaStar_lepOnly");
    varList.push_back("lightJet1CSV");
    //varList.push_back("lightJet2CSV");


  //The list of samples. this is used by the reading, not the training.
  samplelist.push_back("tW_top_nfh");
  
  //At some point this should be filled out with the names of the systematics so that we can read those too
  systlist.push_back("");
  systlist.push_back("_PU_up");
  systlist.push_back("_PU_down");
  systlist.push_back("_LSF_up");
  systlist.push_back("_LSF_down");
  systlist.push_back("_bTag_up");
  systlist.push_back("_bTag_down");
  
}

void mvaTool::doTraining(TString inDir){
  
  //This needs to be done first
  TMVA::Tools::Instance();

  //Create the output file that will store the training results
  TString outfileName("training/tWLepJets_training_BDT.root");
  TFile* outFile = TFile::Open(outfileName, "RECREATE");

  //Create the factory
  TMVA::Factory *factory = new TMVA::Factory("tWLepJet_training",outFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

  //Create a data loader
  TMVA::DataLoader loader{"loader"};
  
  //Make TChains for signal and background
  TChain signal("TNT/BOOM");
  TChain bkg_ttbar("TNT/BOOM");

  //From the inDir, add all skim files to the trees
  signal.Add(inDir+"tW_top_nfh/skims/tW_top*Skim.root");
  signal.Add(inDir+"tW_antitop_nfh/skims/tW_antitop*Skim.root");
  bkg_ttbar.Add(inDir+"ttbar/skims/ttbar*Skim.root");

  //Grab the input files now
  //  TFile * sigFile = TFile::Open("../condorStuff/skims20161129_bdtVariables/tW/tW_top/skims/tW_top0Skim.root"); //Not the final one, of course. Will probably need to sum the skims
  //  TFile * bkgFile = TFile::Open("../condorStuff/skims20161129_bdtVariables/tW/ttbar/skims/ttbar0Skim.root");

  //Get the trees
  //TTree *signal = (TTree*)sigFile->Get("TNT/BOOM");
  //TTree *bkg_ttbar = (TTree*)bkgFile->Get("TNT/BOOM");

  //Add the trees to the factory
  loader.AddSignalTree    (&signal,    1.);
  loader.AddBackgroundTree(&bkg_ttbar,1.);
  
  for (unsigned int i=0; i < varList.size(); i++) loader.AddVariable(varList[i].Data(),'F');

  loader.SetSignalWeightExpression("EventWeight");
  loader.SetBackgroundWeightExpression("EventWeight");

  TCut mycutsSig = "";
  TCut mycutsBkg = "";

  loader.PrepareTrainingAndTestTree( mycutsSig, mycutsBkg,"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_200_10", "!H:!V:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_200_5", "!H:!V:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
    factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_1000_20_0.1", "!H:!V:NTrees=1000:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:Shrinkage=0.1" );
  //  factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_400_10", "!H:!V:NTrees=400:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_400_5", "!H:!V:NTrees=400:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_200_10", "!H:!V:NTrees=200:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_Grad_200_5", "!H:!V:NTrees=200:MaxDepth=3:BoostType=Grad:SeparationType=GiniIndex:nCuts=5:PruneMethod=NoPruning" );
  //factory->BookMethod(&loader,TMVA::Types::kBDT, "BDT_400_10", "!H:!V:NTrees=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=10:PruneMethod=NoPruning" );

  // Train MVAs using the set of training events                  
  factory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events          
  factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  outFile->Close();

  delete factory;

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

  reader->BookMVA( "BDT", baseName+"loader/weights/tWLepJet_training_BDT_Grad_1000_20_0.1.weights.xml" );

  std::cout << "Finished reading BDT training" << std::endl;

  std::cout << "Processing sample: " << sampleName << std::endl;
  
  processMCSample(sampleName,inDir,outDir,treevars, isData);
  
  std::cout << "Finished processing " << sampleName << std::endl;
  
}

//Do the thing
void mvaTool::processMCSample(TString sampleName, TString inDir, TString outDir, float * treevars,bool isData){

  TString dirWithTrees = inDir+sampleName+"/skims/"+sampleName+"*Skim.root";
//  TFile *input = new TFile( (inDir+sampleName+"/hists/merged"+sampleName+".root").Data(), "READ");
  TFile *theoutputfile = new TFile( (outDir+"output_"+sampleName+".root").Data(), "RECREATE");
  //  TFile *thetreefile = new TFile( (outDir+"bdtTree_"+sampleName+".root").Data(), "RECREATE");
  //theTreeOutputFileMap[sampleName] = thetreefile;
  
  //------------------------
  // Systematic loop
  //------------------------
  // WIP. This will include the additional files at some point
  

  for (unsigned int j=0; j < systlist.size(); j++){
    if (isData && systlist[j] != "") continue;
    createHists(sampleName+systlist[j]);
  }

  loopInSample(dirWithTrees,sampleName,treevars,isData);
  makeStatVariationHists(sampleName,theoutputfile); //We do this in processMCSample so that we have the output file to save the stat variations into.
  
  for (unsigned int j=0; j < systlist.size(); j++){
    saveHists(theoutputfile);
  }

  theoutputfile->Close();
  delete theoutputfile;

}

//Loop over the events in the desired sample
void mvaTool::loopInSample(TString dirWithTrees, TString sampleName, float* treevars, bool isData){

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
  float lepSFWeight=0., lepSFWeightUp = 0., lepSFWeightDown = 0.;
  float bWeight=0., bWeighthfs1Up = 0., bWeighthfs1Down = 0., bWeighthfs2Up = 0., bWeighthfs2Down = 0., bWeightcferr1Up = 0., bWeightcferr1Down = 0., bWeightcferr2Up = 0., bWeightcferr2Down = 0., bWeightjerUp = 0., bWeightjerDown = 0., bWeightlfUp = 0., bWeightlfDown = 0.;
  
  if (!isData){
    theTree->SetBranchAddress( "puWeight", &puWeight );
    theTree->SetBranchAddress( "puWeight_SysUp", &puWeightUp );
    theTree->SetBranchAddress( "puWeight_SysDown", &puWeightDown );
  
    std::cout << "[loopInSample] Finished assigning pileup weights" << std::endl;

    theTree->SetBranchAddress( "lepSF", &lepSFWeight );
    theTree->SetBranchAddress( "lepSF_SysUp", &lepSFWeightUp );
    theTree->SetBranchAddress( "lepSF_SysDown", &lepSFWeightDown );
    
    theTree->SetBranchAddress( "bWeight_central", &bWeight );
    theTree->SetBranchAddress( "bWeight_up_hfstats1", &bWeighthfs1Up );
    theTree->SetBranchAddress( "bWeight_down_hfstats1", &bWeighthfs1Down );
    theTree->SetBranchAddress( "bWeight_up_hfstats2", &bWeighthfs2Up );
    theTree->SetBranchAddress( "bWeight_down_hfstats2", &bWeighthfs2Down );
    theTree->SetBranchAddress( "bWeight_up_cferr1", &bWeightcferr1Up );
    theTree->SetBranchAddress( "bWeight_down_cferr1", &bWeightcferr1Down );
    theTree->SetBranchAddress( "bWeight_up_cferr2", &bWeightcferr2Up );
    theTree->SetBranchAddress( "bWeight_down_cferr2", &bWeightcferr2Down );
    theTree->SetBranchAddress( "bWeight_up_jes", &bWeightjerUp );
    theTree->SetBranchAddress( "bWeight_down_jes", &bWeightjerDown );
    theTree->SetBranchAddress( "bWeight_up_lf", &bWeightlfUp );
    theTree->SetBranchAddress( "bWeight_down_lf", &bWeightlfDown );
    
    std::cout << "[loopInSample] Finished assigning lepton weights" << std::endl;
  }
  
  //  std::vector<float> bTagSysts;
  //  setbTagVars(theTree);
  
  if (theTree ==0) cout << "No TTree found for " << sampleName << "!" << std::endl;

  std::tuple<float,float> bSysts (std::make_pair(1.,1.));

  //Loop over the events
  std::cout << theTree->GetEntries() << " events in loop for sample " << sampleName << std::endl; 
  for (int i = 0; i < theTree->GetEntries(); i++){
    //if (i > 20000) break;
    if (i%500 == 0){
      printf ("Processing event %i\r", i);
      fflush(stdout);
    }
    theTree->GetEntry(i);

    mvaValue = reader->EvaluateMVA("BDT");

    fillHists(sampleName,treevars,mvaValue,theweight);
    //Now fill the weight-based systematic histograms
    if (!isData){
      fillHists(sampleName+"_PU_up",treevars,mvaValue,theweight * (puWeightUp/puWeight));
      fillHists(sampleName+"_PU_down",treevars,mvaValue,theweight * (puWeightDown/puWeight));
      fillHists(sampleName+"_LSF_up",treevars,mvaValue,theweight * (lepSFWeightUp/lepSFWeight));
      fillHists(sampleName+"_LSF_down",treevars,mvaValue,theweight * (lepSFWeightDown/lepSFWeight));
      bSysts = calculatebTagSyst(bWeight,{bWeighthfs1Up,bWeighthfs1Down,bWeighthfs2Up,bWeighthfs2Down,bWeightcferr1Up,bWeightcferr1Down,bWeightcferr2Up,bWeightcferr2Down,bWeightjerUp,bWeightjerDown,bWeightlfUp,bWeightlfDown});
      fillHists(sampleName+"_bTag_up",treevars,mvaValue,theweight * std::get<0>(bSysts));
      fillHists(sampleName+"_bTag_down",treevars,mvaValue,theweight * std::get<1>(bSysts));
    }
  }

} 

void mvaTool::createHists(TString sampleName){

  std::vector<TH1F*> histovect;

  //Make a histogram per variable
  for (unsigned int i = 0; i<varList.size(); i++){
    int nbins = 1;
    double xmin = -1000;
    double xmax = 1000;
    if (varList[i] ==  "M_DeltaRBJetLepton") {nbins = 20; xmin = 0; xmax = 6.;};
    if (varList[i] ==  "M_DeltaRlightjets") {nbins = 20; xmin = 0; xmax = 6.;};
    if (varList[i] == "M_topMass2_lep") {nbins = 20; xmin = 0.; xmax = 600.;};
    if (varList[i] == "M_Pt_AllJets2040") {nbins = 20; xmin = 0; xmax = 160;};
    if (varList[i] == "M_Pt_Lepton") {nbins = 20; xmin = 0.; xmax = 300.;};
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


    TH1F* histo = new TH1F((varList[i] + "_" + sampleName).Data(), (varList[i] + "_" + sampleName).Data(),nbins,xmin,xmax);
    histo->Sumw2();
    histovect.push_back(histo);
  }
  TH1F* histo = new TH1F(("MVA_"+sampleName).Data(),("MVA_"+sampleName).Data(),20,-0.8,0.8);
  histo->Sumw2();
  histovect.push_back(histo);
  
  theHistoMap[sampleName] = histovect;

}

void mvaTool::fillHists(TString sampleName, float* treevars, double mvaValue, double theweight){
  std::vector<TH1F*> histovect = theHistoMap[sampleName];

  for (unsigned int i=0; i < varList.size(); i++) histovect[i]->Fill(treevars[i],theweight);
  histovect.back()->Fill(mvaValue,theweight);
}

void mvaTool::saveHists(TFile* outFile){
  outFile->cd();
  for (auto histoMapElement: theHistoMap){
    for (auto hist: histoMapElement.second) hist->Write();
  }
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
      }
      else{
	systUp += pow((bWeightsSyst[i]/bCentral)-1,2);
      }
    }
  return std::make_tuple(1+sqrt(systUp),1-sqrt(systDown));
}
  
void mvaTool::makeStatVariationHists(TString sampleName, TFile * outputFile){
  TH1F * theDefaultMVA = theHistoMap[sampleName].back(); //We only need to do this to nominal.
  outputFile->cd();
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
