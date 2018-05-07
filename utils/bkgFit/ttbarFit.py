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
 
    dataH,ttbarH,mcH = 0,0,0,

    stack = 0
    for i in canvy.GetListOfPrimitives():
        if "TH1" in i.ClassName(): dataH = i
        if i.ClassName() == "THStack":
            stack = i

    print canvy,stack
    for hist in stack.GetHists():
        if "ttbar" in hist.GetName(): ttbarH = hist
        elif "data" in hist.GetName(): dataH = hist
        else:
            if mcH == 0: mcH = hist
            else: mcH.Add(hist)

    return dataH,ttbarH,mcH

def doFit(data,ttbar,mc):
    
    print "Entering fit routine"

    w = RooWorkspace("w",kTRUE)
    if w == 0:
        print "Uh-oh, didn't work for some reason!"
        return

    #The variable we will be using/
    fitVar = RooRealVar("fitVar","fitVar",data.GetXaxis().GetXmin(),data.GetXaxis().GetXmax())

    #Make the pdfs we will be fitting
    mcRooHist = RooDataHist("mcRooHist","mcRooHist",RooArgList(fitVar),mc)
    ttbarRooHist = RooDataHist("ttbarRooHist","ttbarRooHist",RooArgList(fitVar),ttbar)
    dataRooHist = RooDataHist("dataRooHist","dataRooHist",RooArgList(fitVar),data)

    #Define the pdfs here
    mc_template_pdf = RooHistPdf("mc_template_pdf","mc_template_pdf",RooArgSet(fitVar), mcRooHist)
    ttbar_template_pdf = RooHistPdf("ttbar_template_pdf","ttbar_template_pdf",RooArgSet(fitVar), ttbarRooHist)

    #Define the coefficients of the model
    ttbarCoeff = RooRealVar("ttbarCoeff","ttbarCoeff",ttbar.Integral(),0.,2*ttbar.Integral())
    mcCoeff = RooRealVar("mcCoeff","mcCoeff",mc.Integral(),mc.Integral(),mc.Integral())

    modelCoeff = RooRealVar("modelCoeff","modelCoeff",0.5,0.,1.)

    pdf_sum = RooAddPdf("pdf_sum","pdf_sum",RooArgList(mc_template_pdf,ttbar_template_pdf),RooArgList(mcCoeff,ttbarCoeff))

    pdf_sum_reduced = RooAddPdf("pdf_sum","pdf_sum",RooArgList(ttbar_template_pdf),RooArgList(modelCoeff))
    
    pdf_sum.fitTo(dataRooHist,RooFit.Extended(True))
    fitResult = pdf_sum_reduced.fitTo(dataRooHist,RooFit.Save(True),RooFit.Strategy(0),RooFit.Hesse(),RooFit.Minos(True),RooFit.Extended(True))

    #Now print off information about the mnodel
    print "-----------------------------------------------------------------------"
    print "                              Initial info"
    print "-----------------------------------------------------------------------" 
    print "Nevents of Data        = ", data.Integral()
    print "Nevents total MC	  = ", ttbar.Integral() + mc.Integral()
    print "Nevents of ttbar       = ", ttbar.Integral()
    print "Nevents of Other       = ", mc.Integral()
    print 

    print "-----------------------------------------------------------------------" 
    print "                              Fit results"
    print "-----------------------------------------------------------------------"     
    print "ttbar Coeff         = ", ttbarCoeff.getVal()
    print "MC Coeff            = ", mcCoeff.getVal()
    print "Total MC after fit  = ", ttbarCoeff.getVal() + mcCoeff.getVal()
    print "Total Data	       = ", data.Integral()
    print "Model Coeff         = ", modelCoeff.getVal()

    print "-----------------------------------------------------------------------"
    print "                             Scale factors"
    print "-----------------------------------------------------------------------"
    print "ttbar SF	       = ", ttbarCoeff.getVal()/ttbar.Integral()
    print
    print "Done!"


    canvy = TCanvas("c1","plots",400,400,800,600)
    gStyle.SetPadRightMargin(0.13)
    gStyle.SetPadLeftMargin(0.13)

    data.Draw("ep")
    
    frame = fitVar.frame()
    fitVar.plotOn(frame)

    pdf_sum.plotOn(frame,RooFit.Components("ttbar_template_pdf"),RooFit.VisualizeError(fitResult),RooFit.FillColor(kGreen),RooFit.LineWidth(2))
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
    data, ttbar, mc = getHists(sys.argv[1])

#    mc.Scale(-1.)
#    data.Add(mc)

    doFit(data,ttbar,mc)


if __name__ == "__main__":
    main()
