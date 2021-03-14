from ROOT import *
#import ROOT 
#from setTDRStyle import setTDRStyle
from random import *
from array import *
import math
import sys,os
import numpy as np

Indir="/afs/ihep.ac.cn/users/p/pengn/WorkSpace/FullRunIIdataV2/tWIHEPFramework/tool/DataMCCompare/bstar/"
Anti2DQCDinFileName = Indir+"Preselection/Electron2018/Systs/output_SEle_AB.root"
AntiWtaginFileName = Indir+"Preselection/Electron2018/Systs/output_SEle_CD.root"
TTCRinFileName = Indir+"Preselection/Electron2018/Systs/output_Data.root"
var="M_Mass_bstar"
gStyle.SetOptStat(0)
Anti2DQCDinFile = TFile(Anti2DQCDinFileName,"READ")
AntiWtaginFile = TFile(AntiWtaginFileName,"READ")
TTCRinFile = TFile(TTCRinFileName,"READ")

Anti2DQCDHis=Anti2DQCDinFile.Get(var).Clone()
Anti2DQCDHis.SetDirectory(0)
Anti2DQCDHis.Scale(1/Anti2DQCDHis.Integral())


AntiWtagHis=AntiWtaginFile.Get(var).Clone()
AntiWtagHis.SetDirectory(0)
AntiWtagHis.Scale(1/AntiWtagHis.Integral())

TTCRHis=TTCRinFile.Get(var).Clone()
TTCRHis.SetDirectory(0)
TTCRHis.Scale(1/TTCRHis.Integral())



canvy = TCanvas("QCD shape","QCD shape",1000,800)
#leggy = TLegend(0.2,0.6,0.4,0.8)
leggy = TLegend(0.7,0.7,0.9,0.9)
leggy.SetFillStyle(1001)
leggy.SetBorderSize(1)
leggy.SetFillColor(0)
leggy.SetLineColor(0)
leggy.SetShadowColor(0)
leggy.SetFillColor(kWhite)
gStyle.SetOptTitle(0);
canvy.cd()
canvy.SetBottomMargin(0.3)

Anti2DQCDHis.SetLineColor(kBlack)
AntiWtagHis.SetLineColor(kGreen)
TTCRHis.SetLineColor(kRed)


leggy.AddEntry(Anti2DQCDHis,"Electron2018_AB Data","l")
leggy.AddEntry(AntiWtagHis,"Electron2018_CD Data","l")
#leggy.AddEntry(TTCRHis,"Electron2018 Data","l")

Anti2DQCDHis.Draw("Histo")
AntiWtagHis.Draw("SAME Histo")
#TTCRHis.Draw("SAME Histo")
leggy.Draw()

canvy.SaveAs("Electron2018DataShapeCompare.pdf")
