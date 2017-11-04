from ROOT import *

import subprocess, sys, os, time

#gROOT.ProcessLine(".L /publicfs/cms/user/duncanleg/tW13TeV/tmva/mvaTool.C+")

outDir = sys.argv[1]

elePostfix = ""

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]

samplesData = samplesDataMu

if "ele" in sys.argv:
    elePostfix = "Ele"
    samplesData = samplesDataEle

#t = mvaTool()

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar"]

regions = ["","3j2t","2j1t","4j1t","4j2t"]

#samples = ["tW_top_nfh","tW_antitop_nfh"]

processes = []
systs = ["JESUp","JESDown","JERUp","JERDown"]

systDir = ""
systDir = "tWSysts"+elePostfix
#if len(sys.argv) > 2:
#    systDir = sys.argv[2]

toRun = []

for region in regions:

    if (not os.path.isdir(outDir+region)):
        subprocess.call("mkdir -p "+outDir+region,shell=True)
    if (not os.path.isdir(outDir+region+"Systs/")):
        subprocess.call("mkdir -p "+outDir+region+"Systs/",shell=True)
    if (not os.path.isdir(outDir+region+"QCD/")):
        subprocess.call("mkdir -p "+outDir+region+"QCD/",shell=True)
    for syst in systs:
        if (not os.path.isdir(outDir+region+syst+"/")):
            subprocess.call("mkdir -p "+outDir+region+syst+"/",shell=True)

    for sample in samples:
        #    continue
        if not os.path.exists(outDir+region+"/output_"+sample+".root"): toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+region+elePostfix+"/\\\",\\\""+outDir+region+"/\\\");\"")
        for syst in systs:
            if not os.path.exists(outDir+region+syst+"/output_"+sample+".root"): toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+region+syst+elePostfix+"/\\\",\\\""+outDir+region+syst+"/\\\");\"")

    for sample in samplesData:
        #    continue
        if not os.path.exists(outDir+region+"/output_"+sample+".root"): toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+region+"Data"+elePostfix+"/\\\",\\\""+outDir+region+"/\\\");\"")
        if not os.path.exists(outDir+region+"QCD/output_"+sample+".root"): toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tWInv"+region+"Data"+elePostfix+"/\\\",\\\""+outDir+region+"QCD/\\\");\"")

#And do the theory uncertainties if they exist
    if systDir:
        for sample in os.listdir(systDir):
            systDir = "tW{0}Systs{1}/".format(region,elePostfix)
            if not os.path.exists(outDir+region+"Systs/output_"+sample+".root"): toRun.append("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\""+systDir+"/\\\",\\\""+outDir+region+"Systs/\\\");\"")

nFinished = 0
nRunning = 0

while True:
    if len(processes)>0:
        i = 0
        while i < (len(processes)):
            if i >= len(processes): break
            if processes[i].poll() == 0:
                processes.pop(i)
                nFinished += 1
            i+=1
    while len(processes) < 20:
        processes.append(subprocess.Popen(toRun[nRunning],shell=True))
        nRunning+=1
    time.sleep(5)
    if nFinished == len(toRun):
        break
#
#print processes.keys()
#for key in processes.keys():
#    processes[key].wait()
#
#print processes.keys()
