void anaCorr(){
    //gROOT->Macro("~/rootlogon.C");
    gStyle->SetPalette(kDeepSea);
    //gStyle->SetPalette("palette.txt");
    gStyle->SetNumberContours(99);
    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v14.root","READ");

    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->cd();

    TH2F *TimeCorr11 = (TH2F*)in1->Get("TimeCorr11");
    TH2F *TimeCorr12 = (TH2F*)in1->Get("TimeCorr12");

    //TimeCorr11->Rebin(2);

    c1->cd();
    c1->SetTheta(86.25352);
    c1->SetPhi(1.616693);
    TimeCorr11->GetXaxis()->SetTitle("time 1 (ns)");
    TimeCorr11->GetYaxis()->SetTitle("time 2 (ns)");
    TimeCorr11->Draw("surf1");
    //TimeCorr11->Draw("surflz");

    c1->SaveAs("plot_time_surf1_correlation1.png");

    TimeCorr12->GetXaxis()->SetTitle("time 3 (ns)");
    TimeCorr12->GetYaxis()->SetTitle("time 4 (ns)");
    TimeCorr12->Draw("surf1");
    //TimeCorr12->Draw("surflz");

    c1->SaveAs("plot_time_surf1_correlation2.png");

    TH2F *hChCorr1 = (TH2F*)in1->Get("hChCorr11");
    TH2F *hChCorr2 = (TH2F*)in1->Get("hChCorr12");

    c1->cd();
    //hChCorr1->Draw("colz");
    hChCorr1->Draw("surf1");

    c1->SaveAs("plot_channel_surf1_correlation.png");


    /*
    c1->cd();

    TimeCorr11->Draw("colz");
    c1->SaveAs("plot_time_colz_correlation1.png");
    
    TimeCorr12->Draw("colz");
    c1->SaveAs("plot_time_colz_correlation21.png");
    */
}
