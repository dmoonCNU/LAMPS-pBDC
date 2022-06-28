void anaTime(){
    gROOT->Macro("~/rootlogon.C");
    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v14.root","READ");
    TH1F *hTime1 = (TH1F*)in1->Get("TimeDist11");
    TH1F *hTime2 = (TH1F*)in1->Get("TimeDist21");
    TH1F *hTime3 = (TH1F*)in1->Get("TimeDist31");
    TH1F *hTime4 = (TH1F*)in1->Get("TimeDist41");

    hTime1->Rebin(4);
    hTime2->Rebin(4);
    hTime3->Rebin(4);
    hTime4->Rebin(4);

    hTime1->GetXaxis()->SetRangeUser(0,100);
    //hTime1->GetYaxis()->SetRangeUser(0,350);

    hTime1->SetLineColor(kBlue+1);
    hTime2->SetLineColor(kRed+1);
    hTime3->SetLineColor(kViolet+1);
    hTime4->SetLineColor(kOrange+5);

    hTime1->SetMarkerColor(kBlue+1);
    hTime2->SetMarkerColor(kRed+1);
    hTime3->SetMarkerColor(kViolet+1);
    hTime4->SetMarkerColor(kOrange+5);

    hTime1->SetMarkerStyle(20);
    hTime2->SetMarkerStyle(24);
    hTime3->SetMarkerStyle(25);
    hTime4->SetMarkerStyle(32);

    auto lg1 = new TLegend(0.43,0.35,0.73,0.55);
    lg1->SetBorderSize(0);
    lg1->SetMargin(0.2);
    lg1->AddEntry(hTime1,"X1","lp");
    lg1->AddEntry(hTime2,"X1'","lp");
    lg1->AddEntry(hTime3,"X2","lp");
    lg1->AddEntry(hTime4,"X2'","lp");


    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->cd();
    hTime1->Draw("HIST E");
    hTime2->Draw("HIST E same");
    hTime3->Draw("HIST E same");
    hTime4->Draw("HIST E same");

    lg1->Draw("same");

    c1->SaveAs("plot_time_distributions.png");

    

    TH1F *TimeMax11 = (TH1F*)in1->Get("TimeMax11");
    TH1F *TimeMax12 = (TH1F*)in1->Get("TimeMax12");

    auto lg2 = new TLegend(0.43,0.35,0.73,0.55);
    lg2->SetBorderSize(0);
    lg2->SetMargin(0.2);
    lg2->AddEntry(TimeMax11,"Time maximum 1","lp");
    lg2->AddEntry(TimeMax12,"Time maximum 2","lp");

    c1->cd();
    lg2->Draw("same");

    TimeMax11->GetXaxis()->SetRangeUser(0,150);
    TimeMax11->GetXaxis()->SetTitle("time (ns)");
    TimeMax11->SetMarkerStyle(20);
    TimeMax12->SetMarkerStyle(24);
    TimeMax11->SetMarkerColor(kBlue+1);
    TimeMax12->SetMarkerColor(kRed+1);

    TimeMax11->Draw("E");
    TimeMax12->Draw("E same");
    
    c1->SaveAs("plot_tmax_distributions.png");

    TH1F *hDrfVel1 = (TH1F*)in1->Get("DriftVel11");
    TH1F *hDrfVel2 = (TH1F*)in1->Get("DriftVel21");
    c1->cd();
    hDrfVel1->SetLineColor(kBlue+1);
    hDrfVel2->SetLineColor(kRed+1);
    hDrfVel1->SetMarkerColor(kBlue+1);
    hDrfVel2->SetMarkerColor(kRed+1);
    hDrfVel1->SetMarkerStyle(20);
    hDrfVel2->SetMarkerStyle(24);

    hDrfVel1->GetXaxis()->SetTitle("drift velocity (#mum/ns)");
    hDrfVel1->Draw("E");
    hDrfVel2->Draw("E same");


    auto lg4 = new TLegend(0.40,0.63,0.67,0.77);
    lg4->SetBorderSize(0);
    lg4->SetMargin(0.2);
    lg4->SetTextSize(0.029);
    lg4->AddEntry(hDrfVel1,Form("Drift Velocity 1 : %0.2f #pm %0.2f (#mum/ns)", hDrfVel1->GetMean(), hDrfVel1->GetMeanError()),"lp");
    lg4->AddEntry(hDrfVel2,Form("Drift Velocity 2 : %0.2f #pm %0.2f (#mum/ns)", hDrfVel2->GetMean(), hDrfVel2->GetMeanError()),"lp");

    lg4->Draw("same");

    c1->SaveAs("plot_drift_velocity.png");
    

}
