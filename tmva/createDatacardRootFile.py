from ROOT import *

import sys,os,math

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW"}

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar"]

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]
samplesData = samplesDataMu

colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tW_top_nfh":kGreen+2,"tW_antitop_nfh":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow}

plotLeptonSampleName = "Mu"

gROOT.SetBatch()

makeSystComps = True #Make a whole bunch of comparison plots if true
makeStackPlots = True #Make some stack plots of the output
reduceBinsToFilled = True #Reduce the histograms to only their filled bins. This might possibly influence the fit, but my tests do not indicate that it does.

mvaName = "MVA_ttbar_"
mvaPostfix = ""

regions = ["","3j2t","2j1t","4j1t","4j2t"]

inDir = sys.argv[1]
outDir = sys.argv[2]
doSystDir = True
systDir = inDir+"Systs/"
isEle = False
channeltr = "mu"
if "ele" in sys.argv:
    samplesData = samplesDataEle
    plotLeptonSampleName = "Ele"
    channeltr = "ele"
#if len(sys.argv) > 3: systDir = sys.argv[3]

perMCSFs = {}
perMCSFs["ttbar"] = 2.
perMCSFs["qcd"] = 5099897.0/2604652.19727

if isEle:
    perMCSFs["qcd"] *= 0.575639172238
    perMCSFs["ttbar"] *= 0.905594867235
    perMCSFs["wPlusJets"] = 3.08934118354

else:
    perMCSFs["qcd"] = 5227921/8899239.0 #This will be the muon channel once I've re-run all of the files.
    perMCSFs["qcd"] *= 1.10329115653
    perMCSFs["ttbar"] *= 0.937952128327
    perMCSFs["wPlusJets"] = 3.48537322128

if (not os.path.isdir(outDir)):
    os.makedirs(outDir)
if makeSystComps and not os.path.isdir(outDir+"plots/"): os.makedirs(outDir+"plots/")

nominal = {}

systs = [
"LSF","PU","bTag"
]
nStatsBins = 0
systHists = {}

totalYieldsCount = {}

def findMaxAndMinBins(nominalHists,systHist):
    maxBin = 0
    minBin = 50
    returnNominals = {}
    returnSysts = {}
    for key in nominalHists.keys():
        if nominalHists[key].FindFirstBinAbove() < minBin: minBin = nominalHists[key].FindFirstBinAbove()
        if nominalHists[key].FindLastBinAbove() > maxBin: maxBin = nominalHists[key].FindLastBinAbove()
        if key == "data" or key == "qcd":continue
        for key2 in systHist[key].keys():
            if systHist[key][key2].FindFirstBinAbove() < minBin: minBin = systHist[key][key2].FindFirstBinAbove()
            if systHist[key][key2].FindLastBinAbove() > maxBin: maxBin = systHist[key][key2].FindLastBinAbove()
    xLow = nominalHists[key].GetXaxis().GetBinLowEdge(minBin)
    xHigh = nominalHists[key].GetXaxis().GetBinUpEdge(maxBin)
    for key in nominalHists.keys():
        returnNominals[key] = TH1F(nominalHists[key].GetName(),nominalHists[key].GetTitle(),maxBin-minBin+1,xLow,xHigh)
        i = 1
        for j in range(minBin,maxBin+1):
            returnNominals[key].SetBinContent(i,nominalHists[key].GetBinContent(j))
            returnNominals[key].SetBinError(i,nominalHists[key].GetBinError(j))
            i+=1
        if key == "data" or key == "qcd":continue
        returnSysts[key] = {}
        for key2 in systHist[key].keys():
            returnSysts[key][key2] = TH1F(systHist[key][key2].GetName(),systHist[key][key2].GetTitle(),maxBin-minBin+1,xLow,xHigh)
            i = 1
            for j in range(minBin,maxBin+1):
                returnSysts[key][key2].SetBinContent(i,systHist[key][key2].GetBinContent(j))
                returnSysts[key][key2].SetBinError(i,systHist[key][key2].GetBinError(j))
                i+=1
    print "Hists have been rescaled to fit range {0}-{1}".format(xLow,xHigh)
    return (returnNominals,returnSysts)

def setAllNegBinsToZero(hist):
    for i in range(1,hist.GetXaxis().GetNbins()+1):
        if hist.GetBinContent(i) < 0.: hist.SetBinContent(i,0.)

