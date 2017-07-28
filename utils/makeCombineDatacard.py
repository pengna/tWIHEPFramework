#A script that will take the event yields across bins from some file and make a combine datacard.
#Initially I will make it a simple counting experiment, then it will read off from a BDT discriminator

import sys, os

from ROOT import *

inDir = sys.argv[1]
inDirData = sys.argv[2]
inDirQCD = sys.argv[3]
outFile = open(sys.argv[4],"w")

perMCSFs = {}
#perMCSFs['qcd'] = 0.777791411029     
#perMCSFs['wPlusJets'] = 1.21611224258
#perMCSFs['qcd'] = 0.7791
#perMCSFs['wJets'] = 1.2748
#perMCSFs['ttbar'] = 0.887389045755
perMCSFs["qcd"] = 0.853484529465
perMCSFs["ttbar"] = 2.
perMCSFs["wPlusJets"] = 1.43426759985


datasetPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"ST","tChan":"ST","zz":"VV","zPlusJetsLowMass":"zJets","zPlusJetsHighMass":"zJets","wz":"VV","ww":"VV","wPlusJets":"wJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wJets","singleMuon":"Data","tChan_top":"tChan","tChan_antitop":"tChan"}

sampleMC = [
"tW_top",
"tW_antitop",
"wPlusJetsMCatNLO",
"ttbar",
"sChan",
"tChan_top",
"tChan_antitop",
"ww",
"wz",
"zz",
"zPlusJetsLowMass",
"zPlusJetsHighMass",


]

qcdSampleMC = [
"qcd1000_1500",
"qcd100_200",
"qcd1500_2000",
"qcd2000_inf",
"qcd200_300",
"qcd300_500",
"qcd500_700",
"qcd700_1000",

]

dataRange = ["B","C","D","E","F","G"]

eventYields = {} #Map a blank map to store nominal yields
systYields = {}

bTagNames = ['jes','hfstats1','hfstats2','cferr1','cferr2','lf']

#Get the event yields per MC sample
for sample in sampleMC:

    #Set up syst yield tables
    if not datasetPerSample[sample] in systYields.keys():
        systYields[datasetPerSample[sample]] = {}
        for name in bTagNames:
            for ud in ["up_","down_"]:
                systYields[datasetPerSample[sample]]["bSyst_"+ud+name] = 0.

        for ud in ["Up","Down"]:
            for systName in ["lepSF","puWeight"]:
                systYields[datasetPerSample[sample]][systName+"_"+ud] = 0.

    #Get a list of the root files to include in the chain
    print sample, "to be stored in:", datasetPerSample[sample]
    if not datasetPerSample[sample] in eventYields.keys():
        eventYields[datasetPerSample[sample]] = 0.
    filesToChain = [f for f in os.listdir(inDir+sample+"/skims/")]
    skimTree = TChain("TNT/BOOM")
    for fileIt in filesToChain:
        skimTree.Add(inDir+sample+"/skims/"+fileIt)

    for i in range(skimTree.GetEntries()):
        if i%1000 == 0: 
            sys.stdout.write("{0}/{1} processed\r".format(i,skimTree.GetEntries()))
            sys.stdout.flush()
        skimTree.GetEntry(i)
        
        eventYields[datasetPerSample[sample]] += skimTree.EventWeight
        
        #Now get the systematic weights
        for name in bTagNames:
            for ud in ["up_","down_"]:
                if not skimTree.bWeight_central == 0.:
                    systYields[datasetPerSample[sample]]["bSyst_"+ud+name] += skimTree.EventWeight * eval("skimTree.bWeight_"+ud+name)/skimTree.bWeight_central
                else:
                    systYields[datasetPerSample[sample]]["bSyst_"+ud+name] += skimTree.EventWeight
        for ud in ["Up","Down"]:
            for systName in ["lepSF","puWeight"]:
                if not eval("skimTree."+systName) == 0.:
                    systYields[datasetPerSample[sample]][systName+"_"+ud]+= skimTree.EventWeight * eval("skimTree."+systName+"_Sys"+ud)/eval("skimTree."+systName)

#Now do the data ones real quick

    print

for dataPost in dataRange:
    #Get a list of the root files to include in the chain
    if not "data" in eventYields.keys():
        eventYields["data"] = 0.
    print dataPost, " run period"
    filesToChain = [f for f in os.listdir(inDirData+"SingMu"+dataPost+"/skims/")]
    skimTree = TChain("TNT/BOOM")
    for fileIt in filesToChain:
        skimTree.Add(inDirData+"SingMu"+dataPost+"/skims/"+fileIt)

    eventYields["data"] += skimTree.GetEntries()
    
