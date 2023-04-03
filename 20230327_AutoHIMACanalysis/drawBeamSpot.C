void drawBeamSpot(){
  gROOT->Macro("~/rootlogon.C");
  gStyle->SetPadRightMargin(0.1);
  TFile *fin = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v16.root","READ");

  TH1F *h1 = (TH1F*)fin->Get("hBeamSpot1");
  TH1F *h2 = (TH1F*)fin->Get("hBeamSpot2");
  TH1F *h3 = (TH1F*)fin->Get("hBeamSpot3");
  TH1F *h4 = (TH1F*)fin->Get("hBeamSpot4");

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();

  TCanvas *c1 = new TCanvas("c1","",880,800);
  c1->Divide(2,2);
  c1->cd(1);
  h1->Draw("colz");
  lt1->DrawLatex(0.2,0.87,"Beam Spot in 1st layer");
  c1->cd(2);
  h2->Draw("colz");
  lt1->DrawLatex(0.2,0.87,"Beam Spot in 4th layer");
  c1->cd(3);
  h3->Draw("colz");
  lt1->DrawLatex(0.2,0.87,"Beam Spot in middle layer");
  c1->cd(4);
  h4->Draw("colz");
  lt1->DrawLatex(0.2,0.87,"Beam Spot in Target");

  c1->SaveAs("plot_beamspots.png");
}
