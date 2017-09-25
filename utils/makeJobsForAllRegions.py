#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess

baseDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"

for i in [""," data"]:
#for i in [""]:
    for k in [""," inv"]:
#    for k in [""]:
#        for j in ["", " ttbarReg", " wJetsReg"," wJets2"]:
#        for j in ["", " ttbarReg"," wJets2", " ttbar2"," sig2"]:
        for j in [" ttbar2"," sig2"]:

#        for j in [" ttbarReg", " wJetsReg"," wJets2"]:
#        for j in [" ttbarReg", " wJetsReg"]:
#        for j in [" ttbarReg", " wJets2"]:
#        for j in [" wJets2"]:
#        for j in [" wJetsReg"]:
#        for j in [""]:
            for l in [""," electron"]:
#                for m in [""," jesUp"," jesDown"," jerUp"," jerDown"]:
                for m in [""]:
                    if i == " data" and not m == "": continue
                    print "makeHEPSubmit.py"+i+k+j+l
                    subprocess.call( "python "+baseDir+"utils/makeHEPSubmit.py skims"+i+k+j+l+m,shell=True)

#for i in ["jesUp","jesDown","jerUp","jerDown"]:
#    for j in [" electron"]:
#        subprocess.call( "python "+baseDir+"utils/makeHEPSubmit.py skims "+i+j,shell=True)
