void anaTimeZero(){
    gROOT->Macro("~/rootlogon.C");
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetMarkerSize(1.3);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("tTimeTree_BDC_Run_Cosmic_CNU_1430_Org_v15.root","READ");
    TH1F *hTime1 = (TH1F*)in1->Get("TimeDist11");
    TH1F *hTime2 = (TH1F*)in1->Get("TimeDist21");
    TH1F *hTime3 = (TH1F*)in1->Get("TimeDist31");
    TH1F *hTime4 = (TH1F*)in1->Get("TimeDist41");

    hTime1->Rebin(2);
    hTime2->Rebin(2);
    hTime3->Rebin(2);
    hTime4->Rebin(2);

    //hTime1->GetXaxis()->SetRangeUser(0,100);
    //hTime1->GetXaxis()->SetRangeUser(150,350);

    hTime1->SetLineColor(kBlue+1);
    hTime2->SetLineColor(kBlue+1);
    hTime3->SetLineColor(kBlue+1);
    hTime4->SetLineColor(kBlue+1);
    //hTime1->SetLineColor(kBlue+1);
    //hTime2->SetLineColor(kRed+1);
    //hTime3->SetLineColor(kViolet+1);
    //hTime4->SetLineColor(kOrange+5);

    hTime1->SetMarkerColor(kBlue+1);
    hTime2->SetMarkerColor(kBlue+1);
    hTime3->SetMarkerColor(kBlue+1);
    hTime4->SetMarkerColor(kBlue+1);
    //hTime2->SetMarkerColor(kRed+1);
    //hTime3->SetMarkerColor(kViolet+1);
    //hTime4->SetMarkerColor(kOrange+5);

    hTime1->SetMarkerStyle(20);
    hTime2->SetMarkerStyle(20);
    hTime3->SetMarkerStyle(20);
    hTime4->SetMarkerStyle(20);
    //hTime2->SetMarkerStyle(24);
    //hTime3->SetMarkerStyle(25);
    //hTime4->SetMarkerStyle(32);

    auto lg1 = new TLegend(0.23,0.35,0.53,0.55);
    //auto lg1 = new TLegend(0.43,0.35,0.73,0.55);
    lg1->SetBorderSize(0);
    lg1->SetMargin(0.2);
    lg1->AddEntry(hTime1,"X1","lp");
    lg1->AddEntry(hTime2,"X1'","lp");
    lg1->AddEntry(hTime3,"X2","lp");
    lg1->AddEntry(hTime4,"X2'","lp");


    TF1 *errf11 = new TF1("errf11","[0]*TMath::Erf((x-[1])/[2])+[3]",150,220);
    TF1 *errf12 = new TF1("errf12","[0]*TMath::Erf((x-[1])/[2])+[3]",255,310);
    errf11->SetParameters(500,270,10,10);
    errf12->SetParameters(-500,270,10,10);


    TF1 *errf21 = new TF1("errf21","[0]*TMath::Erf((x-[1])/[2])+[3]",150,220);
    TF1 *errf22 = new TF1("errf22","[0]*TMath::Erf((x-[1])/[2])+[3]",254,310);
    errf21->SetParameters(500,270,10,10);
    errf22->SetParameters(-500,270,10,10);


    TF1 *errf31 = new TF1("errf31","[0]*TMath::Erf((x-[1])/[2])+[3]",150,200);
    TF1 *errf32 = new TF1("errf32","[0]*TMath::Erf((x-[1])/[2])+[3]",240,330);
    errf31->SetParameters(500,270,10,10);
    errf32->SetParameters(-500,270,10,10);


    TF1 *errf41 = new TF1("errf41","[0]*TMath::Erf((x-[1])/[2])+[3]",150,220);
    TF1 *errf42 = new TF1("errf42","[0]*TMath::Erf((x-[1])/[2])+[3]",250,310);
    errf41->SetParameters(500,270,10,10);
    errf42->SetParameters(-500,270,10,10);


    errf11->SetLineColor(kRed);
    errf11->SetLineWidth(2);
    errf12->SetLineColor(kRed);
    errf12->SetLineWidth(2);

    errf21->SetLineColor(kRed);
    errf21->SetLineWidth(2);
    errf22->SetLineColor(kRed);
    errf22->SetLineWidth(2);

    errf31->SetLineColor(kRed);
    errf31->SetLineWidth(2);
    errf32->SetLineColor(kRed);
    errf32->SetLineWidth(2);

    errf41->SetLineColor(kRed);
    errf41->SetLineWidth(2);
    errf42->SetLineColor(kRed);
    errf42->SetLineWidth(2);



    TCanvas *c1 = new TCanvas("c1","",1000, 800);
    c1->Divide(2,2);
    c1->cd(1);
    hTime1->Fit(errf11,"rm");
    hTime1->Fit(errf12,"rm");
    hTime1->Draw("HIST E");
    errf11->Draw("same");
    errf12->Draw("same");

    TLatex *lt1 = new TLatex();
    lt1->SetNDC();

    lt1->SetTextSize(0.055);
    lt1->DrawLatex(0.25,0.8,"1^{st} layer");
    lt1->DrawLatex(0.25,0.6,Form("T_{0} : %0.1f (ns)",errf11->GetParameter(1)));
    lt1->DrawLatex(0.25,0.53,Form("T_{1} : %0.1f (ns)",errf12->GetParameter(1)));
    lt1->DrawLatex(0.25,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(errf12->GetParameter(1)-errf11->GetParameter(1))));

    c1->cd(2);
    hTime2->Fit(errf21,"rm");
    hTime2->Fit(errf22,"rm");
    hTime2->Draw("HIST E");
    errf21->Draw("same");
    errf22->Draw("same");

    lt1->DrawLatex(0.25,0.8,"2^{nd} layer");
    lt1->DrawLatex(0.25,0.6,Form("T_{0} : %0.1f (ns)",errf21->GetParameter(1)));
    lt1->DrawLatex(0.25,0.53,Form("T_{1} : %0.1f (ns)",errf22->GetParameter(1)));
    lt1->DrawLatex(0.25,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(errf22->GetParameter(1)-errf21->GetParameter(1))));

    c1->cd(3);
    hTime3->Fit(errf31,"rm");
    hTime3->Fit(errf32,"rm");
    hTime3->Draw("HIST E");
    errf31->Draw("same");
    errf32->Draw("same");


    lt1->DrawLatex(0.25,0.8,"3^{rd} layer");
    lt1->DrawLatex(0.25,0.6,Form("T_{0} : %0.1f (ns)",errf31->GetParameter(1)));
    lt1->DrawLatex(0.25,0.53,Form("T_{1} : %0.1f (ns)",errf32->GetParameter(1)));
    lt1->DrawLatex(0.25,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(errf32->GetParameter(1)-errf31->GetParameter(1))));

    c1->cd(4);
    hTime4->Fit(errf41,"rm");
    hTime4->Fit(errf42,"rm");
    hTime4->Draw("HIST E");
    errf41->Draw("same");
    errf42->Draw("same");

    lt1->DrawLatex(0.25,0.8,"4^{th} layer");
    lt1->DrawLatex(0.25,0.6,Form("T_{0} : %0.1f (ns)",errf41->GetParameter(1)));
    lt1->DrawLatex(0.25,0.53,Form("T_{1} : %0.1f (ns)",errf42->GetParameter(1)));
    lt1->DrawLatex(0.25,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(errf42->GetParameter(1)-errf41->GetParameter(1))));

    //hTime2->Draw("HIST E same");
    //hTime3->Draw("HIST E same");
    //hTime4->Draw("HIST E same");

    //lg1->Draw("same");

    c1->SaveAs("plot_time_distributions.png");

   

}
