#include <TH1.h>

void findt0(int ch, TH1F* hTime, TH1D* ht0val, TH1D* ht1val);


void anaTimeZero(int t0opt=1){
	gROOT->Macro("~/rootlogon.C");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetMarkerSize(1.3);
	//gStyle->SetOptTitle(0);
	TFile *in1 = new TFile("tTimeTree_BDC_Run_Cosmic_CNU_1430_Org_v16.root","READ");
	TH1F *hTime1 = (TH1F*)in1->Get("TimeDist11");
	TH1F *hTime2 = (TH1F*)in1->Get("TimeDist21");
	TH1F *hTime3 = (TH1F*)in1->Get("TimeDist31");
	TH1F *hTime4 = (TH1F*)in1->Get("TimeDist41");
	/*
	   hTime1->Rebin(2);
	   hTime2->Rebin(2);
	   hTime3->Rebin(2);
	   hTime4->Rebin(2);
	 */
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

	TH1D* ht0val = new TH1D("ht0val","",4,0,4);
	TH1D* ht1val = new TH1D("ht1val","",4,0,4);

	TF1 *errf11 = new TF1("errf11","[0]*TMath::Erf((x-[1])/[2])+[3]",35,70);
	TF1 *errf12 = new TF1("errf12","[0]*TMath::Erf((x-[1])/[2])+[3]",100,140);
	errf11->SetParameters(20,50,10,10);
	errf12->SetParameters(-20,130,10,10);


	TF1 *errf21 = new TF1("errf21","[0]*TMath::Erf((x-[1])/[2])+[3]",35,68);
	TF1 *errf22 = new TF1("errf22","[0]*TMath::Erf((x-[1])/[2])+[3]",100,140);
	errf21->SetParameters(20,50,10,10);
	errf22->SetParameters(-20,130,10,10);


	TF1 *errf31 = new TF1("errf31","[0]*TMath::Erf((x-[1])/[2])+[3]",30,68);
	TF1 *errf32 = new TF1("errf32","[0]*TMath::Erf((x-[1])/[2])+[3]",95,140);
	errf31->SetParameters(20,50,10,10);
	errf32->SetParameters(-20,130,10,10);


	TF1 *errf41 = new TF1("errf41","[0]*TMath::Erf((x-[1])/[2])+[3]",30,68);
	TF1 *errf42 = new TF1("errf42","[0]*TMath::Erf((x-[1])/[2])+[3]",90,140);
	errf41->SetParameters(20,50,10,10);
	errf42->SetParameters(-20,130,10,10);

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
	double t0val=0.0;
	double t1val=0.0;

	c1->cd(1);
	hTime1->Draw("HIST E");
	if (t0opt==2) {
		hTime1->Fit(errf11,"rm");
		hTime1->Fit(errf12,"rm");
		errf11->Draw("same");
		errf12->Draw("same");
		ht0val->SetBinContent(1,errf11->GetParameter(1));
		ht1val->SetBinContent(1,errf12->GetParameter(1));
		t0val=errf11->GetParameter(1);
		t1val=errf12->GetParameter(1);
	}
	else if (t0opt==1) {
		findt0(1,hTime1,ht0val,ht1val);
		t0val=ht0val->GetBinContent(1);
		t1val=ht1val->GetBinContent(1);
	}
	TLine *lt0val1 = new TLine(t0val,0.0,t0val,hTime1->GetMaximum());
	TLine *lt1val1 = new TLine(t1val,0.0,t1val,hTime1->GetMaximum());
	lt0val1->SetLineColor(kTeal+3);
	lt1val1->SetLineColor(kTeal+3);
	lt0val1->SetLineWidth(1);
	lt1val1->SetLineWidth(1);
	lt0val1->SetLineStyle(9);
	lt1val1->SetLineStyle(9);
	lt0val1->Draw("same");
	lt1val1->Draw("same");

	TLatex *lt1 = new TLatex();
	lt1->SetNDC();
	lt1->SetTextSize(0.055);

	lt1->DrawLatex(0.60,0.8,"1^{st} layer");
	lt1->DrawLatex(0.60,0.6,Form("T_{0} : %0.1f (ns)",t0val));
	lt1->DrawLatex(0.60,0.53,Form("T_{1} : %0.1f (ns)",t1val));
	lt1->DrawLatex(0.60,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(t1val-t0val)));

	//////////////////////

	c1->cd(2);
	hTime2->Draw("HIST E");
	if (t0opt==2) {
		hTime2->Fit(errf21,"rm");
		hTime2->Fit(errf22,"rm");
		errf21->Draw("same");
		errf22->Draw("same");
		ht0val->SetBinContent(2,errf21->GetParameter(1));
		ht1val->SetBinContent(2,errf22->GetParameter(1));
		t0val=errf21->GetParameter(1);
		t1val=errf22->GetParameter(1);
	}
	else if (t0opt==1) {
		findt0(2,hTime2,ht0val,ht1val);
		t0val=ht0val->GetBinContent(2);
		t1val=ht1val->GetBinContent(2);
	}
	TLine *lt0val2 = new TLine(t0val,0.0,t0val,hTime2->GetMaximum());
	TLine *lt1val2 = new TLine(t1val,0.0,t1val,hTime2->GetMaximum());
	lt0val2->SetLineColor(kTeal+3);
	lt1val2->SetLineColor(kTeal+3);
	lt0val2->SetLineWidth(1);
	lt1val2->SetLineWidth(1);
	lt0val2->SetLineStyle(9);
	lt1val2->SetLineStyle(9);
	lt0val2->Draw("same");
	lt1val2->Draw("same");

	lt1->DrawLatex(0.60,0.8,"2^{nd} layer");
	lt1->DrawLatex(0.60,0.6,Form("T_{0} : %0.1f (ns)",t0val));
	lt1->DrawLatex(0.60,0.53,Form("T_{1} : %0.1f (ns)",t1val));
	lt1->DrawLatex(0.60,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(t1val-t0val)));

	///////
	c1->cd(3);
	hTime3->Draw("HIST E");
	if (t0opt==2) {
		hTime3->Fit(errf31,"rm");
		hTime3->Fit(errf32,"rm");
		errf31->Draw("same");
		errf32->Draw("same");
		ht0val->SetBinContent(3,errf31->GetParameter(1));
		ht1val->SetBinContent(3,errf32->GetParameter(1));
		t0val=errf31->GetParameter(1);
		t1val=errf32->GetParameter(1);
	}
	else if (t0opt==1) {
		findt0(3,hTime3,ht0val,ht1val);
		t0val=ht0val->GetBinContent(3);
		t1val=ht1val->GetBinContent(3);
	}
	TLine *lt0val3 = new TLine(t0val,0.0,t0val,hTime3->GetMaximum());
	TLine *lt1val3 = new TLine(t1val,0.0,t1val,hTime3->GetMaximum());
	lt0val3->SetLineColor(kTeal+3);
	lt1val3->SetLineColor(kTeal+3);
	lt0val3->SetLineWidth(1);
	lt1val3->SetLineWidth(1);
	lt0val3->SetLineStyle(9);
	lt1val3->SetLineStyle(9);
	lt0val3->Draw("same");
	lt1val3->Draw("same");

	lt1->DrawLatex(0.60,0.8,"3^{rd} layer");
	lt1->DrawLatex(0.60,0.6,Form("T_{0} : %0.1f (ns)",t0val));
	lt1->DrawLatex(0.60,0.53,Form("T_{1} : %0.1f (ns)",t1val));
	lt1->DrawLatex(0.60,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(t1val-t0val)));

	//////////////
	c1->cd(4);
	hTime4->Draw("HIST E");
	if (t0opt==2) {
		hTime4->Fit(errf41,"rm");
		hTime4->Fit(errf42,"rm");
		errf41->Draw("same");
		errf42->Draw("same");
		ht0val->SetBinContent(4,errf41->GetParameter(1));
		ht1val->SetBinContent(4,errf42->GetParameter(1));
		t0val=errf41->GetParameter(1);
		t1val=errf42->GetParameter(1);
	}
	else if (t0opt==1) {
		findt0(4,hTime4,ht0val,ht1val);
		t0val=ht0val->GetBinContent(4);
		t1val=ht1val->GetBinContent(4);
	}
	TLine *lt0val4 = new TLine(t0val,0.0,t0val,hTime4->GetMaximum());
	TLine *lt1val4 = new TLine(t1val,0.0,t1val,hTime4->GetMaximum());
	lt0val4->SetLineColor(kTeal+3);
	lt1val4->SetLineColor(kTeal+3);
	lt0val4->SetLineWidth(1);
	lt1val4->SetLineWidth(1);
	lt0val4->SetLineStyle(9);
	lt1val4->SetLineStyle(9);
	lt0val4->Draw("same");
	lt1val4->Draw("same");

	lt1->DrawLatex(0.60,0.8,"4^{th} layer");
	lt1->DrawLatex(0.60,0.6,Form("T_{0} : %0.1f (ns)",t0val));
	lt1->DrawLatex(0.60,0.53,Form("T_{1} : %0.1f (ns)",t1val));
	lt1->DrawLatex(0.60,0.46,Form("V_{drift} : %0.1f (#mum/ns)",2.5*1000/(t1val-t0val)));

	c1->SaveAs("plot_time_distributions.png");

	TCanvas* c2 = new TCanvas("c2","",800,800);
	c2->cd();
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


	auto lg1 = new TLegend(0.20,0.70,0.30,0.90);
	//auto lg1 = new TLegend(0.43,0.35,0.73,0.55);
	lg1->SetBorderSize(0);
	lg1->SetMargin(0.2);
	lg1->AddEntry(hTime1,"X1","lp");
	lg1->AddEntry(hTime2,"X1'","lp");
	lg1->AddEntry(hTime3,"X2","lp");
	lg1->AddEntry(hTime4,"X2'","lp");

	hTime1->GetYaxis()->SetRangeUser(0,hTime1->GetMaximum()*1.2);
	hTime1->Draw("HIST E");
	hTime2->Draw("HIST E same");
	hTime3->Draw("HIST E same");
	hTime4->Draw("HIST E same");

	lg1->Draw("same");

	c2->SaveAs("plot_time_Alldistributions.png");

	TFile* fout = new TFile("anaTimeZero_result.root","RECREATE");
	fout->cd();
	ht0val->Write();
	ht1val->Write();
	fout->Close();

}


void findt0(int ch, TH1F* hTime, TH1D* ht0val, TH1D* ht1val) {

	bool ist0=false;
	bool ist1=false;
	int t0bin=0;
	int t1bin=0;

	double valimit=hTime->GetMaximum()*0.01;
	for (int i=0;i<hTime->GetNbinsX();i++) {
		double tmp = hTime->GetBinContent(i+1);
		//std::cout << i << " - " << tmp << std::endl;
		if (!ist0 && !ist1 && tmp>valimit) {ist0=true;t0bin=i;}
		if (ist0 && !ist1) {
			if (tmp<=valimit) {
				if((i-t0bin)<=30) ist0=false;
				else {ist1=true;t1bin=i-1;}
			}
		}
		if (ist1 && tmp>valimit){
			if((i-t1bin)<=10) ist1=false;
		}		
	}
	std::cout << t0bin << " - " << t1bin << std::endl;

	ht0val->SetBinContent(ch,t0bin);
	ht1val->SetBinContent(ch,t1bin);

}
