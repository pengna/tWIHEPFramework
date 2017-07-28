import subprocess

subprocesses = {}

for i in range(8):
    subprocesses[i] = subprocess.Popen("bash automaticCopyFile{0}.sh".format(i),shell=True)

for i in range(8):
    subprocesses[i].wait()
