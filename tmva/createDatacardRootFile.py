from ROOT import *

import sys,os

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW"}

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar"]

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]
samplesData = samplesDataMu

plotLeptonSampleName = "Mu"

inDir = sys.argv[1]
outDir = sys.argv[2]
systDir = inDir+"Systs/"
isEle = False
if "ele" in sys.argv:
    samplesData = samplesDataEle
    plotLeptonSampleName = "Ele"
#if len(sys.argv) > 3: systDir = sys.argv[3]

perMCSFs = {}
perMCSFs["ttbar"] = 2.
perMCSFs["qcd"] = 5099897.0/2604652.19727

if isEle:
    perMCSFs["qcd"] *= 0.575639172238
    perMCSFs["ttbar"] *= 0.905594867235
    perMCSFs["wPlusJets"] = 3.08934118354

else:
    perMCSFs["qcd"] *= 0.837106815504
    perMCSFs["ttbar"] *= 0.891728577865
    perMCSFs["wPlusJets"] = 3.44115208943


if (not os.path.isdir(outDir)):
    os.makedirs(outDir)

outFile = TFile(outDir+"mvaDists_ForFit.root","RECREATE")

nominal = {}

systs = [
"LSF","PU","bTag"
]
nStatsBins = 0
systHists = {}

def getDownHist(upHist,nominalHist):
    downHist = nominalHist.Clone(upHist.GetName().split("Up")[0]+"Down")
    downHist.SetDirectory(0)
    for i in range(1,nominalHist.GetXaxis().GetNbins()+1):
        diffBin = nominalHist.GetBinContent(i) - upHist.GetBinContent(i)
        downHist.SetBinContent(i,nominalHist.GetBinContent(i) + diffBin)
        if downHist.GetBinContent(i) < 0.: downHist.SetBinContent(i,0.)
    return downHist

for sample in samples:
    #get input file
    inFile = TFile(inDir+"/output_"+sample+".root","READ")
    print sample
    #get nominal plot"
    if histoGramPerSample[sample] in nominal.keys():
        nominal[histoGramPerSample[sample]].Add(inFile.Get("MVA_"+sample))
        for sys in systs:
            #print "MVA_"+sample+"_"+sys+"_up"
            systHists[histoGramPerSample[sample]][sys+"Up"].Add(inFile.Get("MVA_"+sample+"_"+sys+"_up"))
            systHists[histoGramPerSample[sample]][sys+"Down"].Add(inFile.Get("MVA_"+sample+"_"+sys+"_down"))
    else:
        nominal[histoGramPerSample[sample]] = inFile.Get("MVA_"+sample).Clone(histoGramPerSample[sample])
        nominal[histoGramPerSample[sample]].SetDirectory(0)
        if nStatsBins == 0:
            nStatsBins = nominal[histoGramPerSample[sample]].GetXaxis().GetNbins()
            print "nStatsBins: ",nStatsBins
            for i in range(1,nStatsBins+1):
                systs.append("statbin"+str(i))
        systHists[histoGramPerSample[sample]] = {}
        for sys in systs:
            #print sys, "MVA_"+sample+"_"+sys+"_up"
            systNameForClone = histoGramPerSample[sample]+"_"+sys
            if "statbin" in sys: systNameForClone = histoGramPerSample[sample]+"_"+histoGramPerSample[sample]+"_"+plotLeptonSampleName+"_"+sys
            systHists[histoGramPerSample[sample]][sys+"Up"] = inFile.Get("MVA_"+sample+"_"+sys+"_up").Clone(systNameForClone+"Up")
            systHists[histoGramPerSample[sample]][sys+"Up"].SetDirectory(0)
            systHists[histoGramPerSample[sample]][sys+"Down"] = inFile.Get("MVA_"+sample+"_"+sys+"_down").Clone(systNameForClone+"Down")
            systHists[histoGramPerSample[sample]][sys+"Down"].SetDirectory(0)

