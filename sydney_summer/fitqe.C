   // linear background function
   Double_t background(Double_t *x, Double_t *par) {
      return par[0] + par[1]*x[0]+ par[2]*x[0]*x[0];
   }

   // Lorentzian Peak function
   Double_t lorentzianPeak(Double_t *x, Double_t *par) {
      return (0.5*par[0]*par[1]/TMath::Pi()) / TMath::Max(1.e-10,
      (x[0]-par[2])*(x[0]-par[2])+ .25*par[1]*par[1]);
   }

   // Sum of background and peak function
   Double_t fitFunction(Double_t *x, Double_t *par) {
      return background(x,par) + lorentzianPeak(x,&par[3]);
   }
void fitqe()
{
  TFile *_file0 = TFile::Open("qehist.root");
  TH1F *histo = (TH1F*) _file0->Get("pionEnergy");
  TF1 *fitFcn = new TF1("fitFcn",fitFunction,900,2000,6);
  //TF1 *fitFcn = new TF1("fitFcn",lorentzianPeak,900,1200,3);
  //fitFcn->SetParameters(4.5e+4,60,1000.);
  //TF1 *fitFcn = new TF1("fitFcn",background,1500,2000,3);
  fitFcn->SetParameters(1.09518e+02,-1.05302e-01,2.57492e-05,4.52028e+04,6.01075e+01,1.05411e+03);
  fitFcn->SetParNames("p0","p1","p2","norm","#Gamma","x_0");
  //histo->Draw();
  gStyle->SetOptFit(1011);
  histo->GetXaxis()->SetTitle("reconstructed m_{#pi} [MeV]");
  histo->GetYaxis()->SetTitle("N_{Events} [Evts/4MeV]");
  histo->Fit("fitFcn","R");

}
