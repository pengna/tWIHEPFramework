#The point of this script is to assemble the plots created in the skimmer program into stack plots and comparison plots (i.e. where they're all scaled to 1.)

from ROOT import *

from setTDRStyle import setTDRStyle
import sys

inDir = sys.argv[1]
outDir = sys.argv[2]

doData = False
dataFolder = ""

useQCD = False
qcdFolder = ""

if len(sys.argv) > 3: 
    doData = True
    dataFolder = sys.argv[3]

#Do a load of set up for the plots here

gROOT.SetBatch()

gStyle.SetOptTitle(0)

gStyle.SetPalette(1)
gStyle.SetCanvasBorderMode(0)
gStyle.SetCanvasColor(kWhite)
gStyle.SetCanvasDefH(600)
gStyle.SetCanvasDefW(600)
gStyle.SetLabelFont(18,"")

setTDRStyle()

gStyle.SetTitleYOffset(0.8)

cmsTextFont = 61
extraTextFont = 52

#New labels here                                                                                                                                                        
latex = TLatex()
latex.SetNDC()
latex.SetTextAlign(31)

cmsText = "CMS"
extraText = "Preliminary"

latex2 = TLatex();
latex2.SetNDC();
latex2.SetTextSize(0.04);
latex2.SetTextAlign(31);

#text2 = TLatex(0.45,0.98, channelLabelMap[channel]+postFixLabel2)
text2 = TLatex(0.45,0.98, "#mu channel")
text2.SetNDC()
text2.SetTextAlign(13)
text2.SetX(0.18)
text2.SetY(0.92)
text2.SetTextFont(42)
text2.SetTextSize(0.0610687)


#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJets","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJets","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200"]
#samples = ["tW_top","tW_antitop","tChan","zz","wz","ww","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
hists = ["tW","singleTop","VV","ttbar","wPlusJets","zPlusJets","qcd","data"]
#hists = ["tW","singleTop","VV","ttbar","qcd"]

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets"}
colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow,"data":kBlack}

reducedHists = ["tW","ttbar","zPlusJets"]
#reducedHists = ["tW","ttbar"]

inFiles = {}

plotNames = []

for sample in samples:
    inFiles[sample] = TFile(inDir+sample+"/hists/merged"+sample+".root","READ")
    
if doData: inFiles['data'] = TFile(dataFolder+"/singleMuon/hists/mergedsingleMuon.root","READ")

plotPaths = []

for obj in inFiles["tW_top"].GetListOfKeys():
    tempThing = inFiles["tW_top"].Get(obj.GetName())
    if not tempThing.ClassName().find("TH1") == -1 : plotPaths.append(tempThing.GetName())
    if not tempThing.ClassName().find("Directory") == -1:
        for k2 in tempThing.GetListOfKeys():
            temp2 = tempThing.Get(k2.GetName())
            if not temp2.ClassName().find("TH1") == -1:
                plotPaths.append(tempThing.GetName() + "/"+ temp2.GetName())

plotsToConsider = ["PrimaryVertex","METMET"]
plotsToConsider = ["nTrueInteractions"]
for plotName in plotPaths:
    considerPlot = False
    for name in plotsToConsider:
        if name in plotName: 
            considerPlot = True
            break

    if not considerPlot: continue
    print plotName

    if not plotName.find("/") == -1:
        saveName = ""
        for part in plotName.split("/"):
            saveName += part + "_"
        saveName = saveName[:-1]
        print saveName
#for plotName in inFiles["tW_top"].GetListOfKeys():

#    if not plotName.GetName().split("_")[0] in plotNames: plotNames.append( plotName.GetName().split("_")[0] )
    
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)

    histMap = {}

    for sample in samples:
        if histoGramPerSample[sample] in histMap.keys():
            histMap[histoGramPerSample[sample]].Add(inFiles[sample].Get(plotName))
            
        else:
            histMap[histoGramPerSample[sample]] = inFiles[sample].Get(plotName)

    if doData: histMap['data'] = inFiles['data'].Get(plotName)

    mcstack = THStack(plotName,plotName)

    compCanvy = TCanvas(plotName+"comp",plotName+"comp",1000,800)
    compCanvy.cd()


    hists.reverse()                                                                         
    histMax = 0.
    for histName in hists:
        if histName == 'data' and not doData: continue
        leggy.AddEntry(histMap[histName],histName,"f")
        histMap[histName].SetFillColor(0)
        histMap[histName].SetLineWidth(2)
        histMap[histName].SetLineColor(colourPerSample[histName])
        if histMap[histName].Integral() > 0.:
            histMap[histName].Scale(1./histMap[histName].Integral())
        histMap[histName].Draw("hist same")
        if histMap[histName].GetMaximum() > histMax: histMax = histMap[histName].GetMaximum()

    previousMax = histMap["tW"].GetMaximum()
    histMap["tW"].SetMaximum(histMax * 1.3)
    leggy.Draw()

    compCanvy.SaveAs(outDir+saveName+"comp.png")

    totalMC = 0
    for histName in hists:
        if histName == 'data': 
            if not doData: continue
            histMap[histName].SetTitle("dataPV")
            histMap[histName].SetName("dataPV")
            histMap[histName].Scale(1./histMap[histName].Integral())
            histMap[histName].SaveAs("dataPV.root")
        else:
            if totalMC == 0: totalMC = histMap[histName].Clone("pileup")
            else: totalMC.Add(histMap[histName])
    totalMC.Scale(1./totalMC.Integral())
    totalMC.SetTitle("pileup")
    totalMC.SetName("pileup")
    totalMC.SaveAs("mcPV.root")

