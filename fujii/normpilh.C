#include <iostream>
#include <TFile.h>
#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TFrame.h>
using namespace std;
// convert into steradians 
const double avogadro=6.02214e23;
// Pb:
//const double rho=11.35;
//const double A = 207.217;
// C
const double rho=0.0708;
const double A = 2;
const double nevts = 1000000000;
const double thickness=5;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(cos(tmin*degtorad)-cos(tmax*degtorad));
  return sr;
}

void normpilh()
{

  TFile *_file1 = TFile::Open("lH2.root");
  TH1D* hist1 = (TH1D*)_file1->Get("diff2");
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  /*
  TFile *_file2 = TFile::Open("G4DiffuseElastic_pi-_800MeV_G4C.root");
  TH1D* hist2 = (TH1D*)_file2->Get("diff2");
  for (int i=1;i<hist2->GetNbinsX()+1;i++)
    {
      hist2->SetBinContent(i, ((1e27*convert)/nevts)*(hist2->GetBinContent(i)/sterad(hist2->GetXaxis()->GetBinLowEdge(i),hist2->GetXaxis()->GetBinUpEdge(i))));
    }
  */
  TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();

  const int count=21; 
  double angle[count]=
    {
      25.5012,
      26.5386,
      27.532,
      28.4821,
      29.5192,
      30.5125,
      31.5059,
      32.499,
      33.4921,
      34.5278,
      35.5208,
      36.5128,
      37.5062,
      38.5416,
      39.5782,
      40.4859,
      41.5259,
      42.5213,
      43.5167,
      44.5142,
      45.5526,
    };
  
  double cs[count]=
    {5.7483,
     5.089,
     3.9897,
     3.1827,
     2.6747,
     2.0788,
     1.6583,
     1.2667,
     0.95916,
     0.66589,
     0.49555,
     0.32375,
     0.25603,
     0.1702,
     0.13343,
     0.1202,
     0.15061,
     0.15862,
     0.16562,
     0.23433,
     0.23631
    };
 TGraph *graph = new TGraph(count,angle,cs);
 graph->SetMarkerColor(2);
 graph->SetLineColor(2);
 graph->SetMarkerStyle(22);
 graph->SetMarkerSize(2);
 graph->SetLineWidth (2);
 /*
  
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(31,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.70484.v1/t1");
   grae->SetFillStyle(1000);
 */  
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.70484.v1/t1",100,3.198,27.582);
   Graph_Graph1D_y13001->SetMinimum(0.01);
   Graph_Graph1D_y13001->SetMaximum(10000);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   /*
   Graph_Graph1D_y13001->SetLineColor(7);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("#theta");
   //   Graph_Graph1D_y13001->GetXaxis()->SetTitle("THETA(P=3,RF=CM) [DEG]");
     Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   //Graph_Graph1D_y13001->GetYaxis()->SetTitle("D(SIG)/D(OMEGA(P=3,RF=CM)) [MB/SR]");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   grae->SetMarkerColor(2);
   grae->SetLineColor(2);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(1.5);
   grae->SetLineWidth (2);
   grae->SetMinimum(0.01);
   grae->SetMaximum(10000);
*/

    hist1->SetTitle("1100 MeV/c pi- on H" ); 
  hist1->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist1->GetXaxis()->SetTitle("#theta");
  hist1->SetMarkerColor(4);
  hist1->SetLineColor(4);
  hist1->SetMarkerStyle(20);
  hist1->SetMarkerSize(1);
  hist1->SetLineWidth (2);
  hist1->SetMinimum(0.01);
  hist1->SetMaximum(10000);
  hist1 ->SetStats(0);
  /*
  hist2->SetMarkerColor(3);
  hist2->SetLineColor(3);
  hist2->SetMarkerStyle(21);
  hist2->SetMarkerSize(1);
  hist2->SetLineWidth (2);
  */
  hist1->Draw("HIST");
  // hist2->Draw("SAMEHIST");
  graph->Draw("SAME");
   TLegend *legend = new TLegend(0.5,0.5,0.86,0.88);
   legend->AddEntry(hist1,"Geant4_11_0 G4Elastic");
    legend->AddEntry(graph,"Phys Rev. C 64 034608");
    //   legend->AddEntry(grae,"Phys.Rev.C 30 (1984) 1662, 1984." );
   legend->Draw();

}
