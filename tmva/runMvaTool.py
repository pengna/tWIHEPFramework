from ROOT import *

import subprocess, sys, os

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

#samples = ["tW_top_nfh","tW_antitop_nfh"]

processes = {}
systs = ["JESUp","JESDown","JERUp","JERDown"]

systDir = ""
systDir = "tWSysts"+elePostfix
#if len(sys.argv) > 2:
#    systDir = sys.argv[2]

if (not os.path.isdir(outDir)):
    subprocess.call("mkdir -p "+outDir,shell=True)
if (not os.path.isdir(outDir[:-1]+"Systs/")):
    subprocess.call("mkdir -p "+outDir[:-1]+"Systs/",shell=True)
if (not os.path.isdir(outDir[:-1]+"QCD/")):
    subprocess.call("mkdir -p "+outDir[:-1]+"QCD/",shell=True)
for syst in systs:
    if (not os.path.isdir(outDir[:-1]+syst+"/")):
        subprocess.call("mkdir -p "+outDir[:-1]+syst+"/",shell=True)

for sample in samples:
#    continue
    if not os.path.exists(outDir+"output_"+sample+".root"): processes[sample] = subprocess.Popen("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+elePostfix+"/\\\",\\\""+outDir+"\\\");\"",shell=True)
    for syst in systs:
        if not os.path.exists(outDir[:-1]+syst+"/output_"+sample+".root"): processes[sample+syst] = subprocess.Popen("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tW"+syst+elePostfix+"/\\\",\\\""+outDir[:-1]+syst+"/\\\");\"",shell=True)

for sample in samplesData:
#    continue
    if not os.path.exists(outDir+"output_"+sample+".root"): processes[sample] = subprocess.Popen("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tWData"+elePostfix+"/\\\",\\\""+outDir+"\\\");\"",shell=True)
    if not os.path.exists(outDir[:-1]+"QCD/output_"+sample+".root"): processes[sample+"qcd"] = subprocess.Popen("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\"tWInvData"+elePostfix+"/\\\",\\\""+outDir[:-1]+"QCD/\\\");\"",shell=True)

#And do the theory uncertainties if they exist
if systDir:
    for sample in os.listdir(systDir):
        if not os.path.exists(outDir[:-1]+"Systs/output_"+sample+".root"): processes[sample] = subprocess.Popen("root -b -q \"../../framework/tmva/runMVAReading.C(\\\""+sample+"\\\",\\\""+systDir+"/\\\",\\\""+outDir[:-1]+"Systs/\\\");\"",shell=True)

print processes.keys()
for key in processes.keys():
    processes[key].wait()

print processes.keys()
