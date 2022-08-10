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
const double rho= 2;
const double A = 12.011;
const double nevts = 10000000;
const double thickness=1;
const double convert=A/(avogadro*rho*thickness);
double sterad(double tmin,double tmax)
{
  const double degtorad=M_PI/180.;
  double sr= 2.*M_PI*(tmin - tmax);
  return cos(sr);
}

void normpi()
{

  TFile *_file1 = TFile::Open("G4_C_7-5-22.root");
  TH1D* hist1 = (TH1D*)_file1->Get("diff3");
  for (int i=1;i<hist1->GetNbinsX()+1;i++)
    {
      hist1->SetBinContent(i, ((1e27*convert)/nevts)*(hist1->GetBinContent(i)/sterad(hist1->GetXaxis()->GetBinLowEdge(i),hist1->GetXaxis()->GetBinUpEdge(i))));
    }
  /*TFile *_file2 = TFile::Open("HEPData-ins15083-v1-Table_8.root");
  TFile *_file2 = TFile::Open("Table 8");
  TH1D* hist2 = (TH1D*)_file2->Get("Graph1D_y1");
  for (int i=1;i<hist2->GetNbinsX()+1;i++)
    {
      hist2->SetBinContent(i, ((1e27*convert)/nevts)*(hist2->GetBinContent(i)/sterad(hist2->GetXaxis()->GetBinLowEdge(i),hist2->GetXaxis()->GetBinUpEdge(i))));
    }*/
TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();

   /*Double_t Graph1D_y1_fx3001[31] = {
   4.81,
   5.89,
   6.96,
   8.03,
   9.1,
   10.2,
   11.2,
   12.3,
   13.4,
   14.4,
   15.5,
   16.6,
   17.6,
   18.7,
   19.8,
   20.8,
   21.9,
   23,
   24,
   25.1,
   26.2,
   27.2,
   28.3,
   29.4,
   30.4,
   31.5,
   32.5,
   33.6,
   34.7,
   35.7,
   36.8};
   Double_t Graph1D_y1_fy3001[31] = {
   579,
   560,
   481,
   424,
   378,
   299,
   208,
   166,
   133,
   95.9,
   67.9,
   42,
   26.3,
   15.4,
   8.17,
   4.41,
   2.05,
   0.919,
   0.397,
   0.397,
   0.439,
   0.564,
   0.69,
   0.711,
   0.711,
   0.648,
   0.502,
   0.403,
   0.299,
   0.244,
   0.171};
   Double_t Graph1D_y1_felx3001[31] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fely3001[31] = {
   105.9022,
   92.0313,
   76.39131,
   66.26402,
   58.65058,
   46.1087,
   31.82378,
   25.28403,
   20.19404,
   14.56771,
   10.32755,
   6.415146,
   4.028306,
   2.382924,
   1.281884,
   0.7152386,
   0.3528247,
   0.1795205,
   0.09925,
   0.0942858,
   0.09537936,
   0.104065,
   0.123239,
   0.1237154,
   0.1196775,
   0.1103299,
   0.08716249,
   0.07349451,
   0.06130875,
   0.06044146,
   0.05266804};
   Double_t Graph1D_y1_fehx3001[31] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fehy3001[31] = {
   105.9022,
   92.0313,
   76.39131,
   66.26402,
   58.65058,
   46.1087,
   31.82378,
   25.28403,
   20.19404,
   14.56771,
   10.32755,
   6.415146,
   4.028306,
   2.382924,
   1.281884,
   0.7152386,
   0.3528247,
   0.1795205,
   0.09925,
   0.0942858,
   0.09537936,
   0.104065,
   0.123239,
   0.1237154,
   0.1196775,
   0.1103299,
   0.08716249,
   0.07349451,
   0.06130875,
   0.06044146,
   0.05266804};*/


   /*TGraphAsymmErrors *grae = new TGraphAsymmErrors(31,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.70484.v1/t1");
   grae->SetFillStyle(1000);*/

   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.70484.v1/t1",100,3.198,27.582);
   Graph_Graph1D_y13001->SetMinimum(0.01);
   Graph_Graph1D_y13001->SetMaximum(100);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
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
   /*grae->SetHistogram(Graph_Graph1D_y13001);
   grae->SetMarkerColor(2);
   grae->SetLineColor(2);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(1.5);
   grae->SetLineWidth (2);
   grae->SetMinimum(0.001);
   grae->SetMaximum(100000);
*/

  hist1->SetTitle("800 MeV pi- on G4_C" );
  hist1->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  hist1->GetXaxis()->SetTitle("#theta");
  hist1->SetMarkerColor(4);
  hist1->SetLineColor(4);
  hist1->SetMarkerStyle(20);
  hist1->SetMarkerSize(1);
  hist1->SetLineWidth (2);
  hist1->SetMinimum(0.01);
  hist1->SetMaximum(1000);
  hist1 ->SetStats(0);
  /*hist2->SetMarkerColor(3);
  hist2->SetLineColor(3);
  hist2->SetMarkerStyle(21);
  hist2->SetMarkerSize(1);
  hist2->SetLineWidth (2);*/
  hist1->Draw("HIST");
  //hist2->Draw("SAMEHIST");
  //grae->Draw("SAME");
   TLegend *legend = new TLegend(0.5,0.7,0.86,0.88);
   legend->AddEntry(hist1,"Geant4_11_0 G4Elastic");
   //legend->AddEntry(hist2,"HEP data");
   //legend->AddEntry(grae,"Phys.Rev.C 30 (1984) 1662 Table 4" );
   legend->Draw();

}
