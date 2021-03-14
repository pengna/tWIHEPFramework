from ROOT import *

import subprocess, sys, os, time

Analyzerpath = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/"
#dirdetails=["bstar/Electron2016/","bstar/Electron2017/","bstar/Electron2018/"]
#dirdetails=["bstar/Electron2016/","bstar/Electron2017/","bstar/Electron2018/","bstar/Muon2016/","bstar/Muon2017/","bstar/Muon2018/"]
dirdetails=[
"bstar/HighCatStep400/Electron2016/","bstar/HighCatStep400/Electron2017/","bstar/HighCatStep400/Electron2018/","bstar/HighCatStep400/Muon2016/","bstar/HighCatStep400/Muon2017/","bstar/HighCatStep400/Muon2018/",
"bstar/LowCatStep400/Electron2016/","bstar/LowCatStep400/Electron2017/","bstar/LowCatStep400/Electron2018/","bstar/LowCatStep400/Muon2016/","bstar/LowCatStep400/Muon2017/","bstar/LowCatStep400/Muon2018/",
#"bstar/Preselection/Electron2016/","bstar/Preselection/Electron2017/","bstar/Preselection/Electron2018/","bstar/Preselection/Muon2016/","bstar/Preselection/Muon2017/","bstar/Preselection/Muon2018/",
"bstar/Preselection/MuonTTCR2018/","bstar/Preselection/ElectronTTCR2018/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/MuonTTCR2016/","bstar/Preselection/ElectronTTCR2017/","bstar/Preselection/MuonTTCR2017/"
#"bstar/Preselection/Electron2016/","bstar/Preselection/Electron2017/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/ElectronTTCR2017/",

]
#dirdetails=["bstar/HighMETLowBoostedJetpT/Electron2016/","bstar/HighMETLowBoostedJetpT/Electron2017/","bstar/HighMETLowBoostedJetpT/Electron2018/","bstar/HighMETLowBoostedJetpT/Muon2016/","bstar/HighMETLowBoostedJetpT/Muon2017/","bstar/HighMETLowBoostedJetpT/Muon2018/"]
#dirdetails=["bstar/HighCatStep200/Electron2016/","bstar/HighCatStep200/Electron2017/","bstar/HighCatStep200/Electron2018/","bstar/HighCatStep200/Muon2016/","bstar/HighCatStep200/Muon2017/","bstar/HighCatStep200/Muon2018/","bstar/HighCatStep400/Electron2016/","bstar/HighCatStep400/Electron2017/","bstar/HighCatStep400/Electron2018/","bstar/HighCatStep400/Muon2016/","bstar/HighCatStep400/Muon2017/","bstar/HighCatStep400/Muon2018/","bstar/LowCatStep200/Electron2016/","bstar/LowCatStep200/Electron2017/","bstar/LowCatStep200/Electron2018/","bstar/LowCatStep200/Muon2016/","bstar/LowCatStep200/Muon2017/","bstar/LowCatStep200/Muon2018/","bstar/LowCatStep400/Electron2016/","bstar/LowCatStep400/Electron2017/","bstar/LowCatStep400/Electron2018/","bstar/LowCatStep400/Muon2016/","bstar/LowCatStep400/Muon2017/","bstar/LowCatStep400/Muon2018/","bstar/Preselection/ElectronTTCR2018/","bstar/Preselection/Electron2018/","bstar/Preselection/MuonTTCR2018/","bstar/Preselection/Muon2018/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/Electron2016/","bstar/Preselection/MuonTTCR2016/","bstar/Preselection/Muon2016/","bstar/Preselection/ElectronTTCR2017/","bstar/Preselection/Electron2017/","bstar/Preselection/MuonTTCR2017/","bstar/Preselection/Muon2017/"]
#dirdetails=["bstar/1bjetCat/Electron2016/","bstar/1bjetCat/Electron2017/","bstar/1bjetCat/Electron2018/","bstar/1bjetCat/Muon2016/","bstar/1bjetCat/Muon2017/","bstar/1bjetCat/Muon2018/"]
#dirdetails=["bstar/Preselection/MuonTTCR2018/","bstar/Preselection/ElectronTTCR2018/","bstar/Preselection/ElectronTTCR2016/","bstar/Preselection/MuonTTCR2016/","bstar/Preselection/ElectronTTCR2017/","bstar/Preselection/MuonTTCR2017/"]
#dirdetails=["bstar/HighCatStep400/Electron2016/","bstar/HighCatStep400/Electron2017/","bstar/HighCatStep400/Electron2018/","bstar/HighCatStep400/Muon2016/","bstar/HighCatStep400/Muon2017/","bstar/HighCatStep400/Muon2018/","bstar/LowCatStep400/Electron2016/","bstar/LowCatStep400/Electron2017/","bstar/LowCatStep400/Electron2018/","bstar/LowCatStep400/Muon2016/","bstar/LowCatStep400/Muon2017/","bstar/LowCatStep400/Muon2018/"]
#dirdetails=["bstar/MuonTTCR2018/","bstar/Muon2018/","bstar/ElectronTTCR2018/","bstar/Electron2018/"]
#dirdetails=["bstar/METCorrectionCheck/Electron2016/","bstar/METCorrectionCheck/Muon2016/"]
#dirdetails=["bstar/Preselection/Muon2016/"]
#dirdetails=["bstar/Preselection/Muon2017/","bstar/HighCatStep400/Muon2017/"]
#dirdetails=["bstar/Muon2018/","bstar/MuonTTCR2018/","bstar/MuonQCDCR2018/","bstar/Electron2018/","bstar/ElectronTTCR2018/","bstar/ElectronQCDCR2018/"]

#systs = ["JESUp","JESDown","JERUp","JERDown"]
systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]
#systs = ["Systs"]
n=16
mergeAll = file(Analyzerpath+"mergeRLHTTCR.sh","w")
for dirdetail in dirdetails:
	for syst in systs:
		dirpath = Analyzerpath+dirdetail+syst+"/"
		for i in range( n ):
                        massPoint =str( (i+1)*200+1000)
			print >> mergeAll," hadd -f " + dirpath+"output_Vector_"+massPoint+".root "+dirpath+"output_RH_"+massPoint+".root " + dirpath+"output_LH_"+massPoint+".root " 
