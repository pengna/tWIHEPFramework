from ROOT import *

import subprocess, sys, os, time

Analyzerpath = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/"
#dirdetail="bstar/LowCat/"
#dirdetail="bstar/"
systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]
#systs = ["Systs"]
#dirdetails=["bstar/HighCatStep200/","bstar/HighCatStep400/","bstar/HighCat/","bstar/LowCatStep200/","bstar/LowCatStep400/","bstar/LowCat","bstar/Preselection/"]
#dirdetails=["bstar/HighermassregionTo4800/"]
#dirdetails=["bstar/LowCatStep400/"]
samples = ["Data","QCD","TT","WW","WZ","ZZ","ST","SaT","RH_1200","RH_1400","RH_1600","RH_1800","RH_2000","RH_2200","RH_2400","RH_2600","RH_2800","RH_3000","LH_1200","LH_1400","LH_1600","LH_1800","LH_2000","LH_2200","LH_2400","LH_2600","LH_2800","LH_3000","WJetsHT","RH_3200","RH_3400","RH_3600","RH_3800","RH_4000","RH_4200","LH_3200","LH_3400","LH_3600","LH_3800","LH_4000","LH_4200","allbkg"]

#samples=["allbkg","QCD"]
#samples=["allbkg"]
mergeAll = file(Analyzerpath+"mergecombineCat.sh","w")
for sample in samples:
	rootfilename = "output_"+sample+".root " 
	for syst in systs:
			HighCombineMuon2016dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Muon2016/"+syst+"/"
			HighCombineMuon2017dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Muon2017/"+syst+"/"
			HighCombineMuon2018dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Muon2018/"+syst+"/"
			LowCombineMuon2016dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Muon2016/"+syst+"/"
			LowCombineMuon2017dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Muon2017/"+syst+"/"
			LowCombineMuon2018dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Muon2018/"+syst+"/"
			CombineCatMuon2016 = Analyzerpath+"bstar/CombineCatStep400/"+"Muon2016/"+syst+"/"
			CombineCatMuon2017 = Analyzerpath+"bstar/CombineCatStep400/"+"Muon2017/"+syst+"/"
			CombineCatMuon2018 = Analyzerpath+"bstar/CombineCatStep400/"+"Muon2018/"+syst+"/"



			HighCombineElectron2016dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Electron2016/"+syst+"/"
			HighCombineElectron2017dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Electron2017/"+syst+"/"
			HighCombineElectron2018dirpath = Analyzerpath+"bstar/HighCatStep400/"+"Electron2018/"+syst+"/"
			LowCombineElectron2016dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Electron2016/"+syst+"/"
			LowCombineElectron2017dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Electron2017/"+syst+"/"
			LowCombineElectron2018dirpath = Analyzerpath+"bstar/LowCatStep400/"+"Electron2018/"+syst+"/"
			CombineCatElectron2016 = Analyzerpath+"bstar/CombineCatStep400/"+"Electron2016/"+syst+"/"
			CombineCatElectron2017 = Analyzerpath+"bstar/CombineCatStep400/"+"Electron2017/"+syst+"/"
			CombineCatElectron2018 = Analyzerpath+"bstar/CombineCatStep400/"+"Electron2018/"+syst+"/"



			if (not os.path.isdir(CombineCatMuon2016)):
    				subprocess.call("mkdir -p "+CombineCatMuon2016,shell=True)
			if (not os.path.isdir(CombineCatMuon2017)):
				subprocess.call("mkdir -p "+CombineCatMuon2017,shell=True)
			if (not os.path.isdir(CombineCatMuon2018)):
				subprocess.call("mkdir -p "+CombineCatMuon2018,shell=True)

			if (not os.path.isdir(CombineCatElectron2016)):
				subprocess.call("mkdir -p "+CombineCatElectron2016,shell=True)
			if (not os.path.isdir(CombineCatElectron2017)):
				subprocess.call("mkdir -p "+CombineCatElectron2017,shell=True)
			if (not os.path.isdir(CombineCatElectron2018)):
				subprocess.call("mkdir -p "+CombineCatElectron2018,shell=True)



			print >> mergeAll," hadd -f "+CombineCatMuon2016+rootfilename+"  "+LowCombineMuon2016dirpath+rootfilename+"  "+HighCombineMuon2016dirpath+rootfilename
			print >> mergeAll," hadd -f "+CombineCatMuon2017+rootfilename+"  "+LowCombineMuon2017dirpath+rootfilename+"  "+HighCombineMuon2017dirpath+rootfilename
			print >> mergeAll," hadd -f "+CombineCatMuon2018+rootfilename+"  "+LowCombineMuon2018dirpath+rootfilename+"  "+HighCombineMuon2018dirpath+rootfilename
			print >> mergeAll," hadd -f "+CombineCatElectron2016+rootfilename+"  "+LowCombineElectron2016dirpath+rootfilename+"  "+HighCombineElectron2016dirpath+rootfilename
			print >> mergeAll," hadd -f "+CombineCatElectron2017+rootfilename+"  "+LowCombineElectron2017dirpath+rootfilename+"  "+HighCombineElectron2017dirpath+rootfilename
			print >> mergeAll," hadd -f "+CombineCatElectron2018+rootfilename+"  "+LowCombineElectron2018dirpath+rootfilename+"  "+HighCombineElectron2018dirpath+rootfilename
