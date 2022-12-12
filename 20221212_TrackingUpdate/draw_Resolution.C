void draw_Resolution(){
    gROOT->Macro("~/rootlogon.C");
    gStyle->SetOptStat(1);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v10.root","READ");
    TFile *in2 = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v10.root","READ");

    TH1F *hAllX1 = (TH1F*)in2->Get("hDisX_0");
    TH1F *hAllX2 = (TH1F*)in2->Get("hDisX_1");
    TH1F *hAllX3 = (TH1F*)in2->Get("hDisX_2");
    TH1F *hAllX4 = (TH1F*)in2->Get("hDisX_3");
    hAllX1->Add(hAllX2);
    hAllX1->Add(hAllX3);
    hAllX1->Add(hAllX4);

    TCanvas *b1 = new TCanvas("b1","",880, 800);
    b1->cd();
    hAllX1->Rebin(4);
    hAllX1->SetMarkerSize(1.2);
    hAllX1->Draw();
 
    TF1 *gausa = new TF1("gausa","gaus",-0.2,0.2);
    gausa->SetLineColor(kRed+1);
    gausa->SetLineStyle(2);

    hAllX1->Fit(gausa,"rm");

    double sgmAll = gausa->GetParameter(2);

    hAllX1->Draw("E");

    b1->SaveAs("plot_drift_inclusive_X.png");

    TH1F *hDisX_0 = (TH1F*)in1->Get("hDisX_0");
    TH1F *hDisX_1 = (TH1F*)in1->Get("hDisX_1");
    TH1F *hDisX_2 = (TH1F*)in1->Get("hDisX_2");
    TH1F *hDisX_3 = (TH1F*)in1->Get("hDisX_3");
    TH1F *hResDisX = (TH1F*)in1->Get("hDisX2_2");


    hDisX_0->Rebin(4);
    hDisX_1->Rebin(4);
    hDisX_2->Rebin(4);
    hResDisX->Rebin(8);
    hDisX_3->Rebin(4);

    TH1F *hDisY_0 = (TH1F*)in1->Get("hDisY_0");
    TH1F *hDisY_1 = (TH1F*)in1->Get("hDisY_1");
    TH1F *hDisY_2 = (TH1F*)in1->Get("hDisY_2");
    TH1F *hDisY_3 = (TH1F*)in1->Get("hDisY_3");
    TH1F *hResDisY = (TH1F*)in1->Get("hDisY2_2");

    hDisY_0->Rebin(4);
    hDisY_1->Rebin(4);
    hDisY_2->Rebin(4);
    hResDisY->Rebin(8);
    hDisY_3->Rebin(4);

   
    double sgm[4] = {0.0};
 
    TF1 *gaus = new TF1("gaus","gaus",-0.15,0.15);
    gaus->SetLineColor(kRed+1);
    gaus->SetLineStyle(2);


    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->Divide(2,2);
    c1->cd(1);
    hDisY_0->Fit(gaus,"rm");
    sgm[0] = gaus->GetParameter(2);
    hDisY_0->Draw("E");
    c1->cd(2);
    hDisY_1->Fit(gaus,"rm");
    sgm[1] = gaus->GetParameter(2);
    hDisY_1->Draw("E");
    c1->cd(3);
    hDisY_2->Fit(gaus,"rm");
    sgm[2] = gaus->GetParameter(2);
    hDisY_2->Draw("E");
    c1->cd(4);
    hDisY_3->Fit(gaus,"rm");
    sgm[3] = gaus->GetParameter(2);
    hDisY_3->Draw("E");

    c1->SaveAs("plot_drift_difference_full_track_Y.png");

 
    TF1 *gaus1 = new TF1("gaus1","gaus",-0.35,0.35);
    gaus1->SetLineColor(kRed+1);
    gaus1->SetLineStyle(2);


    c1->cd();
    hResDisY->SetTitle("");
    hResDisY->SetMarkerSize(1.8);
    hResDisY->Fit(gaus1,"rm");
    hResDisY->Draw("E");

    c1->SaveAs("plot_drift_difference_resolution_Y.png");

    TCanvas *c2 = new TCanvas("c2","",880, 800);
    c2->Divide(2,2);
    c2->cd(1);
    hDisX_0->Fit(gaus,"rm");
    sgm[0] = gaus->GetParameter(2);
    hDisX_0->Draw("E");
    c2->cd(2);
    hDisX_1->Fit(gaus,"rm");
    sgm[1] = gaus->GetParameter(2);
    hDisX_1->Draw("E");
    c2->cd(3);
    hDisX_2->Fit(gaus,"rm");
    sgm[2] = gaus->GetParameter(2);
    hDisX_2->Draw("E");
    c2->cd(4);
    hDisX_3->Fit(gaus,"rm");
    sgm[3] = gaus->GetParameter(2);
    hDisX_3->Draw("E");

    c2->SaveAs("plot_drift_difference_full_track_X.png");

 
    TF1 *gaus2 = new TF1("gaus2","gaus",-0.35,0.35);
    gaus2->SetLineColor(kRed+1);
    gaus2->SetLineStyle(2);


    c2->cd();
    hResDisX->SetTitle("");
    hResDisX->SetMarkerSize(1.8);
    hResDisX->Fit(gaus2,"rm");
    hResDisX->Draw("E");

    c2->SaveAs("plot_drift_difference_resolution_X.png");



    /*
    TCanvas *c2 = new TCanvas("c2","",1200, 800);
    c2->Divide(3,2);
    c2->cd(1);
    hDisY_0->Fit(gaus,"rm");
    sgm[0] = gaus->GetParameter(2);
    hDisY_0->Draw("E");
    c2->cd(2);
    hDisY_1->Fit(gaus,"rm");
    sgm[1] = gaus->GetParameter(2);
    hDisY_1->Draw("E");
    c2->cd(4);
    hDisY_2->Fit(gaus,"rm");
    sgm[2] = gaus->GetParameter(2);
    hDisY_2->Draw("E");
    c2->cd(5);
    hDisY_3->Fit(gaus,"rm");
    sgm[3] = gaus->GetParameter(2);
    hDisY_3->Draw("E");

    c2->cd(3);
    hResDis->SetTitle("");
    hResDis->SetMarkerSize(1.2);
    hResDis->Fit(gaus1,"rm");
    hResDis->Draw("E");

    c2->SaveAs("plot_drift_difference_resolution_together.png");

    */

    //cout<<"Sigma 1 : "<<sgm[0]<<", Sigma 2 : "<<sgm[1]<<endl;
    //cout<<"Sigma with 3 points : "<<gaus1->GetParameter(2)<<endl;
    cout<<"Inclusive Resolution : "<<sgmAll<<endl;
    cout<<"Exclusive Resolution : "<<gaus2->GetParameter(2)<<endl;
    cout<<"Resolution : "<<sqrt(sgmAll*gaus2->GetParameter(2))<<endl;
    //cout<<"Resolution : "<<sqrt(((sgm[0]+sgm[1])/2.0)*gaus1->GetParameter(2))<<endl;
    //cout<<"Resolution : "<<sqrt(gaus->GetParameter(2)*gaus1->GetParameter(2))<<endl;

}
