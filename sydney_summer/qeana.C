#define qeana_cxx
#include "qeana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>
#include <cmath>
#include <TLegend.h>
#include <TLegendEntry.h>

using namespace std;

const double proton_mass = 938.272088;  //MeV/c^2
const double neutron_mass = 939.565420; //MeV/c^2
const double pion_mass = 139.570;       //MeV/c^2
const double argon_mass = 37244.860;    //MeV/c^2

void qeana::Loop()
{
//   In a ROOT session, you can do:
//      root> .L qeana.C+
//      root> qeana t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile f("qehist.root", "recreate");
   /*TH2D *pionAngle = new TH2D("pionAngle", "Outgoing pion momentum vs outgoing pion angle (most energetic final state pion)", 10000, 0, 1050, 1600, 0, 4);
   TH2D *pionAngle2 = new TH2D("pionAngle2", "Outgoing pion momentum vs outgoing pion angle (most energetic final state pion)", 10000, 0, 1050, 1600, 0, 4);*/
   TH1D *pionEnergy = new TH1D("pionEnergy", "Calculated incoming pion energy for Pi+ lAr 1GeV", 500, 0, 2000);
   //TH2D *pionEnergy2 = new TH2D("pionEnergy2", "Outgoing pion angle vs outgoing pion momentum", 400, 0, 3.14159, 275, 0, 1100);
   TH1D *partEnergy = new TH1D("partEnergy", "Pi+ lAr 1GeV", 50, 0, 100);
   TH1D *partEnergy2 = new TH1D("partEnergy2", "Pi+ lAr 1GeV", 50, 0, 100);
   //TH2D *pionAngle = new TH2D("pionAngle", "Calculated incoming energy for Pi+ lAr 1GeV elastic", 1100, 0, 1100, 1000, 0, 3.5);
   //TF1 *outPiMomentum = new TF1("outPiMomentum2", "(1000*(((1.4624e9)+37211.3264^(2)-938.28^(2))*cos(x)+2*38254.553*sqrt(938.28^(2)-37211.3264^(2)*(sin(x))^(2)))/(2*((1.462e9)+(1000*sin(x))^(2))))", 0, 3.14159);
   //outPiMomentum->Draw();
   TH1D *partNumber = new TH1D("partNumber", " ", 5, 0, 5);



   Long64_t nentries = fChain->GetEntries();
   //Long64_t nentries = fChain->GetEntriesFast();
   nentries = 12546723;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries; ++jentry) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry%100000==0) cout<<jentry<<"/"<<nentries<<endl;
      double max_pi_energy = -1;
      int index_max_pion = -1;
      int part_number = 0;
      double binding_energy = 4; //MeV
      double proton_energy = 0;
      double neutron_energy = 0;
      double pion_energy = 0;
      double pion_momentum = 0;
      double theta = 0;
      double in_pion_momentum = 1000; //MeV
     
      for (size_t i = 0; i<PDGcode->size(); ++i){
        if (i!=0 && (*PDGcode)[i] == 2212){          //proton
          //double pion_momentum = sqrt((*Px)[i]*(*Px)[i] + (*Py)[i]*(*Py)[i] + (*Pz)[i]*(*Pz)[i]);
          //++part_number;
          proton_energy = (*E)[i];
          if (pion_momentum > max_pi_energy){
            max_pi_energy = pion_momentum;
            index_max_pion = i;
          }
          partEnergy->TH1D::Fill((*E)[i] - 938.27231);
          //pionAngle->TH2D::Fill((sqrt((*Px)[i]*(*Px)[i] + (*Py)[i]*(*Py)[i] + (*Pz)[i]*(*Pz)[i])), acos((*Pz)[i] / (sqrt((*Px)[i]*(*Px)[i] + (*Py)[i]*(*Py)[i] + (*Pz)[i]*(*Pz)[i]))));
        }
        else if (i!=0 && (*PDGcode)[i] == 2112){    //neutron
          partEnergy2->TH1D::Fill((*E)[i] - 939.56563);
          neutron_energy = (*E)[i];
        }
        bool pi_bool = false;
        if (i!=0 && (*PDGcode)[i] == 211){
          pion_energy = (*E)[i];
          pion_momentum = sqrt(((*Px)[i])*((*Px)[i]) + ((*Py)[i])*((*Py)[i]) + ((*Pz)[i])*((*Pz)[i]));
          theta = (acos((*Pz)[i] / (sqrt((*Px)[i]*(*Px)[i] + (*Py)[i]*(*Py)[i] + (*Pz)[i]*(*Pz)[i]))));
          pi_bool = true;
          ++part_number;
        }
        if (pi_bool){
          //pionEnergy->TH1D::Fill(1009-pion_energy);
          double in_pion_energy = (neutron_mass*neutron_mass-((proton_mass-binding_energy)*(proton_mass-binding_energy))-pion_mass*pion_mass+(2*(proton_mass-binding_energy)*pion_energy))/(2*(proton_mass-binding_energy-pion_energy+(pion_momentum*cos(theta))));
          pionEnergy->TH1D::Fill(in_pion_energy);
          //pionEnergy2->TH2D::Fill(theta, pion_momentum);
        }
      }
      partNumber->TH1D::Fill(part_number);
      /*if (index_max_pion != -1){
        pionAngle2->TH2D::Fill((sqrt((*Px)[index_max_pion]*(*Px)[index_max_pion] + (*Py)[index_max_pion]*(*Py)[index_max_pion] + (*Pz)[index_max_pion]*(*Pz)[index_max_pion])), acos((*Pz)[index_max_pion] / (sqrt((*Px)[index_max_pion]*(*Px)[index_max_pion] + (*Py)[index_max_pion]*(*Py)[index_max_pion] + (*Pz)[index_max_pion]*(*Pz)[index_max_pion]))));
      }*/
   }
   //inPionEnergy->GetYaxis()->SetTitle("Calculated outgoing pion momentum (MeV/c)");
   //inPionEnergy->GetXaxis()->SetTitle("Angle (#theta)");
   //partNumber->GetXaxis()->SetTitle("Number of #pi+ in final state");
   f.Write();
   f.Close();
}
