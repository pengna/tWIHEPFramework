#!/bin/bash


#bin/bstar/bstar_generic.x -config config/overall/2016data/bstar.config -inlist test.list -hfile hists/2016TTWithout2D.root -skimfile skims/2016TTWithout2D.root -UseTotalEvtFromFile -SelectTrigger bstarMuon -MCatNLO -mc -bTagReshape -lepSFs -PileUpWgt -WSF -JecSourceName NONE 
#bin/bstar/bstar_generic.x -config config/overall/2018data/bstar.config.Ele -inlist config/files/2018data/QCDHT500To700_53.list -hfile hists/QCD.root -skimfile skims/QCD.root -UseTotalEvtFromFile -SelectTrigger bstarElectron -MCatNLO -mc -bTagReshape -lepSFs -PileUpWgt -WSF -JecSourceName NONE 
bin/bstar/bstar_generic.x -config config/overall/2016data/bstar.config -inlist config/files/2016data/RH_1200_0.list  -hfile hists/2016RH1200Without2D.root -skimfile skims/2016RH1200.root -UseTotalEvtFromFile -SelectTrigger bstarMuon -MCatNLO -mc -bTagReshape -lepSFs -PileUpWgt -WSF -JecSourceName NONE
#bin/bstar/bstar_generic.x -config config/overall/2018data/bstar.config -inlist config/files/2018data/RH_1200_0.list  -hfile hists/2018RH1200.root -skimfile skims/2018RH1200.root -UseTotalEvtFromFile -SelectTrigger bstarMuon -MCatNLO -mc -bTagReshape -lepSFs -PileUpWgt -WSF -JecSourceName NONE
