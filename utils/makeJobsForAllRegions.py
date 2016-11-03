#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess

baseDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"

#for i in [""," data"]:
for i in [""]:
#    for k in [""," inv"]:
    for k in [""]:
        for j in ["", " ttbarReg", " wJetsReg"," wJets2"]:
#        for j in [" ttbarReg", " wJetsReg"]:
#        for j in [""]:
            print "maketWSubmit.py"+i+k+j
            subprocess.call( "python "+baseDir+"utils/maketWSubmit.py"+i+k+j,shell=True)
