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

perMCSFs = {}
#perMCSFs['qcd'] = 0.777791411029
#perMCSFs['wPlusJets'] = 1.21611224258
#perMCSFs['qcd'] = 0.496437098882
#perMCSFs['wPlusJets'] = 1.1282169724
#perMCSFs["ttbar"] = 1.1830538502
#perMCSFs['ttbar'] = 0.887389045755

perMCSFs["qcd"] = 0.837106815504
perMCSFs["ttbar"] = 2.

perMCSFs["ttbar"] = 2.*0.891728577865
perMCSFs["wPlusJets"] = 3.44115208943

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

if len(sys.argv) > 3: 
    doData = True
    dataFolder = sys.argv[3]

if len(sys.argv) > 4:
    useQCD = True
    qcdFolder = sys.argv[4]

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
samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
#samples = ["tW_top","tW_antitop","tChan","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJets","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200"]
#samples = ["tW_top","tW_antitop","tChan","zz","wz","ww","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]
hists = ["singleTop","VV","ttbar","wPlusJets","zPlusJets","qcd","tW"]
#hists = ["tW","singleTop","VV","ttbar","qcd"]

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW"}
colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tW_top_nfh":kGreen+2,"tW_antitop_nfh":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow}

reducedHists = ["tW","ttbar","zPlusJets"]
#reducedHists = ["tW","ttbar"]

inFiles = {}

plotNames = []

for sample in samples:
    inFiles[sample] = TFile(inDir+sample+"/hists/merged"+sample+".root","READ")
    
if doData: inFiles['data'] = TFile(dataFolder+"/singleMuon/hists/mergedsingleMuon.root","READ")

if useQCD: inFiles['qcdData'] = TFile(qcdFolder+"/singleMuon/hists/mergedsingleMuon.root","READ")

plotPaths = []

#print inFiles.keys()

for obj in inFiles["tW_top_nfh"].GetListOfKeys():
    tempThing = inFiles["tW_top_nfh"].Get(obj.GetName())
    print obj.GetName()
    if not tempThing.ClassName().find("TH1") == -1 : plotPaths.append(tempThing.GetName())
    if not tempThing.ClassName().find("Directory") == -1:
        for k2 in tempThing.GetListOfKeys():
            temp2 = tempThing.Get(k2.GetName())
            if not temp2.ClassName().find("TH1") == -1:
                plotPaths.append(tempThing.GetName() + "/"+ temp2.GetName())
                

#print plotPaths

#ignorePlots = ["00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23"]
ignorePlots = ["01","02","03","04","05","10","23"]
ignorePlots = ["00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","24"]
#ignorePlots = ["01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","20","23"]ignorePlots = ["01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24"]
#ignorePlots = ["00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24"]
ignorePlots += ["Jet4","Jet5","Jet6","Jet7"]

for plotName in plotPaths:
    doPlot = True
    for ignore in ignorePlots:
        if ignore in plotName:
            doPlot = False
            break
    if not doPlot: continue
    saveName = plotName
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
            if "2000_inf" in sample and "BDTVars" in plotName: continue
            #           if not inFiles[sample].Get(plotName): continue
            #print sample
            histMap[histoGramPerSample[sample]].Add(inFiles[sample].Get(plotName))
        else:
            histMap[histoGramPerSample[sample]] = inFiles[sample].Get(plotName)
            histMap[histoGramPerSample[sample]].SetName(histMap[histoGramPerSample[sample]].GetName()+histoGramPerSample[sample])

    
    if useQCD:
        qcdNormalisation = histMap['qcd'].Integral()
        if inFiles['qcdData'].Get(plotName):
            histMap['qcd'] = inFiles['qcdData'].Get(plotName)
        elif "Tight" in plotName and inFiles['qcdData'].Get(plotName.split("Tight")[0]+"UnIsolated"+plotName.split("Tight")[1]):
            print "Using alternate named data-driven QCD estimation plot"
            histMap['qcd'] = inFiles['qcdData'].Get(plotName.split("Tight")[0]+"UnIsolated"+plotName.split("Tight")[1])
        elif inFiles['qcdData'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1]):
            histMap['qcd'] = inFiles['qcdData'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1])
        elif "Tight" in plotName and inFiles['qcdData'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1].split("Tight")[0]+"UnIsolated"+plotName.split(plotName.split("_")[0])[-1].split("Tight")[1]):
            histMap['qcd'] = inFiles['qcdData'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1].split("Tight")[0]+"UnIsolated"+plotName.split(plotName.split("_")[0])[-1].split("Tight")[1])
        else:
            print "Couldn't find "+plotName+" in the data enriched QCD sample so skipping this histogram."
            continue
        if histMap['qcd'].Integral() > 0.:
            histMap['qcd'].Scale(qcdNormalisation/histMap['qcd'].Integral())
        histMap['qcd'].SetName(histMap['qcd'].GetName() + "qcd")
        #If I need to do any scaling I will do it here I suppose.
#        print "Doing scaling:", histMap['qcd'].Integral(),
#        histMap['qcd'].Scale(0.5)
#        print histMap['qcd'].Integral()

    mcstack = THStack(plotName,plotName)


#    for sample in hists:
#        tempHist = inFiles[sample].Get(plotName.GetName().split("_")[0]+"_"+sample+"_"+plotName.GetName().split("_")[-1]).Clone(histoGramPerSample[sample])
##        print plotName.GetName().split("_")[0]+"_"+sample+"_"+plotName.GetName().split("_")[-1]
#        leggy.AddEntry(tempHist,sample,"f")
#        tempHist.SetFillColor(colourPerSample[sample])
#        tempHist.SetLineColor(kBlack)
#        tempHist.SetLineWidth(1)
#        mcstack.Add(tempHist)
    canvy = TCanvas(plotName,plotName,1000,800)
    #Add in a ratio plot if running with data included
    if doData:
        canvy.SetBottomMargin(0.3)

    canvy.cd()
