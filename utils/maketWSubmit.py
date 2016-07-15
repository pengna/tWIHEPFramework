import sys
import os
import glob
import string
#####
##   Parameters to be specified by the user
#####
#analysis and task
analysis = "tW"
taskname = "EvtSel"
#for the queue
workpath    = os.getcwd()+"/"+analysis +"/"
frameworkDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"
jobDir      = workpath+"/"+"Jobs"
AnalyzerDir = workpath+"/"+"Analyzer"
task        = analysis+"_"+taskname
rootplizer  = "Rootplizer_"+task+".cc"
headplizer  = "Rootplizer_"+task+".h"
#Directory of input files
sample=[
"qcd1000_1500",
"qcd100_200",
"qcd1500_2000",
"qcd2000_inf",
"qcd200_300",
"qcd300_500",
"qcd500_700",
"qcd700_1000",
"sChan",
"tChan",
"ttbar",
"tW_top",
"tW_antitop",
"wPlusJets",
"ww",
"wz",
"zz"
]
#####
##   The script itsself
#####
#cshFilePath = jobDir+"/"+"sh"
#logFilePath = jobDir+"/"+"log"
if os.path.exists(jobDir):
	os.popen('rm -fr '+jobDir)
if os.path.exists(AnalyzerDir):
        os.popen('rm -fr '+AnalyzerDir)
#os.popen('mkdir -p '+cshFilePath)
#os.popen('mkdir -p '+logFilePath)

allJobFileName = "all.sh"
allJobFile      = file(allJobFileName,"w")
print >> allJobFile, "#!/bin/bash"
print >> allJobFile, "cd ",analysis

MergeFileName = "merge.sh"
MergeFile      = file(MergeFileName,"w")
MergeSourceFile = " "
def prepareSubmitJob(submitFileName,cshFileName, outPutFileName, errorFileName):
	cshFile      = file(submitFileName,"w")
	print >> cshFile, "Universe     = vanilla"
	print >> cshFile, "getenv       = true"
	print >> cshFile, "Executable   = ",cshFileName
	print >> cshFile, "Output       = ",outPutFileName
	print >> cshFile, "Error        = ",errorFileName
	print >> cshFile, "Queue"

def prepareCshJob(sample,shFile,frameworkDir,workpath):
        subFile      = file(shFile,"w")
	print >> subFile, "#!/bin/bash"
	print >> subFile, "/bin/hostname"
	print >> subFile, "gcc -v"
	print >> subFile, "pwd"
	#print >> subFile, "cd /publicfs/cms/data/TopQuark/cms13TeV/software/root/bin/"
	#print >> subFile, "source thisroot.csh"
	#print >> subFile, "cd /publicfs/cms/user/libh/CMSSW_5_3_9/src/ttH_13Tev"
	#print >> subFile, "setenv SCRAM_ARCH slc5_amd64_gcc462"
	#print >> subFile, "source /cvmfs/cms.cern.ch/cmsset_default.csh"
	print >> subFile, "source  /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 5.34.18"
        #print >> subFile, "eval \`scramv1 runtime -sh\`"
        print >> subFile, "cd "+frameworkDir
	#print >> subFile, "cp ${jobDir}/getAhist.C ."
	print >> subFile, frameworkDir+"bin/Wt/Wt_generic.x -config "+frameworkDir+"SingleTop.Wt.LP.mm1+j.muonMSSmeardown.config -inlist "+frameworkDir+"config/files/full/"+sample+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+"+hists.root -skimfile "+workpath+"/"+sample+"/skims/"+sample+"Skim.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger Muon -PileUpWgt -BWgt"
        #print >> subFile, "root -b -q -l "+rootplizer+"'(\""+input+"\",\""+output+"\")'"
 
#for iroot in range(nroot):
for k in sample:
	print k
	sampleName = k
	
	#First, let's get rid of any 

	os.popen('mkdir -p '+workpath + sampleName)
	os.popen('mkdir -p '+workpath + sampleName + "/scripts")
	os.popen('mkdir -p '+workpath + sampleName + "/hists")
	os.popen('mkdir -p '+workpath + sampleName + "/skims")
	os.popen('mkdir -p '+workpath + sampleName + "/logs")

	submitFileName = workpath + sampleName + "/scripts/" + sampleName + ".submit"
	shFileName = workpath + sampleName + "/scripts/" + sampleName +  ".sh"
	logFileName = workpath + sampleName + "/logs/" + sampleName + ".log"
	errorFileName = workpath + sampleName + "/logs/" + sampleName + ".error"
	
	prepareSubmitJob(submitFileName, shFileName, logFileName, errorFileName)
	prepareCshJob(sampleName,shFileName,frameworkDir,workpath)

	submitPath = sampleName + "/scripts/" + sampleName + ".submit"

	print >> allJobFile, "condor_submit "+ submitPath + " -group cms -name job@schedd01.ihep.ac.cn"

print >> MergeFile, "cd",outputDirectory
print >> MergeFile, "hadd Merged_rootplas.root",MergeSourceFile

print >> allJobFile, "cd -"
