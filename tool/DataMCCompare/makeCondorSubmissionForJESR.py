from ROOT import *

import subprocess, sys, os, time

#gROOT.ProcessLine(".L /publicfs/cms/user/duncanleg/tW13TeV/tmva/mvaTool.C+")


onlySignal = False


Catname=""
dirdetail = sys.argv[1]
Catname = sys.argv[2]
Analyzerpath = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/"
#outDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"+dirdetail+"/"
#outDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/LowCat/"+dirdetail+"/"
#outDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/HighCatStep400/"+dirdetail+"/"
outDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"+Catname+"/"+dirdetail+"/"
sysname = "Systs"
inDir = "/publicfs/cms/user/pengn/FullRunIIdataV2/tWIHEPFramework/bstar/"+dirdetail


elePostfix = ""

#####2018
samples = ["QCDHT100To200","QCDHT200To300","QCDHT300To500","QCDHT500To700","QCDHT700To1000","QCDHT1000To1500","QCDHT1500To2000","QCDHT2000Toinf","TTToSemiLeptonic","TTToHadronic","TTTo2L2Nu","WW","WZ","ZZ","ST","SaT","RH_1200","RH_1400","RH_1600","RH_1800","RH_2000","RH_2200","RH_2400","RH_2600","RH_2800","RH_3000","LH_1200","LH_1400","LH_1600","LH_1800","LH_2000","LH_2200","LH_2400","LH_2600","LH_2800","LH_3000","WJetHT70To100","WJetHT100To200","WJetHT200To400","WJetHT400To600","WJetHT600To800","WJetHT800To1200","WJetHT1200To2500","WJetHT2500ToInf","RH_3200","RH_3400","RH_3600","RH_3800","RH_4000","RH_4200","LH_3200","LH_3400","LH_3600","LH_3800","LH_4000","LH_4200"]
if "2018" in dirdetail:
	samplesDataMu = ["SMu_A","SMu_B","SMu_C","SMu_D"]
	samplesDataEle = ["SEle_A","SEle_B","SEle_C","SEle_D"]
elif "2017" in dirdetail:
	samplesDataMu = ["SMu_B","SMu_C","SMu_D","SMu_E","SMu_F"]
 	samplesDataEle = ["SEle_B","SEle_C","SEle_D","SEle_E","SEle_F"]
elif "2016" in dirdetail:
	samplesDataMu = ["SMu_B","SMu_C","SMu_D","SMu_E","SMu_F","SMu_G","SMu_H"]
	samplesDataEle = ["SEle_B","SEle_C","SEle_D","SEle_E","SEle_F","SEle_G","SEle_H"]
	samples = ["QCDHT100To200","QCDHT200To300","QCDHT300To500","QCDHT500To700","QCDHT700To1000","QCDHT1000To1500","QCDHT1500To2000","QCDHT2000Toinf","TT","WW","WZ","ZZ","ST","SaT","RH_1200","RH_1400","RH_1600","RH_1800","RH_2000","RH_2200","RH_2400","RH_2600","RH_2800","RH_3000","LH_1200","LH_1400","LH_1600","LH_1800","LH_2000","LH_2200","LH_2400","LH_2600","LH_2800","LH_3000","WJetHT70To100","WJetHT100To200","WJetHT200To400","WJetHT400To600","WJetHT600To800","WJetHT800To1200","WJetHT1200To2500","WJetHT2500ToInf","RH_3200","RH_3400","RH_3600","RH_3800","RH_4000","RH_4200","LH_3200","LH_3400","LH_3600","LH_3800","LH_4000","LH_4200"]

samplesData = [] 

if "Muon" in dirdetail:samplesData = samplesDataMu
elif "Electron" in dirdetail:samplesData = samplesDataEle
else : print "not right channel define"
#t = mvaTool()
regions = [""]
if onlySignal: regions = [""]


processes = []
systs = ["JESUp","JESDown","JERUp","JERDown"]
#systs=[""]
systDir = ""

if (not os.path.isdir(outDir+"/submit/")):
    subprocess.call("mkdir -p "+outDir + "/submit/",shell=True)
if (not os.path.isdir(outDir+"/logs/")):
    subprocess.call("mkdir -p "+outDir + "/logs/",shell=True)
if (not os.path.isdir(outDir+"/Jobs/")):
    subprocess.call("mkdir -p "+outDir + "/Jobs/",shell=True)

for i in range(len(regions)):

    region = regions[i]

    
    if (not os.path.isdir(outDir+region)):
        subprocess.call("mkdir -p "+outDir+region+"/",shell=True)
    if (not os.path.isdir(outDir+"Systs"+region+"/")):
   	subprocess.call("mkdir -p "+outDir+"Systs"+region+"/",shell=True)
    for syst in systs:
        if (not os.path.isdir(outDir+syst+region+"/")):
            subprocess.call("mkdir -p "+outDir+syst+region+"/",shell=True)

def prepareSubmitJob(submitFileName,cshFileName, outPutFileName, errorFileName):
        cshFile      = file(submitFileName,"w")
        print >> cshFile, "Universe     = vanilla"
        print >> cshFile, "getenv       = true"
        print >> cshFile, "accounting_group = cms"
        print >> cshFile, "Executable   = ",cshFileName
        print >> cshFile, "Output       = ",outPutFileName
        print >> cshFile, "Error        = ",errorFileName
        print >> cshFile, "Queue"




