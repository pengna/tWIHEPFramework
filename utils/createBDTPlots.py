#The point of this script is to assemble the plots created in the skimmer program into stack plots and comparison plots (i.e. where they're all scaled to 1.)

from ROOT import *

from setTDRStyle import setTDRStyle
import sys, os

inFile = TFile(sys.argv[1],"READ")
##if (not os.path.exists(outDir)):
#    os.makedirs(outDir)

outFileName = sys.argv[2]

runRanges = ['B','C','D','E','F','G','H']

doData = True
dataFolder = ""

useQCD = False
qcdFolder = ""

perMCSFs = {}
#perMCSFs['qcd'] = 0.777791411029
#perMCSFs['wPlusJets'] = 1.21611224258
#perMCSFs['qcd'] = 0.496437098882
#perMCSFs['wPlusJets'] = 1.1282169724
#perMCSFs["ttbar"] = 1.1830538502
#perMCSFs['ttbar'] = 0.887389045755


perRegMCSFs = {}
perRegMCSFs[""] = {}
perRegMCSFs["3j2t"] = {}
perRegMCSFs["2j1t"] = {}
#perRegMCSFs[""]["zPlusJets"] = 1.106
#perRegMCSFs["3j2t"]["singleTop"] = 1.033
#perRegMCSFs["2j1t"]["singleTop"] = 1.033
#perRegMCSFs["3j2t"]["wPlusJets"] = 1.009
#perRegMCSFs["2j1t"]["wPlusJets"] = 1.009


nBinsForPlots = 20.

masterMCScale = 12554./27217. #runs B-D scale
masterMCScale = 1.
#masterMCScale = 27217./35900.

ratioMin = 0.5
ratioMax = 1.5

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
samples = ["tW_top","tW_antitop","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar"]

#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJets","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200"]
#samples = ["tW_top","tW_antitop","tChan","zz","wz","ww","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
hists = ["singleTop","VV","ttbar","wPlusJets","zPlusJets","qcd","tW"]
#hists = ["tW","singleTop","VV","ttbar","qcd"]

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW"}
colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tW_top_nfh":kGreen+2,"tW_antitop_nfh":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow}

reducedHists = ["tW","ttbar","zPlusJets"]
#reducedHists = ["tW","ttbar"]

samplesToLoopOver = ["tW","zPlusJets","wPlusJets","VV","ttbar","qcd","singleTop"]

histMap = {}

for sample in samplesToLoopOver:
    histMap[sample] = inFile.Get(sample)

histMap["data"] = inFile.Get("data_obs")

systPaths = []

leggy = TLegend(0.8,0.6,0.95,0.9)
leggy.SetFillStyle(1001)
leggy.SetBorderSize(1)
leggy.SetFillColor(0)
leggy.SetLineColor(0)
leggy.SetShadowColor(0)
leggy.SetFillColor(kWhite)

mcstack = THStack("mvaDist","mvaDist")


#    for sample in hists:
#        tempHist = inFiles[sample].Get(plotName.GetName().split("_")[0]+"_"+sample+"_"+plotName.GetName().split("_")[-1]).Clone(histoGramPerSample[sample])
##        print plotName.GetName().split("_")[0]+"_"+sample+"_"+plotName.GetName().split("_")[-1]
#        leggy.AddEntry(tempHist,sample,"f")
#        tempHist.SetFillColor(colourPerSample[sample])
#        tempHist.SetLineColor(kBlack)
#        tempHist.SetLineWidth(1)
#        mcstack.Add(tempHist)
canvy = TCanvas("mvaDist","mvaDist",1000,800)
    #Add in a ratio plot if running with data included
canvy.SetBottomMargin(0.3)

canvy.cd()

dataHist = 0
    
dataHist = histMap["data"]
dataHist.SetMarkerStyle(20)
dataHist.SetMarkerSize(1.2)
dataHist.SetMarkerColor(kBlack)
leggy.AddEntry(dataHist,"Data","p")

