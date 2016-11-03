#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

datasets = ["tW_top","tW_antitop","ttbar","ww","wz","zz","zPlusJetsHighMass","zPlusJetsLowMass","sChan","qcd100_200","qcd200_300","qcd300_500","qcd500_700","qcd700_1000","qcd1000_1500","qcd1500_2000","qcd2000_inf","wPlusJetsMCatNLO","tChan_top","tChan_antitop","SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG"]
#datasets = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG"]
#datasets = ["singleMuon"]
datasetID = {"tW_top":300000,"tW_antitop":300001,"ttbar":300003,"ww":300007,"wz":300008,"zz":300009,"zPlusJetsHighMass":300004,"zPlusJetsLowMass":300005,"tChan":300002,"sChan":300010,"wPlusJets":300006,"qcd100_200":300011,"qcd200_300":300012,"qcd300_500":300013,"qcd500_700":300014,"qcd700_1000":300015,"qcd1000_1500":300016,"qcd1500_2000":300017,"qcd2000_inf":300018,"wPlusJetsMCatNLO":300019,"tChan_antitop":300020,"tChan_top":300021,"SingMuB":400000,"SingMuB_1":400007,"SingMuC":400001,"SingMuD":400002,"SingMuE":400003,"SingMuF":400004,"SingMuG":400005,"SingMuG_1":400008,"SingMuH":400006}
nFilesDataset = {"tW_top":25,"tW_antitop":26,"ttbar":334,"ww":24,"wz":24,"zz":25,"zPlusJetsHighMass":719,"zPlusJetsLowMass":738,"tChan":478,"sChan":24,"wPlusJets":1145,"qcd100_200":532,"qcd200_300":132,"qcd300_500":410,"qcd500_700":434,"qcd700_1000":354,"qcd1000_1500":114,"qcd1500_2000":89,"qcd2000_inf":46,"singleMuon":1072,"wPlusJetsMCatNLO":231,"tChan_antitop":520,"tChan_top":324,"SingMuB":1740,"SingMuB_1":740,"SingMuC":580,"SingMuD":972,"SingMuE":826,"SingMuF":601,"SingMuG":1320,"SingMuG_1":320}
datasetDirs = {"tW_top":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_tW_top/160930_153116/0000/"],
"tW_antitop":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_tW_antitop/160930_153157/0000/"],
"ttbar":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/TT_TuneCUETP8M1_13TeV-powheg-pythia8-evtgen/crab_TTpowheg/160930_153043/0000/"],
"ww":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW/160930_153626/0000/"],
"wz":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ/160930_153658/0000/"],
"zz":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ/160930_153727/0000/"],
"zPlusJetsHighMass":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ZJets_M-50/160930_153451/0000/"],
"zPlusJetsLowMass":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ZJets_M-10-50/160930_153421/0000/"],
"tChan":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_/0000/"],
"tChan_top":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChanT/160930_153319/0000/"],
"tChan_antitop":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChanTbar/160930_153238/0000/"],
"sChan":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_sChan/160930_153349/0000/"],
"wPlusJets":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_WJets/160222_223915/0000/"],
"qcd100_200":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd100_200/160930_153758/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd100_200/160930_153758/0000/"],
"qcd200_300":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd200_300/160930_153828/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd200_300/160930_153828/0000/"],
"qcd300_500":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd300_500/160930_153901/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd300_500/160930_153901/0000/"],
"qcd500_700":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd500_700/160930_153930/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd500_700/160930_153930/0000/"],
"qcd700_1000":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd700_1000/160930_154004/0000/"],
"qcd1000_1500":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd1000_1500/161003_133909/0000/"],
"qcd1500_2000":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd1500_2000/160930_154108/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd1500_2000/160930_154108/0000/"],
"qcd2000_inf":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd2000_Inf/160930_154140/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/qcd/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd2000_Inf/160930_154140/0000/"],
"singleMuon":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_Full2202_SMu_16Dec2015S_JsonGold/160224_170442/0000/"],
"wPlusJetsMCatNLO":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/mc/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsaMCatNLO/160930_153554/0000/"],
"SingMuB":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuB/160930_155025/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuB/160930_155025/0001/"],
"SingMuC":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuC/160930_155057/0000/"],
"SingMuD":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuD/160930_155130/0000/"],
"SingMuE":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuE/160930_155210/0000/"],
"SingMuF":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuF/160930_155245/0000/"],
"SingMuG":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuG/160930_155317/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/data/SingleMuon/crab_SingMuG/160930_155317/0001/"]
}

