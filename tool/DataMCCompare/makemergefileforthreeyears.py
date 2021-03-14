from ROOT import *

import subprocess, sys, os, time

Analyzerpath = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/"
#dirdetail="bstar/LowCat/"
#dirdetail="bstar/"
systs = ["Systs","JESUp","JESDown","JERUp","JERDown"]
#systs = ["Systs"]
#dirdetails=["bstar/HighCatStep200/","bstar/HighCatStep400/","bstar/HighCat/","bstar/LowCatStep200/","bstar/LowCatStep400/","bstar/LowCat","bstar/Preselection/"]
dirdetails=["bstar/Preselection/","bstar/HighCatStep400/","bstar/LowCatStep400/"]
#dirdetails=["bstar/Preselection/"]
#dirdetails=["bstar/LowCatStep400/","bstar/HighCatStep400/"]
samples = ["Data","QCD","TT","WW","WZ","ZZ","ST","SaT","RH_1200","RH_1400","RH_1600","RH_1800","RH_2000","RH_2200","RH_2400","RH_2600","RH_2800","RH_3000","LH_1200","LH_1400","LH_1600","LH_1800","LH_2000","LH_2200","LH_2400","LH_2600","LH_2800","LH_3000","WJetsHT","RH_3200","RH_3400","RH_3600","RH_3800","RH_4000","RH_4200","LH_3200","LH_3400","LH_3600","LH_3800","LH_4000","LH_4200","allbkg","othbkg"]

#samples=["allbkg","QCD"]
#samples=["allbkg"]

mergeyears = file(Analyzerpath+"mergeyears.sh","w")
mergechannel = file(Analyzerpath+"mergechannel.sh","w")
mergeAll = file(Analyzerpath+"mergecombine.sh","w")
for dirdetail in dirdetails:
	for sample in samples:
		rootfilename = "output_"+sample+".root " 
		for syst in systs:
			Muon2016dirpath = Analyzerpath+dirdetail+"Muon2016/"+syst+"/"
			Muon2017dirpath = Analyzerpath+dirdetail+"Muon2017/"+syst+"/"
			Muon2018dirpath = Analyzerpath+dirdetail+"Muon2018/"+syst+"/"
			Electron2016dirpath = Analyzerpath+dirdetail+"Electron2016/"+syst+"/"
                	Electron2017dirpath = Analyzerpath+dirdetail+"Electron2017/"+syst+"/"
                	Electron2018dirpath = Analyzerpath+dirdetail+"Electron2018/"+syst+"/"

			MuonFullRunIIdirpath = Analyzerpath+dirdetail+"MuonFullRunII/"+syst+"/"
			ElectronFullRunIIdirpath = Analyzerpath+dirdetail+"ElectronFullRunII/"+syst+"/"
			Combine2016dirpath = Analyzerpath+dirdetail+"Combine2016/"+syst+"/"
			Combine2017dirpath = Analyzerpath+dirdetail+"Combine2017/"+syst+"/"
			Combine2018dirpath = Analyzerpath+dirdetail+"Combine2018/"+syst+"/"
			CombineFullRunIIdirpath = Analyzerpath+dirdetail+"CombineFullRunII/"+syst+"/"
			if (not os.path.isdir(MuonFullRunIIdirpath)):
    				subprocess.call("mkdir -p "+MuonFullRunIIdirpath,shell=True)
			if (not os.path.isdir(ElectronFullRunIIdirpath)):
				subprocess.call("mkdir -p "+ElectronFullRunIIdirpath,shell=True)
			if (not os.path.isdir(Combine2016dirpath)):
				subprocess.call("mkdir -p "+Combine2016dirpath,shell=True)
			if (not os.path.isdir(Combine2017dirpath)):
				subprocess.call("mkdir -p "+Combine2017dirpath,shell=True)
			if (not os.path.isdir(Combine2018dirpath)):
				subprocess.call("mkdir -p "+Combine2018dirpath,shell=True)
			if (not os.path.isdir(CombineFullRunIIdirpath)):
				subprocess.call("mkdir -p "+CombineFullRunIIdirpath,shell=True)


			print >> mergeyears," hadd -f "+MuonFullRunIIdirpath+rootfilename+"  "+Muon2016dirpath+rootfilename+"  "+Muon2017dirpath+rootfilename+"  "+Muon2018dirpath+rootfilename+"  " 
			print >> mergeyears," hadd -f "+ElectronFullRunIIdirpath+rootfilename+"  "+Electron2016dirpath+rootfilename+"  "+Electron2017dirpath+rootfilename+"  "+Electron2018dirpath+rootfilename+"  " 
			print >> mergechannel," hadd -f "+Combine2016dirpath+rootfilename+"  "+Muon2016dirpath+rootfilename+"  "+Electron2016dirpath+rootfilename 
			print >> mergechannel," hadd -f "+Combine2017dirpath+rootfilename+"  "+Muon2017dirpath+rootfilename+"  "+Electron2017dirpath+rootfilename 
			print >> mergechannel," hadd -f "+Combine2018dirpath+rootfilename+"  "+Muon2018dirpath+rootfilename+"  "+Electron2018dirpath+rootfilename 
			print >> mergeAll," hadd -f "+CombineFullRunIIdirpath+rootfilename+"  "+Combine2016dirpath+rootfilename+"  "+Combine2017dirpath+rootfilename+"  "+Combine2018dirpath+rootfilename+"  " 
