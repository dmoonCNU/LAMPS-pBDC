void anaCorr(double nsigma){
    //gROOT->Macro("~/rootlogon.C");
    //###gStyle->SetPalette(kLake);
    gStyle->SetPalette(kRainBow);
 
	//gStyle->SetPalette(kDeepSea);
    //gStyle->SetPalette("palette.txt");
    gStyle->SetNumberContours(99);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(1);
    //gStyle->SetTitleXOffset(1.0);
    //gStyle->SetTitleYOffset(0.85);
    //gStyle->SetOptTitle(0);
    TFile *in1 = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v16.root","READ");

    TH2F *TimeCorr11 = (TH2F*)in1->Get("TimeCorr11");
    TH2F *TimeCorr21 = (TH2F*)in1->Get("TimeCorr21");
    TH2F *TimeCorr31 = (TH2F*)in1->Get("TimeCorr31");

	TFile* fout = new TFile("anaCorr_result.root","RECREATE");

	TH1D* hcorr = new TH1D("hcorr","",3,0,3);

	TCanvas *c0 = new TCanvas("c0","",2400, 800);
    c0->cd();
	c0->Divide(3);
	c0->cd(1);
	TimeCorr11->Draw("colz");
	c0->cd(2);
	TimeCorr21->Draw("colz");
	c0->cd(3);
	TimeCorr31->Draw("colz");
	c0->cd();
	c0->SaveAs("plot_time_correlation_all.png");



    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->cd();



    //TimeCorr11->Rebin(2);
/*
	TF1 *f1 = new TF1("f1","56-x",-20,110);
    TF1 *f2 = new TF1("f2","78-x",-20,110);
    TF1 *f3 = new TF1("f3","102-x",-20,110);
    TF1 *f4 = new TF1("f4","40-x",0,110);
*/
/*	
	TF1 *f1 = new TF1("f1","88-x",-20,110);
    TF1 *f2 = new TF1("f2","96-x",-20,110);
    TF1 *f3 = new TF1("f3","102-x",-20,110);
    TF1 *f4 = new TF1("f4","40-x",0,110);

	f1->SetLineColor(kRed);
    f2->SetLineColor(kYellow);
    f3->SetLineColor(kRed);
    f4->SetLineColor(kRed);
    f1->SetLineWidth(5);
    f2->SetLineWidth(5);
    f3->SetLineWidth(5);
    f4->SetLineWidth(5);
    c1->cd();
    c1->SetTheta(86.25352);
    c1->SetPhi(1.616693);
    TimeCorr11->GetXaxis()->SetTitle("time 1 (ns)");
    TimeCorr11->GetYaxis()->SetTitle("time 2 (ns)");
    TimeCorr11->GetXaxis()->SetRangeUser(0,120);//80
    TimeCorr11->GetYaxis()->SetRangeUser(0,120);//80
    TimeCorr11->Draw("colz");
    //TimeCorr11->Draw("surf1");
    //TimeCorr11->Draw("surflz");

    f1->Draw("same");
    f2->Draw("same");
    f3->Draw("same");
    //f4->Draw("same");

    c1->SaveAs("plot_time_surf1_correlation1.png");
*/
/*
	TF1 *f1 = new TF1("f1","[0]-x",-20,110);
    TF1 *f2 = new TF1("f2","[0]-x",-20,110);
    TF1 *f3 = new TF1("f3","[0]-x",-20,110);
    TF1 *f4 = new TF1("f4","[0]-x",0,110);
*/
	TF1 *f1 = new TF1("f1","[0]-x",-20,330);
    TF1 *f2 = new TF1("f2","[0]-x",-20,330);
    TF1 *f3 = new TF1("f3","[0]-x",-20,330);
    TF1 *f4 = new TF1("f4","[0]-x",0,330);

	f1->SetLineColor(kRed);
    f2->SetLineColor(kYellow);
    f3->SetLineColor(kRed);
    f4->SetLineColor(kRed);
    f1->SetLineWidth(5);
    f2->SetLineWidth(5);
    f3->SetLineWidth(5);
    f4->SetLineWidth(5);
   
	TF1 *f11 = new TF1("f11","[0]-x",-20,330);
    TF1 *f21 = new TF1("f21","[0]-x",-20,330);
    TF1 *f31 = new TF1("f31","[0]-x",-20,330);
    TF1 *f41 = new TF1("f41","[0]-x",0,330);

	f11->SetLineColor(kRed);
    f21->SetLineColor(kYellow);
    f31->SetLineColor(kRed);
    f41->SetLineColor(kRed);
    f11->SetLineWidth(5);
    f21->SetLineWidth(5);
    f31->SetLineWidth(5);
    f41->SetLineWidth(5);
   
	TF1 *f12 = new TF1("f12","[0]-x",-20,330);
    TF1 *f22 = new TF1("f22","[0]-x",-20,330);
    TF1 *f32 = new TF1("f32","[0]-x",-20,330);
    TF1 *f42 = new TF1("f42","[0]-x",0,330);

	f12->SetLineColor(kRed);
    f22->SetLineColor(kYellow);
    f32->SetLineColor(kRed);
    f42->SetLineColor(kRed);
    f12->SetLineWidth(5);
    f22->SetLineWidth(5);
    f32->SetLineWidth(5);
    f42->SetLineWidth(5);
   
	TF1 *f13 = new TF1("f13","[0]-x",-20,330);
    TF1 *f23 = new TF1("f23","[0]-x",-20,330);
    TF1 *f33 = new TF1("f33","[0]-x",-20,330);
    TF1 *f43 = new TF1("f43","[0]-x",0,330);

	f13->SetLineColor(kRed);
    f23->SetLineColor(kYellow);
    f33->SetLineColor(kRed);
    f43->SetLineColor(kRed);
    f13->SetLineWidth(5);
    f23->SetLineWidth(5);
    f33->SetLineWidth(5);
    f43->SetLineWidth(5);
   

	c1->cd();
    c1->SetTheta(86.25352);
    c1->SetPhi(1.616693);

	TH2F *TimeCorrR11 = (TH2F*)in1->Get("TimeCorrR11");
    TH2F *TimeCorrR12 = (TH2F*)in1->Get("TimeCorrR21");
    TH2F *TimeCorrR32 = (TH2F*)in1->Get("TimeCorrR31");

    TH1D *hProjX11;
    TH1D *hProjX12;
    TH1D *hProjX32;

    //TimeCorrR11->ProjectionX();
    //TimeCorrR21->ProjectionX();
    //TimeCorrR31->ProjectionX();

    TCanvas *c3 = new TCanvas("c3","",1000,500);
    c3->Divide(2,1);
    c3->cd(1);
    TimeCorrR11->Draw("colz");
    hProjX11 = TimeCorrR11->ProjectionX("hProjX11",0,1000,"");

    //hProjX11->Rebin(4);
    hProjX11->SetMarkerStyle(20);

    c3->cd(2);
    TF1 *gs1 = new TF1("gs1","gaus",30,100);
    hProjX11->Fit(gs1,"rm");
    hProjX11->Draw("");
	std::cout << "Mean : " << gs1->GetParameter(1) << std::endl;
	std::cout << "After rotating mean : " << (gs1->GetParameter(1))*sqrt(2) << std::endl;
	std::cout << "Sigma : " << gs1->GetParameter(2) << std::endl;
	std::cout << "After rotating sigma : " << (gs1->GetParameter(2))*sqrt(2) << std::endl;
	std::cout << "Suggested x : " << (gs1->GetParameter(1))*sqrt(2)-(gs1->GetParameter(2))*sqrt(2)*nsigma << " ~ " << (gs1->GetParameter(1))*sqrt(2)+(gs1->GetParameter(2))*sqrt(2)*nsigma << std::endl;

    c3->SaveAs("plot_time_corr11_rotate_X.png");
	hcorr->SetBinContent(1,gs1->GetParameter(1)*sqrt(2)*nsigma);
	hcorr->SetBinError(1,gs1->GetParameter(2)*sqrt(2)*nsigma);


	//c1->cd();
	c0->cd(1);
    TimeCorr11->GetXaxis()->SetTitle("time 1 (ns)");
    TimeCorr11->GetYaxis()->SetTitle("time 2 (ns)");
    TimeCorr11->GetXaxis()->SetRangeUser(0,100);//80
    TimeCorr11->GetYaxis()->SetRangeUser(0,100);//80
    TimeCorr11->Draw("colz");
    //TimeCorr11->Draw("surf1");
    //TimeCorr11->Draw("surflz");

	f11->SetParameter(0,(gs1->GetParameter(1))*sqrt(2)-nsigma*(gs1->GetParameter(2))*sqrt(2));
	f21->SetParameter(0,(gs1->GetParameter(1))*sqrt(2));
	f31->SetParameter(0,(gs1->GetParameter(1))*sqrt(2)+nsigma*(gs1->GetParameter(2))*sqrt(2));
	std::cout << f11->GetParameter(0) << std::endl;
	std::cout << f21->GetParameter(0) << std::endl;
	std::cout << f31->GetParameter(0) << std::endl;



    f11->Draw("same");
    f21->Draw("same");
    f31->Draw("same");
    //f4->Draw("same");
    //c1->SaveAs("plot_time_surf1_correlation1.png");

	c3->cd();
    c3->cd(1);
    TimeCorrR12->Draw("colz");
    hProjX12 = TimeCorrR12->ProjectionX("hProjX12",0,1000,"");

    //hProjX11->Rebin(4);
    hProjX12->SetMarkerStyle(20);
	
    c3->cd(2);
    TF1 *gs12 = new TF1("gs12","gaus",30,100);
    hProjX12->Fit(gs12,"rm");
    hProjX12->Draw("");
	std::cout << "Mean : " << gs12->GetParameter(1) << std::endl;
	std::cout << "After rotating mean : " << (gs12->GetParameter(1))*sqrt(2) << std::endl;
	std::cout << "Sigma : " << gs12->GetParameter(2) << std::endl;
	std::cout << "After rotating sigma : " << (gs12->GetParameter(2))*sqrt(2) << std::endl;
	std::cout << "Suggested x : " << (gs12->GetParameter(1))*sqrt(2)-(gs12->GetParameter(2))*sqrt(2)*nsigma << " ~ " << (gs12->GetParameter(1))*sqrt(2)+(gs12->GetParameter(2))*sqrt(2)*nsigma << std::endl;

    c3->SaveAs("plot_time_corr12_rotate_X.png");
	hcorr->SetBinContent(2,gs12->GetParameter(1)*sqrt(2)*nsigma);
	hcorr->SetBinError(2,gs12->GetParameter(2)*sqrt(2)*nsigma);


	//c1->cd();
	c0->cd(2);
	TimeCorr21->GetXaxis()->SetTitle("time 3 (ns)");
    TimeCorr21->GetYaxis()->SetTitle("time 4 (ns)");
     TimeCorr21->GetXaxis()->SetRangeUser(0,100);//80
    TimeCorr21->GetYaxis()->SetRangeUser(0,100);//80
   TimeCorr21->Draw("colz");
    //TimeCorr12->Draw("surf1");
    //TimeCorr12->Draw("surflz");
	f12->SetParameter(0,(gs12->GetParameter(1))*sqrt(2)-(gs12->GetParameter(2))*sqrt(2)*nsigma);
	f22->SetParameter(0,(gs12->GetParameter(1))*sqrt(2));
	f32->SetParameter(0,(gs12->GetParameter(1))*sqrt(2)+(gs12->GetParameter(2))*sqrt(2)*nsigma);


    f12->Draw("same");
    f22->Draw("same");
    f32->Draw("same");
    //f4->Draw("same");
    //c1->SaveAs("plot_time_surf1_correlation2.png");

	c3->cd();
    c3->cd(1);
    TimeCorrR32->Draw("colz");
    hProjX32 = TimeCorrR32->ProjectionX("hProjX32",0,1000,"");

    //hProjX11->Rebin(4);
    hProjX32->SetMarkerStyle(20);

    c3->cd(2);
    TF1 *gs32 = new TF1("gs32","gaus",30,100);
    hProjX32->Fit(gs32,"rm");
    hProjX32->Draw("");
	std::cout << "Mean : " << gs32->GetParameter(1) << std::endl;
	std::cout << "After rotating mean : " << (gs32->GetParameter(1))*sqrt(2) << std::endl;
	std::cout << "Sigma : " << gs32->GetParameter(2) << std::endl;
	std::cout << "After rotating sigma : " << (gs32->GetParameter(2))*sqrt(2) << std::endl;
	std::cout << "Suggested x : " << (gs32->GetParameter(1))*sqrt(2)-(gs32->GetParameter(2))*sqrt(2)*nsigma << " ~ " << (gs32->GetParameter(1))*sqrt(2)+(gs32->GetParameter(2))*sqrt(2)*nsigma << std::endl;

    c3->SaveAs("plot_time_corr32_rotate_X.png");
	hcorr->SetBinContent(3,gs32->GetParameter(1)*sqrt(2)*nsigma);
	hcorr->SetBinError(3,gs32->GetParameter(2)*sqrt(2)*nsigma);


	//c1->cd();
	c0->cd(3);
    TimeCorr31->GetXaxis()->SetTitle("time 2 (ns)");
    TimeCorr31->GetYaxis()->SetTitle("time 3 (ns)");
      TimeCorr31->GetXaxis()->SetRangeUser(0,100);//80
    TimeCorr31->GetYaxis()->SetRangeUser(0,100);//80
    TimeCorr31->Draw("colz");
    //TimeCorr12->Draw("surf1");
    //TimeCorr12->Draw("surflz");
	f13->SetParameter(0,(gs32->GetParameter(1))*sqrt(2)-nsigma*(gs32->GetParameter(2))*sqrt(2));
	f23->SetParameter(0,(gs32->GetParameter(1))*sqrt(2));
	f33->SetParameter(0,(gs32->GetParameter(1))*sqrt(2)+nsigma*(gs32->GetParameter(2))*sqrt(2));


    f13->Draw("same");
    f23->Draw("same");
    f33->Draw("same");
    //f4->Draw("same");
    //c1->SaveAs("plot_time_surf1_correlation3.png");

	c0->cd();
	c0->SaveAs("plot_time_correlation_allwithcut.png");


    TH1D *x1;
    TH1D *x2;
    TH1D *x3;
    TH1D *x4;
    TH1D *x5;

    x1 = TimeCorr21->ProjectionX("x1",0,5,"");
    x2 = TimeCorr21->ProjectionX("x2",5,10,"");
    x3 = TimeCorr21->ProjectionX("x3",10,15,"");
    x4 = TimeCorr21->ProjectionX("x4",15,20,"");
    x5 = TimeCorr21->ProjectionX("x5",20,25,"");

    int bmax1 = x1->GetMaximumBin();
    int bmax2 = x2->GetMaximumBin();
    int bmax3 = x3->GetMaximumBin();
    int bmax4 = x4->GetMaximumBin();
    int bmax5 = x5->GetMaximumBin();

    double max1 = x1->GetBinContent(bmax1);
    double max2 = x2->GetBinContent(bmax2);
    double max3 = x3->GetBinContent(bmax3);
    double max4 = x4->GetBinContent(bmax4);
    double max5 = x5->GetBinContent(bmax5);

    double xval1 = x1->GetXaxis()->GetBinCenter(bmax1);
    double xval2 = x2->GetXaxis()->GetBinCenter(bmax2);
    double xval3 = x3->GetXaxis()->GetBinCenter(bmax3);
    double xval4 = x4->GetXaxis()->GetBinCenter(bmax4);
    double xval5 = x5->GetXaxis()->GetBinCenter(bmax5);

    cout<<"bmax1 : "<<bmax1<<", max1 : "<<max1<<", xval1 : "<<xval1<<endl;
    cout<<"bmax2 : "<<bmax2<<", max2 : "<<max2<<", xval2 : "<<xval2<<endl;
    cout<<"bmax3 : "<<bmax3<<", max3 : "<<max3<<", xval3 : "<<xval3<<endl;
    cout<<"bmax4 : "<<bmax4<<", max4 : "<<max4<<", xval4 : "<<xval4<<endl;
    cout<<"bmax5 : "<<bmax5<<", max5 : "<<max5<<", xval5 : "<<xval5<<endl;

    double xx[5] = {0.0};
    xx[0] = xval1;
    xx[1] = xval2;
    xx[2] = xval3;
    xx[3] = xval4;
    xx[4] = xval5;


    double yy[5] = {0.0};
    yy[0] = xval1;
    yy[1] = xval2;
    yy[2] = xval3;
    yy[3] = xval4;
    yy[4] = xval5;

    double yerr[5] = {0.0};
    yerr[0] = sqrt(yy[0]);
    yerr[1] = sqrt(yy[1]);
    yerr[2] = sqrt(yy[2]);
    yerr[3] = sqrt(yy[3]);
    yerr[4] = sqrt(yy[4]);

    double xerr[5] = {0.0}; 

    TCanvas *c2 = new TCanvas("c2","",500,500);
    c2->cd();
    TGraphErrors *g1 = new TGraphErrors(5, xx, yy, xerr, yerr);
    g1->Draw();



/*
    TFile *in3 = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v11.root","READ");
    TH2F *hDistVsTimeX_0 = (TH2F*)in3->Get("hDistVsTimeX_0");
    TH2F *hDistVsTimeX_1 = (TH2F*)in3->Get("hDistVsTimeX_1");
    TH2F *hDistVsTimeX_2 = (TH2F*)in3->Get("hDistVsTimeX_2");
    TH2F *hDistVsTimeX_3 = (TH2F*)in3->Get("hDistVsTimeX_3");

    TCanvas *c4 = new TCanvas("c4","",1000,1000);
    c4->Divide(2,2);
    c4->cd(1);
    hDistVsTimeX_0->GetXaxis()->SetTitleOffset(1.0);
    hDistVsTimeX_0->GetYaxis()->SetTitleOffset(0.85);
    hDistVsTimeX_0->GetXaxis()->SetRangeUser(0,100);
    hDistVsTimeX_0->GetYaxis()->SetRangeUser(-2,2);
    hDistVsTimeX_0->Draw("colz");
    c4->cd(2);
    hDistVsTimeX_1->GetXaxis()->SetTitleOffset(1.0);
    hDistVsTimeX_1->GetYaxis()->SetTitleOffset(0.85);
    hDistVsTimeX_1->GetXaxis()->SetRangeUser(0,100);
    hDistVsTimeX_1->GetYaxis()->SetRangeUser(-2,2);
    hDistVsTimeX_1->Draw("colz");
    c4->cd(3);
    hDistVsTimeX_2->GetXaxis()->SetTitleOffset(1.0);
    hDistVsTimeX_2->GetYaxis()->SetTitleOffset(0.85);
    hDistVsTimeX_2->GetXaxis()->SetRangeUser(0,100);
    hDistVsTimeX_2->GetYaxis()->SetRangeUser(-2,2);
    hDistVsTimeX_2->Draw("colz");
    c4->cd(4);
    hDistVsTimeX_3->GetXaxis()->SetTitleOffset(1.0);
    hDistVsTimeX_3->GetYaxis()->SetTitleOffset(0.85);
    hDistVsTimeX_3->GetXaxis()->SetRangeUser(0,100);
    hDistVsTimeX_3->GetYaxis()->SetRangeUser(-2,2);
    hDistVsTimeX_3->Draw("colz");
*/    



    //TH1F *TimeSum1 = (TH1F*)in1->Get("TimeSum11");

    //TF1 *gs2 = new TF1("gs2","gaus",40,100);
    //TimeSum1->Fit(gs2,"rm");

    /*
    TH2F *hChCorr1 = (TH2F*)in1->Get("hChCorr11");
    TH2F *hChCorr2 = (TH2F*)in1->Get("hChCorr12");

    c1->cd();
    //hChCorr1->Draw("colz");
    hChCorr1->Draw("surf1");

    c1->SaveAs("plot_channel_surf1_correlation.png");


    c1->cd();

    TimeCorr11->Draw("colz");
    c1->SaveAs("plot_time_colz_correlation1.png");
    
    TimeCorr12->Draw("colz");
    c1->SaveAs("plot_time_colz_correlation21.png");
    */

	fout->cd();
	hcorr->Write();
	fout->Close();

}
