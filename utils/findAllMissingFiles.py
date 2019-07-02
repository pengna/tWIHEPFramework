#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess

baseDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"

missingFiles = {}

#for i in ["","Data"]:
for i in ["Data"]:
    missingFiles[i] = {}
    for k in ["","Inv"]:
        missingFiles[i][k] = {}
        for j in ["", "3j2t", "3j0t","2j1t"]:
            missingFiles[i][k][j] = 0
#        for j in ["2j1t"]:
#            if i == "" and k == "Inv": continue
#        for j in [""]:
            print "tW"+k+j+i
            subprocess.call("python "+baseDir+"utils/resubmitJobs.py tW"+k+j+i+"/",shell=True)
            subprocess.call("bash missingFiles.sh",shell=True)
            with open("missingFiles.sh") as f:
                for missingFiles[i][k][j], l in enumerate(f):
                    pass
##            subprocess.call( "python "+baseDir+"utils/maketWSubmit.py"+i+k+j,shell=True)

for i in missingFiles.keys():
    for j in missingFiles[i].keys():
        for k in missingFiles[i][j].keys():
            print "tW"+j+k+i," had ",missingFiles[i][j][k],"missing files"


