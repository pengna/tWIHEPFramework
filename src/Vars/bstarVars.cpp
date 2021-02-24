/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/bstarVars.hpp"
#include <iostream>

//Test out a couple of variables, one int and one float I guess
bstarVars::bstarVars(bool makeHistos){
	SetName("bstarVars");
	//some Vars will use in bstar analyize
	//Lepton Vars
	_intVars["M_nLepton"] = -999.;
	_floatVars["M_E_Lepton"]   =-999.;
	_floatVars["M_Pt_Lepton"]  = -999.;
	_floatVars["M_Eta_Lepton"] = -999.;
	_floatVars["M_Phi_Lepton"] = -999; 
	_floatVars["M_Mass_Lepton"]       = -999.;
	_floatVars["M_DeltaRLeptonClostJet"] = 100.;
	_floatVars["M_DeltaRmin_LeptonBJet"] = 100.;
	_floatVars["M_relpt_Jet"] = -999.;
	_floatVars["M_relE_Jet"] = -999.;
	_floatVars["M_mindr_Jet"] = 100.;
	_floatVars["M_minptrel_Jet"] = 10000.;
	_floatVars["M_relIsoR04"] = -999.;
	_floatVars["M_miniIsoR"] = -999.;
	 _floatVars["M_relIsoR_Ele"] =-999.;
	_floatVecVars["M_E_Lepton"] ;
        _floatVecVars["M_Pt_Lepton"] ;
        _floatVecVars["M_Eta_Lepton"] ;
        _floatVecVars["M_Phi_Lepton"] ; 
        _floatVecVars["M_Mass_Lepton"];



	//Jet Vars
	_intVars["M_nJet"] = -999.;
	_floatVars["M_E_Jet"]   =-999.;
	_floatVars["M_Pt_Jet"]  = -999.;
	_floatVars["M_Eta_Jet"] = -999.;
	_floatVars["M_Phi_Jet"] = -999; 
	_floatVars["M_Mass_Jet"]       = -999.;
	_floatVecVars["M_E_AllJet"] ;
	_floatVecVars["M_Pt_AllJet"] ;
	_floatVecVars["M_Eta_AllJet"] ;
	_floatVecVars["M_Phi_AllJet"] ; 
	_floatVecVars["M_Mass_AllJet"];
	//BJet Vars
	_intVars["M_nBJet"] = -999;
	_floatVars["M_E_BJet"]   =-999.;
	_floatVars["M_Pt_BJet"]  = -999.;
	_floatVars["M_Eta_BJet"] = -999.;
	_floatVars["M_Phi_BJet"] = -999; 
	_floatVars["M_Mass_BJet"]       = -999.;
	_floatVars["M_E_LeadBJet"]   =-999.;
        _floatVars["M_Pt_LeadBJet"]  = -999.;
        _floatVars["M_Eta_LeadBJet"] = -999.;
        _floatVars["M_Phi_LeadBJet"] = -999; 
        _floatVars["M_Mass_LeadBJet"]       = -999.;

	_floatVecVars["M_E_AllBJet"];
	_floatVecVars["M_Pt_AllBJet"];
	_floatVecVars["M_Eta_AllBJet"] ;
	_floatVecVars["M_Phi_AllBJet"] ; 
	_floatVecVars["M_Mass_AllBJet"] ;
	_floatVecVars["M_DeltaRBJetLepton"] ;
	_floatVars["M_DeltaRBLeadJetLepton"] =-999.;
	_floatVars["M_DeltaRChosedBJetLepton"] =-999.;
	//Boostedjet Vars
	_floatVars["M_E_BoostedJet"]          =-999.;
	_floatVars["M_Pt_BoostedJet"]         = -999.;
	_floatVars["M_Eta_BoostedJet"]        = -999.;
	_floatVars["M_Phi_BoostedJet"]        = -999.;
	_floatVars["M_Mass_BoostedJet"]       = -999.;
	_floatVars["M_prunedmass_BoostedJet"]       = -999.;
	_floatVars["M_softdropmass_BoostedJet"]       = -999.;
	_floatVars["M_softdropmasscorr_BoostedJet"]       = -999.;
	_floatVars["M_tau21_BoostedJet"]       = -999.0;
	_floatVars["M_tau32_BoostedJet"]       = -999.0;
	
	_intVars["M_nBoostedJet"] = -999;
	_floatVecVars["M_E_AllBoostedJet"] ;
        _floatVecVars["M_Pt_AllBoostedJet"] ;
        _floatVecVars["M_Eta_AllBoostedJet"] ;
        _floatVecVars["M_Phi_AllBoostedJet"] ; 
        _floatVecVars["M_Mass_AllBoostedJet"];
        _floatVecVars["M_Pt_MCTop"] ;


	//W Vars
	_floatVars["M_E_W"]          = -999.;
	_floatVars["M_Pt_W"]         = -999.;
	_floatVars["M_Eta_W"]        = -999.;
	_floatVars["M_Phi_W"]        = -999;
	_floatVars["M_Mass_W"]       = -999.;
	//Top Vars
	_floatVars["M_E_Top"]          =-999.; 
	_floatVars["M_Pt_Top"]         = -999.;
	_floatVars["M_Eta_Top"]        = -999.;
	_floatVars["M_Phi_Top"]        = -999.;
	_floatVars["M_Mass_Top"] = -999.;
	_floatVars["M_E_Topleadjet"]          =-999.; 
	_floatVars["M_Pt_Topleadjet"]         = -999.;
	_floatVars["M_Eta_Topleadjet"]        = -999.;
	_floatVars["M_Phi_Topleadjet"]        = -999;
	_floatVars["M_Mass_Topleadjet"] = -999.;
	//bstar Vars  
	_floatVars["M_E_bstar"]          =-999.;
	_floatVars["M_Pt_bstar"]         = -999.;
	_floatVars["M_Eta_bstar"]        = -999.;
	_floatVars["M_Phi_bstar"]        = -999;
	_floatVars["M_Mass_bstar"] = -999.;
	_floatVars["M_E_bstarleadjet"]          =-999.;
	_floatVars["M_Pt_bstarleadjet"]         = -999.;
	_floatVars["M_Eta_bstarleadjet"]        = -999.;
	_floatVars["M_Phi_bstarleadjet"]        = -999.;
	_floatVars["M_Mass_bstarleadjet"] = -999.;          
//met Vars

	_floatVars["M_MET"] = -999.;          
	_floatVars["M_MET_Phi"] = -999.;          
	_floatVars["M_MET_xy"] = -999.;          
	_floatVars["M_MET_xy_Phi"] = -999.;          


	SetDoHists(makeHistos);
}

