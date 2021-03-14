from ROOT import *

import subprocess, sys, os, time

Analyzerpath = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/"
#dirdetails=["bstar/Electron2016/","bstar/Electron2017/","bstar/Electron2018/"]
#dirdetails=["bstar/Electron2016/","bstar/Electron2017/","bstar/Electron2018/","bstar/Muon2016/","bstar/Muon2017/","bstar/Muon2018/"]
#dirdetails=[
#"bstar/HighCatStep400/Electron2016/","bstar/HighCatStep400/Electron2017/","bstar/HighCatStep400/Electron2018/","bstar/HighCatStep400/Muon2016/","bstar/HighCatStep400/Muon2017/","bstar/HighCatStep400/Muon2018/",
#"bstar/LowCatStep400/Electron2016/","bstar/LowCatStep400/Electron2017/","bstar/LowCatStep400/Electron2018/","bstar/LowCatStep400/Muon2016/","bstar/LowCatStep400/Muon2017/","bstar/LowCatStep400/Muon2018/",
#"bstar/Preselection/Electron2016/","bstar/Preselection/Electron2017/","bstar/Preselection/Electron2018/","bstar/Preselection/Muon2016/","bstar/Preselection/Muon2017/","bstar/Preselection/Muon2018/",
#"bstar/Preselection/MuonTTCR2018/","bstar/Preselection/ElectronTTCR2018/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/MuonTTCR2016/","bstar/Preselection/ElectronTTCR2017/","bstar/Preselection/MuonTTCR2017/"
#"bstar/Preselection/Electron2016/","bstar/Preselection/Electron2017/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/ElectronTTCR2017/",
#"bstar/MtWlessthan1200GeV/Electron2016/","bstar/MtWlessthan1200GeV/Electron2017/","bstar/MtWlessthan1200GeV/Electron2018/","bstar/MtWlessthan1200GeV/Muon2016/","bstar/MtWlessthan1200GeV/Muon2017/","bstar/MtWlessthan1200GeV/Muon2018/",
#"bstar/NewSR/Electron2016/","bstar/NewSR/Electron2017/","bstar/NewSR/Electron2018/","bstar/NewSR/Muon2016/","bstar/NewSR/Muon2017/","bstar/NewSR/Muon2018/",
#"bstar/HighCat1Bin/Electron2016/","bstar/HighCat1Bin/Electron2017/","bstar/HighCat1Bin/Electron2018/","bstar/HighCat1Bin/Muon2016/","bstar/HighCat1Bin/Muon2017/","bstar/HighCat1Bin/Muon2018/",
#"bstar/HighCat4Bin/Electron2016/","bstar/HighCat4Bin/Electron2017/","bstar/HighCat4Bin/Electron2018/","bstar/HighCat4Bin/Muon2016/","bstar/HighCat4Bin/Muon2017/","bstar/HighCat4Bin/Muon2018/",
#]
#dirdetails=["bstar/Preselection/MuonTTCR2018/","bstar/Preselection/ElectronTTCR2018/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/MuonTTCR2016/","bstar/Preselection/ElectronTTCR2017/","bstar/Preselection/MuonTTCR2017/"]
#dirdetails=["bstar/HighCatStep400/Electron2016/","bstar/HighCatStep400/Electron2017/","bstar/HighCatStep400/Electron2018/","bstar/HighCatStep400/Muon2016/","bstar/HighCatStep400/Muon2017/","bstar/HighCatStep400/Muon2018/","bstar/LowCatStep400/Electron2016/","bstar/LowCatStep400/Electron2017/","bstar/LowCatStep400/Electron2018/","bstar/LowCatStep400/Muon2016/","bstar/LowCatStep400/Muon2017/","bstar/LowCatStep400/Muon2018/"]
#dirdetails=["bstar/MuonTTCR2018/","bstar/Muon2018/","bstar/ElectronTTCR2018/","bstar/Electron2018/"]
#dirdetails=["bstar/METCorrectionCheck/Electron2016/","bstar/METCorrectionCheck/Muon2016/"]
dirdetails=["bstar/LToMWRBtag/LooseBtag/Electron2018/"]
#dirdetails=["bstar/Preselection/Muon2017/","bstar/HighCatStep400/Muon2017/"]
#dirdetails=["bstar/Muon2018/","bstar/MuonTTCR2018/","bstar/MuonQCDCR2018/","bstar/Electron2018/","bstar/ElectronTTCR2018/","bstar/ElectronQCDCR2018/"]

#systs = ["JESUp","JESDown","JERUp","JERDown"]
systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]
#systs = ["Systs"]

mergeAll = file(Analyzerpath+"mergeAll.sh","w")
#mergeAll = file(Analyzerpath+"mergeLowcat.sh","w")
for dirdetail in dirdetails:
	for syst in systs:
		dirpath = Analyzerpath+dirdetail+syst+"/"
		print >> mergeAll," hadd -f "+ dirpath+"output_QCD.root " +dirpath+"output_QCDHT*.root "
		print >> mergeAll," hadd -f "+ dirpath+"output_WJetsHT.root " +dirpath+"output_WJetHT*.root "
		print >> mergeAll," hadd -f "+ dirpath+"output_othbkg.root " +dirpath+"output_ST.root " +dirpath+"output_SaT.root " +dirpath+"output_WJetsHT.root " +dirpath+"output_WW.root " +dirpath+"output_WZ.root " +dirpath+"output_ZZ.root "
		if "2017" in dirdetail or "2018" in dirdetail : print >> mergeAll," hadd -f "+ dirpath+"output_TT.root " +dirpath+"output_TTTo*.root "
		if "Muon" in dirdetail and "2016" in dirdetail : print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SMu*.root "	
		elif "Muon" in dirdetail and "2018" in dirdetail : print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SMu*.root "	
		elif "Muon" in dirdetail and "2017" in dirdetail: print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SMu_C.root "+dirpath+"output_SMu_D.root "+dirpath+"output_SMu_E.root "+dirpath+"output_SMu_F.root "	
		elif "Electron" in dirdetail and "2016" in dirdetail: print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SEle*.root "	
		elif "Electron" in dirdetail and "2017" in dirdetail: print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SEle_C.root "+dirpath+"output_SEle_D.root "+dirpath+"output_SEle_E.root "+dirpath+"output_SEle_F.root "	
		elif "Electron" in dirdetail and "2018" in dirdetail: print >> mergeAll," hadd -f "+ dirpath+"output_Data.root " +dirpath+"output_SEle*.root "	
		print >> mergeAll," hadd -f "+ dirpath+"output_allbkgWOQCD.root " +dirpath+"output_TT.root "  +dirpath+"output_othbkg.root " 
		print >> mergeAll," hadd -f "+ dirpath+"output_allbkg.root " +dirpath+"output_TT.root " +dirpath+"output_QCD.root " +dirpath+"output_othbkg.root " 

