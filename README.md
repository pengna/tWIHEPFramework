Overview
1.Event Loop 
Make smaller root files based on a selection criteria ("skimming" or "slimming")
2.Data/MC Plots 
Make stacked histogram plots that compare the (MC/data-driven) prediction with Data

Framework is structured as follows:
Directory		About
bin/			steering macros
config/			text files and generic information
SingleTopRootAnalysis/ 	.h file 	
Makefile		compiles c++ code -- not needed in CMSSW framework!
README.md		This file

setup 			 Add following script in your ~/.bash_profile file:export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH:tWIHEPFrameworkPath/lib/:$PATH


Getting Started
compile: make bstar
run a simple example : sh newTest.sh
