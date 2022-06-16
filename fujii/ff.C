#include <TAxis.h>
#include <cmath>
#include <TCanvas.h> 
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TFrame.h>
using namespace std;
void ff()
{
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
  graph->SetName("Graph1D_y1");
  graph->SetTitle("P#pi=1100MeV/c, Phys Rev. C 64 034608");
  graph->SetFillStyle(1000);
  graph->SetMarkerColor(4);
  graph->SetLineColor(4);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(2);
  graph->SetLineWidth (2);
  graph->SetMinimum(0.1);
  graph->SetMaximum(10);
  graph->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega} (#frac{mb}{ster})");
  graph->GetXaxis()->SetTitle("#Omega");
  TCanvas *c1 = new TCanvas("c1","elastic scattering",1000,800);
  c1->cd();
  c1->SetGrid();
  c1->SetLogy();
  graph->Draw();
}