#    SetOwnership(mcstack,False)

    dataHist = 0

    if doData:
        if inFiles['data'].Get(plotName):
            dataHist = inFiles['data'].Get(plotName)
        elif inFiles['data'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1]):
            dataHist = inFiles['data'].Get(str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1])            
        else:
            print plotName, str(int(plotName.split("_")[0])+1).zfill(2)+plotName.split(plotName.split("_")[0])[-1]
        dataHist.SetName(dataHist.GetName()+"data")
        dataHist.SetMarkerStyle(20)
        dataHist.SetMarkerSize(1.2)
        dataHist.SetMarkerColor(kBlack)
        if dataHist.GetXaxis().GetNbins() > int(nBinsForPlots):
            rebin = int(dataHist.GetXaxis().GetNbins() / nBinsForPlots)
            dataHist.Rebin(rebin)
#        if "MET" in plotName: dataHist.Rebin(4)
        leggy.AddEntry(dataHist,"Data","p")

    for histName in hists:
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
        if "2j1t" in inDir:
            if histName in perRegMCSFs["2j1t"].keys():
                histMap[histName].Scale(perRegMCSFs["2j1t"][histName])
        elif "3j2t" in inDir:
            if histName in perRegMCSFs["3j2t"].keys():
                histMap[histName].Scale(perRegMCSFs["3j2t"][histName])
        else:
            if histName in perRegMCSFs[""].keys():
                histMap[histName].Scale(perRegMCSFs[""][histName])
        # Do rebinning here. Most of these plots have too many bins.
        if histMap[histName].GetXaxis().GetNbins() > int(nBinsForPlots):
            rebin = int(histMap[histName].GetXaxis().GetNbins() / nBinsForPlots)
            histMap[histName].Rebin(rebin)
        #Now grab the systematic variations per sample

#        if "MET" in plotName: histMap[histName].Rebin(4)

#    hists.reverse()

    #Make the sum histogram for the ratio plot
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

 
    if doData: dataHist.Draw("e x0, same")

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
    if doData:
        mcstack.GetXaxis().SetTitle("")
        ratioCanvy = TPad(plotName+"_ratio",plotName+"_ratio",0.0,0.0,1.0,1.0)
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


    canvy.SaveAs(outDir+saveName+".png")
    canvy.SaveAs(outDir+saveName+".root")

#    mcstack.SetMinimum(1)
    canvy.SetLogy()

    canvy.SaveAs(outDir+saveName+"_log.png")
    canvy.SaveAs(outDir+saveName+"_log.root")

    del ratioCanvy
    del sumHistoData
#    del mcstack 
#    del canvy
#    del ratioCanvy
#    del sumHistoMC
#    del sumHistoData
#    del dataHist

    compCanvy = TCanvas(plotName+"comp",plotName+"comp",1000,800)
    compCanvy.cd()


#    hists.reverse()
    histMax = 0.
    for histName in hists:
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
    compCanvy.SaveAs(outDir+saveName+"comp.root")

    reducedCanvy =  TCanvas(plotName+"reducedComp",plotName+"reducedComp",1000,800)
    reducedCanvy.cd()

    reducedLeggy = TLegend(0.7,0.7,0.94,0.94)
    histMap["tW"].SetMaximum(previousMax)
    histMax = 0.
    for hist in reducedHists:
        histMap[hist].Draw("hist same")
        if histMap[hist].GetMaximum() > histMax: histMax = histMap[hist].GetMaximum()
        reducedLeggy.AddEntry(histMap[hist],hist,'f')

    histMap["tW"].SetMaximum(histMax * 1.3)
    reducedLeggy.Draw()

    reducedCanvy.SaveAs(outDir+saveName+"reducedComp.png")
    reducedCanvy.SaveAs(outDir+saveName+"reducedComp.root")
    
stages = ["lepSel","jetSel","bTag","fullSel"]

latexFile = open(outDir+"combinedLatexFile.tex","w")
latexFile.write("\\documentclass{beamer}\n\\usetheme{Warsaw}\n\n\\usepackage{graphicx}\n\\useoutertheme{infolines}\n\\setbeamertemplate{headline}{}\n\n\\begin{document}\n\n")

for plot in plotPaths:
    doPlot = True
    for ignore in ignorePlots:
        if ignore in plot:
            doPlot = False
            break
    if not doPlot: continue
    if not  plot.find(" ") == -1: continue
    saveName = plot
    writtenName = ""
    if not plot.find("/") == -1:
        saveName = ""
        for part in plot.split("/"):
            saveName += part + "_"
        saveName = saveName[:-1]

    for part in saveName.split("_"):
        writtenName += part + "\\_"
        writtenName = writtenName[:-2]

    latexFile.write("\\frame{\n\\frametitle{"+writtenName+"}\n")
    
    nPlots = 0
    for log in ["","_log","comp","reducedComp"]:
        post = log
        if log == "_log": post = " log"
        latexFile.write("\\includegraphics[width=0.45\\textwidth]{"+saveName+log+".png}")
        if  nPlots == 1: latexFile.write(" \\\\")
        latexFile.write("\n")
        nPlots+=1
    latexFile.write("}\n")

latexFile.write("\\end{document}")
#latexFile.Close()
