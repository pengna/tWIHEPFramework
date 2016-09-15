import sys, os, subprocess

samples=[
"qcd1000_1500",
"qcd100_200",
"qcd1500_2000",
"qcd2000_inf",
"qcd200_300",
"qcd300_500",
"qcd500_700",
"qcd700_1000",
"sChan",
"tChan",
"ttbar",
"tW_top",
"tW_antitop",
"wPlusJets",
"ww",
"wz",
"zz",
"zPlusJetsLowMass",
"zPlusJetsHighMass",
]

nJobs = {
"qcd1000_1500":13,
"qcd100_200":193,
"qcd1500_2000":10,
"qcd2000_inf":6,
"qcd200_300":46,
"qcd300_500":50,
"qcd500_700":48,
"qcd700_1000":36,
"sChan":3,
"tChan":48,
"ttbar":242,
"tW_top":3,
"tW_antitop":3,
"wPlusJets":115,
"ww":3,
"wz":3,
"zz":3,
"zPlusJetsLowMass":76,
"zPlusJetsHighMass":69
}

dirToCheck = sys.argv[1]

missedFile = open("missingFiles.sh","w")

missedFile.write("#!/bin/bash\n")

for sample in samples:
    print sample, nJobs[sample]
    prefix = dirToCheck + sample
    for i in range(nJobs[sample]):
        statinfo = os.stat(prefix + "/logs/"+sample+str(i)+".error")
        if statinfo.st_size < 1000:
            print prefix + "/logs/"+sample+str(i)+".error"
            missedFile.write("condor_submit "+prefix + "/scripts/"+sample+str(i)+".submit -group cms -name job@schedd01.ac.cn\n")
