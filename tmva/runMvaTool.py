from ROOT import *

import subprocess, sys, os, time

#gROOT.ProcessLine(".L /publicfs/cms/user/duncanleg/tW13TeV/tmva/mvaTool.C+")

reducedttbarSet = False

onlySignal = False

nProcesserAtATime = 5

outDir = sys.argv[1]

elePostfix = ""

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]

samplesData = samplesDataMu
if reducedttbarSet: samplesData = []

if "ele" in sys.argv:
    elePostfix = "Ele"
    samplesData = samplesDataEle

#t = mvaTool()

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMadgraph","wPlusJetsMCatNLO","ttbar","ttbarBU"]
if reducedttbarSet: samples = ["ttbar"]

regions = ["3j1t","3j2t","2j1t","4j1t","4j2t"]
if reducedttbarSet: regions = [""]
if onlySignal: regions = [""]

#samples = ["tW_top_nfh","tW_antitop_nfh"]

processes = []
systs = ["JESUp","JESDown","JERUp","JERDown"]
if reducedttbarSet or onlySignal: systs = []

systDir = ""
systDir = "tWSysts"+elePostfix
#if len(sys.argv) > 2:
#    systDir = sys.argv[2]
if reducedttbarSet or onlySignal: systDir = ""

for i in range(len(regions)):

    region = regions[i]

    if (not os.path.isdir(outDir+region)):
        subprocess.call("mkdir -p "+outDir+region+"/",shell=True)
    if (not os.path.isdir(outDir+"Systs"+region+"/")):
        subprocess.call("mkdir -p "+outDir+"Systs"+region+"/",shell=True)
    if (not os.path.isdir(outDir+"QCD"+region+"/")):
        subprocess.call("mkdir -p "+outDir+"QCD"+region+"/",shell=True)
    for syst in systs:
        if (not os.path.isdir(outDir+syst+region+"/")):
            subprocess.call("mkdir -p "+outDir+syst+region+"/",shell=True)

def runMvaOnce(systDir):
    
    toRun = []

    for sample in samples:
            #    continue
        runSample = False
        for region in regions:
            if not os.path.exists(outDir+region+"/output_"+sample+".root") or os.stat(outDir+region+"/output_"+sample+".root").st_size < 350: runSample = True
        if runSample: toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+elePostfix+"/\\\",\\\""+outDir+"\\\");\"")
        for syst in systs:
            runSysts = False
            for region in regions:
                if not os.path.exists(outDir+syst+region+"/output_"+sample+".root") or os.stat(outDir+syst+region+"/output_"+sample+".root").st_size < 350: runSysts = True
            if runSysts: toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+syst+elePostfix+"/\\\",\\\""+outDir+syst+"\\\");\"")

    for sample in samplesData:
        #    continue
        runData = False
        for region in regions:
            if not os.path.exists(outDir+region+"/output_"+sample+".root") or os.stat(outDir+region+"/output_"+sample+".root").st_size < 350: runData = True
        if runData: toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tWData"+elePostfix+"/\\\",\\\""+outDir+"\\\",);\"")
        runQCD = False
        for region in regions:
            if not os.path.exists(outDir+"QCD"+region+"/output_"+sample+".root") or os.stat(outDir+"QCD"+region+"/output_"+sample+".root") < 350: runQCD = True
        if runQCD: toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tWInvData"+elePostfix+"/\\\",\\\""+outDir+"QCD\\\",);\"")

    #And do the theory uncertainties if they exist
    if systDir:
        for sample in os.listdir(systDir):
            systDir = "tW{0}Systs{1}/".format("",elePostfix)
            runSyst = False
            for region in regions:
                if not os.path.exists(outDir+"Systs"+region+"/output_"+sample+".root") or os.stat(outDir+"Systs"+region+"/output_"+sample+".root").st_size < 350: runSyst = False
            if runSyst: toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\""+systDir+"/\\\",\\\""+outDir+"Systs\\\","+str(i)+");\"")

    nFinished = 0
    nRunning = 0

    while True:
        if len(toRun) == 0:
            print "No processes to run!"
            return False
        if len(processes)>0:
            i = 0
            while i < (len(processes)):
                if i >= len(processes): break
                if processes[i].poll() == 0:
                    processes.pop(i)
                    nFinished += 1
                i+=1
        while len(processes) < nProcesserAtATime and len(processes) < len(toRun):
            processes.append(subprocess.Popen(toRun[nRunning],shell=True))
            nRunning+=1
        time.sleep(5)
        if nFinished == len(toRun):
            break
    #
    print "Exited correctly after running {0} jobs".format(len(toRun))
    #print processes.keys()
    #for key in processes.keys():
    #    processes[key].wait()
    #
    #print processes.keys()
    return True

if __name__ == "__main__":
    runAgain = runMvaOnce(systDir)
    while runAgain:
        runAgain = runMvaOnce(systDir)
