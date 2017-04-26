#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"
treeName = "OutTree_ttbar_"

datasets = ["tW_top","tW_antitop","ttbar","ww","wz","zz","zPlusJetsHighMass","zPlusJetsLowMass","sChan","qcd100_200","qcd200_300","qcd300_500","qcd500_700","qcd700_1000","qcd1000_1500","qcd1500_2000","qcd2000_inf","wPlusJetsMCatNLO","tChan_top","tChan_antitop","SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG"]
#datasets = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG"]
#datasets = ["singleMuon"]
datasets = ["ttbar","ttbarBU"]
datasetID = {"tW_top":500000,"tW_antitop":500001,"ttbar":500024,"ww":500007,"wz":500008,"zz":500009,"zPlusJetsHighMass":500004,"zPlusJetsLowMass":500005,"tChan":500002,"sChan":500010,"wPlusJets":500006,"qcd100_200":500011,"qcd200_300":500012,"qcd300_500":500013,"qcd500_700":500014,"qcd700_1000":500015,"qcd1000_1500":500016,"qcd1500_2000":500017,"qcd2000_inf":500018,"wPlusJetsMCatNLO":500019,"tChan_antitop":500020,"tChan_top":500021,"SingMuB":400000,"SingMuB_1":400007,"SingMuC":400001,"SingMuD":400002,"SingMuE":400003,"SingMuF":400004,"SingMuG":400005,"SingMuG_1":400008,"SingMuH":400006,"ttbarBU":500025}
nFilesDataset = {"tW_top":14,"tW_antitop":17,"ttbar":983,"ww":11,"wz":30,"zz":12,"zPlusJetsHighMass":477,"zPlusJetsLowMass":237,"tChan":478,"sChan":21,"wPlusJets":422,"qcd100_200":738,"qcd200_300":179,"qcd300_500":199,"qcd500_700":210,"qcd700_1000":184,"qcd1000_1500":90,"qcd1500_2000":80,"qcd2000_inf":36,"singleMuon":1072,"wPlusJetsMCatNLO":300,"tChan_antitop":406,"tChan_top":723,"SingMuB":1756,"SingMuB_1":740,"SingMuC":580,"SingMuD":972,"SingMuE":826,"SingMuF":603,"SingMuG":1423,"SingMuG_1":320,"ttbarBU":1192}
datasetDirs = {"tW_top":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/crab_tW_topReTrig/170210_081934/0000/"],
"tW_antitop":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/crab_tW_antitopReTrig/170210_082043/0000/"],
#"ttbar":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8-evtgen/crab_TTpowhegReTrig/170210_081831/0000/"],
"ttbar":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_ttbarNewReTrig/170404_120840/0000/"],
"ttbarBU":["/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_ttbarBackupNewReTrig/170404_121029/0000/","/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_ttbarBackupNewReTrig/170404_121029/0001/"],
"ww":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/WW_TuneCUETP8M1_13TeV-pythia8/crab_WWReTrig/170210_103335/0000/"],
"wz":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZReTrig/170210_083217/0000/"],
"zz":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZReTrig/170210_083340/0000/"],
"zPlusJetsHighMass":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_ZJets_M-50ReTrig/170210_103203/0000/"],
"zPlusJetsLowMass":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ZJets_M-10-50ReTrig/170210_082606/0000/"],
"tChan":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_/0000/"],
"tChan_top":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChanTReTrig/170210_082257/0000/"],
"tChan_antitop":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/crab_tChanTbarReTrig/170210_082143/0000/"],
"sChan":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_sChanReTrig/170210_082418/0000/"],
"wPlusJets":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsaMCatNLOReTrig/170210_083000/0000/"],
"qcd100_200":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd100_200ReTrig/170210_103443/0000/"],
"qcd200_300":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd200_300ReTrig/170210_083759/0000/"],
"qcd300_500":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd300_500ReTrig/170210_105633/0000/"],
"qcd500_700":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd500_700ReTrig/170210_105746/0000/"],
"qcd700_1000":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd700_1000ReTrig/170210_084005/0000/"],
"qcd1000_1500":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd1000_1500ReTrig/170210_084106/0000/"],
"qcd1500_2000":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd1500_2000ReTrig/170210_105902/0000/"],
"qcd2000_inf":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_qcd2000_InfReTrig/170210_084346/0000/"],
"singleMuon":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_Full2202_SMu_16Dec2015S_JsonGold/160224_170442/0000/"],
"wPlusJetsMCatNLO":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/mc/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsaMCatNLOReTrig/170210_083000/0000/"],
"SingMuB":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuBReTrig/170210_083224/0000/","/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuBReTrig/170210_083224/0001/"],
"SingMuC":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuCReTrig/170210_083351/0000/"],
"SingMuD":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuDReTrig/170210_105844/0000/"],
"SingMuE":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuEReTrig/170210_102817/0000/"],
"SingMuF":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuFReTrig/170210_083759/0000/"],
"SingMuG":["/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuGReTrig/170210_084032/0000/","/acfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/moriond17/data/SingleMuon/crab_SingMuGReTrig/170210_084032/0001/"]
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
            line = treeName + str(j) + ".root"
            fileLocation = ""
            fileSize = 0.
            for dataDir in datasetDirs[dataset]:
                if os.path.exists(dataDir+treeName+str(j)+".root"):
                    statinfo = os.stat(dataDir+treeName+str(j)+".root")
                    if statinfo.st_size > fileSize:
                        fileLocation = dataDir+treeName+str(j)+".root"
                        fileSize = statinfo.st_size
            if not fileLocation == "" and fileSize > 0:
                currentFile.write(fileLocation+"\n")
            elif copyScript: 
                fileNameForCopy = dataDir.split("tWlJetSamples/moriond17/")[-1]
                if "mc/" in fileNameForCopy: fileNameForCopy = "mcMoriond17/" + fileNameForCopy.split("mc/")[-1]
                else: fileNameForCopy = "reRecoData/"+fileNameForCopy.split("data/")[-1]
                copyScript.write("srmcp --debug srm://srm.ihep.ac.cn/pnfs/ihep.ac.cn/data/cms/store/user/leggat/tWSamples/"+ fileNameForCopy + treeName+str(j) +".root file:///" + dataDir+"\n")
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
            line = treeName + str(j) + ".root"
            if s.find(line) != -1:
                currentFile.write(remoteDir + line + "\n")
#                print line
#            currentFile.write(remoteDir + "
        
        
    
print "Thank you for using the create jobs program. Have a nice day"
