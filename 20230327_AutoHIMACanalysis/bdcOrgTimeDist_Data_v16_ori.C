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

//void bdcOrgTimeDist_Data_v16_ori(TString loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int minip=-1, int maxip=10, TString rmk="3067"){
//void bdcOrgTimeDist_Data_v16_ori(TString loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int minip=-1, int maxip=10, string rmk="3067"){
//void bdcOrgTimeDist_Data_v16_ori(TString loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data", int minip=-1, int maxip=10, int RunNumber=3067){
void bdcOrgTimeDist_Data_v16_ori(int locano=2, int minip=-1, int maxip=10, int runopt=1, int RunNumber=3067){

	TString loca;
	if (locano==1) loca="~/Research_2023/202302HIMACBeamTest/AllData/1_Proton100MeV/Data"; 
	else if (locano==2) loca="~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data"; 


	//int RunNumber = stoi(rmk);
	std::cout << RunNumber << std::endl;
	TFile *itf1 = new TFile(Form("%s/%d_ASD16.root",loca.Data(),RunNumber),"READ");
	TFile *itf2 = new TFile(Form("%s/%d_ASD18.root",loca.Data(),RunNumber),"READ");
	TFile *itf3 = new TFile(Form("%s/%d_ASD17.root",loca.Data(),RunNumber),"READ");
	TFile *itf4 = new TFile(Form("%s/%d_ASD18.root",loca.Data(),RunNumber),"READ");

	TTree* itr1 = (TTree*)itf1->Get("DataTree");
	TTree* itr2 = (TTree*)itf2->Get("DataTree");
	TTree* itr3 = (TTree*)itf3->Get("DataTree");
	TTree* itr4 = (TTree*)itf4->Get("DataTree");

	std::cout << "itr1->GetEntries() : " << itr1->GetEntries() << std::endl;
	std::cout << "itr2->GetEntries() : " << itr2->GetEntries() << std::endl;
	std::cout << "itr3->GetEntries() : " << itr3->GetEntries() << std::endl;
	std::cout << "itr4->GetEntries() : " << itr4->GetEntries() << std::endl;

	cout<<"check"<<endl;

	UShort_t id1;
	UShort_t trigTime1;
	Int_t    DataLength1;  
	UShort_t Data1[228000];

	itr1->SetBranchAddress("id"       ,&id1       );
	itr1->SetBranchAddress("trigTime" ,&trigTime1 );
	itr1->SetBranchAddress("DataLength",&DataLength1);
	itr1->SetBranchAddress("Data"      ,Data1       );

	UShort_t id2;
	UShort_t trigTime2;
	Int_t    DataLength2;
	UShort_t Data2[228000];

	itr2->SetBranchAddress("id"       ,&id2       );
	itr2->SetBranchAddress("trigTime" ,&trigTime2 );
	itr2->SetBranchAddress("DataLength",&DataLength2);
	itr2->SetBranchAddress("Data"      ,Data2       );

	UShort_t id3;
	UShort_t trigTime3;
	Int_t    DataLength3;
	UShort_t Data3[228000];

	itr3->SetBranchAddress("id"       ,&id3       );
	itr3->SetBranchAddress("trigTime" ,&trigTime3 );
	itr3->SetBranchAddress("DataLength",&DataLength3 );
	itr3->SetBranchAddress("Data"      ,Data3       );

	UShort_t id4;
	UShort_t trigTime4;
	Int_t    DataLength4;
	UShort_t Data4[228000];

	itr4->SetBranchAddress("id"       ,&id4       );
	itr4->SetBranchAddress("trigTime" ,&trigTime4 );
	itr4->SetBranchAddress("DataLength",&DataLength4 );
	itr4->SetBranchAddress("Data"      ,Data4       );

	int minevt = 0;
/*
	//	int minip = 0;
	//	int maxip = 10;
	//Carbon 200 MeV
	minip = 2;//3
	maxip = 8;

	//Proton 100 MeV, 3067
	minip = 1;//3
	maxip = 6;

	//default
	minip=-1;
	maxip=10;
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

	//0
	diftime1 = 0;
	diftime2 = 0;
	diftime3 = 0;
	diftime4 = 0;

	/*
	//1950
	diftime1 = 1890;
	diftime2 = 1890;
	diftime3 = 1890;
	diftime4 = 1890;
	 */

	// Basic histogram
	/*
	   TH1D* TimeDist1 = new TH1D("TimeDist1" ,"TimeDist1;time;Hit",150,0,300);
	   TH1D* TimeDist2 = new TH1D("TimeDist2" ,"TimeDist2;time;Hit",150,0,300);
	   TH1D* TimeDist3 = new TH1D("TimeDist3" ,"TimeDist3;time;Hit",150,0,300);
	   TH1D* TimeDist4 = new TH1D("TimeDist4" ,"TimeDist4;time;Hit",150,0,300);

	   TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time;Hit",150,0,300);
	   TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time;Hit",150,0,300);
	   TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time;Hit",150,0,300);
	   TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time;Hit",150,0,300);

	   TH1D* TimeDist12 = new TH1D("TimeDist12" ,"TimeDist1;time;Hit",150,0,300);
	   TH1D* TimeDist22 = new TH1D("TimeDist22" ,"TimeDist2;time;Hit",150,0,300);
	   TH1D* TimeDist32 = new TH1D("TimeDist32" ,"TimeDist3;time;Hit",150,0,300);
	   TH1D* TimeDist42 = new TH1D("TimeDist42" ,"TimeDist4;time;Hit",150,0,300);
	 */

	TH1D* TimeDist1 = new TH1D("TimeDist1" ,"TimeDist1;time;Hit",400,1800,2200);
	TH1D* TimeDist2 = new TH1D("TimeDist2" ,"TimeDist2;time;Hit",400,1800,2200);
	TH1D* TimeDist3 = new TH1D("TimeDist3" ,"TimeDist3;time;Hit",400,1800,2200);
	TH1D* TimeDist4 = new TH1D("TimeDist4" ,"TimeDist4;time;Hit",400,1800,2200);

	TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time;Hit",400,1800,2200);
	TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time;Hit",400,1800,2200);
	TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time;Hit",400,1800,2200);
	TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time;Hit",400,1800,2200);

	TH1D* TimeDist12 = new TH1D("TimeDist12" ,"TimeDist1;time;Hit",400,1800,2200);
	TH1D* TimeDist22 = new TH1D("TimeDist22" ,"TimeDist2;time;Hit",400,1800,2200);
	TH1D* TimeDist32 = new TH1D("TimeDist32" ,"TimeDist3;time;Hit",400,1800,2200);
	TH1D* TimeDist42 = new TH1D("TimeDist42" ,"TimeDist4;time;Hit",400,1800,2200);

/*
	TH1D* TimeDist1 = new TH1D("TimeDist1" ,"TimeDist1;time;Hit",32768,0,32768);
	TH1D* TimeDist2 = new TH1D("TimeDist2" ,"TimeDist2;time;Hit",32768,0,32768);
	TH1D* TimeDist3 = new TH1D("TimeDist3" ,"TimeDist3;time;Hit",32768,0,32768);
	TH1D* TimeDist4 = new TH1D("TimeDist4" ,"TimeDist4;time;Hit",32768,0,32768);

	TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time;Hit",32768,0,32768);
	TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time;Hit",32768,0,32768);
	TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time;Hit",32768,0,32768);
	TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time;Hit",32768,0,32768);

	TH1D* TimeDist12 = new TH1D("TimeDist12" ,"TimeDist1;time;Hit",32768,0,32768);
	TH1D* TimeDist22 = new TH1D("TimeDist22" ,"TimeDist2;time;Hit",32768,0,32768);
	TH1D* TimeDist32 = new TH1D("TimeDist32" ,"TimeDist3;time;Hit",32768,0,32768);
	TH1D* TimeDist42 = new TH1D("TimeDist42" ,"TimeDist4;time;Hit",32768,0,32768);
*/

	int maxevt = itr4->GetEntries();

	TFile *outfile = new TFile("tTimeTree_BDC_Run_Cosmic_CNU_1430_Org_v16_ori.root","RECREATE");
	TTree *bdcTree = new TTree("bdcTree","BDC Data Tree");
	const int nArr = 20000;
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
		//for( int ievt = minevt; ievt < 10000; ievt++){

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
						//double time = Data2[ip*128+64+ich]&0x7FFF;
						if (time<0) time+=32768;
						if(ich < 32) { 
							if(Data2[ip*128+64+ich] > 0 ) {
								//firedch2_1[cnt2_1] = 31-ich;
								firedch2_1[cnt2_1] = ich;
								Ch1Y1[cnt2_1] = firedch2_1[cnt2_1];
								time2_1[cnt2_1] = time - diftime1;
								DT1Y1[cnt2_1] = time2_1[cnt2_1];
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
								if(time2_2[cnt2_2] > 160) DL1Y2[cnt2_2] = 2.5;
								cout<<"Ch : "<<firedch2_2[cnt2_2]<<", DT1Y2 : "<<DT1Y2[cnt2_2]<<", DL1Y2 : "<<DL1Y2[cnt2_2]<<endl;
								cnt2_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
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
						//double time = Data3[ip*128+64+ich]&0x7FFF;
						if (time<0) time+=32768;
						// X
						if(ich < 32) { 
							if(Data3[ip*128+64+ich] > 0) {
								firedch3_1[cnt3_1] = 31-ich;
								Ch2X1[cnt3_1] = firedch3_1[cnt3_1];
								//firedch3_1[cnt3_1] = ich;
								time3_1[cnt3_1] = time - diftime3;
								DT2X1[cnt3_1] = time3_1[cnt3_1];
								TimeDist3->Fill(DT2X1[cnt3_1]);
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
								TimeDist4->Fill(DT2X2[cnt3_2]);
								cout<<"Ch : "<<firedch3_2[cnt3_2]<<", DT2X2 : "<<DT2X2[cnt3_2]<<", DL2X2 : "<<DL2X2[cnt3_2]<<endl;
								cnt3_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
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
						//double time = Data4[ip*128+64+ich]&0x7FFF;
						if (time<0) time+=32768;
						// Y 
						if(ich < 32) { 
							if(Data4[ip*128+64+ich] > 0) {
								//firedch4_1[cnt4_1] = 31-ich;
								firedch4_1[cnt4_1] = ich;
								Ch2Y1[cnt4_1] = firedch4_1[cnt4_1];
								time4_1[cnt4_1] = time - diftime3;
								DT2Y1[cnt4_1] = time4_1[cnt4_1];
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
								cout<<"Ch : "<<firedch4_2[cnt4_2]<<", DT2Y2 : "<<DT2Y2[cnt4_2]<<", DL2Y2 : "<<DL2Y2[cnt4_2]<<endl;
								cnt4_2++;
							}
						}
					} // QDC cut
				} // ip cut 
			} // ip 
		} // ch
		nY21 = cnt4_1;
		nY22 = cnt4_2;


		cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
		cout<<"nY11 : "<<nY11<<", nY12 : "<<nY12<<", nY21 : "<<nY21<<", nY22 : "<<nY22<<endl;
		//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
		if(nX11 > 0 && nX12 > 0 && nX21 > 0 && nX22 > 0) {
			allfiredEvt++;
			//nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
			//cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;

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

	TCanvas* can = new TCanvas("can","",800,800);
	can->Divide(2,2);
	can->cd();
	can->cd(1);
	TimeDist1->Draw();
	can->cd();
	can->cd(2);
	TimeDist2->Draw();
	can->cd();
	can->cd(3);
	TimeDist3->Draw();
	can->cd();
	can->cd(4);
	TimeDist4->Draw();
	can->cd();
	can->SaveAs("TimeDistAll_ori.png");

	can->cd();
	can->cd(1);
	TimeDist11->Draw();
	can->cd();
	can->cd(2);
	TimeDist21->Draw();
	can->cd();
	can->cd(3);
	TimeDist31->Draw();
	can->cd();
	can->cd(4);
	TimeDist41->Draw();
	can->cd();
	can->SaveAs("TimeDistAll1_ori.png");


	outfile->cd();
	TimeDist1->Write();
	TimeDist2->Write();
	TimeDist3->Write();
	TimeDist4->Write();

	TimeDist11->Write();
	TimeDist21->Write();
	TimeDist31->Write();
	TimeDist41->Write();

	TimeDist12->Write();
	TimeDist22->Write();
	TimeDist32->Write();
	TimeDist42->Write();

	bdcTree->Write();

	outfile->Write();
	outfile->Close();

	}
