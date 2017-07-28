#ifndef mvaTool_h
#define mvaTool_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>

#include <TLorentzVector.h>

#include <iostream>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <tuple>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TThread.h"

#include "TMVAGui.C"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"




class mvaTool {
 public :
  mvaTool();
  //  ~mvaTool();

  void doTraining(TString inDir);
  void doReading(TString sampleName, TString inDir = "tW",TString outDir = "mvaOutput/", bool isData = false);

  //  void doReading();

 private:

  //Used to loop over things
  void processMCSample(TString sampleName,TString inDir,TString outDir, float * treevars, bool isData);
  void loopInSample(TString dirName, TString sampleName, float* treevars, bool isData);
  void createHists(TString sampleName);
  void fillHists(TString sampleName, float* treevars, double mvaValue, double theweight);
  void saveHists(TFile * outFile);
  void setbTagVars(TChain* theTree);

  void makeStatVariationHists(TString sampleName,TFile* outputFile);

  std::tuple<float,float> calculatebTagSyst(float,std::vector<float>);

  std::map<TString,std::vector<TH1F*> > theHistoMap;

  std::vector<TString > varList;
  std::vector<TString > samplelist;
  std::vector<TString > systlist;
  TString baseName;
  std::vector<float> bTagSysts;

  TMVA::Reader *reader;

  float theweight;
  float mvaValue;
};

#endif
