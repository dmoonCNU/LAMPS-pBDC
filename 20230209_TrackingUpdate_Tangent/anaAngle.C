void anaAngle(){
    gROOT->Macro("~/rootlogon.C");
    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v11.root","READ");
    TH1F *hAngX = (TH1F*)in1->Get("hAngX");

    hAngX->Rebin(4);

    hAngX->GetXaxis()->SetRangeUser(-45,45);
    hAngX->GetYaxis()->SetTitle("Counts");
    hAngX->GetXaxis()->SetTitle("angle #theta (Degrees)");

    hAngX->SetLineColor(kBlue+1);

    hAngX->SetMarkerColor(kBlue+1);

    hAngX->SetMarkerStyle(20);

    /*
    auto lg1 = new TLegend(0.43,0.35,0.73,0.55);
    lg1->SetBorderSize(0);
    lg1->SetMargin(0.2);
    lg1->AddEntry(hTime1,"X1","lp");
    lg1->AddEntry(hTime2,"X1'","lp");
    lg1->AddEntry(hTime3,"X2","lp");
    lg1->AddEntry(hTime4,"X2'","lp");
    */


    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->cd();
    hAngX->Draw("HIST E");

    //lg1->Draw("same");

    c1->SaveAs("plot_angle_distributions.png");

}
