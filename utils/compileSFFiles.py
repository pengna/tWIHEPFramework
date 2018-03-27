from ROOT import *

def combineSFFiles(inFiles,inDir,lumiFractions,outFile):
    outHist = ""
    for i in range(len(inFiles)):
        inFile = TFile(inFiles[i],"READ")
        hist = inFile.Get(inDir+"/pt_abseta_ratio")
        if not outHist:
            outHist = hist.Clone()
            outHist.SetDirectory(0)
            outHist.Scale(lumiFractions[i])
        else:
            hist.Scale(lumiFractions[i])
            outHist.Add(hist)

    out = TFile(outFile,"RECREATE")
    outDir = out.mkdir(inDir)
    outDir.cd()
    outHist.Write()
    out.Close()


if __name__ == "__main__":
    inFilesList = [["config/weights/muon/MuonID_BtoF.root","config/weights/muon/MuonID_GH.root"],["config/weights/muon/MuonISO_BtoF.root","config/weights/muon/MuonISO_GH.root"],["config/weights/muon/MuonTrig_BtoF.root","config/weights/muon/MuonTrig_GH.root"]]
    inDir = ["MC_NUM_TightID_DEN_genTracks_PAR_pt_eta","TightISO_TightID_pt_eta","IsoMu24_OR_IsoTkMu24_PtEtaBins"]
    
    outFileList = ["config/weights/muon/MuonID_all.root","config/weights/muon/MuonISO_all.root","config/weights/muon/MuonTrig_all.root"]
    
    lumiFractions = [19.7/35.85,1-(19.7/35.85)]

    for i in range(3):
        
        combineSFFiles(inFilesList[i],inDir[i],lumiFractions,outFileList[i])
