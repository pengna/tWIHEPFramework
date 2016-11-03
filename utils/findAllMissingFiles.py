#Make the job folders for all of the regions we want to study for the tW lepton+jets

import subprocess

baseDir = "/publicfs/cms/user/duncanleg/tW13TeV/framework/"

#for i in ["","Data"]:
for i in [""]:
    for k in ["","Inv"]:
        for j in ["", "3j2t", "3j0t"]:
#        for j in ["2j1t"]:
#            if i == "" and k == "Inv": continue
#        for j in [""]:
            print "tW"+k+j+i
            subprocess.call("python "+baseDir+"utils/resubmitJobs.py tW"+k+j+i+"/",shell=True)
#            subprocess.call("bash missingFiles.sh",shell=True)
##            subprocess.call( "python "+baseDir+"utils/maketWSubmit.py"+i+k+j,shell=True)




