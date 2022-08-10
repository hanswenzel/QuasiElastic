{
gStyle->SetOptStat(0);
TFile f("qehist.root");
TH1D *partEnergy = (TH1D*) f.Get("partEnergy");
TH1D *partEnergy2 = (TH1D*) f.Get("partEnergy2");

//TH1D *pionEnergy = (TH1D*) f.Get("pionEnergy");
TH2D *pionEnergy2 = (TH2D*) f.Get("pionEnergy2");
TF1 *outPiMomentum = new TF1("outPiMomentum", "(1000*(((2794598.482)+139.570^(2)-938.28^(2))*cos(x)+2*1947.9729*sqrt(938.28^(2)-139.570^(2)*(sin(x))^(2)))/(2*((2794598.482)+(1000*sin(x))^(2))))", 0, 3.14159);
TF1 *outPiMomentum2 = new TF1("outPiMomentum2", "(1000*(((1.4624e9)+139.578^(2)-37211.3264^(2))*cos(x)+2*38254.553*sqrt(37211.3264^(2)-139.570^(2)*(sin(x))^(2)))/(2*((1.462e9)+(1000*sin(x))^(2))))", 0, 3.14159);
//TCanvas c1;
//partEnergy->Draw("HIST");
//partEnergy2->Draw("SAMEHIST");
//c1.SetLogy();

TCanvas c2;
//c2.SetLogy();
//TLegend *legend = new TLegend(0.5, 0.7, 0.86, 0.88);
/*legend->AddEntry(partEnergy, "proton");
legend->AddEntry(partEnergy2, "neutron");
TH1D *ratio = (TH1D*) partEnergy2->Clone("ratio");
ratio->Divide(partEnergy);
legend->AddEntry(ratio, "neutron/proton");

ratio->SetLineColor(2);
partEnergy->SetLineColor(3);
partEnergy2->SetLineColor(4);
ratio->GetXaxis()->SetTitle("Energy (MeV)");
ratio->GetYaxis()->SetTitle("average number");
ratio->SetTitle("Pi+ lAr 1GeV");
ratio->Draw("HIST");
partEnergy->Draw("SAMEHIST");
partEnergy2->Draw("SAMEHIST");
ratio->GetYaxis()->SetRangeUser(0.1,100000000);
*/

outPiMomentum->SetLineColor(2);
outPiMomentum2->SetLineColor(1);
pionEnergy2->GetXaxis()->SetTitle("angle (rad)");
pionEnergy2->GetYaxis()->SetTitle("momentum (MeV/c)");
//pionEnergy->SetLineColor(4);
//pionEnergy->Draw("HIST");
pionEnergy2->Draw("colz");
outPiMomentum->Draw("SAMEHIST");
outPiMomentum2->Draw("SAMEHIST");

TLegend *legend = new TLegend(0.5, 0.7, 0.86, 0.88);
legend->AddEntry(outPiMomentum, "calculated elastic outgoing pion momentum (proton mass)");
legend->AddEntry(outPiMomentum2, "calculated elastic outgoing pion momentum (argon mass)");
//legend->AddEntry(ratio, "neutrons/protons");
legend->Draw();
}
