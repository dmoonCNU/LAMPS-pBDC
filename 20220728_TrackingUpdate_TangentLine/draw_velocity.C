void draw_velocity(){
    gROOT->Macro("~/rootlogon.C");
    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_20220601.root","READ");

    TH1F *DriftVel11 = (TH1F*)in1->Get("DriftVel11");
    TH1F *DriftVel21 = (TH1F*)in1->Get("DriftVel21");

    TCanvas *c3 = new TCanvas("c3","",880, 800);
    c3->cd();
    DriftVel11->SetMarkerColor(kRed+1);
    DriftVel21->SetMarkerColor(kBlue+1);
    DriftVel11->SetMarkerStyle(20);
    DriftVel21->SetMarkerStyle(25);

    auto lg4 = new TLegend(0.44,0.63,0.71,0.75);
    lg4->SetBorderSize(0);
    lg4->SetMargin(0.2);
    lg4->SetTextSize(0.029);
    lg4->AddEntry(DriftVel11,Form("Drift Velocity 1 : %0.2f #pm %0.2f (#mum/ns)", DriftVel11->GetMean(), DriftVel11->GetMeanError()),"lp");
    lg4->AddEntry(DriftVel21,Form("Drift Velocity 2 : %0.2f #pm %0.2f (#mum/ns)", DriftVel21->GetMean(), DriftVel21->GetMeanError()),"lp");



    DriftVel11->Draw("E");
    DriftVel21->Draw("E same");
    lg4->Draw("same");
    c3->SaveAs("plot_drift_velocity_10deg.png");

}
