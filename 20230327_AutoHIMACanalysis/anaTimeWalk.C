
void anaTimeWalk() {
	
	//TFile* fin = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v16.root","READ");
	TFile* fin = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v16.root","READ");

	const int nArr=3000;

	Int_t		numEvt;
	Int_t		nX11;
	Int_t		nX12;
	Int_t		nX21;
	Int_t		nX22;
	Int_t		Ch1X1[nArr];
	Int_t		Ch1X2[nArr];
	Int_t		Ch2X1[nArr];
	Int_t		Ch2X2[nArr];
	Double_t	QD1X1[nArr];
	Double_t	QD1X2[nArr];
	Double_t	QD2X1[nArr];
	Double_t	QD2X2[nArr];
	Double_t	DT1X1[nArr];
	Double_t	DT1X2[nArr];
	Double_t	DT2X1[nArr];
	Double_t	DT2X2[nArr];

	TH1D* hQD1X1 = new TH1D("hQD1X1",";QDC;Entries",2000,-1000,1000);
	TH1D* hQD1X2 = new TH1D("hQD1X2",";QDC;Entries",2000,-1000,1000);
	TH1D* hQD2X1 = new TH1D("hQD2X1",";QDC;Entries",2000,-1000,1000);
	TH1D* hQD2X2 = new TH1D("hQD2X2",";QDC;Entries",2000,-1000,1000);

	TH2D* hDTvsQD1X1 = new TH2D("hDTvsQD1X1",";QDC;#Delta{t} (ns)",2000,-1000,1000,150,0,150);
	TH2D* hDTvsQD1X2 = new TH2D("hDTvsQD1X2",";QDC;#Delta{t} (ns)",2000,-1000,1000,150,0,150);
	TH2D* hDTvsQD2X1 = new TH2D("hDTvsQD2X1",";QDC;#Delta{t} (ns)",2000,-1000,1000,150,0,150);
	TH2D* hDTvsQD2X2 = new TH2D("hDTvsQD2X2",";QDC;#Delta{t} (ns)",2000,-1000,1000,150,0,150);

	TTree* myTree = (TTree*)fin->Get("bdcTree");

	myTree->SetBranchAddress("numEvt",	&numEvt);
    myTree->SetBranchAddress("nX11",	&nX11);
    myTree->SetBranchAddress("nX12",	&nX12);
    myTree->SetBranchAddress("nX21",	&nX21);
    myTree->SetBranchAddress("nX22",	&nX22);
	myTree->SetBranchAddress("Ch1X1",	Ch1X1);
	myTree->SetBranchAddress("Ch1X2",	Ch1X2);
	myTree->SetBranchAddress("Ch2X1",	Ch2X1);
	myTree->SetBranchAddress("Ch2X2",	Ch2X2);
	myTree->SetBranchAddress("QD1X1",	QD1X1);
	myTree->SetBranchAddress("QD1X2",	QD1X2);
	myTree->SetBranchAddress("QD2X1",	QD2X1);
	myTree->SetBranchAddress("QD2X2",	QD2X2);
	myTree->SetBranchAddress("DT1X1",	DT1X1);
	myTree->SetBranchAddress("DT1X2",	DT1X2);
	myTree->SetBranchAddress("DT2X1",	DT2X1);
	myTree->SetBranchAddress("DT2X2",	DT2X2);

	for (int ievt=0;ievt<myTree->GetEntries();ievt++) {
		myTree->GetEntry(ievt);
		if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;

		for (int i=0;i<nX11;i++){
			hQD1X1->Fill(QD1X1[i]);
			hQD1X2->Fill(QD1X2[i]);
			hQD2X1->Fill(QD2X1[i]);
			hQD2X2->Fill(QD2X2[i]);

			hDTvsQD1X1->Fill(QD1X1[i],200-DT1X1[i]);
			hDTvsQD1X2->Fill(QD1X2[i],200-DT1X2[i]);
			hDTvsQD2X1->Fill(QD2X1[i],200-DT2X1[i]);
			hDTvsQD2X2->Fill(QD2X2[i],200-DT2X2[i]);
	}
	}
	TCanvas* c1 = new TCanvas("c1","",800,800);
	c1->Divide(2,2);
	c1->cd(1);
	hQD1X1->Draw();
	c1->cd(2);
	hQD1X2->Draw();
	c1->cd(3);
	hQD2X1->Draw();
	c1->cd(4);
	hQD2X2->Draw();
	c1->SaveAs("QDCDistribution_v2.pdf");


}
