#A script that will automatically generate bash files that will copy files from the t2 to the publicfs

import os, sys

totalBase = "/pnfs/ihep.ac.cn/data/cms/store/user/leggat/tWSamples/mcMoriond17/"

dirsToDo = ["TT_","tW_top","tW_antitop"]
dirsToSkip = ["PlusTrig","ReTrig"]

listOfDirs = os.listdir(totalBase)

def openNewFile(count):
    fileToOpen = open("automaticCopyFile{0}.sh".format(count),"w")
    fileToOpen.write("for ((i=1;i<1001;i++))\ndo\n")
    return fileToOpen

def closeFile(fileToClose):
    fileToClose.write("done\n")
    fileToClose.close() 

fileCounter = 0
currentFile = openNewFile(fileCounter)

nDsetsPerFile = 5
dirsInFileCounter = 0
for baseDir in listOfDirs:
    doDir = False
    for dirToDo in dirsToDo:
        if dirToDo in baseDir: 
            doDir = True
    if not doDir: continue
#    print baseDir
    nextDir = os.path.join(totalBase,baseDir)
    nextLayerDirs = os.listdir(nextDir)
#    print nextDir
    for nextLayerDir in nextLayerDirs:
        dir2 = os.path.join(nextDir,nextLayerDir)
        for dirToSkip in dirsToSkip:
            if dirToSkip in dir2:
                doDir = False
        if not doDir: continue
#        print dir2
        nextLayer2 = os.listdir(dir2)
        for nextLayer in nextLayer2:
            dir3 = os.path.join(dir2,nextLayer)
#            print dir3
            nextLayer3 = os.listdir(dir3)
            for nextNextLayer in nextLayer3:
                dir4 = os.path.join(dir3,nextNextLayer)
                outputDir = os.path.join(baseDir,nextLayerDir,nextLayer,nextNextLayer)
                print dir4
                if not os.path.exists("/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/systematicSamples/{0}".format(outputDir)):
                    os.makedirs("/publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/systematicSamples/{0}".format(outputDir))
                currentFile.write("srmcp --debug srm://srm.ihep.ac.cn{0}/OutTree_ttbar_${{i}}.root file:////publicfs/cms/data/TopQuark/cms13TeV/tWlJetSamples/systematicSamples/{1}\n".format(dir4,outputDir))
                currentFile.write("srmrm srm://srm.ihep.ac.cn{0}/OutTree_ttbar_${{i}}.root\n".format(dir4))
                dirsInFileCounter += 1
                if dirsInFileCounter == nDsetsPerFile:
                    closeFile(currentFile)
                    fileCounter+=1
                    currentFile = openNewFile(fileCounter)
                    dirsInFileCounter = 0

closeFile(currentFile)