def makeAllSystHists(nominal,systHists,region):
    latexFile = open(outDir+"plots/{0}latexFile.tex".format(region),"w")
    latexFile.write("\\documentclass{beamer}\n\\usetheme{Warsaw}\n\n\\usepackage{graphicx}\n\\useoutertheme{infolines}\n\\setbeamertemplate{headline}{}\n\n\\begin{document}\n\n")
    for sample in nominal.keys():
        if sample == "data" or sample == "qcd": continue
        for syst in systHists[sample].keys():
            if "Down" in syst or "stat" in syst or "down" in syst: continue
            downSystName = syst.split("Up")[0]+"Down"
            shortenedName = syst.split("Up")[0]
            if "up" in syst: downSystName = syst.split("up")[0]+"down"
            makeSystHist(nominal[sample],systHists[sample][syst],systHists[sample][downSystName],region+sample+shortenedName)
            latexFile.write("\\frame{{\n\\frametitle{{{0}-{1}-{2}}}\n".format(region,sample,shortenedName))
            latexFile.write("\\includegraphics[width=0.9\\textwidth]{"+region+sample+shortenedName+".png}")
            latexFile.write("\n}\n")

    latexFile.write("\\frame{{\n\\frametitle{{MVA {0}}}\n".format(region))
    latexFile.write("\\includegraphics[width=0.9\\textwidth]{{mva{0}.png}}".format(region))
    latexFile.write("\n}\n")                                                                       

    latexFile.write("\\end{document}")
            

def makeSystHist(nominalHist,upHist,downHist,canvasName):
#    canvasName = upHist.GetName().split("Up")[0]
    canvy = TCanvas(canvasName,canvasName,1000,800)
    canvy.cd()
    nominalHist.SetLineColor(kBlack)
    histMax = 0.
    if upHist.GetMaximum() > histMax: histMax = upHist.GetMaximum() 
    if downHist.GetMaximum() > histMax: histMax = downHist.GetMaximum()
    nominalHist.SetMaximum(histMax*1.2)
    nominalHist.Draw("hist")
    upHist.SetLineColor(kRed)
    upHist.Draw("hist same")
    downHist.SetLineColor(kBlue)
    downHist.Draw("hist same")
    canvy.SaveAs(outDir+"plots/"+canvasName+".png")

def makeStackPlot(nominal,systHists,region):
    stack = THStack("mva_{0}".format(region),"mva_{0}".format(region))
    canvy = TCanvas("MVA_{0}".format(region),"MVA_{0}".format(region),1000,800)
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    
    canvy.cd()
    canvy.SetBottomMargin(0.3)
    dataHist = 0
    sumHist = nominal["tW"].Clone()
    sumHist.Reset()
    for i in nominal.keys():
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            leggy.AddEntry(dataHist,"Data","p")
            continue
        leggy.AddEntry(nominal[i],i,"f")
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        stack.Add(nominal[i])
        sumHist.Add(nominal[i])
        #Do systematic estimation here when I get aorund to it)

    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack.GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")
    
    dataHist.Draw("e1x0 same")
    leggy.Draw()

    ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
    ratioCanvy.SetTopMargin(0.7)
    ratioCanvy.SetFillColor(0)
    ratioCanvy.SetFillStyle(0)
    ratioCanvy.SetGridy(1)
    ratioCanvy.Draw()
    ratioCanvy.cd(0)
    SetOwnership(ratioCanvy,False)

    sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
    sumHistoData.Sumw2()
    sumHistoData.Divide(sumHist)

    sumHistoData.GetYaxis().SetTitle("Data/MC")
    sumHistoData.GetYaxis().SetTitleOffset(1.3)
    ratioCanvy.cd()
    SetOwnership(sumHistoData,False)
    sumHistoData.SetMinimum(0.8)
    sumHistoData.SetMaximum(1.2)
    sumHistoData.GetXaxis().SetTitleOffset(1.2)
    sumHistoData.GetXaxis().SetLabelSize(0.04)
    sumHistoData.GetYaxis().SetNdivisions(6)
    sumHistoData.GetYaxis().SetTitleSize(0.03)
    sumHistoData.Draw("E1X0")

    canvy.SaveAs(outDir+"plots/mva{0}.png".format(region))
    canvy.SaveAs(outDir+"plots/mva{0}.root".format(region))


def getDownHist(upHist,nominalHist):
    downHist = nominalHist.Clone(upHist.GetName().split("Up")[0]+"Down")
    downHist.SetDirectory(0)
    for i in range(1,nominalHist.GetXaxis().GetNbins()+1):
        diffBin = nominalHist.GetBinContent(i) - upHist.GetBinContent(i)
        downHist.SetBinContent(i,nominalHist.GetBinContent(i) + diffBin)
        if downHist.GetBinContent(i) < 0.: downHist.SetBinContent(i,0.)
    return downHist

