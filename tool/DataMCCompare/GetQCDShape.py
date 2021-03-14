from ROOT import *
#import ROOT 
#from setTDRStyle import setTDRStyle
from random import *
from array import *
import math
import sys,os
import numpy as np

Indir="/afs/ihep.ac.cn/users/p/pengn/WorkSpace/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"
NReBins =9
nominal={}
#xbins = [0.0,400.0,800.0,1200.0,1600.0,2000.0,2400.0,4000.0]
xbins = [0.0,400.0,800.0,1200.0,1600.0,2000.0,2400.0,2800.0,4000.0]
Bincontents={}
#print xbins 
#dirdetails=["LowCatStep400"]
dirdetails=["Preselection"]
#dirdetails=["LToMWRBtag/LooseBtag"]
#regions=["Muon2016","Muon2017","Muon2018","Electron2016","Electron2017","Electron2018"]
regions=["MuonAntiWtag2016","MuonAntiWtag2017","MuonAntiWtag2018","ElectronAntiWtag2016","ElectronAntiWtag2017","ElectronAntiWtag2018"]
#regions=["Electron2018"]
#regions=["MuonTTCR2016","MuonTTCR2017","MuonTTCR2018","ElectronTTCR2016","ElectronTTCR2017","ElectronTTCR2018"]

var="M_Mass_bstar"
Systs =["Sys","PU","LSF","LepIDSF","LepRecoSF","Trig","bTag_bc","bTag_udsg","WSF","Toppt_a","Toppt_b","PDFHess","topsfmerged","topsfunmerged","topsfsemimerged"]
#systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]

systs = ["Systs"]
#samples = ["Data","QCD","TT","WW","WZ","ZZ","ST","SaT","RH_1200","RH_1400","RH_1600","RH_1800","RH_2000","RH_2200","RH_2400","RH_2600","RH_2800","RH_3000","LH_1200","LH_1400","LH_1600","LH_1800","LH_2000","LH_2200","LH_2400","LH_2600","LH_2800","LH_3000","WJetsHT","RH_3200","RH_3400","RH_3600","RH_3800","RH_4000","RH_4200","LH_3200","LH_3400","LH_3600","LH_3800","LH_4000","LH_4200","allbkg","othbkg"]
systematics=["up","down"]


def GetQCDShape(DataHist,BkgWoQCDHist,varname):
 #	NewHis=OldHis.Rebin(NReBins-1,varname,array("d",xbins))
	DataHist.Add(BkgWoQCDHist,-1)
	DataHist.SetDirectory(0)
        DataHist.Sumw2()
	newHist=DataHist.Clone(varname)
	newHist.SetDirectory(0)
        newHist.Sumw2()
	return newHist




if __name__ == "__main__":
	for dirs in dirdetails:
		for region in regions:
			for syst in systs:
				OutfileDir = Indir+"QCDShape"+dirs+"/"+region+"/"+syst+"/"
				if not os.path.exists(OutfileDir):
	        			os.popen('mkdir -p '+OutfileDir)
				DatainFileName = Indir+dirs+"/"+region+"/"+syst+"/output_Data.root"
				OthbkginFileName = Indir+dirs+"/"+region+"/"+syst+"/output_allbkgWOQCD.root"
				DatainFile = TFile(DatainFileName,"READ")
				OthbkginFile = TFile(OthbkginFileName,"READ")
				outFileName=OutfileDir+"output_QCDNewShape.root"
				outFile = TFile(outFileName,"recreate")
				outFile.cd()
				print DatainFileName
				varname=var
				print varname
				DataHis=DatainFile.Get(varname).Clone()
				DataHis.SetDirectory(0)
				DataHis.Sumw2()
				OthbkgHis=OthbkginFile.Get(varname).Clone()
                                OthbkgHis.SetDirectory(0)
                                OthbkgHis.Sumw2()
			 	NewHis=GetQCDShape(DataHis,OthbkgHis,varname)
				NewHis.Write()
				for Syst in Systs:
					for systematic in systematics:
						varname= var+"_"+Syst+"_"+systematic
						print varname
					
						DataHis=DatainFile.Get(var).Clone()
        		                        DataHis.SetDirectory(0)
	                	                DataHis.Sumw2()
                                		OthbkgHis=OthbkginFile.Get(varname).Clone()
                                		OthbkgHis.SetDirectory(0)
                                		OthbkgHis.Sumw2()
                                		NewHis=GetQCDShape(DataHis,OthbkgHis,varname)
                                		NewHis.Write()

				outFile.Close()
