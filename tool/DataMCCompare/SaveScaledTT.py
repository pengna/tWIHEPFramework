from ROOT import *
#import ROOT 
from setTDRStyle import setTDRStyle
from random import *
from array import *
import math
import sys,os
allFileDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/Blind/"
vartodraw=["DeltaRPhilv","M_nBJet","M_DeltaRChosedBJetLepton","M_softdropmass_BoostedJet","M_Mass_BJet","M_Mass_LeadBJet","M_Mass_BoostedJet","M_Mass_W","M_Pt_Top","M_Pt_Topleadjet","M_prunedmass_BoostedJet","M_tau21_BoostedJet","M_tau32_BoostedJet","met","mTW","M_Pt_BoostedJet","M_Pt_BJet","M_Pt_LeadBJet","M_Pt_Lepton","M_Mass_Top","M_Mass_Topleadjet","M_Pt_W","M_Mass_bstar","M_Mass_bstarleadjet","M_Eta_BoostedJet","M_Eta_BJet","M_Eta_LeadBJet","M_Eta_Lepton"]
systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]
regions=["Muon2016","Muon2017","Muon2018","Electron2016","Electron2017","Electron2018"]
systsForAll = ["","_bTag_up","_bTag_down","_PU_up","_PU_down","_LSF_up","_LSF_down","_mistag_up","_mistag_down","_Trig_up","_Trig_down","_PDF_up","_PDF_down","_WSF_up","_WSF_down","_Toppt_a_up","_Toppt_a_down","_Toppt_b_up","_Toppt_b_down","_Sys_up","_Sys_down"]

for region in regions:

	if "Muon" in region and "2016" in region :
    		TTscale = 1.06
   # TTscale =  1.17
	elif "Muon" in region and "2017" in region :
    		TTscale= 1.09
   # TTscale= 0.802
	elif "Muon" in region and "2018" in region :
    #TTscale = 0.96
    		TTscale = 1.03

	elif "Electron" in region and "2016" in region :
   # TTscale =  0.938
    		TTscale =  0.9
	elif "Electron" in region and "2017" in region :
    		TTscale= 0.91
   # TTscale= 0.802
	elif "Electron" in region and "2018" in region :
    #TTscale = 0.96
   		 TTscale = 1.06
	else :
    		print ("wrong data year information")

	for sys in systs:
		inFileName=allFileDir+region+"/"+sys+"/output_TT.root"
		outFileName=allFileDir+region+"/"+sys+"/output_ttbar.root"
		inFile = TFile(inFileName,"READ")
        	outFile = TFile(outFileName,"recreate")
		outFile.cd()
		for var in vartodraw:
			for systema in systsForAll:
				print region,var,sys,systema
				mc=var+systema
				normal=inFile.Get(mc).Clone()
				normal.Scale(TTscale)
				normal.Write()
		outFile.Close()
