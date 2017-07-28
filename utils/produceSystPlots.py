#This script will produce histograms with systematics on them by looping over the skim files with additional weights in them.

from ROOT import *

import os,sys

samples = ["tW_top","tW_antitop","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar","qcd700_1000","qcd500_700","qcd300_500","qcd200_300","qcd2000_inf","qcd1500_2000","qcd100_200","qcd1000_1500"]

inDir = sys.argv[1]
inDirs = ["tW/"] #Making this a list for ease later

histsToRun = ["M_Pt_sys"]
xAxMax = {"M_Pt_sys":500}
xAxLabel = {"M_Pt_sys":"P_{T,sys}"}

histsPerSamplePerSyst = {}

systListUD = ["lepSF"]

for inDir in inDirs:
    for sample in samples:
        if sample not in histsPerSamplePerSyst.keys():
            histsPerSamplePerSyst[sample] = {}
        print "Processing sample: {0}\n".format(sample)
        
    #Populate a chain with the skims
        eventTree = TChain("TNT/BOOM")
        
        for f in os.listdir("{0}/{1}/skims/".format(inDir,sample)):
            eventTree.Add("{0}/{1}/skims/{2}".format(inDir,sample,f))
            
        for hist in histsToRun:
            histsPerSamplePerSyst[sample][hist] = {}
            histsPerSamplePerSyst[sample][hist]["central"] = TH1F("{0}_{1}_central".format(sample,hist),"{0}_{1}_central".format(sample,hist),50,0,xAxMax[hist])
            for syst in systListUD:
                for ud in ["SysUp","SysDown"]:
                    histsPerSamplePerSyst[sample][hist][syst+ud] = TH1F("{0}_{1}_{2}_{3}".format(sample,hist,syst,ud),"{0}_{1}_{2}_{3}".format(sample,hist,syst,ud),50,0,xAxMax[hist])
            
            for i in range(eventTree.GetEntries()):
                eventTree.GetEntry(i)
                histsPerSamplePerSyst[sample][hist]["central"].Fill(eval("eventTree.{0}".format(hist)),eventTree.EventWeight)
                for syst in systListUD:
                    histsPerSamplePerSyst[sample][hist][syst+"SysUp"].Fill(eval("eventTree.{0}".format(hist)),eventTree.EventWeight * (eval("eventTree.{0}_SysUp".format(syst))))
                    histsPerSamplePerSyst[sample][hist][syst+"SysDown"].Fill(eval("eventTree.{0}".format(hist)),eventTree.EventWeight * (eval("eventTree.{0}_SysDown".format(syst))))
                
            
    
