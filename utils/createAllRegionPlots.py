import subprocess,os

dirMap = {"":"signal","2j1t":"wJets","3j2t":"ttbar"}

subprocesses = []

for i in dirMap.keys():
    subprocess.call("mkdir -p plots/{0}/".format(dirMap[i]),shell=True)
    subprocesses.append(subprocess.Popen("python ../../framework/utils/createPlots.py tW{0}/ plots/{1}/ tW{0}Data/ tWInv{0}Data/".format(i,dirMap[i]),shell=True))
#    subprocess.call("cd plots/{0}/".format(dirMap[i]),shell=True)
#    subprocess.call("pdflatex combinedLatexFile.tex",shell=True)
#    subprocess.call("cd ../../",shell=True)

for i in subprocesses:
    i.wait()

for i in dirMap.keys():
    os.chdir("plots/{0}/".format(dirMap[i]))
    subprocesses.append(subprocess.Popen("pdflatex combinedLatexFile.tex",shell=True))
    os.chdir("../../")

for i in subprocesses:
    i.wait()
