#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess,os

baseDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"
thisDir = os.getcwd()

directoryPostfixes = ["MCOnly","InvIsoRegion","DDAsQCD"]
#directoryPostfixes = ["DDAsQCD"]
regions = ["","3j0t","3j2t"] 
#regions = ["3j0t","3j2t"] 

mcDir = "../skims20161017_80XAttempt2/"

threads = []

for i in regions:
    for j in directoryPostfixes:
        subprocess.call("mkdir tW"+i+j,shell=True)
    threads.append(subprocess.Popen("python "+baseDir+"utils/createPlots.py "+mcDir+"tW"+i+"/ tW"+i+"MCOnly/ tW"+i+"Data/",shell=True))
    threads.append(subprocess.Popen("python "+baseDir+"utils/createPlots.py "+mcDir+"tWInv"+i+"/ tW"+i+"InvIsoRegion/ tWInv"+i+"Data/",shell=True))
    threads.append(subprocess.Popen("python "+baseDir+"utils/createPlots.py "+mcDir+"tW"+i+"/ tW"+i+"DDAsQCD/ tW"+i+"Data/ tWInv"+i+"Data/",shell=True))

for i in threads:
    i.wait()

for i in regions:
    for j in directoryPostfixes:
        os.chdir(thisDir+"/tW"+i+j)
        print 
        print
        print "tW"+i+j
        subprocess.call("pdflatex combinedLatexFile.tex",shell=True)
        subprocess.call("mv combinedLatexFile.pdf combinedPlots"+i+j+"plots.pdf",shell=True)
        os.chdir(thisDir)
