#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iomanip>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"

using namespace std;
// Data : KOMAC 2022

const bool MAXQDC = false; 

//void bdcTimeDist_Data_v16(TString loc="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int RunNumber=3067){
void bdcTimeDist_Data_v16(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067){

	    TString loca;
    if (locano==1) loca="~/Research_2023/202302HIMACBeamTest/AllData/1_Proton100MeV/Data";
    else if (locano==2) loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data";

	TFile* itf1 = new TFile(Form("%s/%d_ASD16.root",loca.Data(),RunNumber),"READ"); // X1-X1'
	TFile* itf2 = new TFile(Form("%s/%d_ASD18.root",loca.Data(),RunNumber),"READ"); // Y1-Y1'
	TFile* itf3 = new TFile(Form("%s/%d_ASD17.root",loca.Data(),RunNumber),"READ"); // X2-X2'
	TFile* itf4 = new TFile(Form("%s/%d_ASD18.root",loca.Data(),RunNumber),"READ"); // Y2-Y2'

	TTree* itr1 = (TTree*)itf1->Get("DataTree");
	TTree* itr2 = (TTree*)itf2->Get("DataTree");
	TTree* itr3 = (TTree*)itf3->Get("DataTree");
	TTree* itr4 = (TTree*)itf4->Get("DataTree");

	std::cout << "itr1->GetEntries() : " << itr1->GetEntries() << std::endl;
	std::cout << "itr2->GetEntries() : " << itr2->GetEntries() << std::endl;
	std::cout << "itr3->GetEntries() : " << itr3->GetEntries() << std::endl;
	std::cout << "itr4->GetEntries() : " << itr4->GetEntries() << std::endl;


	cout<<"check"<<endl;
	Int_t EventNum1;
	UShort_t type1;
	UShort_t ver1;
	UShort_t id1;
	UShort_t trigTime1;
	UShort_t dataLen1;
	UInt_t   trigCount1;
	UInt_t   eventNum1;
	UInt_t   spillNum1;
	Int_t    DataLength1;  
	UShort_t Data1[228000];
	Int_t    TrigCount1;
	UShort_t eNum1;
	UShort_t sNum1;
	UInt_t day1;
	UInt_t hour1;
	UInt_t min1;
	UInt_t sec1;

	itr1->SetBranchAddress("EventNum" ,&EventNum1 );
	itr1->SetBranchAddress("type"     ,&type1     );
	itr1->SetBranchAddress("ver"      ,&ver1      );
	itr1->SetBranchAddress("id"       ,&id1       );
	itr1->SetBranchAddress("trigTime" ,&trigTime1 );
	itr1->SetBranchAddress("dataLen"  ,&dataLen1  );
	itr1->SetBranchAddress("trigCount",&trigCount1);
	itr1->SetBranchAddress("eventNum" ,&eventNum1 );
	itr1->SetBranchAddress("spillNum" ,&spillNum1 );
	itr1->SetBranchAddress("DataLength",&DataLength1);
	itr1->SetBranchAddress("Data"      ,Data1       );
	itr1->SetBranchAddress("TrigCount" ,&TrigCount1 );
	itr1->SetBranchAddress("eNum"      ,&eNum1      );
	itr1->SetBranchAddress("sNum"      ,&sNum1      );
	Double_t dur_defsec1;
	itr1->SetBranchAddress("dur_defsec"      ,&dur_defsec1      );
	itr1->SetBranchAddress("now_mday"	,&day1);
	itr1->SetBranchAddress("now_hour"	,&hour1);
	itr1->SetBranchAddress("now_min"	,&min1);
	itr1->SetBranchAddress("now_sec"	,&sec1);
	Int_t EventNum2;
	UShort_t type2;
	UShort_t ver2;
	UShort_t id2;
	UShort_t trigTime2;
	UShort_t dataLen2;
	UInt_t   trigCount2;
	UInt_t   eventNum2;
	UInt_t   spillNum2;
	Int_t    DataLength2;
	UShort_t Data2[228000];
	Int_t    TrigCount2;
	UShort_t eNum2;
	UShort_t sNum2;
	itr2->SetBranchAddress("EventNum" ,&EventNum2 );
	itr2->SetBranchAddress("type"     ,&type2     );
	itr2->SetBranchAddress("ver"      ,&ver2      );
	itr2->SetBranchAddress("id"       ,&id2       );
	itr2->SetBranchAddress("trigTime" ,&trigTime2 );
	itr2->SetBranchAddress("dataLen"  ,&dataLen2  );
	itr2->SetBranchAddress("trigCount",&trigCount2);
	itr2->SetBranchAddress("eventNum" ,&eventNum2 );
	itr2->SetBranchAddress("spillNum" ,&spillNum2 );
	itr2->SetBranchAddress("DataLength",&DataLength2);
	itr2->SetBranchAddress("Data"      ,Data2       );
	itr2->SetBranchAddress("TrigCount" ,&TrigCount2 );
	itr2->SetBranchAddress("eNum"      ,&eNum2      );
	itr2->SetBranchAddress("sNum"      ,&sNum2      );
	Double_t dur_defsec2;
	UInt_t		day2;
	UInt_t		hour2;
	UInt_t		min2;
	UInt_t		sec2;
	itr2->SetBranchAddress("dur_defsec"      ,&dur_defsec2      );
	itr2->SetBranchAddress("now_mday"	,&day2);
	itr2->SetBranchAddress("now_hour"	,&hour2);
	itr2->SetBranchAddress("now_min"	,&min2);
	itr2->SetBranchAddress("now_sec"	,&sec2);



	Int_t EventNum3;
	UShort_t type3;
	UShort_t ver3;
	UShort_t id3;
	UShort_t trigTime3;
	UShort_t dataLen3;
	UInt_t   trigCount3;
	UInt_t   eventNum3;
	UInt_t   spillNum3;
	Int_t    DataLength3;
	UShort_t Data3[228000];
	Int_t    TrigCount3;
	UShort_t eNum3;
	UShort_t sNum3;
	itr3->SetBranchAddress("EventNum" ,&EventNum3 );
	itr3->SetBranchAddress("type"     ,&type3     );
	itr3->SetBranchAddress("ver"      ,&ver3      );
	itr3->SetBranchAddress("id"       ,&id3       );
	itr3->SetBranchAddress("trigTime" ,&trigTime3 );
	itr3->SetBranchAddress("dataLen"  ,&dataLen3  );
	itr3->SetBranchAddress("trigCount",&trigCount3 );
	itr3->SetBranchAddress("eventNum" ,&eventNum3 );
	itr3->SetBranchAddress("spillNum" ,&spillNum3 );
	itr3->SetBranchAddress("DataLength",&DataLength3 );
	itr3->SetBranchAddress("Data"      ,Data3       );
	itr3->SetBranchAddress("TrigCount" ,&TrigCount3 );
	itr3->SetBranchAddress("eNum"      ,&eNum3      );
	itr3->SetBranchAddress("sNum"      ,&sNum3      );
	Double_t dur_defsec3;
	UInt_t		day3;
	UInt_t		hour3;
	UInt_t		min3;
	UInt_t		sec3;
	itr3->SetBranchAddress("dur_defsec"      ,&dur_defsec3      );
	itr3->SetBranchAddress("now_mday"	,&day3);
	itr3->SetBranchAddress("now_hour"	,&hour3);
	itr3->SetBranchAddress("now_min"	,&min3);
	itr3->SetBranchAddress("now_sec"	,&sec3);



	Int_t EventNum4;
	UShort_t type4;
	UShort_t ver4;
	UShort_t id4;
	UShort_t trigTime4;
	UShort_t dataLen4;
	UInt_t   trigCount4;
	UInt_t   eventNum4;
	UInt_t   spillNum4;
	Int_t    DataLength4;
	UShort_t Data4[228000];
	Int_t    TrigCount4;
	UShort_t eNum4;
	UShort_t sNum4;
	itr4->SetBranchAddress("EventNum" ,&EventNum4 );
	itr4->SetBranchAddress("type"     ,&type4     );
	itr4->SetBranchAddress("ver"      ,&ver4      );
	itr4->SetBranchAddress("id"       ,&id4       );
	itr4->SetBranchAddress("trigTime" ,&trigTime4 );
	itr4->SetBranchAddress("dataLen"  ,&dataLen4  );
	itr4->SetBranchAddress("trigCount",&trigCount4 );
	itr4->SetBranchAddress("eventNum" ,&eventNum4 );
	itr4->SetBranchAddress("spillNum" ,&spillNum4 );
	itr4->SetBranchAddress("DataLength",&DataLength4 );
	itr4->SetBranchAddress("Data"      ,Data4       );
	itr4->SetBranchAddress("TrigCount" ,&TrigCount4 );
	itr4->SetBranchAddress("eNum"      ,&eNum4      );
	itr4->SetBranchAddress("sNum"      ,&sNum4      );
	Double_t dur_defsec4;
	UInt_t		day4;
	UInt_t		hour4;
	UInt_t		min4;
	UInt_t	sec4;
	itr4->SetBranchAddress("dur_defsec"      ,&dur_defsec4      );
	itr4->SetBranchAddress("now_mday"	,&day4);
	itr4->SetBranchAddress("now_hour"	,&hour4);
	itr4->SetBranchAddress("now_min"	,&min4);
	itr4->SetBranchAddress("now_sec"	,&sec4);



	int minevt = 0;
/*
//	int minip = 0;
//	int maxip = 10;

	minip = 1;
	maxip = 6;

	minip = -1;
	maxip = 10;


	//int minip = 3;
	//int maxip = 8;
*/
	double QDCCUT1 = 370; //300;
	double QDCCUT2 = 290; //300;
	double QDCCUT3 = 320; //300;
	double QDCCUT4 = 320; //300;
						  // ASD 16, 17 : 300
						  // ASD 18 : 320;
						  // ASD 19 : 300; 
	QDCCUT1 = 300;
	QDCCUT2 = 300;
	QDCCUT3 = 320;
	QDCCUT4 = 300;

	QDCCUT1 = 320;
	QDCCUT2 = 320;
	QDCCUT3 = 320;
	QDCCUT4 = 320;

	QDCCUT1 = 0;
	QDCCUT2 = 0;
	QDCCUT3 = 0;
	QDCCUT4 = 0;


	//QDCCUT2 = 220;
	double timecut = 150;
	int ngoodtrack = 0;

	//double diftime = 0; // delay 180 ns
	double diftime = 110+70; // delay 180 ns
	double diftime1 = 193.3;
	double diftime2 = 187.3;
	double diftime3 = 188.8;
	double diftime4 = 185.9;

	diftime1 = 185;
	diftime2 = 183;
	diftime3 = 184;
	diftime4 = 183;

	diftime1 = 1950+60.0;
	diftime2 = 1950+59.1;
	diftime3 = 1950+63.5;
	diftime4 = 1950+54.6;

	diftime1 = 1900+53.2;
	diftime2 = 1900+53.0;
	diftime3 = 1900+62.7;
	diftime4 = 1900+61.0;

	// Carbon 200 MeV, run 3057
	diftime1 = 1890+63.2;
	diftime2 = 1890+62.3;
	diftime3 = 1890+72.8;
	diftime4 = 1890+71.7;

	// Carbon 200 MeV, run 3067
	diftime1 = 1890+97.5;
	diftime2 = 1890+96.9;
	diftime3 = 1890+107.5;
	diftime4 = 1890+106.0;

	// Carbon 200 MeV, run 3067, nocut v20230315
	diftime1 = 1890+99.7;
	diftime2 = 1890+99.1;
	diftime3 = 1890+110.0;
	diftime4 = 1890+108.5;

	// Carbon 200 MeV, run 3067, nocut v20230316, ip -1~10, only 1 hit per layer
	diftime1 = 1890+100.2;
	diftime2 = 1890+99.4;
	diftime3 = 1890+110.4;
	diftime4 = 1890+108.8;

	// Proton 100 MeV, run 2043, nocut v20230320, ip -1~10, only 1 hit per layer
	diftime1 = 1950+50.6;
	diftime2 = 1950+50.0;
	diftime3 = 1950+52.8;
	diftime4 = 1950+51.7;

	// Proton 100 MeV, run 2043, nocut v20230320, ip -1~10, only 1 hit per layer, t0 starting points
	diftime1 = 1950+30;//26
	diftime2 = 1950+30;//26
	diftime3 = 1950+30;//28
	diftime4 = 1950+30;//22

	// Carbon 200 MeV, run 3067, nocut v20230320, ip -1~10, only 1 hit per layer, t0 starting points
	diftime1 = 1950+33;//
	diftime2 = 1950+33;//
	diftime3 = 1950+44;//or 42
	diftime4 = 1950+41;//

	TFile* ift0 = new TFile("anaTimeZero_result.root","READ");
	TH1D* ht0val = (TH1D*)ift0->Get("ht0val");
	TH1D* ht1val = (TH1D*)ift0->Get("ht1val");
   
	diftime1 = 1850 + ht0val->GetBinContent(1);
	diftime2 = 1850 + ht0val->GetBinContent(2);
	diftime3 = 1850 + ht0val->GetBinContent(3);
	diftime4 = 1850 + ht0val->GetBinContent(4);




	//diftime1 = 180;
	//diftime2 = 180;
	//diftime3 = 180;
	//diftime4 = 180;


	// Basic histogram
	TH2D* hisQDC1 = new TH2D("hisQDC1","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh1= new TH3D("hisQDCCh1","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit1 = new TH1D("hisTDCHit1" ,"hisTDCHit;channel;Hit",64,0,64);
	TH2D* hisQDC2 = new TH2D("hisQDC2","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh2= new TH3D("hisQDCCh2","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit2 = new TH1D("hisTDCHit2" ,"hisTDCHit;channel;Hit",64,0,64);
	TH2D* hisQDC3 = new TH2D("hisQDC3","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh3= new TH3D("hisQDCCh3","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit3 = new TH1D("hisTDCHit3" ,"hisTDCHit;channel;Hit",64,0,64);
	TH2D* hisQDC4 = new TH2D("hisQDC4","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh4= new TH3D("hisQDCCh4","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit4 = new TH1D("hisTDCHit4" ,"hisTDCHit;channel;Hit",64,0,64);

	TH1D* TimeDist1 = new TH1D("TimeDist1" ,"TimeDist1;time;Hit",200,0,200);
	TH1D* TimeDist2 = new TH1D("TimeDist2" ,"TimeDist2;time;Hit",200,0,200);
	TH1D* TimeDist3 = new TH1D("TimeDist3" ,"TimeDist3;time;Hit",200,0,200);
	TH1D* TimeDist4 = new TH1D("TimeDist4" ,"TimeDist4;time;Hit",200,0,200);


	TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time;Hit",200,0,200);
	TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time;Hit",200,0,200);
	TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time;Hit",200,0,200);
	TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time;Hit",200,0,200);

	TH1D* TimeDist1Ch[64];
	TH1D* TimeDist2Ch[64];
	TH1D* TimeDist3Ch[64];
	TH1D* TimeDist4Ch[64];

	for (int i=0;i<64;i++) {
		TimeDist1Ch[i] = new TH1D(Form("TimeDist1Ch%d",i),Form("TimeDist1Ch%d;time;Hit",i),200,0,200);
		TimeDist2Ch[i] = new TH1D(Form("TimeDist2Ch%d",i),Form("TimeDist2Ch%d;time;Hit",i),200,0,200);
		TimeDist3Ch[i] = new TH1D(Form("TimeDist3Ch%d",i),Form("TimeDist3Ch%d;time;Hit",i),200,0,200);
		TimeDist4Ch[i] = new TH1D(Form("TimeDist4Ch%d",i),Form("TimeDist4Ch%d;time;Hit",i),200,0,200);
	}


	TH1D* TimeDist12 = new TH1D("TimeDist12" ,"TimeDist1;time;Hit",200,0,200);
	TH1D* TimeDist22 = new TH1D("TimeDist22" ,"TimeDist2;time;Hit",200,0,200);
	TH1D* TimeDist32 = new TH1D("TimeDist32" ,"TimeDist3;time;Hit",200,0,200);
	TH1D* TimeDist42 = new TH1D("TimeDist42" ,"TimeDist4;time;Hit",200,0,200);

	TH1D* TimeMax11 = new TH1D("TimeMax11",";time;Counts",500,0,500);
	TH1D* TimeMax21 = new TH1D("TimeMax21",";time;Counts",500,0,500);
	TH1D* DriftVel11 = new TH1D("DriftVel11",";time;Counts",50,0,150);
	TH1D* DriftVel21 = new TH1D("DriftVel21",";time;Counts",50,0,150);

	TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",25,0,100,25,0,100);
	TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",25,0,100,25,0,100);
	TH2D* TimeCorr12 = new TH2D("TimeCorr12",";time;time",25,0,100,25,0,100);
	TH2D* TimeCorr22 = new TH2D("TimeCorr22",";time;time",25,0,100,25,0,100);


	TH2D* hChCorr1 = new TH2D("hChCorr11",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr2 = new TH2D("hChCorr21",";Y;Y'",32,0,32,32,0,32);
	TH2D* hChCorr3 = new TH2D("hChCorr31",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr4 = new TH2D("hChCorr41",";Y;Y'",32,0,32,32,0,32);

	TH1D* TimeMax12 = new TH1D("TimeMax12",";time;Counts",500,0,500);
	TH1D* TimeMax22 = new TH1D("TimeMax22",";time;Counts",500,0,500);
	TH1D* DriftVel12 = new TH1D("DriftVel12",";time;Counts",50,0,150);
	TH1D* DriftVel22 = new TH1D("DriftVel22",";time;Counts",50,0,150);


	TH1D* hTimeMult = new TH1D("hTimeMult",";time1 * time2;Counts",100,0,10000);


	TH2D* hChCorr12 = new TH2D("hChCorr12",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr22 = new TH2D("hChCorr22",";Y;Y'",32,0,32,32,0,32);
	TH2D* hChCorr32 = new TH2D("hChCorr32",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr42 = new TH2D("hChCorr42",";Y;Y'",32,0,32,32,0,32);


	int maxevt = itr4->GetEntries();
	//TFile *outfile = new TFile(Form("bdcTrackInfo_Run_%d_convertdata_v14.root",RunNumber),"RECREATE");
	TFile *outfile = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v16.root","RECREATE");


	TTree *bdcTree = new TTree("bdcTree","BDC Data Tree");
	const int nArr = 2000;//20000
						  //const int nArr = itr2->GetEntries();

	int numEvt = 0;
	int nX11 = 0, nX12 = 0, nX21 = 0, nX22 = 0; // number of 2 D hits
	int nY11 = 0, nY12 = 0, nY21 = 0, nY22 = 0; // number of 2 D hits
	int Ch1X1[nArr] = {0}, Ch1X2[nArr] = {0}, Ch1Y1[nArr] = {0}, Ch1Y2[nArr] = {0}; // fired channel x, y at chamber 1
	int Ch2X1[nArr] = {0}, Ch2X2[nArr] = {0}, Ch2Y1[nArr] = {0}, Ch2Y2[nArr] = {0}; // fired channel x, y at chamber 2
	double DL1X1[nArr] = {0}, DL1X2[nArr] = {0}, DL1Y1[nArr] = {0}, DL1Y2[nArr] = {0}; // drift time at chamber 1
	double DL2X1[nArr] = {0}, DL2X2[nArr] = {0}, DL2Y1[nArr] = {0}, DL2Y2[nArr] = {0}; // drift time at chamber 2
	double DT1X1[nArr] = {0}, DT1X2[nArr] = {0}, DT1Y1[nArr] = {0}, DT1Y2[nArr] = {0}; // drift time at chamber 1
	double DT2X1[nArr] = {0}, DT2X2[nArr] = {0}, DT2Y1[nArr] = {0}, DT2Y2[nArr] = {0}; // drift time at chamber 2



	bdcTree->Branch("numEvt",&numEvt,"numEvt/I");
	bdcTree->Branch("nX11",&nX11,"nX11/I");
	bdcTree->Branch("nX12",&nX12,"nX12/I");
	bdcTree->Branch("nX21",&nX21,"nX21/I");
	bdcTree->Branch("nX22",&nX22,"nX22/I");

	bdcTree->Branch("nY11",&nY11,"nY11/I");
	bdcTree->Branch("nY12",&nY12,"nY12/I");
	bdcTree->Branch("nY21",&nY21,"nY21/I");
	bdcTree->Branch("nY22",&nY22,"nY22/I");

	bdcTree->Branch("Ch1X1",&Ch1X1,"Ch1X1[nX11]/I");
	bdcTree->Branch("Ch1X2",&Ch1X2,"Ch1X2[nX12]/I");
	bdcTree->Branch("DL1X1",&DL1X1,"DL1X1[nX11]/D");
	bdcTree->Branch("DL1X2",&DL1X2,"DL1X2[nX12]/D");
	bdcTree->Branch("DT1X1",&DT1X1,"DT1X1[nX11]/D");
	bdcTree->Branch("DT1X2",&DT1X2,"DT1X2[nX12]/D");

	bdcTree->Branch("Ch2X1",&Ch2X1,"Ch2X1[nX21]/I");
	bdcTree->Branch("Ch2X2",&Ch2X2,"Ch2X2[nX22]/I");
	bdcTree->Branch("DL2X1",&DL2X1,"DL2X1[nX21]/D");
	bdcTree->Branch("DL2X2",&DL2X2,"DL2X2[nX22]/D");
	bdcTree->Branch("DT2X1",&DT2X1,"DT2X1[nX21]/D");
	bdcTree->Branch("DT2X2",&DT2X2,"DT2X2[nX22]/D");

	bdcTree->Branch("Ch1Y1",&Ch1Y1,"Ch1Y1[nY11]/I");
	bdcTree->Branch("Ch1Y2",&Ch1Y2,"Ch1Y2[nY12]/I");
	bdcTree->Branch("DL1Y1",&DL1Y1,"DL1Y1[nY11]/D");
	bdcTree->Branch("DL1Y2",&DL1Y2,"DL1Y2[nY12]/D");
	bdcTree->Branch("DT1Y1",&DT1Y1,"DT1Y1[nY11]/D");
	bdcTree->Branch("DT1Y2",&DT1Y2,"DT1Y2[nY12]/D");

	bdcTree->Branch("Ch2Y1",&Ch2Y1,"Ch2Y1[nY21]/I");
	bdcTree->Branch("Ch2Y2",&Ch2Y2,"Ch2Y2[nY22]/I");
	bdcTree->Branch("DL2Y1",&DL2Y1,"DL2Y1[nY21]/D");
	bdcTree->Branch("DL2Y2",&DL2Y2,"DL2Y2[nY22]/D");
	bdcTree->Branch("DT2Y1",&DT2Y1,"DT2Y1[nY21]/D");
	bdcTree->Branch("DT2Y2",&DT2Y2,"DT2Y2[nY22]/D");

	//maxevt = 100;

	int inv1=0;
	int inv2=0;
	int inv3=0;
	int inv4=0;

	int dif1[nArr] = {0};
	int dif2[nArr] = {0};
	int dif3[nArr] = {0};
	int dif4[nArr] = {0};

	double ds1[nArr] = {0};
	double ds2[nArr] = {0};
	double ds3[nArr] = {0};
	double ds4[nArr] = {0};


	int allfiredEvt = 0;
	int allfiredEvt2 = 0;
	int allfiredEvt3 = 0;
	int allfiredEvt4 = 0;

	int sumevt=0;
	for( int ievt = minevt; ievt < maxevt; ievt++){

		cout<<"### Events : "<<ievt<<" ###"<<endl;
		// Sejong Configuration : XX'YY'Y'YX'X, 
		// X'X : file 0
		// X : 0 - 31, X' : 32 - 63
		// XX' : file 1
		// X : 0 - 31, X' : 32 - 63
		// Y'Y : file 2
		// Y : 0 - 31, Y' : 32 - 63
		// YY' : file 3
		// Y : 0 - 31, Y' : 32 - 63

		itr1->GetEntry(ievt);
		numEvt = ievt;
		//cout<<"numEvt : "<<numEvt<<endl;
		Int_t nPoints1 = DataLength1 / 128;
		Double_t QDCSum1[64]={0};
		//std::cout<< "point" << std::endl;

		if(ievt%100==0) std::cout<< "Event : " << ievt << " !!! "<<(double)ievt/maxevt*100<<"(%)"<<std::endl;
		//std::cout<< "Event : " << ievt <<endl;
		int firedch1_1[20000] = {0};
		int firedch1_2[20000] = {0};
		int cnt1_1 = 0;
		int cnt1_2 = 0;
		double time1_1[20000] = {0};
		double time1_2[20000] = {0};
		double maxQDC1_1 = 0;
		double maxQDC1_2 = 0;
		///////////////////// Chamber1-XX' /////////////////////////////////////
		//cout<< "ASD 16 X11-X12"<<endl;
		for( int ip = 0; ip < nPoints1; ip++){
			for( int ich = 0; ich < 64; ich++){
				//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
				if(ip>minip && ip<maxip){
					double tmpQDC=Data1[ip*128+ich];
					unsigned short ftt1
						= ((trigTime1 & 0xFF00 ) >> 8 )
						+ ((trigTime1 & 0x007F ) << 8 );

					if (tmpQDC > QDCCUT1){
						//double time = (ftt1-(Data1[ip*128+64+ich]&0x7FFF));
						double time = 4000+(-ftt1+(Data1[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;
						hisQDCCh1->Fill(ip,tmpQDC,ich);
						hisQDC1->Fill(ip,tmpQDC);
						if(Data1[ip*128+64+ich] > 0) hisTDCHit1->Fill(ich);
						if(ich < 32 ) { 
							if(Data1[ip*128+64+ich] > 0) {
								firedch1_1[cnt1_1] = ich;
								//firedch1_1[cnt1_1] = 31-ich;
								Ch1X1[cnt1_1] = firedch1_1[cnt1_1];
								time1_1[cnt1_1] = time - diftime1;
								DT1X1[cnt1_1] = time1_1[cnt1_1];
								TimeDist1->Fill(DT1X1[cnt1_1]);
								cout<<"Ch : "<<firedch1_1[cnt1_1]<<", DT1X1 : "<<DT1X1[cnt1_1]<<", DL1X1 : "<<DL1X1[cnt1_1]<<endl;
								cnt1_1++;
							}
						}
						if(ich >= 32 ) { 
							if(Data1[ip*128+64+ich] > 0) {
								firedch1_2[cnt1_2] = ich-32;
								//firedch1_2[cnt1_2] = 63-ich;
								Ch1X2[cnt1_2] = firedch1_2[cnt1_2];
								time1_2[cnt1_2] = time - diftime2;
								DT1X2[cnt1_2] = time1_2[cnt1_2];
								TimeDist2->Fill(DT1X2[cnt1_2]);
								cout<<"Ch : "<<firedch1_2[cnt1_2]<<", DT1X2 : "<<DT1X2[cnt1_2]<<", DL1X2 : "<<DL1X2[cnt1_2]<<endl;
								cnt1_2++;
							}
						}
					} // QCD cut
				} // ip cut
			} // ip 
		}// ch
		hChCorr1->Fill(Ch1X1[0],Ch1X2[0]);
		nX11 = cnt1_1;
		nX12 = cnt1_2;

		///////////////////// Chamber1-YY' /////////////////////////////////////
		// Chamber 18 Y11-Y12
		//cout<< "ASD 18 Y11-Y12"<<endl;
		itr2->GetEntry(ievt);
		//itr2->GetEntry(ievt+dif2[ievt]);
		Int_t nPoints2 = DataLength2 / 128;
		Double_t QDCSum2[64]={0};
		int firedch2_1[20000] = {0};
		int firedch2_2[20000] = {0};
		double time2_1[20000] = {0};
		double time2_2[20000] = {0};
		double maxQDC2_1 = 0;
		double maxQDC2_2 = 0;
		int cnt2_1 = 0;
		int cnt2_2 = 0;
		for( int ip = 0; ip < nPoints2; ip++){
			for( int ich = 0; ich < 64; ich++){
				//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
				if(ip>minip && ip<maxip){
					double tmpQDC=Data2[ip*128+ich];
					unsigned short ftt2
						= ((trigTime2 & 0xFF00 ) >> 8 )
						+ ((trigTime2 & 0x007F ) << 8 );

					if (tmpQDC > QDCCUT2){
						//double time = (ftt2 - (Data2[ip*128+64+ich]&0x7FFF));
						double time = 4000+(-ftt2+(Data2[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;
						//hisTDC2->Fill(ip,ich,fabs(time));
						hisQDCCh2->Fill(ip,tmpQDC,ich);
						hisQDC2->Fill(ip,tmpQDC);
						if(Data2[ip*128+64+ich] > 0) hisTDCHit2->Fill(ich);
						if(ich < 32) { 
							if(Data2[ip*128+64+ich] > 0 ) {
								//firedch2_1[cnt2_1] = 31-ich;
								firedch2_1[cnt2_1] =ich;
								Ch1Y1[cnt2_1] = firedch2_1[cnt2_1];
								time2_1[cnt2_1] = time - diftime1;
								DT1Y1[cnt2_1] = time2_1[cnt2_1];
								TimeDist3->Fill(DT1Y1[cnt2_1]);
								cout<<"Ch : "<<firedch2_1[cnt2_1]<<", DT1Y1 : "<<DT1Y1[cnt2_1]<<", DL1Y1 : "<<DL1Y1[cnt2_1]<<endl;
								cnt2_1++;
							}
						}
						if(ich >= 32) { 
							//time = time-mintime2_2;
							if(Data2[ip*128+64+ich] > 0 ) {
								//firedch2_2[cnt2_2] = 63-ich;
								firedch2_2[cnt2_2] = ich-32;
								Ch1Y2[cnt2_2] = firedch2_2[cnt2_2];
								time2_2[cnt2_2] = time - diftime2;
								DT1Y2[cnt2_2] = time2_2[cnt2_2];
								TimeDist4->Fill(DT1Y2[cnt2_2]);
								if(time2_2[cnt2_2] > 160) DL1Y2[cnt2_2] = 2.5;
								cout<<"Ch : "<<firedch2_2[cnt2_2]<<", DT1Y2 : "<<DT1Y2[cnt2_2]<<", DL1Y2 : "<<DL1Y2[cnt2_2]<<endl;
								cnt2_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
		hChCorr2->Fill(Ch1Y1[cnt2_1],Ch1Y2[cnt2_2]);
		nY11 = cnt2_1;
		nY12 = cnt2_2;

		///////////////////// Chamber2-XX' /////////////////////////////////////
		//cout<< "ASD 16 X21-X22"<<endl;
		itr3->GetEntry(ievt);
		//itr3->GetEntry(ievt+dif3[ievt]);
		Int_t nPoints3 = DataLength3 / 128;
		Double_t QDCSum3[64]={0};
		int firedch3_1[20000] = {0};
		int firedch3_2[20000] = {0};
		double time3_1[20000] = {0};
		double time3_2[20000] = {0};
		double maxQDC3_1 = 0;
		double maxQDC3_2 = 0;
		int cnt3_1 = 0;
		int cnt3_2 = 0;
		for( int ip = 0; ip < nPoints3; ip++){
			for( int ich = 0; ich < 64; ich++){
				//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
				if(ip>minip && ip<maxip){
					double tmpQDC=Data3[ip*128+ich];
					unsigned short ftt3
						= ((trigTime3 & 0xFF00 ) >> 8 )
						+ ((trigTime3 & 0x007F ) << 8 );

					if (tmpQDC > QDCCUT3){
						//double time = (ftt3 - (Data3[ip*128+64+ich]&0x7FFF));
						double time = 4000+(-ftt3+(Data3[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;
						//hisTDC3->Fill(ip,ich,fabs(time));
						hisQDCCh3->Fill(ip,tmpQDC,ich);
						hisQDC3->Fill(ip,tmpQDC);
						if(Data3[ip*128+64+ich] > 0) hisTDCHit3->Fill(ich);
						// X
						if(ich < 32) { 
							if(Data3[ip*128+64+ich] > 0) {
								firedch3_1[cnt3_1] = 31-ich;
								Ch2X1[cnt3_1] = firedch3_1[cnt3_1];
								//firedch3_1[cnt3_1] = ich;
								time3_1[cnt3_1] = time - diftime3;
								DT2X1[cnt3_1] = time3_1[cnt3_1];
								//TimeDist3->Fill(DT2X1[cnt3_1]);
								cout<<"Ch : "<<firedch3_1[cnt3_1]<<", DT2X1 : "<<DT2X1[cnt3_1]<<", DL2X1 : "<<DL2X1[cnt3_1]<<endl;
								cnt3_1++;
							}
						}
						// X'
						if(ich >= 32) { 
							//time = time-mintime3_2;
							if(Data3[ip*128+64+ich] > 0) {
								//	if(mintime3_2>time) mintime3_2 = time;
								firedch3_2[cnt3_2] = 63-ich;
								Ch2X2[cnt3_2] = firedch3_2[cnt3_2];
								time3_2[cnt3_2] = time - diftime4;
								DT2X2[cnt3_2] = time3_2[cnt3_2];
								//TimeDist3->Fill(DT2X2[cnt3_2]);
								cout<<"Ch : "<<firedch3_2[cnt3_2]<<", DT2X2 : "<<DT2X2[cnt3_2]<<", DL2X2 : "<<DL2X2[cnt3_2]<<endl;
								cnt3_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
		hChCorr3->Fill(Ch2X1[cnt3_1],Ch2X2[cnt3_2]);
		nX21 = cnt3_1;
		nX22 = cnt3_2;

		///////////////////// Chamber2-YY' /////////////////////////////////////
		//cout<< "ASD 18 Y21-Y22"<<endl;
		itr4->GetEntry(ievt);
		//itr4->GetEntry(ievt+dif4[ievt]);
		Int_t nPoints4 = DataLength4 / 128;
		Double_t QDCSum4[64]={0};
		int firedch4_1[20000] = {0};
		int firedch4_2[20000] = {0};
		double time4_1[20000] = {0};
		double time4_2[20000] = {0};
		double maxQDC4_1 = 0;
		double maxQDC4_2 = 0;
		int cnt4_1 = 0;
		int cnt4_2 = 0;
		for( int ip = 0; ip < nPoints4; ip++){
			for( int ich = 0; ich < 64; ich++){
				// if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
				if(ip>minip && ip<maxip){
					double tmpQDC=Data4[ip*128+ich];
					unsigned short ftt4
						= ((trigTime4 & 0xFF00 ) >> 8 )
						+ ((trigTime4 & 0x007F ) << 8 ); // trigTime4

					if (tmpQDC > QDCCUT4){
						//double time = (ftt4 - (Data4[ip*128+64+ich]&0x7FFF));
						double time = 4000+(-ftt4+(Data4[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;
						//hisTDC4->Fill(ip,ich,fabs(time));
						hisQDCCh4->Fill(ip,tmpQDC,ich);
						hisQDC4->Fill(ip,tmpQDC);
						if(Data4[ip*128+64+ich] > 0) hisTDCHit4->Fill(ich);
						// Y 
						if(ich < 32) { 
							if(Data4[ip*128+64+ich] > 0) {
								//firedch4_1[cnt4_1] = 31-ich;
								firedch4_1[cnt4_1] = ich;

								Ch2Y1[cnt4_1] = firedch4_1[cnt4_1];
								time4_1[cnt4_1] = time - diftime3;
								DT2Y1[cnt4_1] = time4_1[cnt4_1];
								//TimeDist4->Fill(DT2Y1[cnt4_1]);
								cout<<"Ch : "<<firedch4_1[cnt4_1]<<", DT2Y1 : "<<DT2Y1[cnt4_1]<<", DL2Y1 : "<<DL2Y1[cnt4_1]<<endl;
								cnt4_1++;
							}
						}
						// Y'
						if(ich >= 32) { 
							if(Data4[ip*128+64+ich] > 0) {
								//firedch4_2[cnt4_2] = 63-ich;
								firedch4_2[cnt4_2] = ich-32;

								Ch2Y2[cnt4_2] = firedch4_2[cnt4_2];
								time4_2[cnt4_2] = time - diftime4;
								DT2Y2[cnt4_2] = time4_2[cnt4_2];
								//TimeDist4->Fill(DT2Y2[cnt4_2]);
								cout<<"Ch : "<<firedch4_2[cnt4_2]<<", DT2Y2 : "<<DT2Y2[cnt4_2]<<", DL2Y2 : "<<DL2Y2[cnt4_2]<<endl;
								cnt4_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
		hChCorr4->Fill(Ch2Y1[cnt4_1],Ch2Y2[cnt4_2]);
		nY21 = cnt4_1;
		nY22 = cnt4_2;


		cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
		cout<<"nY11 : "<<nY11<<", nY12 : "<<nY12<<", nY21 : "<<nY21<<", nY22 : "<<nY22<<endl;
		//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
		if(nX11 > 0 && nX12 > 0 && nX21 > 0 && nX22 > 0) {
			allfiredEvt++;
			//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
			//cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
			//if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;
                          if (runopt==0 || runopt==1 || runopt==2) {if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;}    
              if (runopt==1) {
                  int datadiff1 = Ch1X2[0]-Ch1X1[0];
                  int datadiff2 = Ch2X2[0]-Ch2X1[0];
                 if (!(datadiff1==-1 || datadiff1==0)) continue;
                 if (!(datadiff2==0 || datadiff2==1)) continue;
                 }   
             else if (runopt==2) {
                 if (!(13<=Ch1X1[0] && Ch1X1[0]<=17)) continue;
             }    
			for(int i = 0; i < nX11; i++){
				for(int j = 0; j < nX12; j++){
					for(int k = 0; k < nX21; k++){
						for(int l = 0; l < nX22; l++){
							double time1 = DT1X1[i];
							double time2 = DT1X2[j];
							double time3 = DT2X1[k];
							double time4 = DT2X2[l];
							if(time1 < 0 || time2 < 0 || time3 < 0 || time4 < 0) continue;
							TimeDist11->Fill(time1);
							TimeDist21->Fill(time2);
							TimeDist31->Fill(time3);
							TimeDist41->Fill(time4);
							TimeDist1Ch[Ch1X1[i]]->Fill(time1);
							TimeDist2Ch[Ch1X2[j]]->Fill(time2);
							TimeDist3Ch[Ch2X1[k]]->Fill(time3);
							TimeDist4Ch[Ch2X2[l]]->Fill(time4);



							TimeCorr11->Fill(time1,time2);
							TimeCorr21->Fill(time3,time4);
							hTimeMult->Fill(time1*time2);
							TimeMax11->Fill((time1+time3)/2+time2);
							TimeMax21->Fill((time2+time4)/2+time3);
							DriftVel11->Fill(2.5/((time1+time3)/2+time2)*1000.0);
							DriftVel21->Fill(2.5/((time2+time4)/2+time3)*1000.0);
							cout<<"dhmoon chk 1 time 1 : "<<time1<<", time 2 : "<<time2<<", time 3 : "<<time3<<", time4 : "<<time4<<endl;
							allfiredEvt2++;
						}
					}
				}
			}
		}


		//nY11 = 1; nY12 = 1; nY21 = 1; nY22 = 1;
		if(nY11 > 0 && nY12 > 0 && nY21 > 0 && nY22 > 0) {
			allfiredEvt3++;
			nY11 = 1; nY12 = 1; nY21 = 1; nY22 = 1;
			//cout<<"nY11 : "<<nY11<<", nY12 : "<<nY12<<", nY21 : "<<nY21<<", nY22 : "<<nY22<<endl;
			for(int i = 0; i < nY11; i++){
				for(int j = 0; j < nY12; j++){
					for(int k = 0; k < nY21; k++){
						for(int l = 0; l < nY22; l++){
							double time1 = DT1Y1[i];
							double time2 = DT1Y2[j];
							double time3 = DT2Y1[k];
							double time4 = DT2Y2[l];
							if(time1 < 0 || time2 < 0 || time3 < 0 || time4 < 0) continue;
							TimeDist12->Fill(time1);
							TimeDist22->Fill(time2);
							TimeDist32->Fill(time3);
							TimeDist42->Fill(time4);
							TimeCorr12->Fill(time1,time2);
							TimeCorr22->Fill(time3,time4);
							TimeMax12->Fill((time1+time3)/2+time2);
							TimeMax22->Fill((time2+time4)/2+time3);
							DriftVel12->Fill(2.5/((time1+time3)/2+time2)*1000.0);
							DriftVel22->Fill(2.5/((time2+time4)/2+time3)*1000.0);
							cout<<"dhmoon chk 2 time 1 : "<<time1<<", time 2 : "<<time2<<", time 3 : "<<time3<<", time4 : "<<time4<<endl;
							allfiredEvt4++;
						}
					}
				}
			}
		}


		cout<<"nX11 : "<<nX11<<" nX12 : "<<nX12<<" nX21 : "<<nX21<<" nX22 : "<<nX22<<endl;
		cout<<"nY11 : "<<nY11<<" nY12 : "<<nY12<<" nY21 : "<<nY21<<" nY22 : "<<nY22<<endl;

		bdcTree->Fill();
		sumevt++;


	}

	std::cout << "--- Sum of initial data : " << maxevt-minevt <<std::endl;
	std::cout << "------ Sum of events filled : " << sumevt << std::endl;

	cout<<" Number of events with all fired layers at X : "<<allfiredEvt<<endl;
	cout<<" Number of events with all fired layers with positive time at X : "<<allfiredEvt2<<endl;

	cout<<" Number of events with all fired layers at Y : "<<allfiredEvt3<<endl;
	cout<<" Number of events with all fired layers with positive time at Y: "<<allfiredEvt4<<endl;


	outfile->cd();
	bdcTree->Write();
	TimeDist1->Write();
	TimeDist2->Write();
	TimeDist3->Write();
	TimeDist4->Write();

	TimeDist11->Write();
	TimeDist21->Write();
	TimeDist31->Write();
	TimeDist41->Write();

	for (int i=0;i<64;i++) {
		TimeDist1Ch[i]->Write();
		TimeDist2Ch[i]->Write();
		TimeDist3Ch[i]->Write();
		TimeDist4Ch[i]->Write();
	}

	TimeMax11->Write();
	TimeMax21->Write();

	DriftVel11->Write();
	DriftVel21->Write();

	TimeCorr11->Write();
	TimeCorr21->Write();
	TimeCorr12->Write();
	TimeCorr22->Write();

	hTimeMult->Write();

	TimeDist12->Write();
	TimeDist22->Write();
	TimeDist32->Write();
	TimeDist42->Write();

	TimeMax12->Write();
	TimeMax22->Write();

	DriftVel12->Write();
	DriftVel22->Write();



	outfile->Write();
	outfile->Close();

	TFile *sfile = new TFile("convert_data_CNU_Cosmic_EXP.root","RECREATE");
	sfile ->cd();

	TH1D* Time1[4];
	TH1D* Time2[4];

	Time1[0] = (TH1D*)TimeDist11->Clone();
	Time1[1] = (TH1D*)TimeDist21->Clone();
	Time1[2] = (TH1D*)TimeDist31->Clone();
	Time1[3] = (TH1D*)TimeDist41->Clone();

	Time2[0] = (TH1D*)TimeDist12->Clone();
	Time2[1] = (TH1D*)TimeDist22->Clone();
	Time2[2] = (TH1D*)TimeDist32->Clone();
	Time2[3] = (TH1D*)TimeDist42->Clone();

	TH1D* TimeInt1[4];
	TH1D* TimeInt2[4];

	TH1D* Time1Ch[4][64];

	TH1D* TimeInt1Ch[4][64];


	for(int i=0;i<4;i++)
	{
		TimeInt1[i] = new TH1D(Form("TimeInt%d1",i),Form("TimeInt%d1",i),160,0,160);
		TimeInt1[i] -> GetXaxis() -> SetTitle("drift time[ns]");
		TimeInt1[i] -> GetYaxis() -> SetTitle("drift length[mm]");
		TimeInt2[i] = new TH1D(Form("TimeInt%d2",i),Form("TimeInt%d2",i),160,0,160);
		TimeInt2[i] -> GetXaxis() -> SetTitle("drift time[ns]");
		TimeInt2[i] -> GetYaxis() -> SetTitle("drift length[mm]");
	}

	for(int j=0;j<64;j++)
	{
		Time1Ch[0][j] = (TH1D*)(TimeDist1Ch[j])->Clone();
		Time1Ch[1][j] = (TH1D*)(TimeDist2Ch[j])->Clone();
		Time1Ch[2][j] = (TH1D*)(TimeDist3Ch[j])->Clone();
		Time1Ch[3][j] = (TH1D*)(TimeDist4Ch[j])->Clone();
		for(int i=0;i<4;i++)
		{
			TimeInt1Ch[i][j] = new TH1D(Form("TimeInt1%dCh%d",i,j),Form("TimeInt1%dCh%d",i,j),160,0,160);
			TimeInt1Ch[i][j]->GetXaxis()->SetTitle("drift time[ns]");
			TimeInt1Ch[i][j]->GetYaxis()->SetTitle("drift length[mm]");

		}
	}
	TimeInt1[0] -> SetTitle("BDC X");
	TimeInt1[1] -> SetTitle("BDC X'");
	TimeInt1[2] -> SetTitle("BDC X");
	TimeInt1[3] -> SetTitle("BDC X'");


	TimeInt2[0] -> SetTitle("BDC Y");
	TimeInt2[1] -> SetTitle("BDC Y'");
	TimeInt2[2] -> SetTitle("BDC Y");
	TimeInt2[3] -> SetTitle("BDC Y'");


	double dl = 2.5; //drift length
	double factor1[4]={0.};
	double factor2[4]={0.};
	for(int i=0;i<4;i++)
	{
		factor1[i] = Time1[i]->Integral();
		factor2[i] = Time2[i]->Integral();
		for(int nbin=1;nbin<160;nbin++)
		{
			double num1=0;
			double num2=0;
			num1 = dl*(Time1[i]->Integral(1,nbin)/factor1[i]);
			num2 = dl*(Time2[i]->Integral(1,nbin)/factor2[i]);
			if(num1 > 2.5) num1 = 2.5;
			if(num2 > 2.5) num2 = 2.5;
			//cout<<"X : "<<nbin<<", num1 : "<<num1<<endl;
			//cout<<"Y : "<<nbin<<", num2 : "<<num2<<endl;
			//TimeInt1[i]->SetBinContent(nbin,num1);
			TimeInt2[i]->SetBinContent(nbin,num2);
		}
	}

	double factorch=0.0;
	for(int i=0;i<4;i++){
		for(int j=0;j<64;j++){
			factorch=Time1Ch[i][j]->Integral(0);
			for(int nbin=1;nbin<160;nbin++) {
				double num=0;
				num=dl*(Time1Ch[i][j]->Integral(1,nbin)/factorch);
				if(num>2.5) num = 2.5;
				TimeInt1Ch[i][j]->SetBinContent(nbin,num);
			}
		}
	}

	TCanvas* canch = new TCanvas("canch","canch",800,800);
	canch->cd();
	/*
	for(int j=0;j<32;j++) {
	TimeInt1Ch[0][j]->Draw("HIST");
		TimeInt1Ch[1][j]->Draw("same HIST");
		TimeInt1Ch[2][j]->Draw("same HIST");
		TimeInt1Ch[3][j]->Draw("same HIST");
		canch->SaveAs(Form("plot_time_dist_X_Ch%d.png",j));
	}
*/
	for(int j=0;j<31;j++) {
			TimeInt1Ch[0][j]->SetLineColor(kRed+2);
		TimeInt1Ch[1][j]->SetLineColor(kBlue+2);
		TimeInt1Ch[2][j]->SetLineColor(kOrange+2);
		TimeInt1Ch[3][j]->SetLineColor(kGreen+2);
		TimeInt1Ch[0][j]->Draw("HIST");
		TimeInt1Ch[1][j+1]->Draw("same HIST");
		TimeInt1Ch[2][j]->Draw("same HIST");
		TimeInt1Ch[3][j]->Draw("same HIST");
		canch->SaveAs(Form("plot_time_dist_X_X1Ch%dline.png",j));
	}

	TH1D* difTimeCH13vsCH15 = new TH1D("difTimeCH13vsCH15",";drift time(ns);drift time(CH X - CH 15)",80,0,80);
	TH1D* difTimeCH14vsCH15 = new TH1D("difTimeCH14vsCH15",";drift time(ns);drift time(CH X - CH 15)",80,0,80);
	TH1D* difTimeCH16vsCH15 = new TH1D("difTimeCH16vsCH15",";drift time(ns);drift time(CH X - CH 15)",80,0,80);
	TH1D* difTimeCH17vsCH15 = new TH1D("difTimeCH17vsCH15",";drift time(ns);drift time(CH X - CH 15)",80,0,80);


	for (int i=0;i<80;i++) {
		difTimeCH13vsCH15->SetBinContent(i+1,(TimeInt1Ch[0][13]->GetBinContent(i+1)-TimeInt1Ch[0][15]->GetBinContent(i+1)));
		difTimeCH14vsCH15->SetBinContent(i+1,(TimeInt1Ch[0][14]->GetBinContent(i+1)-TimeInt1Ch[0][15]->GetBinContent(i+1)));
		difTimeCH16vsCH15->SetBinContent(i+1,(TimeInt1Ch[0][16]->GetBinContent(i+1)-TimeInt1Ch[0][15]->GetBinContent(i+1)));
		difTimeCH17vsCH15->SetBinContent(i+1,(TimeInt1Ch[0][17]->GetBinContent(i+1)-TimeInt1Ch[0][15]->GetBinContent(i+1)));
	}

	difTimeCH13vsCH15->SetLineColor(kRed);
	difTimeCH14vsCH15->SetLineColor(kOrange);
	difTimeCH16vsCH15->SetLineColor(kTeal);
	difTimeCH17vsCH15->SetLineColor(kAzure);

	difTimeCH13vsCH15->GetYaxis()->SetRangeUser(-0.5,0.5);

	difTimeCH13vsCH15->Draw("HIST");
	difTimeCH14vsCH15->Draw("same HIST");
	difTimeCH16vsCH15->Draw("same HIST");
	difTimeCH17vsCH15->Draw("same HIST");
	canch->SaveAs("plot_time_dist_X_X1Ch15Dif.png");

	TimeInt1[0]=(TH1D*)TimeInt1Ch[0][15]->Clone();
	TimeInt1[1]=(TH1D*)TimeInt1Ch[1][16]->Clone();
	TimeInt1[2]=(TH1D*)TimeInt1Ch[2][15]->Clone();
	TimeInt1[3]=(TH1D*)TimeInt1Ch[3][15]->Clone();

	TimeInt1[0]->SetName("TimeInt01");
	TimeInt1[1]->SetName("TimeInt11");
	TimeInt1[2]->SetName("TimeInt21");
	TimeInt1[3]->SetName("TimeInt31");





	TimeInt1[0] -> SetTitle("BDC X");
	TimeInt1[1] -> SetTitle("BDC X'");
	TimeInt1[2] -> SetTitle("BDC X");
	TimeInt1[3] -> SetTitle("BDC X'");




	TCanvas* can = new TCanvas("can","can",1200,1200);
	can->Divide(2,2);
	for(int i=0;i<4;i++)
	{
		can->cd(i+1);
		TimeInt1[i]->Draw("HIST");
	}

	can->SaveAs("plot_time_dist_X.png");

	for(int i=0;i<4;i++)
	{
		can->cd(i+1);
		TimeInt2[i]->Draw("HIST");
	}

	can->SaveAs("plot_time_dist_Y.png");

	TCanvas* can2 = new TCanvas("can2","can2",800,800);
	can2->cd();
	TimeInt1[0]->SetLineColor(kRed+2);
	TimeInt1[1]->SetLineColor(kBlue+2);
	TimeInt1[2]->SetLineColor(kOrange+2);
	TimeInt1[3]->SetLineColor(kGreen+2);

	TimeInt2[0]->SetLineColor(kRed+2);
	TimeInt2[1]->SetLineColor(kBlue+2);
	TimeInt2[2]->SetLineColor(kOrange+2);
	TimeInt2[3]->SetLineColor(kGreen+2);


	auto legend1 = new TLegend(0.1,0.7,0.28,0.9);
	//legend->SetHeader("RunAll","C");
	legend1->AddEntry(TimeInt1[0],"BDC X","l");
	legend1->AddEntry(TimeInt1[1],"BDC X'","l");
	legend1->AddEntry(TimeInt1[2],"BDC X","l");
	legend1->AddEntry(TimeInt1[3],"BDC X'","l");

	for(int i=0;i<4;i++)
	{
		if (i==0) TimeInt1[i]->Draw("HIST");
		else TimeInt1[i]->Draw("HIST SAME");
	}
	legend1->Draw();

	can2->SaveAs("plot_time_comp_X.png");


	auto legend2 = new TLegend(0.1,0.7,0.28,0.9);
	//legend->SetHeader("RunAll","C");
	legend2->AddEntry(TimeInt2[0],"BDC Y","l");
	legend2->AddEntry(TimeInt2[1],"BDC Y'","l");
	legend2->AddEntry(TimeInt2[2],"BDC Y","l");
	legend2->AddEntry(TimeInt2[3],"BDC Y'","l");

	for(int i =0;i<4;i++)
	{
		if (i==0) TimeInt2[i]->Draw("HIST");
		else TimeInt2[i]->Draw("HIST SAME");
	}
	legend2->Draw();

	can2->SaveAs("plot_time_comp_Y.png");


	for(int i =0;i<4;i++)
	{
		TimeInt1[i]->Write();
		TimeInt2[i]->Write();
	}
	sfile->Close();

}
