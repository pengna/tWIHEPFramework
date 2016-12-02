from ROOT import gSystem

gSystem.Load('libRooFit')

from ROOT import *

import sys

def getHists(inputFile):
    #do things
    print "Entering getHists"

    inFile = TFile(inputFile,"READ")

    canvy = 0

    for prim in inFile.GetListOfKeys():
        canvy = prim.ReadObj()
#        canvy =  inFile.Get(prim.GetName())
 
    dataH,qcdH,wJetsH,mcH = 0,0,0,0

    stack = 0
    for i in canvy.GetListOfPrimitives():
        if "TH1" in i.ClassName(): dataH = i
        if i.ClassName() == "THStack":
            stack = i

    print canvy,stack
    for hist in stack.GetHists():
        if "wPlusJets" in hist.GetName(): wJetsH = hist
        elif "qcd" in hist.GetName(): qcdH = hist
        elif "data" in hist.GetName(): dataH = hist
        else:
            if mcH == 0: mcH = hist
            else: mcH.Add(hist)

    return dataH,qcdH,wJetsH,mcH

def doFit(data,qcd,wJets,mc):
    
    print "Entering fit routine"

    w = RooWorkspace("w",kTRUE)
    if w == 0:
        print "Uh-oh, didn't work for some reason!"
        return

    #The variable we will be using/
    fitVar = RooRealVar("fitVar","fitVar",data.GetXaxis().GetXmin(),data.GetXaxis().GetXmax())

    #Make the pdfs we will be fitting
    mcRooHist = RooDataHist("mcRooHist","mcRooHist",RooArgList(fitVar),mc)
    wJRooHist = RooDataHist("wJRooHist","wJRooHist",RooArgList(fitVar),wJets)
    qcdRooHist = RooDataHist("qcdRooHist","qcdRooHist",RooArgList(fitVar),qcd)
    dataRooHist = RooDataHist("dataRooHist","dataRooHist",RooArgList(fitVar),data)

    #Define the pdfs here
    mc_template_pdf = RooHistPdf("mc_template_pdf","mc_template_pdf",RooArgSet(fitVar), mcRooHist)
    wJ_template_pdf = RooHistPdf("wJ_template_pdf","wJ_template_pdf",RooArgSet(fitVar), wJRooHist)
    qcd_template_pdf = RooHistPdf("qcd_template_pdf","qcd_template_pdf",RooArgSet(fitVar), qcdRooHist)

    #Define the coefficients of the model
    wJCoeff = RooRealVar("wJCoeff","wJCoeff",wJets.Integral(),0.,5*wJets.Integral())
    qcdCoeff = RooRealVar("qcdCoeff","qcdCoeff",qcd.Integral(),0.,2*qcd.Integral())
    mcCoeff = RooRealVar("mcCoeff","mcCoeff",mc.Integral(),mc.Integral(),mc.Integral())

    modelCoeff = RooRealVar("modelCoeff","modelCoeff",0.5,0.,1.)

    pdf_sum = RooAddPdf("pdf_sum","pdf_sum",RooArgList(mc_template_pdf,wJ_template_pdf,qcd_template_pdf),RooArgList(mcCoeff,wJCoeff,qcdCoeff))

    pdf_sum_reduced = RooAddPdf("pdf_sum","pdf_sum",RooArgList(wJ_template_pdf,qcd_template_pdf),RooArgList(modelCoeff))
    
    pdf_sum.fitTo(dataRooHist,RooFit.Extended(True))
    fitResult = pdf_sum_reduced.fitTo(dataRooHist,RooFit.Save(True),RooFit.Strategy(0),RooFit.Hesse(),RooFit.Minos(True),RooFit.Extended(True))

    #Now print off information about the mnodel
    print "-----------------------------------------------------------------------"
    print "                              Initial info"
    print "-----------------------------------------------------------------------" 
    print "Nevents of Data        = ", data.Integral()
    print "Nevents total MC	  = ", qcd.Integral() + wJets.Integral() + mc.Integral()
    print "Nevents of QCD         = ", qcd.Integral()
    print "Nevents of WZ          = ", wJets.Integral() 
    print "Nevents of Other       = ", mc.Integral()
    print 

    print "-----------------------------------------------------------------------" 
    print "                              Fit results"
    print "-----------------------------------------------------------------------"     
    print "wJets Coeff         = ", wJCoeff.getVal()
    print "QCD Coeff           = ", qcdCoeff.getVal()
    print "MC Coeff            = ", mcCoeff.getVal()
    print "Total MC after fit  = ", wJCoeff.getVal() + qcdCoeff.getVal() + mcCoeff.getVal()
    print "Total Data	       = ", data.Integral()
    print "Model Coeff         = ", modelCoeff.getVal()

    print "-----------------------------------------------------------------------"
    print "                             Scale factors"
    print "-----------------------------------------------------------------------"
    print "wJet SF	       = ", wJCoeff.getVal()/wJets.Integral()
    print "QCD SF	       = ", qcdCoeff.getVal()/qcd.Integral()
    print
    print "Done!"


    canvy = TCanvas("c1","plots",400,400,800,600)
    gStyle.SetPadRightMargin(0.13)
    gStyle.SetPadLeftMargin(0.13)

    data.Draw("ep")
    
    frame = fitVar.frame()
    fitVar.plotOn(frame)

    pdf_sum.plotOn(frame,RooFit.Components("qcd_template_pdf"),RooFit.VisualizeError(fitResult),RooFit.FillColor(kGreen),RooFit.LineWidth(2))
    pdf_sum.plotOn(frame,RooFit.Components("wJ_template_pdf"),RooFit.VisualizeError(fitResult),RooFit.FillColor(kRed),RooFit.LineWidth(2))
    pdf_sum.plotOn(frame,RooFit.Components("mc_template_pdf"),RooFit.VisualizeError(fitResult),RooFit.FillColor(kBlue),RooFit.LineWidth(2))
    pdf_sum.plotOn(frame,RooFit.LineStyle(kDashed),RooFit.VisualizeError(fitResult),RooFit.FillColor(kBlack))
#    pdf_sum_reduced.plotOn(frame,(wJ_template_pdf),(fitResult),FillColor =kRed, LineWidth = 2 )
#    pdf_sum_reduced.plotOn(frame,LineStyle(kDashed),(fitResult),(kBlue), LineWidth(2) )

    fitVar.plotOn(frame)
    frame.Draw("hsame")

    canvy.SaveAs("fit.png")
    canvy.SaveAs("fit.pdf")

def main():
    print "Entering main"
    data, qcd, wJets, mc = getHists(sys.argv[1])

#    mc.Scale(-1.)
#    data.Add(mc)

    doFit(data,qcd,wJets,mc)


if __name__ == "__main__":
    main()
