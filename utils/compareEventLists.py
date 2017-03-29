# A script to compare two file lists. Will print off events not found in both lists.

import sys

inFile1 = open(sys.argv[1],"r")
inFile2 = open(sys.argv[2],"r")

events1 = [line for line in inFile1.readlines()]
events2 = [line for line in inFile2.readlines()]

eventsIn1Only = []
eventsIn2Only = []

for eventNu in events1:
    if eventNu in events2:
        continue
    eventsIn1Only.append(eventNu)

print "In "+ sys.argv[1] + "only:"
for i in eventsIn1Only:
    print i[:-1]
print "A total of",len(eventsIn1Only)," events"

for eventNu in events2:
    if eventNu in events1:
        continue
    eventsIn2Only.append(eventNu)

print "In "+ sys.argv[2] + "only:"
for i in eventsIn2Only:
    print i[:-1]

print "A total of ",len(eventsIn2Only)," events"
