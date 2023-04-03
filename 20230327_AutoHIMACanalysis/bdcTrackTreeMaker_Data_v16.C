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
// Data1-v2 : Sejong Setup
//Required files to run : convert_data_SJEXP.root / BDCSJU_(0,1,2,3)_(RUNNUMBER).root Files
//RunNumber list : 520 530 531 532 533 534 550 560 561

const bool MAXQDC = false; //Find MaxQDC Hit which will be used to make reconstrcution track.

//void bdcTrackTreeMaker_Data_v16(TString loc="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int RunNumber=3067){
//void bdcTrackTreeMaker_Data_v16(int locano=2, int minip=-1, int maxip=10, int runopt=0, int RunNumber=3067){
//void bdcTrackTreeMaker_Data_v16(TString loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int minip=-1, int maxip=10, int runopt=1, int RunNumber=3067){
void bdcTrackTreeMaker_Data_v16(int locano=2, int minip=1, int maxip=7, int tdopt=1, int hitopt=1, int chopt=1, int centopt=1, int pedopt=1,  int RunNumber=3067){

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




	TFile *convtime = new TFile("convert_data_CNU_Cosmic_EXP.root","READ");
	int workingHV1 = 1200;//1350
	int workingHV2 = 1200;//1350
	TH1D* convfunc11 = (TH1D*) convtime->Get("TimeInt01");
	TH1D* convfunc12 = (TH1D*) convtime->Get("TimeInt11");
	TH1D* convfunc13 = (TH1D*) convtime->Get("TimeInt21");
	TH1D* convfunc14 = (TH1D*) convtime->Get("TimeInt31");

	TH1D* convfunc21 = (TH1D*) convtime->Get("TimeInt02");
	TH1D* convfunc22 = (TH1D*) convtime->Get("TimeInt12");
	TH1D* convfunc23 = (TH1D*) convtime->Get("TimeInt22");
	TH1D* convfunc24 = (TH1D*) convtime->Get("TimeInt32");


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
	   int minip = 0;
	   int maxip = 10;

	   minip = 1;
	   maxip = 6;

	   minip = -1;
	   maxip = 10;


	//int minip = 3;
	//int maxip = 7; //8;
	 */
	double QDCCUT1 = 370; //300;
	double QDCCUT2 = 290; //300;
	double QDCCUT3 = 290; //300;
	double QDCCUT4 = 290; //300;
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

	// 20230330
	double ped1 = 370;
	double ped2 = 270;
	double ped3 = 270;
	double ped4 = 270;


	//QDCCUT2 = 220;
	double timecut = 150;
	int ngoodtrack = 0;

	double diftime = 0;
	double diftime1 = 193.3;
	double diftime2 = 187.3;
	double diftime3 = 188.8;
	double diftime4 = 185.9;
	//double diftime = 110+70; // delay 180 ns
	/*
	   diftime1 = 185;
	   diftime2 = 183;
	   diftime3 = 184;
	   diftime4 = 183;
	 */

	diftime1 = 1950+60.0;
	diftime2 = 1950+59.1;
	diftime3 = 1950+63.5;
	diftime4 = 1950+54.6;
	//diftime1 = 180;
	//diftime2 = 180;
	//diftime3 = 180;
	//diftime4 = 180;

	diftime1 = 1900+53.2;
	diftime2 = 1900+53.0;
	diftime3 = 1900+62.7;
	diftime4 = 1900+61.0;

	// 3097, Carbon 200 MeV
	diftime1 = 1890+63.2;
	diftime2 = 1890+62.3;
	diftime3 = 1890+72.8;
	diftime4 = 1890+71.7;

	// Carbon 200 MeV, run 3067
	diftime1 = 1890+97.5;
	diftime2 = 1890+96.9;
	diftime3 = 1890+107.5;
	diftime4 = 1890+106.0;

	// Carbon 200 MeV, run 3067, no cut, v20230315
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


	// Basic histogram
	//  TH2D* hisTDC1 = new TH2D("hisTDC1","hisTDC;time;ch",128,0,128,64,0,64);
	TH2D* hisQDC1 = new TH2D("hisQDC1","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh1= new TH3D("hisQDCCh1","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit1 = new TH1D("hisTDCHit1" ,"hisTDCHit;channel;Hit",64,0,64);
	//  TH2D* hisTDC2 = new TH2D("hisTDC2","hisTDC;time;ch",128,0,128,64,0,64);
	TH2D* hisQDC2 = new TH2D("hisQDC2","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh2= new TH3D("hisQDCCh2","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit2 = new TH1D("hisTDCHit2" ,"hisTDCHit;channel;Hit",64,0,64);
	//  TH2D* hisTDC3 = new TH2D("hisTDC3","hisTDC;time;ch",128,0,128,64,0,64);
	TH2D* hisQDC3 = new TH2D("hisQDC3","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh3= new TH3D("hisQDCCh3","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit3 = new TH1D("hisTDCHit3" ,"hisTDCHit;channel;Hit",64,0,64);
	//  TH2D* hisTDC4 = new TH2D("hisTDC4","hisTDC;time;ch",128,0,128,64,0,64);
	TH2D* hisQDC4 = new TH2D("hisQDC4","hisQDC;time;QCD",128,0,128,1000,0,1000);
	TH3D* hisQDCCh4= new TH3D("hisQDCCh4","Ch;time;QDC",128,0,128,1000,0,1000,64,0,64);
	TH1D* hisTDCHit4 = new TH1D("hisTDCHit4" ,"hisTDCHit;channel;Hit",64,0,64);

	TH1D* TimeDist1 = new TH1D("TimeDist1" ,"TimeDist1;time;Hit",200,0,200);
	TH1D* TimeDist2 = new TH1D("TimeDist2" ,"TimeDist2;time;Hit",200,0,200);
	TH1D* TimeDist3 = new TH1D("TimeDist3" ,"TimeDist3;time;Hit",200,0,200);
	TH1D* TimeDist4 = new TH1D("TimeDist4" ,"TimeDist4;time;Hit",200,0,200);

	TH1D* TimeSum11 = new TH1D("TimeSum11" ,"TimeSum11;time (ns);Counts",75,0,150);
	TH1D* TimeSum21 = new TH1D("TimeSum21" ,"TimeSum21;time (ns);Counts",75,0,150);
	TH1D* TimeSum31 = new TH1D("TimeSum31" ,"TimeSum31;time (ns);Counts",75,0,150);
	TH1D* TimeSum41 = new TH1D("TimeSum41" ,"TimeSum41;time (ns);Counts",75,0,150);


	TH1D* TimeSum12 = new TH1D("TimeSum12" ,"TimeSum12;time (ns);Counts",75,0,150);
	TH1D* TimeSum22 = new TH1D("TimeSum22" ,"TimeSum22;time (ns);Counts",75,0,150);
	TH1D* TimeSum32 = new TH1D("TimeSum32" ,"TimeSum32;time (ns);Counts",75,0,150);
	TH1D* TimeSum42 = new TH1D("TimeSum42" ,"TimeSum42;time (ns);Counts",75,0,150);

	TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time (ns);Counts",300,0,300);
	TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time (ns);Counts",300,0,300);
	TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time (ns);Counts",300,0,300);
	TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time (ns);Counts",300,0,300);

	TH1D* TimeMax11 = new TH1D("TimeMax11",";time;Counts",500,0,500);
	TH1D* TimeMax21 = new TH1D("TimeMax21",";time;Counts",500,0,500);
	TH1D* DriftVel11 = new TH1D("DriftVel11",";time;Counts",50,0,150);
	TH1D* DriftVel21 = new TH1D("DriftVel21",";time;Counts",50,0,150);
	/*
	   TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",30,-20,100,30,-20,100);
	   TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",30,-20,100,30,-20,100);
	   TH2D* TimeCorr31 = new TH2D("TimeCorr31",";time;time",30,-20,100,30,-20,100); // time2 vs time3


	   TH2D* TimeCorrR11 = new TH2D("TimeCorrR11",";time;time",30,0,120,30,0,120);
	   TH2D* TimeCorrR21 = new TH2D("TimeCorrR21",";time;time",30,0,120,30,0,120);
	   TH2D* TimeCorrR31 = new TH2D("TimeCorrR31",";time;time",30,0,120,30,0,120); // time2 vs time3


	   TH2D* TimeCorrR12 = new TH2D("TimeCorrR12",";time;time",30,0,120,30,0,120);
	   TH2D* TimeCorrR22 = new TH2D("TimeCorrR22",";time;time",30,0,120,30,0,120);
	   TH2D* TimeCorrR32 = new TH2D("TimeCorrR32",";time;time",30,0,120,30,0,120); // time2 vs time3
	 */
	/*
	   TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",120,-20,100,120,-20,100);
	   TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",120,-20,100,120,-20,100);
	   TH2D* TimeCorr31 = new TH2D("TimeCorr31",";time;time",120,-20,100,120,-20,100); // time2 vs time3


	   TH2D* TimeCorrR11 = new TH2D("TimeCorrR11",";time;time",120,0,120,120,0,120);
	   TH2D* TimeCorrR21 = new TH2D("TimeCorrR21",";time;time",120,0,120,120,0,120);
	   TH2D* TimeCorrR31 = new TH2D("TimeCorrR31",";time;time",120,0,120,120,0,120); // time2 vs time3


	   TH2D* TimeCorrR12 = new TH2D("TimeCorrR12",";time;time",120,0,120,120,0,120);
	   TH2D* TimeCorrR22 = new TH2D("TimeCorrR22",";time;time",120,0,120,120,0,120);
	   TH2D* TimeCorrR32 = new TH2D("TimeCorrR32",";time;time",120,0,120,120,0,120); // time2 vs time3
	 */

	TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorr31 = new TH2D("TimeCorr31",";time;time",100,0,100,100,0,100); // time2 vs time3


	TH2D* TimeCorrR11 = new TH2D("TimeCorrR11",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorrR21 = new TH2D("TimeCorrR21",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorrR31 = new TH2D("TimeCorrR31",";time;time",100,0,100,100,0,100); // time2 vs time3


	TH2D* TimeCorrR12 = new TH2D("TimeCorrR12",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorrR22 = new TH2D("TimeCorrR22",";time;time",100,0,100,100,0,100);
	TH2D* TimeCorrR32 = new TH2D("TimeCorrR32",";time;time",100,0,100,100,0,100); // time2 vs time3

	/*
	   TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorr31 = new TH2D("TimeCorr31",";time;time",300,0,300,300,0,300); // time2 vs time3


	   TH2D* TimeCorrR11 = new TH2D("TimeCorrR11",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorrR21 = new TH2D("TimeCorrR21",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorrR31 = new TH2D("TimeCorrR31",";time;time",300,0,300,300,0,300); // time2 vs time3


	   TH2D* TimeCorrR12 = new TH2D("TimeCorrR12",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorrR22 = new TH2D("TimeCorrR22",";time;time",300,0,300,300,0,300);
	   TH2D* TimeCorrR32 = new TH2D("TimeCorrR32",";time;time",300,0,300,300,0,300); // time2 vs time3
	 */


	TH1D* TimeMult1 = new TH1D("TimeMult1",";time1 * time2;Counts",900,0,9000);

	TH2D* hChCorr1 = new TH2D("hChCorr11",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr2 = new TH2D("hChCorr21",";Y;Y'",32,0,32,32,0,32);
	TH2D* hChCorr3 = new TH2D("hChCorr31",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr4 = new TH2D("hChCorr41",";Y;Y'",32,0,32,32,0,32);

	TH1D* TimeDist12 = new TH1D("TimeDist12" ,"TimeDist1;time (ns);Counts",300,0,300);
	TH1D* TimeDist22 = new TH1D("TimeDist22" ,"TimeDist2;time (ns);Counts",300,0,300);
	TH1D* TimeDist32 = new TH1D("TimeDist32" ,"TimeDist3;time (ns);Counts",300,0,300);
	TH1D* TimeDist42 = new TH1D("TimeDist42" ,"TimeDist4;time (ns);Counts",300,0,300);

	TH1D* TimeMax12 = new TH1D("TimeMax12",";time;Counts",500,0,500);
	TH1D* TimeMax22 = new TH1D("TimeMax22",";time;Counts",500,0,500);
	TH1D* DriftVel12 = new TH1D("DriftVel12",";time;Counts",50,0,150);
	TH1D* DriftVel22 = new TH1D("DriftVel22",";time;Counts",50,0,150);
	/*
	   TH2D* TimeCorr12 = new TH2D("TimeCorr12",";time;time",30,-20,100,30,-20,100);
	   TH2D* TimeCorr22 = new TH2D("TimeCorr22",";time;time",30,-20,100,30,-20,100);
	   TH2D* TimeCorr32 = new TH2D("TimeCorr32",";time;time",30,-20,100,30,-20,100); // time2 vs time3
	 */
	TH2D* TimeCorr12 = new TH2D("TimeCorr12",";time;time",120,-20,100,120,-20,100);
	TH2D* TimeCorr22 = new TH2D("TimeCorr22",";time;time",120,-20,100,120,-20,100);
	TH2D* TimeCorr32 = new TH2D("TimeCorr32",";time;time",120,-20,100,120,-20,100); // time2 vs time3

	TH2D* hChCorr12 = new TH2D("hChCorr12",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr22 = new TH2D("hChCorr22",";Y;Y'",32,0,32,32,0,32);
	TH2D* hChCorr32 = new TH2D("hChCorr32",";X;X'",32,0,32,32,0,32);
	TH2D* hChCorr42 = new TH2D("hChCorr42",";Y;Y'",32,0,32,32,0,32);

	TH1D* hChDist1 = new TH1D("hChDist1",";Ch at X1;Entries;",32,0,32);
	TH1D* hChDist2 = new TH1D("hChDist2",";Ch at X1';Entries;",32,0,32);
	TH1D* hChDist3 = new TH1D("hChDist3",";Ch at X2;Entries;",32,0,32);
	TH1D* hChDist4 = new TH1D("hChDist4",";Ch at X2';Entries;",32,0,32);

	TH1D* hDT1X1Ch[32];
	TH1D* hDT1X2Ch[32];
	TH1D* hDT2X1Ch[32];
	TH1D* hDT2X2Ch[32];

	for (int i=0;i<32;i++) {
		hDT1X1Ch[i] = new TH1D(Form("hDT1X1Ch_%d",i),Form("hDT1X1Ch_%d;time (ns);Entries",i),300,0,300);
		hDT1X2Ch[i] = new TH1D(Form("hDT1X2Ch_%d",i),Form("hDT1X2Ch_%d;time (ns);Entries",i),300,0,300);
		hDT2X1Ch[i] = new TH1D(Form("hDT2X1Ch_%d",i),Form("hDT2X1Ch_%d;time (ns);Entries",i),300,0,300);
		hDT2X2Ch[i] = new TH1D(Form("hDT2X2Ch_%d",i),Form("hDT2X2Ch_%d;time (ns);Entries",i),300,0,300);
	}    

	int maxevt = itr1->GetEntries();
	//TFile *outfile = new TFile(Form("bdcTrackInfo_Run_%d_convertdata_v14.root",RunNumber),"RECREATE");
	TFile *outfile = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v16.root","RECREATE");


	// TFile *outfile = new TFile("bdcTrackInfo_Data_Sejong_Cosmic_evt1000_20210616.root","RECREATE");
	outfile->cd();

	TTree *bdcTree = new TTree("bdcTree","BDC Data Tree");
	const int nArr = 2000;//20000
						  //const int nArr = itr2->GetEntries();

	int numEvt = 0;
	int nX11 = 0, nX12 = 0, nX21 = 0, nX22 = 0; // number of 2 D hits
	int nY11 = 0, nY12 = 0, nY21 = 0, nY22 = 0; // number of 2 D hits
	int Ch1X1[nArr] = {-1}, Ch1X2[nArr] = {-1}, Ch1Y1[nArr] = {-1}, Ch1Y2[nArr] = {-1}; // fired channel x, y at chamber 1
	int Ch2X1[nArr] = {-1}, Ch2X2[nArr] = {-1}, Ch2Y1[nArr] = {-1}, Ch2Y2[nArr] = {-1}; // fired channel x, y at chamber 2
	double DL1X1[nArr] = {0}, DL1X2[nArr] = {0}, DL1Y1[nArr] = {0}, DL1Y2[nArr] = {0}; // drift time at chamber 1
	double DL2X1[nArr] = {0}, DL2X2[nArr] = {0}, DL2Y1[nArr] = {0}, DL2Y2[nArr] = {0}; // drift time at chamber 2
	double DT1X1[nArr] = {0}, DT1X2[nArr] = {0}, DT1Y1[nArr] = {0}, DT1Y2[nArr] = {0}; // drift time at chamber 1
	double DT2X1[nArr] = {0}, DT2X2[nArr] = {0}, DT2Y1[nArr] = {0}, DT2Y2[nArr] = {0}; // drift time at chamber 2

	double QD1X1[nArr] = {0}, QD1X2[nArr] = {0}, QD2X1[nArr] = {0}, QD2X2[nArr] = {0}; // QDC at X1, X1', X2, X2'


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

	bdcTree->Branch("QD1X1",&QD1X1,"QD1X1[nX11]/D");
	bdcTree->Branch("QD1X2",&QD1X2,"QD1X2[nX12]/D");
	bdcTree->Branch("QD2X1",&QD2X1,"QD2X1[nX21]/D");
	bdcTree->Branch("QD2X2",&QD2X2,"QD2X2[nX22]/D");

	//maxevt = 20;

	int allfiredEvt = 0;
	int allfiredEvt2 = 0;
	int allfiredEvt3 = 0;
	int allfiredEvt4 = 0;
	int threefired = 0;


	int sumevt=0;

	for( int ievt = minevt; ievt < maxevt; ievt++){


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
		//itr1->GetEntry(ievt+dif1[ievt]);
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
		for( int ich = 0; ich < 64; ich++){
			//			if (ich<2 || (ich>29 && ich<34) || ich>61) continue; 
			bool isTDC=false;
			for( int ip = 0; ip < nPoints1; ip++){
				if(ip>minip && ip<maxip){
					//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
					double tmpQDC=Data1[ip*128+ich];
					unsigned short ftt1
						= ((trigTime1 & 0xFF00 ) >> 8 )
						+ ((trigTime1 & 0x007F ) << 8 );
					if (tmpQDC > QDCCUT1){
						double time = 4000+(-ftt1+(Data1[ip*128+64+ich]&0x7FFF));
						if ((time-4000)>0) time-=32768;
						if (tdopt==2) {time = (ftt1-(Data1[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;}
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
								DL1X1[cnt1_1] = convfunc11->GetBinContent(convfunc11->FindBin(time1_1[cnt1_1]));
								TimeDist1->Fill(DT1X1[cnt1_1]);
								cout<<"Ch : "<<firedch1_1[cnt1_1]<<", DT1X1 : "<<DT1X1[cnt1_1]<<", DL1X1 : "<<DL1X1[cnt1_1]<<endl;
								cnt1_1++;
								isTDC=true;
							}
						}
						if(ich >= 32 ) { 
							if(Data1[ip*128+64+ich] > 0) {
								firedch1_2[cnt1_2] = ich-32;
								//firedch1_2[cnt1_2] = 63-ich;
								Ch1X2[cnt1_2] = firedch1_2[cnt1_2];
								time1_2[cnt1_2] = time - diftime2;
								//std::cout << time1_2[cnt1_2] << std::endl;
								DL1X2[cnt1_2] = convfunc12->GetBinContent(convfunc12->FindBin(time1_2[cnt1_2]));
								//  std::cout << "OK?" << ip << " - " << ich << std::endl;
								DT1X2[cnt1_2] = time1_2[cnt1_2];
								TimeDist2->Fill(DT1X2[cnt1_2]);
								cout<<"Ch : "<<firedch1_2[cnt1_2]<<", DT1X2 : "<<DT1X2[cnt1_2]<<", DL1X2 : "<<DL1X2[cnt1_2]<<endl;
								cnt1_2++;
								isTDC=true;
							}
						}
					} // QCD cut
				} // ip cut
			} // ip 
			if (isTDC) {
				int cc=0;
				if (ich<32) cc=cnt1_1-1;
				if (ich>=32) cc=cnt1_2-1;
				if (ievt<5) std::cout << "--- ievt : " << ievt << " - ich : " << ich << " -----" << cc << std::endl;
				for (int ip=minip+1;ip<maxip;ip++) {
					double corQDC=Data1[ip*128+ich];
					if (pedopt==2) corQDC=Data1[ip*128+ich]-ped1;
					else if (pedopt==1) {
						if (Data1[ip*128+64+ich]>0) corQDC=Data1[ip*128+ich];
						else corQDC=0;
					}
					if (ich<32) {
						if (ip==minip+1) QD1X1[cc]=corQDC;
						else QD1X1[cc] += corQDC;
						if (ievt<5) std::cout << corQDC << " - " << QD1X1[cc] << std::endl;}
					if (ich>=32) {
						if (ip==minip+1) QD1X2[cc]=corQDC;
						else QD1X2[cc]+= corQDC;
						if (ievt<5) std::cout << corQDC << " - " << QD1X2[cc] << std::endl;}
				}
			}

		}// ch
		hChCorr1->Fill(Ch1X1[0],Ch1X2[0]);
		//hChCorr1->Fill(Ch1X1[cnt1_1],Ch1X2[cnt1_2]);
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
		for( int ich = 0; ich < 64; ich++){
			for( int ip = 0; ip < nPoints2; ip++){
				if(ip>minip && ip<maxip){
					//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
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
								firedch2_1[cnt2_1] = ich;
								Ch1Y1[cnt2_1] = firedch2_1[cnt2_1];
								time2_1[cnt2_1] = time - diftime1;
								DL1Y1[cnt2_1] = convfunc21->GetBinContent(convfunc21->FindBin(time2_1[cnt2_1]));
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
								DL1Y2[cnt2_2] = convfunc22->GetBinContent(convfunc22->FindBin(time2_2[cnt2_2]));
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
		  //hChCorr2->Fill(Ch1Y1[cnt2_1],Ch1Y2[cnt2_2]);
		hChCorr2->Fill(Ch1Y1[0],Ch1Y2[0]);
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
		for( int ich = 0; ich < 64; ich++){
			//				if (ich<2 || (ich>29 && ich<34) || ich>61) continue; 
			bool isTDC=false;
			for( int ip = 0; ip < nPoints3; ip++){
				if(ip>minip && ip<maxip){
					//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
					double tmpQDC=Data3[ip*128+ich];
					unsigned short ftt3
						= ((trigTime3 & 0xFF00 ) >> 8 )
						+ ((trigTime3 & 0x007F ) << 8 );

					if (tmpQDC > QDCCUT3){
						double time = 4000+(-ftt3+(Data3[ip*128+64+ich]&0x7FFF));
						if ((time-4000)>0) time-=32768;
						if (tdopt==2) {time = (ftt3-(Data3[ip*128+64+ich]&0x7FFF));
						if (time<0) time+=32768;}


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
								DL2X1[cnt3_1] = convfunc13->GetBinContent(convfunc13->FindBin(time3_1[cnt3_1]));
								DT2X1[cnt3_1] = time3_1[cnt3_1];
								//TimeDist3->Fill(DT2X1[cnt3_1]);
								if(time3_1[cnt3_1] > 160) DL2X1[cnt3_1] = 2.5;
								cout<<"Ch : "<<firedch3_1[cnt3_1]<<", DT2X1 : "<<DT2X1[cnt3_1]<<", DL2X1 : "<<DL2X1[cnt3_1]<<endl;
								cnt3_1++;
								isTDC=true;
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
								DL2X2[cnt3_2] = convfunc23->GetBinContent(convfunc23->FindBin(time3_2[cnt3_2]));
								DT2X2[cnt3_2] = time3_2[cnt3_2];
								//TimeDist3->Fill(DT2X2[cnt3_2]);
								if(time3_2[cnt3_2] > 160) DL2X2[cnt3_2] = 2.5;
								cout<<"Ch : "<<firedch3_2[cnt3_2]<<", DT2X2 : "<<DT2X2[cnt3_2]<<", DL2X2 : "<<DL2X2[cnt3_2]<<endl;
								cnt3_2++;
								isTDC=true;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
			/*
			   for (int icnt31=0;icnt31<cnt3_1;icnt31++) {
			   for (int ip =0;ip<nPoints3;ip++) {
			   double corQDC=Data3[ip*128+(31-Ch2X1[icnt31])]-ped3;
			   QD2X1[icnt31] += corQDC;
			   }//ip
			   }//icnt31
			   for (int icnt32=0;icnt32<cnt3_2;icnt32++) {
			   for (int ip =0;ip<nPoints3;ip++) {
			   double corQDC=Data3[ip*128+(63-Ch2X2[icnt32])]-ped3;
			   QD2X2[icnt32] += corQDC;
			   }//ip
			   }//icnt32
			 */
			if (isTDC) {
				int cc=0;
				if (ich<32) cc=cnt3_1-1;
				if (ich>=32) cc=cnt3_2-1;
				if (ievt<5) std::cout << "--- ievt : " << ievt << " - ich : " << ich << " -----" << cc << std::endl;
				for (int ip=minip+1;ip<maxip;ip++) {
					double corQDC=Data3[ip*128+ich];
					if (pedopt==2) corQDC=Data3[ip*128+ich]-ped3;
					else if (pedopt==1) {
						if (Data3[ip*128+64+ich]>0) corQDC=Data3[ip*128+ich];
						else corQDC=0;
					}
					if (ich<32) {
						if (ip==minip+1) QD2X1[cc]=corQDC;
						else QD2X1[cc] += corQDC;
						if (ievt<5) std::cout << corQDC << " - " << QD2X1[cc] << std::endl;}
					if (ich>=32) {
						if (ip==minip+1) QD2X2[cc]=corQDC;
						else QD2X2[cc]+= corQDC;
						if (ievt<5) std::cout << corQDC << " - " << QD2X2[cc] << std::endl;}
				}
			}


		} // ch
		hChCorr3->Fill(Ch2X1[0],Ch2X2[0]);
		//hChCorr3->Fill(Ch2X1[cnt3_1],Ch2X2[cnt3_2]);
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
			if(ip>minip && ip<maxip){
				for( int ich = 0; ich < 64; ich++){
					//if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
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
								DL2Y1[cnt4_1] = convfunc14->GetBinContent(convfunc14->FindBin(time4_1[cnt4_1]));
								DT2Y1[cnt4_1] = time4_1[cnt4_1];
								//TimeDist4->Fill(DT2Y1[cnt4_1]);
								if(time4_1[cnt4_1] > 160) DL2Y1[cnt4_1] = 2.5;
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
								DL2Y2[cnt4_2] = convfunc24->GetBinContent(convfunc24->FindBin(time4_2[cnt4_2]));
								DT2Y2[cnt4_2] = time4_2[cnt4_2];
								//TimeDist4->Fill(DT2Y2[cnt4_2]);
								if(time4_2[cnt4_2] > 160) DL2Y2[cnt4_2] = 2.5;
								cout<<"Ch : "<<firedch4_2[cnt4_2]<<", DT2Y2 : "<<DT2Y2[cnt4_2]<<", DL2Y2 : "<<DL2Y2[cnt4_2]<<endl;
								cnt4_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
		hChCorr4->Fill(Ch2Y1[0],Ch2Y2[0]);
		//hChCorr4->Fill(Ch2Y1[cnt4_1],Ch2Y2[cnt4_2]);
		nY21 = cnt4_1;
		nY22 = cnt4_2;

		cout<<"Before filling up, nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;

		int threefired1 = 0;
		int threefired2 = 0;
		int threefired3 = 0;
		int threefired4 = 0;
		if(nX11 > 0 && nX12 > 0 && nX21 > 0 && nX22 == 0) {
			threefired1++;
		}
		if(nX11 == 0 && nX12 > 0 && nX21 > 0 && nX22 > 0) {
			threefired2++;
		}
		if(nX11 > 0 && nX12 == 0 && nX21 > 0 && nX22 > 0) {
			threefired3++;
		}
		if(nX11 > 0 && nX12 > 0 && nX21 == 0 && nX22 > 0) {
			threefired4++;
		}

		cout<<"threefired1 : "<<threefired1<<", threefired2 : "<<threefired2<<", threefired3 : "<<threefired3<<", threefired4 : "<<threefired4<<endl;
		if(threefired1 > 0 || threefired2 > 0 || threefired3 > 0 || threefired4 > 0) threefired++;


		//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
		if(nX11 > 0 && nX12 > 0 && nX21 > 0 && nX22 > 0) {
			allfiredEvt++;
			//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
			//cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
			//if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;
			if (hitopt==1) {if (!(nX11==1 && nX12==1 && nX21==1 && nX22==1)) continue;}
			if (chopt==1) {
				int datadiff1 = Ch1X2[0]-Ch1X1[0];
				int datadiff2 = Ch2X2[0]-Ch2X1[0];
				int datadiff3 = Ch2X1[0]-Ch1X2[0];
				if (!(datadiff1==1 || datadiff1==0)) continue;
				if (!(datadiff2==0 || datadiff2==-1)) continue;
				if (!(datadiff3==0 || datadiff3==-1)) continue;
			}
			if (centopt==2) {
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
							//###if(time1 > 90 || time2 > 90 || time3 > 90 || time4 > 90) continue;
							//if(time1 > 80 || time2 > 80 || time3 > 80 || time4 > 80) continue;

							double tmax1 = time1 + time2;
							double tmax2 = time3 + time4;
							double tmax3 = time2 + time3;
							//if(tmax1>100) continue;
							//if(tmax1<50) continue;
							//if(tmax2>100) continue;
							//if(tmax2<50) continue;
							TimeDist11->Fill(time1);
							TimeDist21->Fill(time2);
							TimeDist31->Fill(time3);
							TimeDist41->Fill(time4);
							TimeCorr11->Fill(time1,time2);
							TimeCorr21->Fill(time3,time4);
							TimeCorr31->Fill(time2,time3);
							TimeSum11->Fill(time1+time2);
							TimeSum21->Fill(time3+time4);
							TimeSum31->Fill(time2+time3);
							TimeMax11->Fill((time1+time3)/2+time2);
							TimeMax21->Fill((time2+time4)/2+time3);
							TimeMult1->Fill(time1*time2);

							double time11 = time1*1/sqrt(2) + time2*1/sqrt(2);
							double time21 = -time1*1/sqrt(2) + time2*1/sqrt(2);
							double time31 = time3*1/sqrt(2) + time4*1/sqrt(2);
							double time41 = -time3*1/sqrt(2) + time4*1/sqrt(2);
							TimeCorrR11->Fill(time11,time21+60);
							TimeCorrR21->Fill(time31,time41+60);
							TimeCorrR31->Fill(time2*1/sqrt(2)+time3*1/sqrt(2),-time2*1/sqrt(2)+time3*1/sqrt(2)+60);
							hDT1X1Ch[Ch1X1[i]]->Fill(time1);
							hDT1X2Ch[Ch1X2[j]]->Fill(time2);
							hDT2X1Ch[Ch2X1[k]]->Fill(time3);
							hDT2X2Ch[Ch2X2[l]]->Fill(time4);

							hChDist1->Fill(Ch1X1[i]);
							hChDist2->Fill(Ch1X2[j]);
							hChDist3->Fill(Ch2X1[k]);
							hChDist4->Fill(Ch2X2[l]);
							std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
							/*
							   double time11 = time1*1/sqrt(2);
							   double time21 = time2*1/sqrt(2);
							   double time31 = time3*1/sqrt(2);
							   double time41 = time4*1/sqrt(2);

							   TimeCorrR11->Fill(time11+time21,-time11+time21+85);
							   TimeCorrR21->Fill(time31+time41,-time31+time41+85);
							 */
							DriftVel11->Fill(2.5/((time1+time3)/2+time2)*1000.0);
							DriftVel21->Fill(2.5/((time2+time4)/2+time3)*1000.0);
							allfiredEvt2++;
						}
					}
				}
			}
		}

		/*
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
		double tmax1 = time1 + time2;
		double tmax2 = time3 + time4;
		//if(tmax1>100) continue;
		//if(tmax1<50) continue;
		//if(tmax2>100) continue;
		//if(tmax2<50) continue;
		TimeDist12->Fill(time1);
		TimeDist22->Fill(time2);
		TimeDist32->Fill(time3);
		TimeDist42->Fill(time4);
		TimeCorr12->Fill(time1,time2);
		TimeCorr22->Fill(time3,time4);
		TimeCorr32->Fill(time2,time3);
		TimeSum12->Fill(time1+time2);
		TimeSum22->Fill(time2+time3);
		TimeSum32->Fill(time3+time4);
		TimeMax12->Fill((time1+time3)/2+time2);
		TimeMax22->Fill((time2+time4)/2+time3);
		double time11 = time1*1/sqrt(2) + time2*1/sqrt(2);
		double time21 = -time1*1/sqrt(2) + time2*1/sqrt(2);
		double time31 = time3*1/sqrt(2) + time4*1/sqrt(2);
		double time41 = -time3*1/sqrt(2) + time4*1/sqrt(2);
		TimeCorrR12->Fill(time11,time21+60);
		TimeCorrR22->Fill(time31,time41+60);
		DriftVel12->Fill(2.5/((time1+time3)/2+time2)*1000.0);
		DriftVel22->Fill(2.5/((time2+time4)/2+time3)*1000.0);
		allfiredEvt4++;
		}
		}
		}
		}
		}
		 */

		cout<<"After nX11 : "<<nX11<<" nX12 : "<<nX12<<" nX21 : "<<nX21<<" nX22 : "<<nX22<<endl;
		cout<<"After nY11 : "<<nY11<<" nY12 : "<<nY12<<" nY21 : "<<nY21<<" nY22 : "<<nY22<<endl;

		bdcTree->Fill();
		sumevt++;


	}

	std::cout << "--- Sum of initial data : " << maxevt-minevt <<std::endl;
	std::cout << "------ Sum of events filled : " << sumevt << std::endl;

	cout<<" Number of events with all fired layers at X : "<<allfiredEvt<<endl;
	cout<<" Number of events with all 3 layers at X : "<<threefired<<endl;
	cout<<" Number of events firing 3 and 4 layers at X : "<<threefired+allfiredEvt<<endl;
	cout<<" Number of events with all fired layers with positive time at X : "<<allfiredEvt2<<endl;

	cout<<" Number of events with all fired layers at Y : "<<allfiredEvt3<<endl;
	cout<<" Number of events with all fired layers with positive time at Y: "<<allfiredEvt4<<endl;

    gROOT->Macro("~/rootlogon.C");
    //gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);

    TimeDist11->SetLineColor(kBlue+1);
	TimeDist21->SetLineColor(kRed+1);
    TimeDist31->SetLineColor(kViolet+1);
    TimeDist41->SetLineColor(kOrange+5);

    TimeDist11->SetMarkerColor(kBlue+1);
    TimeDist21->SetMarkerColor(kRed+1);
    TimeDist31->SetMarkerColor(kViolet+1);
    TimeDist41->SetMarkerColor(kOrange+5);

    TimeDist11->SetMarkerStyle(20);
    TimeDist21->SetMarkerStyle(24);
    TimeDist31->SetMarkerStyle(25);
    TimeDist41->SetMarkerStyle(32);

    //auto lg1 = new TLegend(0.23,0.35,0.53,0.55);
    auto lg1 = new TLegend(0.61,0.48,0.91,0.68);
    lg1->SetBorderSize(0);
    lg1->SetMargin(0.2);
    lg1->AddEntry(TimeDist11,"X1","lp");
    lg1->AddEntry(TimeDist21,"X1'","lp");
    lg1->AddEntry(TimeDist31,"X2","lp");
    lg1->AddEntry(TimeDist41,"X2'","lp");


    TCanvas *c1 = new TCanvas("c1","",880, 800);
    c1->cd();
    TimeDist11->Draw("HIST E");
    TimeDist21->Draw("HIST E same");
    TimeDist31->Draw("HIST E same");
    TimeDist41->Draw("HIST E same");

    lg1->Draw("same");

    c1->SaveAs("plot_time_distributions_aftert0cor.png");

	//outfile->cd();
	//bdcTree->Write();

	TimeMult1->Write();

	TimeDist1->Write();
	TimeDist2->Write();
	TimeDist3->Write();
	TimeDist4->Write();

	TimeSum11->Write();
	TimeSum21->Write();
	TimeSum31->Write();

	TimeSum12->Write();
	TimeSum22->Write();
	TimeSum32->Write();

	TimeDist11->Write();
	TimeDist21->Write();
	TimeDist31->Write();
	TimeDist41->Write();

	TimeMax11->Write();
	TimeMax21->Write();

	DriftVel11->Write();
	DriftVel21->Write();

	TimeCorr11->Write();
	TimeCorr21->Write();
	TimeCorr31->Write();

	TimeCorrR11->Write();
	TimeCorrR21->Write();
	TimeCorrR31->Write();


	TimeDist12->Write();
	TimeDist22->Write();
	TimeDist32->Write();
	TimeDist42->Write();

	TimeMax12->Write();
	TimeMax22->Write();

	DriftVel12->Write();
	DriftVel22->Write();

	TimeCorr12->Write();
	TimeCorr22->Write();
	TimeCorr32->Write();

	TimeCorrR12->Write();
	TimeCorrR22->Write();
	TimeCorrR32->Write();


	hChCorr1->Write();
	hChCorr2->Write();
	hChCorr3->Write();
	hChCorr4->Write();

	hisQDC1->Write();
	hisQDCCh1->Write();
	hisTDCHit1->Write();
	hisQDC2->Write();
	hisQDCCh2->Write();
	hisTDCHit2->Write();
	hisQDC3->Write();
	hisQDCCh3->Write();
	hisTDCHit3->Write();
	hisQDC4->Write();
	hisQDCCh4->Write();
	hisTDCHit4->Write();

	hChDist1->Write();
	hChDist2->Write();
	hChDist3->Write();
	hChDist4->Write();

	for (int i=0;i<32;i++) {
		hDT1X1Ch[i]->Write();
		hDT1X2Ch[i]->Write();
		hDT2X1Ch[i]->Write();
		hDT2X2Ch[i]->Write();
	}

	outfile->Write();
	outfile->Close();
	//cout<<"RunNumber : "<<RunNumber<<endl;

}