for histName in histMap.keys():
    if histName == "data": continue
    leggy.AddEntry(histMap[histName],histName,"f")
    histMap[histName].SetFillColor(colourPerSample[histName])
    histMap[histName].SetLineColor(kBlack)
    histMap[histName].SetLineWidth(1)
        #This is the master rescaling - we do this to account for incorrect lumi calculations or whatever. Change the master variable at the top of the code
    histMap[histName].Scale(masterMCScale)
        #Now do per MC scaling if there's a SF in there somewhere
    if histName in perMCSFs.keys():
            #print histName, "rescaling",perMCSFs[histName]
        histMap[histName].Scale(perMCSFs[histName])
    else:
        if histName in perRegMCSFs[""].keys():
            histMap[histName].Scale(perRegMCSFs[""][histName])

sumHistoMC = histMap[hists[0]].Clone()
sumHistoMC.Reset()

for histName in hists:
    mcstack.Add(histMap[histName])
#        print histName,histMap[histName].Integral()
    sumHistoMC.Add(histMap[histName])


maxi = mcstack.GetMaximum() #if not doData or dataHist.GetMaximum() < mcstack.GetMaximum() else dataHist.GetMaximum()
if doData and dataHist.GetMaximum() > mcstack.GetMaximum(): maxi = dataHist.GetMaximum()

mcstack.Draw("hist")
if doData: mcstack.GetXaxis().SetLabelSize(0.0)

mcstack.GetXaxis().SetTitle(histMap[hists[0]].GetXaxis().GetTitle())

mcstack.GetYaxis().SetTitleOffset(1.)
mcstack.GetYaxis().SetLabelSize(0.03)
mcstack.GetYaxis().SetTitleSize(0.04)
mcstack.GetYaxis().CenterTitle()

mcstack.GetXaxis().SetTitleSize(0.045)
mcstack.GetYaxis().SetTitle("Events")


#    hists.reverse()

mcstack.SetMaximum(maxi*1.3)
minim = mcstack.GetMinimum()
#    mcstack.SetMinimum(0.0001)

 
dataHist.Draw("e x0, same")

leggy.Draw()

latex.SetTextSize(0.04)
latex.SetTextFont(cmsTextFont)
latex.DrawLatex(0.23, 0.95, cmsText )

latex.SetTextFont(extraTextFont)
latex.SetTextSize(0.04*0.76)
latex.DrawLatex(0.35, 0.95 , extraText )

latex2.DrawLatex(0.95, 0.95, "35.9 fb^{-1} (13TeV)");

text2.Draw()


    #If we're running on data, add in the ratio plot here
ratioCanvy = 0
sumHistoData = 0

mcstack.GetXaxis().SetTitle("")
ratioCanvy = TPad("BDT_ratio","BDT_ratio",0.0,0.0,1.0,1.0)
ratioCanvy.SetTopMargin(0.7)
ratioCanvy.SetFillColor(0)
ratioCanvy.SetFillStyle(0)
ratioCanvy.SetGridy(1)
ratioCanvy.Draw()
ratioCanvy.cd(0)
SetOwnership(ratioCanvy,False)

sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
sumHistoData.Sumw2()
sumHistoData.Divide(sumHistoMC)

sumHistoData.GetYaxis().SetTitle("Data/MC")
sumHistoData.GetYaxis().SetTitleOffset(1.3)
ratioCanvy.cd()
SetOwnership(sumHistoData,False)
sumHistoData.SetMinimum(ratioMin)
sumHistoData.SetMaximum(ratioMax)
sumHistoData.GetXaxis().SetTitleOffset(1.2)
sumHistoData.GetXaxis().SetLabelSize(0.04)
sumHistoData.GetYaxis().SetNdivisions(6)
sumHistoData.GetYaxis().SetTitleSize(0.03)
sumHistoData.Draw("E1X0")


canvy.SaveAs(outFileName+".png")
canvy.SaveAs(outFileName+".root")

#    mcstack.SetMinimum(1)
canvy.SetLogy()

canvy.SaveAs(outFileName+"_log.png")
canvy.SaveAs(outFileName+"_log.root")

del ratioCanvy
del sumHistoData