def makeStatBinVariations(hist, binNumber, region):

    variationHistUp = hist.Clone("{2}_{2}_Mu{1}_statbin{0}Up".format(binNumber,region,hist.GetName()))
    variationHistDown = hist.Clone("{2}_{2}_Mu{1}_statbin{0}Down".format(binNumber,region,hist.GetName()))
    binWeight = hist.GetBinContent(binNumber)
    shift = 0

    shift = math.sqrt(math.fabs(binWeight))
    variationHistUp.SetBinContent(binNumber,binWeight+shift)
    variationHistDown.SetBinContent(binNumber,binWeight-shift)
    return (variationHistUp,variationHistDown)

for region in regions:
    outFile = TFile(outDir+"mvaDists_{0}_{1}.root".format(region,channeltr),"RECREATE")

    totalYieldsCount[region] = {}
    nominal = {}
    systHists = {}
    if doSystDir: systDir = inDir + region + "Systs/"
    for sample in samples:
        #get input file
        inFile = TFile(inDir+region+"/output_"+sample+".root","READ")
        print sample
        #get nominal plot"
        if histoGramPerSample[sample] in nominal.keys():
            nominal[histoGramPerSample[sample]].Add(inFile.Get(mvaName+sample))
            for sys in systs:
                #print mvaName+sample+"_"+sys+"_up"
                systHists[histoGramPerSample[sample]][sys+"Up"].Add(inFile.Get(mvaName+sample+"_"+sys+"_up"))
                systHists[histoGramPerSample[sample]][sys+"Down"].Add(inFile.Get(mvaName+sample+"_"+sys+"_down"))
        else:
            nominal[histoGramPerSample[sample]] = inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample])
            nominal[histoGramPerSample[sample]].SetDirectory(0)
#            if nStatsBins == 0:
#                nStatsBins = nominal[histoGramPerSample[sample]].GetXaxis().GetNbins()
#                print "nStatsBins: ",nStatsBins
#                for i in range(1,nStatsBins+1):
#                    systs.append("statbin"+str(i))
            systHists[histoGramPerSample[sample]] = {}
            for sys in systs:
                #print sys, mvaName+sample+"_"+sys+"_up"
                systNameForClone = histoGramPerSample[sample]+"_"+sys
                if "statbin" in sys: systNameForClone = histoGramPerSample[sample]+"_"+histoGramPerSample[sample]+"_"+plotLeptonSampleName+"_"+sys
                systHists[histoGramPerSample[sample]][sys+"Up"] = inFile.Get(mvaName+sample+"_"+sys+"_up").Clone(systNameForClone+"Up")
                systHists[histoGramPerSample[sample]][sys+"Up"].SetDirectory(0)
                systHists[histoGramPerSample[sample]][sys+"Down"] = inFile.Get(mvaName+sample+"_"+sys+"_down").Clone(systNameForClone+"Down")
                systHists[histoGramPerSample[sample]][sys+"Down"].SetDirectory(0)

    dirSysts = ["JES","JER"]
    upDown = ["Up","Down"]
    for ud in upDown:
        for syst in dirSysts:
            dirName = syst+ud
            print "Processing systematic in {0}".format(dirName)
            for sample in samples:
                inFile = TFile(inDir+region+dirName+"/output_"+sample+".root","READ")
                print "Processing sample {0}".format(sample)
                if dirName not in systHists[histoGramPerSample[sample]]:
                    systHists[histoGramPerSample[sample]][dirName] = inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud)
                    systHists[histoGramPerSample[sample]][dirName].SetDirectory(0)
                else:
                    systHists[histoGramPerSample[sample]][dirName].Add(inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud))

    for sample in samplesData:
        print "Dataset: {0}".format(sample)
        inFile = TFile(inDir+region+"/output_"+sample+".root","READ")
        inFileQCD = TFile(inDir+region+"QCD/output_"+sample+".root","READ")
        if "data" not in nominal.keys():
            nominal["data"] = inFile.Get(mvaName+sample).Clone("data_obs")
            nominal["data"].SetDirectory(0)
            nominal["qcd"] = inFileQCD.Get(mvaName+sample).Clone("qcd")
            nominal["qcd"].SetDirectory(0)
        else:
            nominal["data"].Add(inFile.Get(mvaName+sample))
            nominal["qcd"].Add(inFileQCD.Get(mvaName+sample))

    #Here we should grab the systematic samples if we're doing that.        
    sysDirNamesList = []
    sysNamesToGetDownHist = []
    if doSystDir:
        for fileName in os.listdir(systDir):
            sample = fileName.split("_")[1]
            sample2 = fileName.split("output_")[1].split(".root")[0]
            syst = fileName.split("_")[-1].split(".")[0]
            inFile = TFile(systDir+fileName,"READ")
            if syst in systHists[sample].keys():
                print "Adding 1 {0},{1},{2}".format( sample, syst, sample2), systHists[sample][syst].Integral(),
                systHists[sample][syst].Add(inFile.Get(mvaName+sample2))
                print systHists[sample][syst].Integral()
            elif syst+"Up" in systHists[sample].keys():
                print "Adding 2 {0},{1},{2}".format( sample, syst, sample2),
                print systHists[sample][syst+"Up"].Integral(),
                systHists[sample][syst+"Up"].Add(inFile.Get(mvaName+sample2))
                print sample2,systHists[sample][syst+"Up"].Integral()
    #            systHists[sample][syst+"Down"].Add(getDownHist(inFile.Get(mvaName+sample2),nominal[sample]))
            else:
                print "Making new {0},{1},{2}".format( sample, syst, sample2)
                cloneName = syst
                sysDirNamesList.append(syst)
                if "up" in syst:
                    cloneName = syst.split("up")[0]+"Up"
                elif "down" in syst:
                    cloneName = syst.split("down")[0]+"Down"
                else:
                    systHists[sample][syst+"Up"] = inFile.Get(mvaName+sample2).Clone(sample+"_"+syst+"Up")
                    systHists[sample][syst+"Up"].SetDirectory(0)
                    sysNamesToGetDownHist.append((sample,syst))
    #                systHists[sample][syst+"Down"] = getDownHist(systHists[sample][syst+"Up"],nominal[sample])
                    continue
                systHists[sample][syst] = inFile.Get(mvaName+sample2).Clone(sample+"_"+cloneName)
                systHists[sample][syst].SetDirectory(0)

    for pair in sysNamesToGetDownHist:

        print "Entry: ",pair[0],pair[1]
        #A hack to normalise herwig sample correctly
        if pair[0] == "ttbar" and pair[1] == "herwig":
            systHists[pair[0]][pair[1]+"Up"].Scale(0.5)
        systHists[pair[0]][pair[1]+"Down"] = getDownHist(systHists[pair[0]][pair[1]+"Up"],nominal[pair[0]])

    halveSize = ["isr","fsr","tune"]