void bstarVars::ResetVars(){


        _intVars["M_nLepton"] = -999.;
        _floatVars["M_E_Lepton"]   =-999.;
        _floatVars["M_Pt_Lepton"]  = -999.;
        _floatVars["M_Eta_Lepton"] = -999.;
        _floatVars["M_Phi_Lepton"] = -999; 
        _floatVars["M_Mass_Lepton"]       = -999.;
        _floatVars["M_DeltaRLeptonClostJet"] = 100.;
        _floatVars["M_DeltaRmin_LeptonBJet"] = 100.;
        _floatVars["M_relpt_Jet"] = -999.;
        _floatVars["M_relE_Jet"] = -999.;
        _floatVars["M_mindr_Jet"] = 100.;
        _floatVars["M_minptrel_Jet"] = 10000.;
        _floatVars["M_relIsoR04"] = -999.;
        _floatVars["M_miniIsoR"] = -999.;
         _floatVars["M_relIsoR_Ele"] =-999.;

       _intVars["M_nJet"] = -999.;
        _floatVars["M_E_Jet"]   =-999.;
        _floatVars["M_Pt_Jet"]  = -999.;
        _floatVars["M_Eta_Jet"] = -999.;
        _floatVars["M_Phi_Jet"] = -999;
        _floatVars["M_Mass_Jet"]       = -999.;

        _intVars["M_nBJet"] = -999;
        _floatVars["M_E_BJet"]   =-999.;
        _floatVars["M_Pt_BJet"]  = -999.;
        _floatVars["M_Eta_BJet"] = -999.;
        _floatVars["M_Phi_BJet"] = -999;
        _floatVars["M_Mass_BJet"]       = -999.;
        _floatVars["M_E_LeadBJet"]   =-999.;
        _floatVars["M_Pt_LeadBJet"]  = -999.;
        _floatVars["M_Eta_LeadBJet"] = -999.;
        _floatVars["M_Phi_LeadBJet"] = -999;
        _floatVars["M_Mass_LeadBJet"]       = -999.;
   _floatVars["M_DeltaRBLeadJetLepton"] =-999.;
        _floatVars["M_DeltaRChosedBJetLepton"] =-999.;
   _floatVars["M_E_BoostedJet"]          =-999.;
        _floatVars["M_Pt_BoostedJet"]         = -999.;
        _floatVars["M_Eta_BoostedJet"]        = -999.;
        _floatVars["M_Phi_BoostedJet"]        = -999.;
        _floatVars["M_Mass_BoostedJet"]       = -999.;
        _floatVars["M_prunedmass_BoostedJet"]       = -999.;
        _floatVars["M_softdropmass_BoostedJet"]       = -999.;
        _floatVars["M_softdropmasscorr_BoostedJet"]       = -999.;
        _floatVars["M_tau21_BoostedJet"]       = -999.0;
        _floatVars["M_tau32_BoostedJet"]       = -999.0;

        _intVars["M_nBoostedJet"] = -999;


	_floatVars["M_E_W"]          = -999.;
	_floatVars["M_Pt_W"]         = -999.;
	_floatVars["M_Eta_W"]        = -999.;
	_floatVars["M_Phi_W"]        = -999;
	_floatVars["M_Mass_W"]       = -999.;
	_floatVars["M_E_Top"]          =-999.;
	_floatVars["M_Pt_Top"]         = -999.;
	_floatVars["M_Eta_Top"]        = -999.;
	_floatVars["M_Phi_Top"]        = -999.;
	_floatVars["M_Mass_Top"] = -999.;
	_floatVars["M_E_Topleadjet"]          =-999.;
	_floatVars["M_Pt_Topleadjet"]         = -999.;
	_floatVars["M_Eta_Topleadjet"]        = -999.;
	_floatVars["M_Phi_Topleadjet"]        = -999;
	_floatVars["M_Mass_Topleadjet"] = -999.;
	//bstar Vars  
	_floatVars["M_E_bstar"]          =-999.;
	_floatVars["M_Pt_bstar"]         = -999.;
	_floatVars["M_Eta_bstar"]        = -999.;
	_floatVars["M_Phi_bstar"]        = -999;
	_floatVars["M_Mass_bstar"] = -999.;
	_floatVars["M_E_bstarleadjet"]          =-999.;
	_floatVars["M_Pt_bstarleadjet"]         = -999.;
	_floatVars["M_Eta_bstarleadjet"]        = -999.;
	_floatVars["M_Phi_bstarleadjet"]        = -999.;
	_floatVars["M_Mass_bstarleadjet"] = -999.;


}