def prepareCshJob(submitFileName,directory,commandToRun):
    subFile      = file(submitFileName,"w")
    print >> subFile, "#!/bin/bash"
#    print >> subFile, "/bin/hostname"
    print >> subFile, "gcc -v"
 #   print >> subFile, "pwd"
#    print >> subFile, "source /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 6.08.02"
    print >> subFile, "cd {0}".format(directory)
    print >> subFile, commandToRun
    subprocess.call("chmod 777 "+submitFileName,shell=True)

def makeSubmissionFiles(systDir):
    
    toRun = []
    toDir = []
    for sample in samples:
	        
        print "{0} is done ".format(sample)                  
       
	runSample = False
	if runSample: toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+"\",\""+outDir+sysname+"\",false)\'")
	thisDir = outDir+sysname+ "/Jobs/"+sample+"/"                               
	print thisDir
	toDir.append(thisDir)
	os.popen('mkdir -p '+thisDir)
	command_cp_cc = 'cp '+Analyzerpath+"/scripts/"+Catname+"/runReadingNoMVA.C "+thisDir
	command_cp_c = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.C "+thisDir
	command_cp_h = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.h "+thisDir
	os.system(command_cp_cc)
	os.system(command_cp_c)
	os.system(command_cp_h)
	
	for syst in systs:
		thisDir = outDir+syst+ "/Jobs/"+sample+"/"
		print thisDir
		toDir.append(thisDir)
		os.popen('mkdir -p '+thisDir)
		command_cp_cc = 'cp '+Analyzerpath+"/scripts/"+Catname+"/runReadingNoMVA.C "+thisDir
		command_cp_c = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.C "+thisDir
		command_cp_h = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.h "+thisDir
		os.system(command_cp_cc)
		os.system(command_cp_c)
        	os.system(command_cp_h)
		runCUT = False 
		runJESR = True
		if runJESR:toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+syst+"/\",\""+outDir+syst+"\",false)\'")
		if runCUT:toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+"/\",\""+outDir+syst+"\",false)\'")

    for sample in samplesData:
        print "{0} is done ".format(sample)
	runData= False

	if runData : toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+"\",\""+outDir+sysname+"\",true)\'")
        thisDir = outDir+sysname+ "/Jobs/"+sample+"/"                                
	print thisDir
	toDir.append(thisDir)
	os.popen('mkdir -p '+thisDir)
	command_cp_cc = 'cp '+Analyzerpath+"/scripts/"+Catname+"/runReadingNoMVA.C "+thisDir
        command_cp_c = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.C "+thisDir  	
        command_cp_h = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.h "+thisDir
        os.system(command_cp_cc)
        os.system(command_cp_c)
        os.system(command_cp_h)
	for syst in systs:
                thisDir = outDir+syst+ "/Jobs/"+sample+"/"
		print thisDir
		toDir.append(thisDir)
		os.popen('mkdir -p '+thisDir)
		command_cp_cc = 'cp '+Analyzerpath+"/scripts/"+Catname+"/runReadingNoMVA.C "+thisDir
		command_cp_c = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.C "+thisDir
                command_cp_h = 'cp '+Analyzerpath+"/scripts/"+Catname+"/mvaTool.h "+thisDir
		os.system(command_cp_cc)
		os.system(command_cp_c)
		os.system(command_cp_h)
		runCUTdata = False
		#runJESRdata = True
		runJESRdata = False
                if runJESRdata:toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+syst+"/\",\""+outDir+syst+"\",true)\'")
                if runCUTdata:toRun.append("root -l -b -q runReadingNoMVA.C+\'(\""+sample+"\",\""+inDir+"/\",\""+outDir+syst+"\",true)\'")



    nFinished = 0
    nRunning = 0

    #Here we will make condor submission jobs instead of just running it locally because that just won't work anymore.
    submitAll = file(outDir+"/submit/submitAll.sh","w")
    print >> submitAll, "#!/bin/bash"
    dir_path = os.path.dirname(os.path.realpath(__file__))

    for runNum in range(len(toRun)):
        prepareCshJob(outDir+"/submit/submissionJob{0}.sh".format(runNum),toDir[runNum],toRun[runNum])
#        prepareSubmitJob(outDir+"submit/submissionJob{0}.submit".format(runNum),outDir+"submit/submissionJob{0}.sh".format(runNum),outDir+"logs/submissionJob{0}.log".format(runNum),outDir+"logs/submissionJob{0}.err".format(runNum))
 #       print >> submitAll, "condor_submit {0}submit/submissionJob{1}.submit -name job@schedd01.ihep.ac.cn".format(outDir,runNum)
     #   print >> submitAll, "hep_sub {0}submit/submissionJob{1}.sh -o".format(outDir,runNum)+" {0}logs/submissionJob{1}.log -e ".format(outDir,runNum)+"{0}logs/submissionJob{1}.err".format(outDir,runNum)+" -g cms -wt short"
        print >> submitAll, "hep_sub {0}submit/submissionJob{1}.sh -o".format(outDir,runNum)+" {0}logs/submissionJob{1}.log -e ".format(outDir,runNum)+"{0}logs/submissionJob{1}.err".format(outDir,runNum)
    print "Made {0} submission files".format(len(toRun))

if __name__ == "__main__":
    makeSubmissionFiles(systDir)
    print "Made submission files"