#    halveSize = []

    for key in nominal.keys():
        setAllNegBinsToZero(nominal[key])
        totalYieldsCount[region][key] = nominal[key].Integral()
        
        #Make the stat variation histograms
        if "data" in key or "qcd" in key: continue
        for i in range(1,nominal[key].GetXaxis().GetNbins()+1):
            systHists[key]["statbin"+str(i)+"up"],systHists[key]["statbin"+str(i)+"down"] = makeStatBinVariations(nominal[key],i,region)

    #Here make a loop to find out the highest and lowest filled bins so get rid of zero occupancy bins?
#    for key in nominal.keys():
        
    (nominal,systHists) = findMaxAndMinBins(nominal,systHists)
    outFile.cd()
    print sysDirNamesList
    for key in nominal.keys():
        if key in perMCSFs.keys():
            nominal[key].Scale(perMCSFs[key])
            totalYieldsCount[region][key] *= perMCSFs[key]
        nominal[key].Write()
        print key, nominal[key].Integral()
        if key == "data" or key == "qcd": continue
        for key2 in systHists[key].keys():
            if key in perMCSFs.keys():
                for systName in halveSize:
                    if key == "ttbar" and systName in key2: 
#                        print "rescaling: ",key,key2
                        systHists[key][key2].Scale(0.5)
                systHists[key][key2].Scale(perMCSFs[key])
            setAllNegBinsToZero(systHists[key][key2])
            systHists[key][key2].Write()
    
    if makeSystComps: 
        makeAllSystHists(nominal,systHists,region)
    if makeStackPlots:
        makeStackPlot(nominal,systHists,region)


for region in regions:
    print region
    for key in totalYieldsCount[region].keys():
        print key, totalYieldsCount[region][key]

for j in ["","2j1t","3j2t","4j2t","4j1t"]:
    for i in ["VV", "wPlusJets", "zPlusJets", "ttbar", "singleTop", "qcd", "tW"]:
        print totalYieldsCount[j][i],

print ""

for j in ["","2j1t","3j2t","4j2t","4j1t"]:
    for i in ["VV", "wPlusJets", "zPlusJets", "ttbar", "singleTop", "qcd", "tW"]:
        print "{0} {1}".format(j,i),

print

for j in ["","2j1t","3j2t","4j2t","4j1t"]:
    print totalYieldsCount[j]["data"],