dirSysts = ["JES","JER"]
upDown = ["Up","Down"]
for ud in upDown:
    for syst in dirSysts:
        dirName = syst+ud
        print "Processing systematic in {0}".format(dirName)
        for sample in samples:
            inFile = TFile(inDir+dirName+"/output_"+sample+".root","READ")
            print "Processing sample {0}".format(sample)
            if dirName not in systHists[histoGramPerSample[sample]]:
                systHists[histoGramPerSample[sample]][dirName] = inFile.Get("MVA_"+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud)
                systHists[histoGramPerSample[sample]][dirName].SetDirectory(0)
            else:
                systHists[histoGramPerSample[sample]][dirName].Add(inFile.Get("MVA_"+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud))
                
for sample in samplesData:
    print "Dataset: {0}".format(sample)
    inFile = TFile(inDir+"/output_"+sample+".root","READ")
    inFileQCD = TFile(inDir+"QCD/output_"+sample+".root","READ")
    if "data" not in nominal.keys():
        nominal["data"] = inFile.Get("MVA_"+sample).Clone("data_obs")
        nominal["data"].SetDirectory(0)
        nominal["qcd"] = inFileQCD.Get("MVA_"+sample).Clone("qcd")
        nominal["qcd"].SetDirectory(0)
    else:
        nominal["data"].Add(inFile.Get("MVA_"+sample))
        nominal["qcd"].Add(inFileQCD.Get("MVA_"+sample))

#Here we should grab the systematic samples if we're doing that.        
sysDirNamesList = []
sysNamesToGetDownHist = []
if systDir:
    for fileName in os.listdir(systDir):
        sample = fileName.split("_")[1]
        sample2 = fileName.split("output_")[1].split(".root")[0]
        syst = fileName.split("_")[-1].split(".")[0]
        inFile = TFile(systDir+fileName,"READ")
        if syst in systHists[sample].keys():
            print "Adding 1 {0},{1},{2}".format( sample, syst, sample2), systHists[sample][syst].Integral(),
            systHists[sample][syst].Add(inFile.Get("MVA_"+sample2))
            print systHists[sample][syst].Integral()
        elif syst+"Up" in systHists[sample].keys():
            print "Adding 2 {0},{1},{2}".format( sample, syst, sample2),
            print systHists[sample][syst+"Up"].Integral(),
            systHists[sample][syst+"Up"].Add(inFile.Get("MVA_"+sample2))
            print sample2,systHists[sample][syst+"Up"].Integral()
#            systHists[sample][syst+"Down"].Add(getDownHist(inFile.Get("MVA_"+sample2),nominal[sample]))
        else:
            print "Making new {0},{1},{2}".format( sample, syst, sample2)
            cloneName = syst
            sysDirNamesList.append(syst)
            if "up" in syst:
                cloneName = syst.split("up")[0]+"Up"
            elif "down" in syst:
                cloneName = syst.split("down")[0]+"Down"
            else:
                systHists[sample][syst+"Up"] = inFile.Get("MVA_"+sample2).Clone(sample+"_"+syst+"Up")
                systHists[sample][syst+"Up"].SetDirectory(0)
                sysNamesToGetDownHist.append((sample,syst))
#                systHists[sample][syst+"Down"] = getDownHist(systHists[sample][syst+"Up"],nominal[sample])
                continue
            systHists[sample][syst] = inFile.Get("MVA_"+sample2).Clone(sample+"_"+cloneName)
            systHists[sample][syst].SetDirectory(0)

for pair in sysNamesToGetDownHist:
    
    print "Entry: ",pair[0],pair[1]
    #A hack to normalise herwig sample correctly
    if pair[0] == "ttbar" and pair[1] == "herwig":
        systHists[pair[0]][pair[1]+"Up"].Scale(0.5)
    systHists[pair[0]][pair[1]+"Down"] = getDownHist(systHists[pair[0]][pair[1]+"Up"],nominal[pair[0]])

halveSize = ["isr","fsr","tune"]

outFile.cd()
print sysDirNamesList
for key in nominal.keys():
    if key in perMCSFs.keys():
        nominal[key].Scale(perMCSFs[key])
    nominal[key].Write()
    print key, nominal[key].Integral()
    if key == "data" or key == "qcd": continue
    for key2 in systHists[key].keys():
        if key in perMCSFs.keys():
            for systName in halveSize:
                if key == "ttbar" and systName in key2: 
                    print "rescaling: ",key,key2
                    systHists[key][key2].Scale(0.5)
            systHists[key][key2].Scale(perMCSFs[key])
        systHists[key][key2].Write()
