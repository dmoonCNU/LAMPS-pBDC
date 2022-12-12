void anaTime(){
    gROOT->Macro("~/rootlogon.C");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v15.root","READ");
    TH1F *hTime1 = (TH1F*)in1->Get("TimeDist11");
    TH1F *hTime2 = (TH1F*)in1->Get("TimeDist21");
    TH1F *hTime3 = (TH1F*)in1->Get("TimeDist31");
    TH1F *hTime4 = (TH1F*)in1->Get("TimeDist41");

    hTime1->Rebin(4);
    hTime2->Rebin(4);
    hTime3->Rebin(4);
    hTime4->Rebin(4);

    //hTime1->GetXaxis()->SetRangeUser(0,100);
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

    //auto lg1 = new TLegend(0.23,0.35,0.53,0.55);
    auto lg1 = new TLegend(0.61,0.48,0.91,0.68);
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

    
    TFile *in2 = new TFile("convert_data_CNU_Cosmic_EXP.root","READ");

    //gStyle->SetOptStat(0);
    TH1F *hTimeInt01 = (TH1F*)in2->Get("TimeInt01");
    TH1F *hTimeInt02 = (TH1F*)in2->Get("TimeInt11");
    TH1F *hTimeInt03 = (TH1F*)in2->Get("TimeInt21");
    TH1F *hTimeInt04 = (TH1F*)in2->Get("TimeInt31");

    hTimeInt01->Draw();
    hTimeInt02->Draw("same");
    hTimeInt03->Draw("same");
    hTimeInt04->Draw("same");

    hTimeInt01->SetLineColor(kBlue);
    hTimeInt02->SetLineColor(kRed);
    hTimeInt03->SetLineColor(kViolet);
    hTimeInt04->SetLineColor(kMagenta);

    auto lg2 = new TLegend(0.61,0.48,0.91,0.68);
    lg2->SetBorderSize(0);
    lg2->SetMargin(0.2);
    lg2->AddEntry(hTimeInt01,"X1","l");
    lg2->AddEntry(hTimeInt02,"X1'","l");
    lg2->AddEntry(hTimeInt03,"X2","l");
    lg2->AddEntry(hTimeInt04,"X2'","l");

    lg2->Draw("same");
    
    c1->SaveAs("plot_time_distance_distributions.png");

    

}