import sys, math, mmap, subprocess

namesPerFile = float(raw_input("How many files to run over per job? "))
if namesPerFile == 0:
    print "You idiot, we can't divide by 0"
    sys.exit()
outputDirectory = raw_input("Output directory: ")

finishCopyScripts = raw_input("File for additional copies: ")
copyScript = 0
if finishCopyScripts:
    copyScript = file(finishCopyScripts,"w")
    print copyScript.write("#!/bin/bash\n")

for dataset in datasets:
    nJobs = int(math.ceil(nFilesDataset[dataset]/namesPerFile))
    print ("Dataset: {0}, ID: {1}. Number of jobs created = {2}".format(dataset,datasetID[dataset],nJobs))
#    if os.path.exists("config/files/full80X/"+dataset+".list"): subprocess.call("rm config/files/full80X/"+dataset+".list",shell=True)
#    for dirName in datasetDirs[dataset]:
#        subprocess.call("\"ls\" "+dirName + "* >> config/files/full80X/"+dataset+".list",shell=True)
#    bigDatasetFile = open("config/files/full80X/"+dataset+".list")
#    s = mmap.mmap(bigDatasetFile.fileno(), 0, access=mmap.ACCESS_READ)
    for i in range(nJobs):
        currentFile = open(outputDirectory + dataset + str(i) + ".list","w")
        currentFile.write("Name: " + dataset)
        currentFile.write("\nNumber: " + str(datasetID[dataset]) + "_1\n")
        maxFiles = (i+1)*namesPerFile+1
        if nFilesDataset[dataset]+1 < maxFiles: maxFiles = nFilesDataset[dataset]+1
        for j in range(i*namesPerFile+1,maxFiles):
            line = "OutTree_" + str(j) + ".root"
            fileLocation = ""
            fileSize = 0.
            for dataDir in datasetDirs[dataset]:
                if os.path.exists(dataDir+"OutTree_"+str(j)+".root"):
                    statinfo = os.stat(dataDir+"OutTree_"+str(j)+".root")
                    if statinfo.st_size > fileSize:
                        fileLocation = dataDir+"OutTree_"+str(j)+".root"
                        fileSize = statinfo.st_size
            if not fileLocation == "" and fileSize > 0:
                currentFile.write(fileLocation+"\n")
            elif copyScript: 
                copyScript.write("srmcp --debug srm://srm.ihep.ac.cn/pnfs/ihep.ac.cn/data/cms/store/user/leggat/tWSamples/"+dataDir.split("tWlJetSamples/")[-1] + "OutTree_"+str(j) +".root file:///" + dataDir+"\n")
                print "Couldn't find file " + str(j)
#            if s.find(line) != -1:
#                currentFile.write(datasetDirs[dataset] + line + "")
#                print line
        

while False:
    datasetName = raw_input("Dataset name: ")
    if datasetName == "end" or datasetName == "stop": break
    datasetNum = raw_input("Corresponds to the number: ")
    totalDatasetFiles = float(raw_input("Total number of files in this dataset: "))
    nJobs = int(math.ceil(totalDatasetFiles/namesPerFile))
    print "That means we will make " + str(nJobs) + " jobs"
    remoteDir = raw_input("Remote directory: ")
    bigDatasetFile = open("config/files/full/"+datasetName+".list")
    s = mmap.mmap(bigDatasetFile.fileno(), 0, access=mmap.ACCESS_READ)
    for i in range(nJobs):
        currentFile = open(outputDirectory + datasetName + str(i) + ".list","w")
        currentFile.write("Name: "+datasetName)
        currentFile.write("\nNumber: " + datasetNum + "_1\n")
        maxFiles = (i+1)*namesPerFile+1
        if totalDatasetFiles+1 < maxFiles: maxFiles = totalDatasetFiles+1
        for j in range(i*namesPerFile+1,maxFiles):
            line = "OutTree_" + str(j) + ".root"
            if s.find(line) != -1:
                currentFile.write(remoteDir + line + "\n")
#                print line
#            currentFile.write(remoteDir + "
        
        
    
print "Thank you for using the create jobs program. Have a nice day"
