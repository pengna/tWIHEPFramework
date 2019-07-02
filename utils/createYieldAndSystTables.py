#A utility program that will loop through some files, extracting yields for nominal and systematic variations.
#This will then produce a pretty latex table outlining the yields and deviations from nominal per systematic

import sys,os,math

from ROOT import *

inDir = sys.argv[1]

samplesToProcess=[
"tW_top",
"tW_antitop"
]

testFile = "skims/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.rootskimBkgd.root"
testJesUp = "skims/jesUp.root"
testJesDown = "skims/jesDown.root"

fileToRead = TFile(testFile,"READ")

readTree = fileToRead.Get("TNT/BOOM")

nominalYield = 0.
bTagNames = ['jes','hfstats1','hfstats2','cferr1','cferr2','lf']
systYields = {}

for name in bTagNames:
    for ud in ["up_","down_"]:
        systYields["bSyst_"+ud+name] = 0.

for ud in ["Up","Down"]:            
    for sys in ["lepSF","puWeight"]:
        systYields[sys+"_"+ud] = 0.

for i in range(readTree.GetEntries()):
    if i%100 == 0: print i
    readTree.GetEntry(i)
    
    nominalYield  += readTree.EventWeight;
    for name in bTagNames:
        for ud in ["up_","down_"]:
            if not readTree.bWeight_central == 0.:
                systYields["bSyst_"+ud+name] += readTree.EventWeight * eval("readTree.bWeight_"+ud+name)/readTree.bWeight_central
            else:
                systYields += readTree.EventWeight
    for ud in ["Up","Down"]:
        for sys in ["lepSF","puWeight"]:
            if not eval("readTree."+sys) == 0.:
                systYields[sys+"_"+ud]+= readTree.EventWeight * eval("readTree."+sys+"_Sys"+ud)/eval("readTree."+sys)
    
#Now do the systematics that have had to be run independently
for filePref in ['jesUp','jesDown','jerUp','jerDown']:
    systYields[filePref] = 0.
    tempFile = TFile("skims/"+filePref+".root")
    readTree = tempFile.Get("TNT/BOOM")
    for i in range(readTree.GetEntries()):    
        if i%100 == 0: print i                
        readTree.GetEntry(i)                  
        
        systYields[filePref]  += readTree.EventWeight;


print nominalYield

bWeightUp = 0.
bWeightDown = 0.

for name in systYields.keys():
#    print name,systYields[name],(systYields[name]/nominalYield-1.)*100
    print '{0} {1:.1f} {2:.1f}'.format(name,systYields[name],(systYields[name]/nominalYield-1.)*100)
    if "bSyst" in name:
        if "up" in name:
            bWeightUp += (systYields[name]/nominalYield-1.)*100 * (systYields[name]/nominalYield-1.)*100
        else:
            bWeightDown += (systYields[name]/nominalYield-1.)*100 * (systYields[name]/nominalYield-1.)*100

print 'bTag up: {0:.1f} bTag down: {1:.2f}'.format(sqrt(bWeightUp),sqrt(bWeightDown))
#for ud in ["up_","down_"]:
    
