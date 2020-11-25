#define TopAnalysis_cxx
// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.

#include "TopAnalysis.h"
#include "Tophistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void TopAnalysis::Begin(TTree * )
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
}

void TopAnalysis::SlaveBegin(TTree * )
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());

  name=option;

  define_histograms();

  FillOutputList();
}

Bool_t TopAnalysis::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fChain->GetTree()->GetEntry(entry);
  //  int cut1_mc = 0;

  if(fChain->GetTree()->GetEntries()>0)
  {
    //Do analysis

    //SF
    Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_TRIGGER;
    //EventW
    Float_t eventWeight = mcWeight*scaleFactor_PILEUP*scaleFactor_ZVERTEX;
    //weight = SF * EventW
    Double_t weight = scaleFactor*eventWeight;

    // Make difference between data and MC
    if (weight == 0. && channelNumber != 110090 && channelNumber != 110091) weight = 1.;

    // Missing Et of the event in GeV
    Float_t missingEt = met_et/1000.;


    // Preselection cut for electron/muon trigger, Good Run List, and good vertex
    if(trigE || trigM)
    {
      if(passGRL)
      {
        if(hasGoodVertex)
        {
          //Find the good leptons
          int goodlep_index = 0;
          int goodlep_n = 0;
	  int lep_index = 0;

          for(int i=0; i<lep_n; i++)
          {
            if(lep_pt[i]>25000. && (lep_ptcone30[i]/lep_pt[i]) < 0.15 && (lep_etcone20[i]/lep_pt[i]) < 0.15 )
	      {
		// electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
		if ( lep_type[i]==11 && TMath::Abs(lep_eta[i]) < 2.47 && ( TMath::Abs(lep_eta[i]) < 1.37 || TMath::Abs(lep_eta[i]) > 1.52 ) ) {
		  goodlep_n++;
		  goodlep_index = i;
		  lep_index++;
		}
		if ( lep_type[i] == 13 && TMath::Abs(lep_eta[i]) < 2.5 ) {
		  goodlep_n++;
		  goodlep_index = i;
		  lep_index++;
		}
	      }
	  }



          //Zero cut
          if(goodlep_n==1)
          {
            for(int i=0; i<lep_n; i++)
            {
              if(lep_pt[i]>25000. && (lep_ptcone30[i]/lep_pt[i]) < 0.15 && (lep_etcone20[i]/lep_pt[i]) < 0.15 )
              {
                goodlep_index = i;
              }
            }

            // TLorentzVector definitions
            TLorentzVector Lepton_1  = TLorentzVector();
            TLorentzVector      MeT  = TLorentzVector();
            TLorentzVector   Lepton1_MeT = TLorentzVector();



            Lepton_1.SetPtEtaPhiE(lep_pt[goodlep_index], lep_eta[goodlep_index], lep_phi[goodlep_index],lep_E[goodlep_index]);
            MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);


            //Calculation of the Invariant Mass using TLorentz vectors (First Lepton + MeT)
            Lepton1_MeT = Lepton_1 + MeT;
            float InvMass1       = Lepton1_MeT.Mag();
            float InvMass1_inGeV = InvMass1/1000.;
            float Lepton1_MeT_MT = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));


            //First cut : Exactly one good leptons with pT>25GeV
            if(goodlep_n ==1 && lep_pt[goodlep_index] >25000. && (lep_ptcone30[goodlep_index]/lep_pt[goodlep_index]) < 0.15 && (lep_etcone20[goodlep_index]/lep_pt[goodlep_index]) < 0.15)
            {
	      //Preselection of good jets
	      int goodjet_n = 0;
	      int goodbjet_n = 0;

	      int goodjet_index[jet_n];
	      int jet_index = 0;

	      int goodbjet_index[jet_n];
	      int bjet_index = 0;

	      if(jet_n > 3.)
              {
                std::vector<Float_t*> jet_variable={jet_pt,jet_eta,jet_phi,jet_E,jet_m,jet_jvf,jet_SV0,jet_MV1};
                int pass_jet = 0;
                for(int i = 0;i < jet_n;i++)
                {
		  if(jet_pt[i] > 25000. && TMath::Abs(jet_eta[i]) < 2.5)
		    {
		      // JVF cleaning
		      bool jvf_pass=true;
		      if (jet_pt[i] < 50000. && TMath::Abs(jet_eta[i]) < 2.4 && jet_jvf[i] < 0.5) jvf_pass=false;
		      if (jvf_pass)
			{
			  goodjet_n++;
			  goodjet_index[jet_index] = i;
			  jet_index++;

			  // cut on 0.7982 is 70% WP
			  if (jet_MV1[i] >0.7982 )
			    {
			      goodbjet_n++;
			      goodbjet_index[bjet_index] = i;
			      bjet_index++;
			    }
			}
		    }
		}


		if(goodjet_n >= 4)
		  {
		    //At least two b-tagged jets
		    if(goodbjet_n >= 2)
		      {

			if(Lepton1_MeT_MT > 30000.)
			      {
                    double max_pt = 0;
                    double max_m = 0;
                    int j1 = 0;
                    int j2 = 0;
                    int j3 = 0;
                    int j4 = 0;

                    double sum_pt = 0;

                for(unsigned int i = 0; i < goodjet_n; i++)
                {
                    for(unsigned int j = i+1; j < goodjet_n; j++)
                    {
                        for(unsigned int k = j+1; k < goodjet_n; k++)
                        {
                            for(unsigned int l = k+1; l < goodjet_n ; l++){

                            TLorentzVector jet1 = TLorentzVector();
                            jet1.SetPtEtaPhiE(jet_pt[goodjet_index[i]], jet_eta[goodjet_index[i]], jet_phi[goodjet_index[i]], jet_E[goodjet_index[i]]);

                            TLorentzVector jet2 = TLorentzVector();
                            jet2.SetPtEtaPhiE(jet_pt[goodjet_index[j]], jet_eta[goodjet_index[j]], jet_phi[goodjet_index[j]], jet_E[goodjet_index[j]]);

                            TLorentzVector jet3 = TLorentzVector();
                            jet3.SetPtEtaPhiE(jet_pt[goodjet_index[k]], jet_eta[goodjet_index[k]], jet_phi[goodjet_index[k]], jet_E[goodjet_index[k]]);

                            TLorentzVector jet4 = TLorentzVector();
                            jet4.SetPtEtaPhiE(jet_pt[goodjet_index[l]], jet_eta[goodjet_index[l]], jet_phi[goodjet_index[l]], jet_E[goodjet_index[l]]);


                            if ( (jet1.Pt() + jet2.Pt() + jet3.Pt() ) /1000 > sum_pt ){
                                sum_pt = (jet1.Pt() + jet2.Pt() + jet3.Pt() ) /1000;
                                max_m = (jet1.M() + jet2.M() + jet3.M() )/1000;

                                j1 = i, j2 = j, j3 = k, j4=l;

                                double jet12_pt = (jet1.Pt() + jet2.Pt() )/1000;
                                double jet23_pt = (jet2.Pt() + jet3.Pt() )/1000;
                                double jet13_pt = (jet1.Pt() + jet3.Pt() )/1000;

                                if (jet12_pt > jet13_pt && jet12_pt > jet23_pt){j1=i; j2=j; j3=k;}
                                if (jet23_pt > jet12_pt && jet23_pt > jet13_pt ){j1=i; j2=k; j3=j;}
                                if (jet13_pt > jet12_pt && jet13_pt > jet23_pt){j1=k; j2=k; j3=i;}
                            }
                            }

                        }
                    }
                }

                TLorentzVector jet_1 = TLorentzVector();
                jet_1.SetPtEtaPhiE(jet_pt[goodjet_index[j1]], jet_eta[goodjet_index[j1]], jet_phi[goodjet_index[j1]], jet_E[goodjet_index[j1]]);

                TLorentzVector jet_2 = TLorentzVector();
                jet_2.SetPtEtaPhiE(jet_pt[goodjet_index[j2]], jet_eta[goodjet_index[j2]], jet_phi[goodjet_index[j2]], jet_E[goodjet_index[j2]]);

                TLorentzVector jet_3 = TLorentzVector();
                jet_3.SetPtEtaPhiE(jet_pt[goodjet_index[j3]], jet_eta[goodjet_index[j3]], jet_phi[goodjet_index[j3]], jet_E[goodjet_index[j3]]);

                TLorentzVector jet_4 = TLorentzVector();
                jet_4.SetPtEtaPhiE(jet_pt[goodjet_index[j4]], jet_eta[goodjet_index[j4]], jet_phi[goodjet_index[j4]], jet_E[goodjet_index[j4]]);

                double mass2_max = (jet_1 + jet_2 ).M()/1000;        

                double Zmass = (jet_1 + jet_2 + jet_3 + jet_4 + Lepton_1 + MeT).M()/1000;


                hist_three_jets -> Fill(sum_pt,weight);
                hist_two_jets -> Fill(mass2_max,weight);
                hist_Zprime_mass -> Fill(Zmass,weight);

				double names_of_global_variable[]={InvMass1_inGeV, missingEt, vxp_z, (double)pvxp_n, Lepton1_MeT_MT/1000.};
				double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep_index], (double)lep_type[goodlep_index], lep_ptcone30[goodlep_index], lep_etcone20[goodlep_index], lep_z0[goodlep_index], lep_trackd0pvunbiased[goodlep_index]};
				double names_of_jet_variable[]={(double)jet_n, jet_pt[0]/1000., jet_eta[0], jet_m[0]/1000., jet_jvf[0], jet_MV1[0]};

				TString histonames_of_global_variable[]={"hist_vismass","hist_etmiss","hist_vxp_z","hist_pvxp_n", "hist_mt"};
				TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
				TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_leadjet_m", "hist_leadjet_jvf", "hist_leadjet_MV1"};

				int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
				int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
				int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);

				for (int i=0; i<length_global; i++)
				  {
				    FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				  }
				for (int i=0; i<length_leadlep; i++)
				  {
				    FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
				  }
				for (int i=0; i<length_leadjet; i++)
				  {
				    FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
				  }
			      }
			  }
		      }
		  }
	      }
	    }
	  }
	}
      }
    }

  //  std::cout<<cut1_mc<<std::endl;
  return kTRUE;
}

void TopAnalysis::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}

void TopAnalysis::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  name="output_Top/"+name+".root";

  const char* filename = name.c_str();

  TFile physicsoutput_Top(filename,"recreate");
  WriteHistograms();
  physicsoutput_Top.Close();


}