#Now do the same but for qcd
for dataPost in dataRange:
    continue
    #Get a list of the root files to include in the chain
    if not "qcd" in eventYields.keys():
        eventYields["qcd"] = 0.
    print dataPost, "run period QCD"
    filesToChain = [f for f in os.listdir(inDirQCD+"SingMu"+dataPost+"/skims/")]
    skimTree = TChain("TNT/BOOM")
    for fileIt in filesToChain:
        skimTree.Add(inDirQCD+"SingMu"+dataPost+"/skims/"+fileIt)

    eventYields["qcd"] += skimTree.GetEntries()
    

bTagYieldsUp = {}
bTagYieldsDown = {}
for key in eventYields.keys():
    if key == "data":
        print key, eventYields[key]
        continue
    if key == "qcd":
        print key, eventYields[key]
        continue
    #Unite all b systs into one manageable monthly payment
    systYields[key]["totalBTag_Up"] = 0.
    systYields[key]["totalBTag_Down"] = 0.
    if eventYields[key] > 0.:
        for name in bTagNames:
            systYields[key]["totalBTag_Up"] += (((systYields[key]["bSyst_up_"+name]/eventYields[key])-1.)*100 * ((systYields[key]["bSyst_up_"+name]/eventYields[key])-1.)*100 )
            systYields[key]["totalBTag_Down"] += (((systYields[key]["bSyst_down_"+name]/eventYields[key])-1.)*100 * ((systYields[key]["bSyst_down_"+name]/eventYields[key])-1.)*100 )
    systYields[key]["totalBTag_Up"] = (sqrt(systYields[key]["totalBTag_Up"])/100.+1.)*eventYields[key]

    systYields[key]["totalBTag_Down"] = (sqrt(systYields[key]["totalBTag_Down"])/100.+1.)*eventYields[key]

        
    print key, eventYields[key]
    for systKey in systYields[key]:
        if "bSyst" in systKey: continue
        yieldPer = 1.
        if eventYields[key] > 0.:
            yieldPer = systYields[key][systKey]/eventYields[key]
        print "\t",systKey,systYields[key][systKey], yieldPer

#Here we will write to the datacard
systsToInclude = ["totalBTag","lepSF","puWeight"]
#For now only one channel.
outFile.write("imax 1 number of channels\n")
outFile.write(("jmax {0} number of backgrounds\n").format(len(eventYields.keys())-2))#-2 for data and signal
outFile.write(("kmax {0} number of nuisance parameters\n").format(len(systsToInclude)))
outFile.write("------------\n")

#Here we need to write the observed events
outFile.write("bin 1\n")
outFile.write("observation {0}\n".format(eventYields["data"]))
outFile.write("------------\n")

outOrderPre = ["tW","ttbar","wJets","qcd","ST","zJets","VV"]
outOrder = [f for f in outOrderPre if f in eventYields.keys()]

outFile.write("bin\t\t\t")
for u in range(len(outOrder)): #-1 for data
    outFile.write(" 1\t")
outFile.write("\n")

outFile.write("process\t\t\t")
for key in outOrder: #-1 for data
    outFile.write("{0}\t".format(key))
outFile.write("\n")

outFile.write("process\t\t\t")
for u in range(len(outOrder)):
    outFile.write(" {0}\t".format(u))
outFile.write("\n")

outFile.write("rate\t\t\t")
for key in outOrder:
    outFile.write("{0:.1f}\t".format(eventYields[key]))
outFile.write("\n")

outFile.write("------------\n")

#Now we deal with the systematics
systYieldsKeys = systYields.keys()
for syst in systsToInclude:
    if "bSyst" in name: continue
    outFile.write("{0}".format(syst))
    if syst == "lepSF": outFile.write("\t")
    outFile.write("\tlnN\t")
    for dsetKey in outOrder:
        if "qcd" in dsetKey:
            outFile.write(" -\t")
            continue
        uncert = 1.
        if eventYields[dsetKey] > 0.: uncert = systYields[dsetKey][syst+"_Up"]/eventYields[dsetKey]
        outFile.write("{0:.2f}\t".format(uncert))
    outFile.write("\n")

#Finally close the datacard
outFile.close()
