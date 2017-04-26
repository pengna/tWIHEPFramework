#A script that will add together the cut flows from the different datasets

import sys,os,math

samplesMC=[
"qcd1000_1500",
"qcd100_200",
"qcd1500_2000",
"qcd2000_inf",
"qcd200_300",
"qcd300_500",
"qcd500_700",
"qcd700_1000",
"sChan",
"tChan_top",
"tChan_antitop",
"ttbar",
"tW_top",
"tW_antitop",
#"wPlusJets",
"ww",
"wz",
"zz",
"zPlusJetsLowMass",
"zPlusJetsHighMass",
"wPlusJetsMCatNLO",
]

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","singleMuon":"Data","tChan_top":"tChan","tChan_antitop":"tChan"}

#samplesMC = ["tW_top","tW_antitop","ttbar","singleMuon"]
#samplesMC = ["tW_top"]

sampleData = ['SingMuB','SingMuC','SingMuD','SingMuE','SingMuF','SingMuG']

emptyFile = {}

inDirMC = sys.argv[1]
inDirData = ""
if len(sys.argv) > 2:
    inDirData = sys.argv[2]

cutYield = {}
cutOrder = []

cutYield["total"] = {}

for sampleName in samplesMC:
    inDir = inDirMC
    sample = histoGramPerSample[sampleName]
    if sample == "Data":
        if inDirData == "":
            continue
        inDir= inDirData
    if not sample in cutYield.keys():
        cutYield[sample] = {}
    logFiles = [f for f in os.listdir(inDir+sampleName+"/logs/") if "log" in f and "#" not in f]
    for logFileName in logFiles:
        logFile = open(inDir+sampleName+"/logs/"+logFileName,'r')
        for line in logFile:
            if not len(line.split("|")) == 7: continue
            cut = line.split("|")[1]
            if "Min" in cut or "Max" in cut: continue
            if not cut in cutOrder:
                cutOrder.append(cut)
            if cut == "                                ":
                if not cut in cutYield['total'].keys():
                    cutYield['total'][cut] = "Total"
                cutYield[sample][cut] = sample
                continue
            if "PV" in cut:
                nEvt = float(line.split("|")[5])
                if nEvt == 0:
                    if sample not in emptyFile.keys():
                        emptyFile[sample] = []
                    emptyFile[sample].append(inDir+sampleName+"/logs/"+logFileName)
            if cut in cutYield[sample].keys():
                cutYield[sample][cut] += float(line.split("|")[5])
            else:
                cutYield[sample][cut] = float(line.split("|")[5])
            if sample == "Data": continue
            if cut in cutYield['total'].keys():
                cutYield['total'][cut] += float(line.split("|")[5])
            else:
                cutYield['total'][cut] = float(line.split("|")[5])

cutYield['totalMinusQCD'] = {}
cutYield['sOverb'] = {}
for cut in cutYield['total'].keys():
    if cut == "                                ":
        cutYield['totalMinusQCD'][cut] = "Total (no QCD)"
        cutYield['sOverb'][cut] = "S/sqrt(S+B)"
    else:
        cutYield['totalMinusQCD'][cut] = cutYield['total'][cut] - cutYield['qcd'][cut]
        cutYield['sOverb'][cut] = cutYield['tW'][cut]/math.sqrt(cutYield['total'][cut])

cutYield['Data'] = {}
emptyFile["data"] = []
for sampleName in sampleData:
    if inDirData == "": continue
    logFiles = [f for f in os.listdir(inDirData+sampleName+"/logs/") if "log" in f and "#" not in f]
    for logFileName in logFiles:
        logFile = open(inDirData+sampleName+"/logs/"+logFileName,'r')
        for line in logFile:
            if not len(line.split("|")) == 7: continue
            cut = line.split("|")[1]
            if "Min" in cut or "Max" in cut: continue
            if not cut in cutOrder:
                cutOrder.append(cut)
            if cut == "                                ":
                cutYield['Data'][cut] = "Data"
                continue
            if "PV" in cut:
                nEvt = float(line.split("|")[5])
                if nEvt == 0:                            
                    emptyFile["data"].append(inDirData+sampleName+"/logs/"+logFileName)
            if cut in cutYield["Data"].keys():
                cutYield["Data"][cut] += float(line.split("|")[5])
            else:
                cutYield["Data"][cut] = float(line.split("|")[5])
                
    print sample

tableDict = {"                             PV ":"Primary Vertex      ",
             "                    MuonTrigger ":"Trigger             ",
             "           TightMuon.Number.All ":"1 muon              ",
             "            VetoMuon.Number.All ":"Loose muon veto     ",
             "        VetoElectron.Number.All ":"Loose electron veto ",
             "                 Jet.Number.All ":"3 jets              ",
             "          Tagged.Jet.Number.All ":"1 tag               ",
             "                                ":"                    "
}

for cut in cutOrder:
    print tableDict[cut],
    for sample in cutYield.keys():
        if sample == "Data" or sample == "total" or sample == "totalMinusQCD" or sample == "sOverb": continue
        print " \t&",cutYield[sample][cut],
    if inDirData == "": print " \t&",cutYield["total"][cut]," \t&",cutYield['totalMinusQCD'][cut]," \t&"," \t&",cutYield['sOverb'][cut],
    else: print " \t&",cutYield["total"][cut]," \t&",cutYield['totalMinusQCD'][cut]," \t&",cutYield["Data"][cut]," \t&",cutYield['sOverb'][cut], 
    print "\t\\\\"

print "empty log files"

for sample in emptyFile.keys():
    print sample
    print "missing files: ", len(emptyFile[sample])
    for i in emptyFile[sample]:
        print i