void bstarVars::FillBranches(EventContainer * evtObj){
	ResetVars();
	//Initialise vectors;
	//  BoostedJet.clear();
	Jet.clear();
	BJet.clear();
	Muon.clear();
	Electron.clear();
	BoostedJets.clear();
	_floatVecVars["M_DeltaRBJetLepton"].clear();
	_floatVecVars["M_E_AllJet"].clear() ;
	_floatVecVars["M_Pt_AllJet"].clear() ;
	_floatVecVars["M_Eta_AllJet"].clear() ;
	_floatVecVars["M_Phi_AllJet"].clear() ;      
	_floatVecVars["M_Mass_AllJet"].clear();
	_floatVecVars["M_E_AllBJet"].clear();
	_floatVecVars["M_Pt_AllBJet"].clear();
	_floatVecVars["M_Eta_AllBJet"].clear() ;
	_floatVecVars["M_Phi_AllBJet"].clear() ;
	_floatVecVars["M_Mass_AllBJet"].clear() ;

	_floatVecVars["M_E_AllLepton"].clear() ;
	_floatVecVars["M_Pt_AllLepton"].clear() ;
	_floatVecVars["M_Eta_AllLepton"].clear() ;
	_floatVecVars["M_Phi_AllLepton"].clear() ;      
	_floatVecVars["M_Mass_AllLepton"].clear();
	_floatVecVars["M_E_AllBoostedJet"].clear();
	_floatVecVars["M_Pt_AllBoostedJet"].clear();
	_floatVecVars["M_Eta_AllBoostedJet"].clear() ;
	_floatVecVars["M_Phi_AllBoostedJet"].clear() ;
	_floatVecVars["M_Mass_AllBoostedJet"].clear() ;


	LeadJet.SetPtEtaPhiE(0,0,0,0);
	sumJet.SetPtEtaPhiE(0,0,0,0);
	sumBJet.SetPtEtaPhiE(0,0,0,0);
	totalJets.SetPtEtaPhiE(0,0,0,0);

	Int_t _bstar = 0;
	Int_t _Elechannel = 0;
	TEnv *config = evtObj-> GetConfig();
	_bstar = config -> GetValue("ifbstar",0);
	_Elechannel =        config -> GetValue("ifelechannel",0);
	EventTree* eventTree = evtObj->GetEventTree();
	if(_bstar){
		//set up lepton and met
		TLorentzVector Lepton(0,0,0,0);		
		TLorentzVector Leptonfor2D(0,0,0,0);		
		TLorentzVector lep_p4(0,0,0,0);	
		TVector3 Jet_p3(0,0,0);
		TVector3 lep_p3(0,0,0);	
		if( _Elechannel ){
			for(int i=0;i<evtObj->electronsToUsePtr->size();i++){
				float detaR=100.0,mindetaR =100.0,relpt=-999.0,relE=-999.0,minrelpt=-999.0,minrelE=-999.0,deltaRBjet=-999.0,mindeltaRBjet =-999.0;
				Lepton.SetPtEtaPhiE(evtObj->electronsToUsePtr->at(i).Pt(),evtObj->electronsToUsePtr->at(i).Eta(),evtObj->electronsToUsePtr->at(i).Phi(),evtObj->electronsToUsePtr->at(i).E());
				lep_p4 = TLorentzVector(evtObj->electronsToUsePtr->at(i).Px(),evtObj->electronsToUsePtr->at(i).Py(),evtObj->electronsToUsePtr->at(i).Pz(),evtObj->electronsToUsePtr->at(i).E());
				TVector3 lep_p3(evtObj->electronsToUsePtr->at(i).Px(),evtObj->electronsToUsePtr->at(i).Py(),evtObj->electronsToUsePtr->at(i).Pz());

				_floatVars["M_Mass_Lepton"]       = (Lepton).M();
				_floatVars["M_E_Lepton"]          = (Lepton).E();
				_floatVars["M_Pt_Lepton"]         = (Lepton).Pt();
				_floatVars["M_Eta_Lepton"]        = (Lepton).Eta();
				_floatVars["M_Phi_Lepton"]        = (Lepton).Phi();
				//	_floatVars["M_mindr_Jet"]      = evtObj->electronsToUsePtr->at(i).dr();  	
				//	_floatVars["M_minptrel_Jet"]      = evtObj->electronsToUsePtr->at(i).ptrel();  	
				//	_floatVars["M_relIsoR_Ele"]      = evtObj->electronsToUsePtr->at(i).relIsoR();  	
				//  	_floatVars["M_miniIsoR"]      = evtObj->electronsToUsePtr->at(i).miniIsoR();  	


				for(int i=0;i<evtObj->jetsToUsePtr->size();i++){
					detaR =fabs(evtObj->jetsToUsePtr->at(i).DeltaR(Lepton)); 
					TVector3 Jet_p3(evtObj->jetsToUsePtr->at(i).Px(),evtObj->jetsToUsePtr->at(i).Py(),evtObj->jetsToUsePtr->at(i).Pz());
					relpt=sin(Jet_p3.Angle(lep_p3))*lep_p3.Mag();
					relE = (evtObj->jetsToUsePtr->at(i).E()-(Lepton).E())/(evtObj->jetsToUsePtr->at(i).E()+(Lepton).E());
					//if(evtObj->jetsToUsePtr->at(i).Pt()>30&&detaR<mindetaR){mindetaR=detaR;minrelpt=relpt;}
					if(detaR<mindetaR){mindetaR=detaR;minrelpt=relpt;minrelE=relE;}
					//cout<<"Jet_p3.Angle(lep_p3)="<<Jet_p3.Angle(lep_p3)<<endl<<"lep_p3.Mag()="<<lep_p3.Mag()<<endl;
				}        
				//	if(mindetaR<0.4)cout<<"mindetaR ="<<mindetaR<<endl;
				_floatVars["M_DeltaRLeptonClostJet"]=mindetaR;
				_floatVars["M_relpt_Jet"]  =	minrelpt; 
				_floatVars["M_relE_Jet"]  =	minrelE; 

				 for(int i=0;i<evtObj->taggedjetsToUsePtr->size();i++){
					 deltaRBjet =fabs(evtObj->taggedjetsToUsePtr->at(i).DeltaR(Lepton));
					if(deltaRBjet<mindeltaRBjet){mindeltaRBjet=deltaRBjet;}
					
					}
				_floatVars["M_DeltaRmin_LeptonBJet"]=mindeltaRBjet;
			}


			int electronnumber=0;
			TLorentzVector tempelectron(0,0,0,0);
			for (auto electron : evtObj-> tightElectrons){

				tempelectron.SetPtEtaPhiE(electron.Pt(),electron.Eta(),electron.Phi(),electron.E());
				Electron.push_back(tempelectron);
				_floatVecVars["M_E_AllLepton"].push_back(tempelectron.E());       
				_floatVecVars["M_Pt_AllLepton"].push_back(tempelectron.Pt());
				_floatVecVars["M_Eta_AllLepton"].push_back(tempelectron.Eta()) ;
				_floatVecVars["M_Phi_AllLepton"].push_back(tempelectron.Phi()) ;
				_floatVecVars["M_Mass_AllLepton"].push_back(tempelectron.M()) ;

			}

			electronnumber=Electron.size();                                                                  	
			_intVars["M_nLepton"] = electronnumber;                                                                 				
		}

		else {
			for(int i=0;i<evtObj->muonsToUsePtr->size();i++){
				Lepton.SetPtEtaPhiE(evtObj->muonsToUsePtr->at(i).Pt(),evtObj->muonsToUsePtr->at(i).Eta(),evtObj->muonsToUsePtr->at(i).Phi(),evtObj->muonsToUsePtr->at(i).E());
				lep_p4 = TLorentzVector(evtObj->muonsToUsePtr->at(i).Px(),evtObj->muonsToUsePtr->at(i).Py(),evtObj->muonsToUsePtr->at(i).Pz(),evtObj->muonsToUsePtr->at(i).E()); 
				TVector3 lep_p3(evtObj->muonsToUsePtr->at(i).Px(),evtObj->muonsToUsePtr->at(i).Py(),evtObj->muonsToUsePtr->at(i).Pz()); 

				_floatVars["M_Mass_Lepton"]       = (Lepton).M();
				_floatVars["M_E_Lepton"]          = (Lepton).E();
				_floatVars["M_Pt_Lepton"]         = (Lepton).Pt();
				_floatVars["M_Eta_Lepton"]        = (Lepton).Eta();
				_floatVars["M_Phi_Lepton"]        = (Lepton).Phi();
				_floatVars["M_mindr_Jet"]      = evtObj->muonsToUsePtr->at(i).dr();  	
				_floatVars["M_minptrel_Jet"]      = evtObj->muonsToUsePtr->at(i).ptrel();  	
				_floatVars["M_relIsoR04"]      = evtObj->muonsToUsePtr->at(i).relIsoR04();  	
				_floatVars["M_miniIsoR"]      = evtObj->muonsToUsePtr->at(i).miniIsoR();  	

				float detaR=100.0,mindetaR =100.0,relpt=-999.0,minrelpt=-999.0,relE=-999.0,minrelE=-999.0,deltaRBjet=100.0,mindeltaRBjet =100.0;
				//	Lepton.SetPtEtaPhiE(evtObj->muonsToUsePtr->at(i).Pt(),evtObj->muonsToUsePtr->at(i).Eta(),evtObj->muonsToUsePtr->at(i).Phi(),evtObj->muonsToUsePtr->at(i).E());
				//	TVector3 lep_p3(evtObj->muonsToUsePtr->at(i).Px(),evtObj->muonsToUsePtr->at(i).Py(),evtObj->muonsToUsePtr->at(i).Pz()); 
				for(int i=0;i<evtObj->jetsToUsePtr->size();i++){
					detaR =fabs(evtObj->jetsToUsePtr->at(i).DeltaR(Lepton));  
					//		cout <<"Jet E = "<<evtObj->jetsToUsePtr->at(i).E()<<"Jet Pt = "<<evtObj->jetsToUsePtr->at(i).Pt()<<"Jet Eta = "<<evtObj->jetsToUsePtr->at(i).Eta()<<"Jet Phi = "<<evtObj->jetsToUsePtr->at(i).Phi()<<endl;
					TVector3 Jet_p3(evtObj->jetsToUsePtr->at(i).Px(),evtObj->jetsToUsePtr->at(i).Py(),evtObj->jetsToUsePtr->at(i).Pz());
					relpt=sin(Jet_p3.Angle(lep_p3))*lep_p3.Mag();
					relE = (evtObj->jetsToUsePtr->at(i).E()-(Lepton).E())/(evtObj->jetsToUsePtr->at(i).E()+(Lepton).E());
					if(detaR<mindetaR){mindetaR=detaR;minrelpt=relpt;minrelE=relE;
					}
				}
				_floatVars["M_DeltaRLeptonClostJet"]=mindetaR;
				_floatVars["M_relpt_Jet"]  =	minrelpt; 
				_floatVars["M_relE_Jet"]  =	minrelE; 


				for(int i=0;i<evtObj->taggedjetsToUsePtr->size();i++){
					deltaRBjet =fabs(evtObj->taggedjetsToUsePtr->at(i).DeltaR(Lepton));
					if(deltaRBjet<mindeltaRBjet){mindeltaRBjet=deltaRBjet;}

				}
				_floatVars["M_DeltaRmin_LeptonBJet"]=mindeltaRBjet;
			}






		int muonnumber=0;
		TLorentzVector tempmuon(0,0,0,0);
		for (auto muon : evtObj-> tightMuons){

			tempmuon.SetPtEtaPhiE(muon.Pt(),muon.Eta(),muon.Phi(),muon.E());
			Muon.push_back(tempmuon);
			_floatVecVars["M_E_AllLepton"].push_back(tempmuon.E());       
			_floatVecVars["M_Pt_AllLepton"].push_back(tempmuon.Pt());
			_floatVecVars["M_Eta_AllLepton"].push_back(tempmuon.Eta()) ;
			_floatVecVars["M_Phi_AllLepton"].push_back(tempmuon.Phi()) ;
			_floatVecVars["M_Mass_AllLepton"].push_back(tempmuon.M()) ;

		}

		muonnumber=Muon.size();                                                                  	
		_intVars["M_nLepton"] = muonnumber;                                                                 				       
		}  

	TLorentzVector met(00,0,0,0);
	TLorentzVector W(00,0,0,0);
	TLorentzVector lep_neutrino(0,0,0,0);

	met.SetPtEtaPhiE(evtObj->missingEt,0,evtObj->missingPhi,0.);
//	met.SetPtEtaPhiE(evtObj->missingEt_xy_corr,0,evtObj->missingPhi_xy_corr,0.);
	_floatVars["M_MET"]=(evtObj->missingEt) ;          
	_floatVars["M_MET_xy"]=(evtObj->missingEt_xy_corr) ;          
	_floatVars["M_MET_Phi"]=(evtObj->missingPhi) ;          
	_floatVars["M_MET_xy_Phi"]=(evtObj->missingPhi_xy_corr) ;          
	//Get W
		double M_W  = 80.4;
		double M_mu =  0.10566;
		double M_e = 0.511e-3;
		double M_lepton = M_mu;
		double emu = Lepton.E();
		double pxmu = Lepton.Px();
		double pymu = Lepton.Py();
		double pzmu = Lepton.Pz();
		double pxnu = met.Px();
		double pynu = met.Py();
		double pznu = 0.;
		double a = M_W*M_W - M_lepton*M_lepton + 2.0*(pxmu*pxnu + pymu*pynu);
		double A = 4.0*(emu*emu - pzmu*pzmu);
		double B = -4.0*a*pzmu;
		double C = 4.0*emu*emu*(pxnu*pxnu + pynu*pynu) - a*a;

		double tmproot = B*B - 4.0*A*C;
		bool isComplex_ = false;
		if (tmproot<0) {
			isComplex_= true;
			pznu = - B/(2*A); // take real part of complex roots
		}
		else {
			isComplex_ = false;
			double tmpsol1 = (-B + TMath::Sqrt(tmproot))/(2.0*A);
			double tmpsol2 = (-B - TMath::Sqrt(tmproot))/(2.0*A);
			if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2;}
			else pznu = tmpsol1;
			// if pznu is > 300 pick the most central root
		//	if ( pznu > 300. ) {
		//		if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) pznu = tmpsol1;
		//		else pznu = tmpsol2;
		//	}
		} 
		float mu_nupz=pznu ;
		float  mu_nuE  = sqrt( met.Px()*met.Px() + met.Py()*met.Py()+mu_nupz*mu_nupz); 
		lep_neutrino  = TLorentzVector(met.Px(), met.Py(), mu_nupz, mu_nuE );
		//W  = lep_neutrino+Lepton;
		W  = lep_neutrino+lep_p4;
		_floatVars["M_Mass_W"]       = (W).M();
		_floatVars["M_E_W"]          = (W).E();
		_floatVars["M_Pt_W"]         = (W).Pt();
		_floatVars["M_Eta_W"]        = (W).Eta();
		_floatVars["M_Phi_W"]        = (W).Phi();

		//Get Top
		TLorentzVector Jet_p4(0,0,0,0);
		TLorentzVector LeadJet_p4(0,0,0,0);
		TLorentzVector ChosedJet_p4(0,0,0,0);
		TLorentzVector Top_p4(0,0,0,0);
		TLorentzVector Top(0,0,0,0);
		TLorentzVector Top_temp(0,0,0,0);
		TLorentzVector Topleadjet_p4(0,0,0,0);
		TLorentzVector Topleadjet(0,0,0,0);
		float mintopmassdiff=9999.9;
		float topmassdiff_temp=999.9;
		float DeltaRLepton=0.0;
		//cout <<"muon number is:"<<evtObj->muonsToUsePtr->size()<<"tagged jet number is :"<<evtObj->taggedjetsToUsePtr->size()<<"boostedjet number is :"<<evtObj->boostedjetsToUsePtr->size()<<endl;
		for(int i=0;i<evtObj->taggedjetsToUsePtr->size();i++){
			Jet_p4 = TLorentzVector(evtObj->taggedjetsToUsePtr->at(i).Px(),evtObj->taggedjetsToUsePtr->at(i).Py(),evtObj->taggedjetsToUsePtr->at(i).Pz(),evtObj->taggedjetsToUsePtr->at(i).E());
			//		 Jet = TLorentzVector(evtObj->jetsToUsePtr->at(i).Pt(),evtObj->jetsToUsePtr->at(i).Eta(),evtObj->jetsToUsePtr->at(i).Phi(),evtObj->jetsToUsePtr->at(i).E());

			Top_temp = Jet_p4+W;
			topmassdiff_temp =fabs(Top_temp.M()-172.5);
			//cout<<"topmassdiff_temp="<<topmassdiff_temp<<endl;
			if(topmassdiff_temp<mintopmassdiff){
				DeltaRLepton = evtObj->taggedjetsToUsePtr->at(i).DeltaR(Lepton);
				mintopmassdiff=topmassdiff_temp;
				ChosedJet_p4=Jet_p4;
				Top = Top_temp;
				Top_p4.SetPtEtaPhiM(Top.Pt(),Top.Eta(),Top.Phi(),Top.M());
				
			}
			
			if (Jet_p4.Pt()>LeadJet_p4.Pt())LeadJet_p4=Jet_p4; 
		}
		//cout<<"mintopmassdiff ="<<mintopmassdiff<<endl;
		Topleadjet =LeadJet_p4+W;
		Topleadjet_p4.SetPtEtaPhiM(Topleadjet.Pt(),Topleadjet.Eta(),Topleadjet.Phi(),Topleadjet.M());
		 _floatVars["M_DeltaRChosedBJetLepton"] = DeltaRLepton;
		_floatVars["M_Mass_Top"]       = (Top_p4).M();
		_floatVars["M_E_Top"]          = (Top_p4).E();
		_floatVars["M_Pt_Top"]         = (Top_p4).Pt();
		_floatVars["M_Eta_Top"]        = (Top_p4).Eta();
		_floatVars["M_Phi_Top"]        = (Top_p4).Phi();	

		_floatVars["M_Mass_Topleadjet"]       = (Topleadjet_p4).M();
		_floatVars["M_E_Topleadjet"]          = (Topleadjet_p4).E();
		_floatVars["M_Pt_Topleadjet"]         = (Topleadjet_p4).Pt();
		_floatVars["M_Eta_Topleadjet"]        = (Topleadjet_p4).Eta();   
		_floatVars["M_Phi_Topleadjet"]        = (Topleadjet_p4).Phi();	

		_floatVars["M_Mass_BJet"]     = (ChosedJet_p4).M();
                _floatVars["M_E_BJet"]     = (ChosedJet_p4).E();
                _floatVars["M_Pt_BJet"]     = (ChosedJet_p4).Pt();
                _floatVars["M_Eta_BJet"]     = (ChosedJet_p4).Eta();
                _floatVars["M_Phi_BJet"]     = (ChosedJet_p4).Phi();


		_floatVars["M_Mass_LeadBJet"]     = (LeadJet_p4).M();
		_floatVars["M_E_LeadBJet"]     = (LeadJet_p4).E();
		_floatVars["M_Pt_LeadBJet"]     = (LeadJet_p4).Pt();
		_floatVars["M_Eta_LeadBJet"]     = (LeadJet_p4).Eta();
		_floatVars["M_Phi_LeadBJet"]     = (LeadJet_p4).Phi();



		//Get Jet and BJet pt eta phi 
		int Bjetnumber=0;
		int jetnumber=0;
		float tempDeltaR=0.0;
		int i =0;
		TLorentzVector tempjet(0,0,0,0);
		for (auto jet : evtObj->taggedJets){

			tempjet.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
			tempDeltaR = tempjet.DeltaR(Lepton);
			BJet.push_back(tempjet);
			_floatVecVars["M_DeltaRBJetLepton"].push_back(tempDeltaR);
			_floatVecVars["M_E_AllBJet"].push_back(tempjet.E());
			_floatVecVars["M_Pt_AllBJet"].push_back(tempjet.Pt());
			_floatVecVars["M_Eta_AllBJet"].push_back(tempjet.Eta()) ;
			_floatVecVars["M_Phi_AllBJet"].push_back(tempjet.Phi()) ;
			_floatVecVars["M_Mass_AllBJet"].push_back(tempjet.M()) ;

		}
			//cout<<"tempDealtaR="<<tempDeltaR<<"vector size ="<<_floatVecVars["M_DeltaRBJetLepton"].size()<<"first Delta R = "<<_floatVecVars["M_DeltaRBJetLepton"][0]<<endl;
		for (auto jet : evtObj->jets){
			tempjet.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
			Jet.push_back(tempjet);
			_floatVecVars["M_E_AllJet"].push_back(tempjet.E());
			_floatVecVars["M_Pt_AllJet"].push_back(tempjet.Pt());
			_floatVecVars["M_Eta_AllJet"].push_back(tempjet.Eta()) ;
			_floatVecVars["M_Phi_AllJet"].push_back(tempjet.Phi()) ;
			_floatVecVars["M_Mass_AllJet"].push_back(tempjet.M()) ;



		}
		Bjetnumber=BJet.size();
		jetnumber=Jet.size();
		if (jetnumber>0)LeadJet = Jet.at(0);
	 //	if (Bjetnumber>0)_floatVars["M_DeltaRBJetLepton"]=BJet.at(0).DeltaR(Lepton);
		_floatVars["M_Mass_Jet"]          = (LeadJet).M();
		_floatVars["M_E_Jet"]          = (LeadJet).E();
		_floatVars["M_Pt_Jet"]         = (LeadJet).Pt();
		_floatVars["M_Eta_Jet"]        = (LeadJet).Eta();
		_floatVars["M_Phi_Jet"]        = (LeadJet).Phi();
		_floatVars["M_DeltaRBLeadJetLepton"] =(LeadJet).DeltaR(Lepton);	
		_intVars["M_nBJet"] = Bjetnumber;
	//	cout<<"number of bJet is :"<<Bjetnumber<<endl; 
		_intVars["M_nJet"] = jetnumber; 


		//Get bstar
		TLorentzVector bstar(0,0,0,0);
		TLorentzVector bstarleadjet(0,0,0,0);
		 TLorentzVector BoostedJet(0,0,0,0);
		// TLorentzVector Top_p4(0,0,0,0);
	//	cout<<"BoostedJet size is:" <<evtObj->boostedjetsToUsePtr->size()<<endl;
		for(int i=0;i<evtObj->boostedjetsToUsePtr->size();i++){
		BoostedJet.SetPtEtaPhiM(evtObj->boostedjetsToUsePtr->at(i).Pt(),evtObj->boostedjetsToUsePtr->at(i).Eta(),evtObj->boostedjetsToUsePtr->at(i).Phi(),evtObj->boostedjetsToUsePtr->at(i).M());
			//  BoostedJet.Setprunedmass(evtObj->boostedjetsToUsePtr->at(i).prunedmass());
			bstar = Top_p4+BoostedJet;
			bstarleadjet = Topleadjet_p4+BoostedJet;

			_floatVars["M_Mass_BoostedJet"]          = (BoostedJet).M();
			_floatVars["M_prunedmass_BoostedJet"]          = evtObj->boostedjetsToUsePtr->at(i).prunedmass();
			_floatVars["M_softdropmass_BoostedJet"]          = evtObj->boostedjetsToUsePtr->at(i).softdropmass();
			_floatVars["M_softdropmasscorr_BoostedJet"]          = evtObj->boostedjetsToUsePtr->at(i).softdropmasscorr();
			//cout<<"M_prunedmass_BoostedJet = "<<evtObj->boostedjetsToUsePtr->at(i).prunedmass()<<" ;M_softdropmass_BoostedJet = "<<evtObj->boostedjetsToUsePtr->at(i).softdropmass()<<endl;
			_floatVars["M_tau21_BoostedJet"]          = evtObj->boostedjetsToUsePtr->at(i).tau2()/evtObj->boostedjetsToUsePtr->at(i).tau1();
			_floatVars["M_tau32_BoostedJet"]          = evtObj->boostedjetsToUsePtr->at(i).tau3()/evtObj->boostedjetsToUsePtr->at(i).tau2();
			_floatVars["M_E_BoostedJet"]          = (BoostedJet).E();
			_floatVars["M_Pt_BoostedJet"]         = (BoostedJet).Pt();
			_floatVars["M_Eta_BoostedJet"]        = (BoostedJet).Eta();
			_floatVars["M_Phi_BoostedJet"]        = (BoostedJet).Phi();

			_floatVars["M_Mass_bstar"]       = (bstar).M();
			_floatVars["M_E_bstar"]          = (bstar).E();
			_floatVars["M_Pt_bstar"]         = (bstar).Pt();
			_floatVars["M_Eta_bstar"]        = (bstar).Eta();
			_floatVars["M_Phi_bstar"]        = (bstar).Phi();

			_floatVars["M_Mass_bstarleadjet"]       = (bstarleadjet).M();
			_floatVars["M_E_bstarleadjet"]          = (bstarleadjet).E();
			_floatVars["M_Pt_bstarleadjet"]         = (bstarleadjet).Pt();
			_floatVars["M_Eta_bstarleadjet"]        = (bstarleadjet).Eta();
			_floatVars["M_Phi_bstarleadjet"]        = (bstarleadjet).Phi();


		}



		int Boostedjetnumber=0;
		TLorentzVector tempboostedjet(0,0,0,0);
		for (auto boostedjet : evtObj->boostedjets){

			tempboostedjet.SetPtEtaPhiE(boostedjet.Pt(),boostedjet.Eta(),boostedjet.Phi(),boostedjet.E());
			BoostedJets.push_back(tempboostedjet);
			_floatVecVars["M_E_AllBoostedJet"].push_back(tempboostedjet.E());       
		_floatVecVars["M_Pt_AllBoostedJet"].push_back(tempboostedjet.Pt());
		_floatVecVars["M_Eta_AllBoostedJet"].push_back(tempboostedjet.Eta()) ;
		_floatVecVars["M_Phi_AllBoostedJet"].push_back(tempboostedjet.Phi()) ;
		_floatVecVars["M_Mass_AllBoostedJet"].push_back(tempboostedjet.M()) ;

	}

		Boostedjetnumber=BoostedJets.size();
	_intVars["M_nBoostedJet"] = Boostedjetnumber;


		for (auto const & mctop : *evtObj->mcTopsPtr){
	if(mctop.TopIsDecay(mctop,*evtObj->mcParticlesPtr)&&mctop.PdgId()==6 )	 _floatVecVars["M_Pt_MCTop"].push_back(mctop.Pt());
}

}
}
