#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys

datasets = ["tW_top","tW_antitop","ttbar","ww","wz","zz","zPlusJetsHighMass","zPlusJetsLowMass","tChan","sChan","wPlusJets","qcd100_200","qcd200_300","qcd300_500","qcd500_700","qcd700_1000","qcd1000_1500","qcd1500_2000","qcd2000_inf"]
#datasets = ["tW_top"]
datasetID = {"tW_top":100000,"tW_antitop":100001,"ttbar":100004,"ww":100007,"wz":100008,"zz":100009,"zPlusJetsHighMass":100004,"zPlusJetsLowMass":100005,"tChan":100002,"sChan":100010,"wPlusJets":100006,"qcd100_200":100011,"qcd200_300":100012,"qcd300_500":100013,"qcd500_700":100014,"qcd700_1000":100015,"qcd1000_1500":100016,"qcd1500_2000":100017,"qcd2000_inf":100018}
nFilesDataset = {"tW_top":23,"tW_antitop":27,"ttbar":2413,"ww":26,"wz":25,"zz":24,"zPlusJetsHighMass":682,"zPlusJetsLowMass":753,"tChan":478,"sChan":24,"wPlusJets":1145,"qcd100_200":1925,"qcd200_300":458,"qcd300_500":497,"qcd500_700":472,"qcd700_1000":356,"qcd1000_1500":125,"qcd1500_2000":99,"qcd2000_inf":55}
datasetDirs = {"tW_top":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_Full2202_ST/160222_223524/0000/",
"tW_antitop":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_Full2202_SaT/160222_223547/0000.",
"ttbar":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_Full2202_TT/160222_223457/0000/",
"ww":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/WW_TuneCUETP8M1_13TeV-pythia8/crab_Full2202_WW/160222_223947/0000/",
"wz":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/WZ_TuneCUETP8M1_13TeV-pythia8/crab_Full2202_WZ/160222_224007/0000/",
"zz":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_Full2202_ZZ/160222_224032/0000/",
"zPlusJetsHighMass":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_Full2202_amcDY/160222_223759/0000",
"zPlusJetsLowMass":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_Full2202_amcDY1050/160222_223718/0000/",
"tChan":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_Full2202_STt/160222_223629/0000/",
"sChan":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_Full2202_STs/160222_223608/0000/",
"wPlusJets":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_WJets/160222_223915/0000/",
"qcd100_200":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT100to200/160222_224054/0000/",
"qcd200_300":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT200to300/160222_224121/0000/",
"qcd300_500":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT300to500/160222_224202/0000/",
"qcd500_700":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT500to700/160222_224225/0000/",
"qcd700_1000":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT700to1000/160222_224245/0000",
"qcd1000_1500":"publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT1000to1500/160222_224313/0000/",
"qcd1500_2000":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT1500to2000/160222_224332/0000/",
"qcd2000_inf":"/publicfs/cms/data/TopQuark/cms13TeV/Samples2202/mc/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_Full2202_QCD_HT2000toInf/160222_224406/0000/"}

import sys, math, mmap

namesPerFile = float(raw_input("How many files to run over per job? "))
if namesPerFile == 0:
    print "You idiot, we can't divide by 0"
    sys.exit()
outputDirectory = raw_input("Output directory: ")

for dataset in datasets:
    nJobs = int(math.ceil(nFilesDataset[dataset]/namesPerFile))
    print ("Dataset: {0}, ID: {1}. Number of jobs created = {2}".format(dataset,datasetID[dataset],nJobs))
    bigDatasetFile = open("config/files/full/"+dataset+".list")
    s = mmap.mmap(bigDatasetFile.fileno(), 0, access=mmap.ACCESS_READ)
    for i in range(nJobs):
        currentFile = open(outputDirectory + dataset + str(i) + ".list","w")
        currentFile.write("Name: " + dataset)
        currentFile.write("\nNumber: " + str(datasetID[dataset]) + "_1\n")
        maxFiles = (i+1)*namesPerFile+1
        if nFilesDataset[dataset]+1 < maxFiles: maxFiles = nFilesDataset[dataset]+1
        for j in range(i*namesPerFile+1,maxFiles):
            line = "OutTree_" + str(j) + ".root"
            if s.find(line) != -1:
                currentFile.write(datasetDirs[dataset] + line + "\n")
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
