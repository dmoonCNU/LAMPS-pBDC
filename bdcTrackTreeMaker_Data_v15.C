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

const bool MAXQDC = false; //Find MaxQDC Hit which will be used to make reconstrcution track.

void bdcTrackTreeMaker_Data_v15(int RunNumber = 561){

  //int RunNumber = 360;

  TFile* itf1 = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD16.root","READ"); // X1-X1'
  TFile* itf2 = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD17.root","READ"); // Y1-Y1'
  TFile* itf3 = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD18.root","READ"); // X2-X2'
  TFile* itf4 = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD19.root","READ"); // Y2-Y2'
  

  TTree* itr1 = (TTree*)itf1->Get("DataTree");
  TTree* itr2 = (TTree*)itf2->Get("DataTree");
  TTree* itr3 = (TTree*)itf3->Get("DataTree");
  TTree* itr4 = (TTree*)itf4->Get("DataTree");

  std::cout << "itr1->GetEntries() : " << itr1->GetEntries() << std::endl;
  std::cout << "itr2->GetEntries() : " << itr2->GetEntries() << std::endl;
  std::cout << "itr3->GetEntries() : " << itr3->GetEntries() << std::endl;
  std::cout << "itr4->GetEntries() : " << itr4->GetEntries() << std::endl;




  TFile *convtime = new TFile("convert_data_CNU_Cosmic_EXP.root","READ");
  int workingHV1 = 1410;
  int workingHV2 = 1410;
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
  UShort_t Data1[128000];
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
  //int minip = 0;
  //int maxip = 100;
  int minip = 3;
  int maxip = 8;
  double QDCCUT1 = 370; //300;
  double QDCCUT2 = 290; //300;
  QDCCUT1 = 360;
  QDCCUT2 = 300;
  QDCCUT1 = 300;
  QDCCUT2 = 300;
  //QDCCUT2 = 220;
  double timecut = 150;
  int ngoodtrack = 0;

  //double diftime = 110+60; // delay 180 ns
  double diftime = 110+70; // delay 180 ns
  //double diftime = 110+60;
  //double diftime = 90+80;


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


  TH1D* TimeDist11 = new TH1D("TimeDist11" ,"TimeDist1;time (ns);Counts",300,0,300);
  TH1D* TimeDist21 = new TH1D("TimeDist21" ,"TimeDist2;time (ns);Counts",300,0,300);
  TH1D* TimeDist31 = new TH1D("TimeDist31" ,"TimeDist3;time (ns);Counts",300,0,300);
  TH1D* TimeDist41 = new TH1D("TimeDist41" ,"TimeDist4;time (ns);Counts",300,0,300);

  TH1D* TimeMax11 = new TH1D("TimeMax11",";time;Counts",500,0,500);
  TH1D* TimeMax21 = new TH1D("TimeMax21",";time;Counts",500,0,500);
  TH1D* DriftVel11 = new TH1D("DriftVel11",";time;Counts",50,0,150);
  TH1D* DriftVel21 = new TH1D("DriftVel21",";time;Counts",50,0,150);

  TH2D* TimeCorr11 = new TH2D("TimeCorr11",";time;time",25,0,100,25,0,100);
  TH2D* TimeCorr21 = new TH2D("TimeCorr21",";time;time",25,0,100,25,0,100);


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

  TH2D* TimeCorr12 = new TH2D("TimeCorr12",";time;time",25,0,100,25,0,100);
  TH2D* TimeCorr22 = new TH2D("TimeCorr22",";time;time",25,0,100,25,0,100);


  TH2D* hChCorr12 = new TH2D("hChCorr12",";X;X'",32,0,32,32,0,32);
  TH2D* hChCorr22 = new TH2D("hChCorr22",";Y;Y'",32,0,32,32,0,32);
  TH2D* hChCorr32 = new TH2D("hChCorr32",";X;X'",32,0,32,32,0,32);
  TH2D* hChCorr42 = new TH2D("hChCorr42",";Y;Y'",32,0,32,32,0,32);


  int maxevt = itr4->GetEntries();
  //TFile *outfile = new TFile(Form("bdcTrackInfo_Run_%d_convertdata_v14.root",RunNumber),"RECREATE");
  TFile *outfile = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v14.root","RECREATE");


  // TFile *outfile = new TFile("bdcTrackInfo_Data_Sejong_Cosmic_evt1000_20210616.root","RECREATE");
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


  int EvtTime1=0;
  int EvtTime2=0;
  int EvtTime3=0;
  int EvtTime4=0;
  double dur_sec1=0.;
  double dur_sec2=0.;
  double dur_sec3=0.;
  double dur_sec4=0.;

  int EvtTimeDif1=0;
  int EvtTimeDif2=0;
  int EvtTimeDif3=0;
  int EvtTimeDif4=0;
  double dur_secDif1=0.;
  double dur_secDif2=0.;
  double dur_secDif3=0.;
  double dur_secDif4=0.;

  int EvtTag1=0;
  int EvtTag2=0;
  int EvtTag3=0;
  int EvtTag4=0;


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

  bdcTree->Branch("EvtTime1",&EvtTime1,"EvtTime1/I");
  bdcTree->Branch("EvtTime2",&EvtTime2,"EvtTime2/I");
  bdcTree->Branch("EvtTime3",&EvtTime3,"EvtTime3/I");
  bdcTree->Branch("EvtTime4",&EvtTime4,"EvtTime4/I");
  bdcTree->Branch("dur_sec1",&dur_sec1,"dur_sec1/D");
  bdcTree->Branch("dur_sec2",&dur_sec2,"dur_sec2/D");
  bdcTree->Branch("dur_sec3",&dur_sec3,"dur_sec3/D");
  bdcTree->Branch("dur_sec4",&dur_sec4,"dur_sec4/D");

  bdcTree->Branch("EvtTimeDif1",&EvtTimeDif1,"EvtTimeDif1/I");
  bdcTree->Branch("EvtTimeDif2",&EvtTimeDif2,"EvtTimeDif2/I");
  bdcTree->Branch("EvtTimeDif3",&EvtTimeDif3,"EvtTimeDif3/I");
  bdcTree->Branch("EvtTimeDif4",&EvtTimeDif4,"EvtTimeDif4/I");
  bdcTree->Branch("dur_secDif1",&dur_secDif1,"dur_secDif1/D");
  bdcTree->Branch("dur_secDif2",&dur_secDif2,"dur_secDif2/D");
  bdcTree->Branch("dur_secDif3",&dur_secDif3,"dur_secDif3/D");
  bdcTree->Branch("dur_secDif4",&dur_secDif4,"dur_secDif4/D");

  bdcTree->Branch("EvtTag1",&EvtTag1,"EvtTag1/I");
  bdcTree->Branch("EvtTag2",&EvtTag2,"EvtTag2/I");
  bdcTree->Branch("EvtTag3",&EvtTag3,"EvtTag3/I");
  bdcTree->Branch("EvtTag4",&EvtTag4,"EvtTag4/I");

  //maxevt = 20;

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
  int threefired = 0;

  for( int i = 0; i < itr4->GetEntries(); i++){
    itr1->GetEntry(i+inv1);
    itr2->GetEntry(i+inv2);
    itr3->GetEntry(i+inv3);
    itr4->GetEntry(i+inv4);
    ds1[i]=dur_defsec1;
    ds2[i]=dur_defsec2;
    ds3[i]=dur_defsec3;
    ds4[i]=dur_defsec4;

    if (fabs(dur_defsec2-dur_defsec4)>0.1){
      //std::cout << i << " - " << dur_defsec << " , " << dur_defsec2 << " , " << dur_defsec3 << " , " << dur_defsec4 << std::endl;
      inv1=inv1+1;
      inv2=inv2+1;
      itr1->GetEntry(i+inv1);
      itr2->GetEntry(i+inv2);
      ds1[i]+=dur_defsec1;
      ds2[i]+=dur_defsec2;
    }
    dif1[i]=inv1;
    dif2[i]=inv2;
    dif3[i]=inv3;
    dif4[i]=inv4;
    //cout<<"dhmoon chk 000 Event : "<<i<<", inv1 : "<<inv1<<" inv2 : "<<inv2<<" inv3 : "<<inv3<<" inv4 : "<<inv4<<endl;
  }

  int day1_ini=0;
  int hour1_ini=0;
  int min1_ini=0;
  int sec1_ini=0;

  int day2_ini=0;
  int hour2_ini=0;
  int min2_ini=0;
  int sec2_ini=0;

  int day3_ini=0;
  int hour3_ini=0;
  int min3_ini=0;
  int sec3_ini=0;

  int day4_ini=0;
  int hour4_ini=0;
  int min4_ini=0;
  int sec4_ini=0;

  int ievtpre = minevt;
  int sumevt=0;
  for( int ievt = minevt; ievt < maxevt; ievt++){
    EvtTag1=0;
    EvtTag2=0;
    EvtTag3=0;
    EvtTag4=0;

    cout<<"### Events : "<<ievt<<" ###"<<endl;
    int isspark1=0;
    itr1->GetEntry(ievt+dif1[ievt]);
    if (ievt==minevt) {
      day1_ini=day1;hour1_ini=hour1;min1_ini=min1;sec1_ini=sec1;
      std::cout << "### 1 : " << day1_ini << " (Day) " << hour1_ini << " (h) " << min1_ini << " (m) " << sec1_ini << " (s) " << std::endl;
    }
    Int_t ipspark;
    ipspark= DataLength1 / 128;
    isspark1=0;
    for( int ich = 0; ich < 64; ich++){
      //f(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
      for( int ip = 0; ip < ipspark; ip++){
        if (Data1[ip*128+64+ich] > 0) isspark1++;
      }
    }
    //###if (isspark1>10) continue;
    if (isspark1>10) EvtTag1+=2;

    itr2->GetEntry(ievt+dif2[ievt]);
    if (ievt==minevt) {
      day2_ini=day2;hour2_ini=hour2;min2_ini=min2;sec2_ini=sec2;
      std::cout << "### 2 : " << day2_ini << " (Day) " << hour2_ini << " (h) " << min2_ini << " (m) " << sec2_ini << " (s) " << std::endl;
    }
    ipspark= DataLength2 / 128;
    int isspark2=0;
    for( int ich = 0; ich < 64; ich++){
      //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
      for( int ip = 0; ip < ipspark; ip++){
        if (Data2[ip*128+64+ich] > 0) isspark2++;
      }
    }
    //###if (isspark2>10) continue;
    if (isspark2>10) EvtTag2+=2;

    itr3->GetEntry(ievt+dif3[ievt]);
    if (ievt==minevt) {
      day3_ini=day3;hour3_ini=hour3;min3_ini=min3;sec3_ini=sec3;
      std::cout << "### 3 : " << day3_ini << " (Day) " << hour3_ini << " (h) " << min3_ini << " (m) " << sec3_ini << " (s) " << std::endl;
    }

    ipspark= DataLength3 / 128;
    int isspark3=0;
    for( int ich = 0; ich < 64; ich++){
      //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
      for( int ip = 0; ip < ipspark; ip++){
        if (Data3[ip*128+64+ich] > 0) isspark3++;
      }
    }
    //###if (isspark3>10) continue;
    if (isspark3>10) EvtTag3+=2;

    itr4->GetEntry(ievt+dif4[ievt]);
    if (ievt==minevt) {
      day4_ini=day4;hour4_ini=hour4;min4_ini=min4;sec4_ini=sec4;
      std::cout << "### 4 : " << day4_ini << " (Day) " << hour4_ini << " (h) " << min4_ini << " (m) " << sec4_ini << " (s) " << std::endl;
    }

    ipspark= DataLength4 / 128;
    int isspark4=0;
    for( int ich = 0; ich < 64; ich++){
      //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
      for( int ip = 0; ip < ipspark; ip++){
        if (Data4[ip*128+64+ich] > 0) isspark4++;
      }
    }
    //###if (isspark4>10) continue;
    if (isspark4>10) EvtTag4+=2;

    dur_sec1=0.0;
    dur_sec2=0.0;
    dur_sec3=0.0;
    dur_sec4=0.0;

    for(int v=ievtpre+1;v<=ievt;v++) {
      //std::cout << "v: " << v << " " << ds1[v] << " " << ds2[v] << " " << ds3[v] << " " << ds4[v] << std::endl;
      dur_sec1+=ds1[v];
      dur_sec2+=ds2[v];
      dur_sec3+=ds3[v];
      dur_sec4+=ds4[v];
    }
    //std::cout << "### ievt : " << ievt << " " << dur_sec1 << " " << dur_sec2 << " " << dur_sec3 << " " << dur_sec4 << std::endl;
    if (ievt!=minevt) {
      dur_secDif1+=dur_sec1;
      dur_secDif2+=dur_sec2;
      dur_secDif3+=dur_sec3;
      dur_secDif4+=dur_sec4;
    }

    EvtTag1=0;
    EvtTag2=0;
    EvtTag3=0;
    EvtTag4=0;



    ievtpre=ievt;



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
    EvtTime1 = day1*1e6 + hour1*1e4 + min1*1e2 + sec1;
    EvtTimeDif1 = (day1-day1_ini)*24*60*60 + (hour1-hour1_ini)*60*60 + (min1-min1_ini)*60 + (sec1-sec1_ini);
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
    if (EvtTag1!=2) {
      for( int ich = 0; ich < 64; ich++){
        //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
        for( int ip = 0; ip < nPoints1; ip++){
          if(ip>minip && ip<maxip){
            double tmpQDC=Data1[ip*128+ich];
            unsigned short ftt1
              = ((trigTime1 & 0xFF00 ) >> 8 )
              + ((trigTime1 & 0x007F ) << 8 );

            if (tmpQDC > QDCCUT1){
              double time = (ftt1-(Data1[ip*128+64+ich]&0x7FFF));
              hisQDCCh1->Fill(ip,tmpQDC,ich);
              hisQDC1->Fill(ip,tmpQDC);
              if(Data1[ip*128+64+ich] > 0) hisTDCHit1->Fill(ich);
              if(ich < 32 ) { 
                if(Data1[ip*128+64+ich] > 0) {
                  //firedch1_1[cnt1_1] = ich;
                  firedch1_1[cnt1_1] = 31-ich;
                  Ch1X1[cnt1_1] = firedch1_1[cnt1_1];
                  time1_1[cnt1_1] = time-diftime;
                  DT1X1[cnt1_1] = time1_1[cnt1_1];
                  DL1X1[cnt1_1] = convfunc11->GetBinContent(convfunc11->FindBin(time1_1[cnt1_1]));
                  TimeDist1->Fill(DT1X1[cnt1_1]);
                  cout<<"Ch : "<<firedch1_1[cnt1_1]<<", DT1X1 : "<<DT1X1[cnt1_1]<<", DL1X1 : "<<DL1X1[cnt1_1]<<endl;
                  cnt1_1++;
                }
              }
              if(ich >= 32 ) { 
                if(Data1[ip*128+64+ich] > 0) {
                  time = time - diftime;
                  //firedch1_2[cnt1_2] = ich-32;
                  firedch1_2[cnt1_2] = 63-ich;
                  Ch1X2[cnt1_2] = firedch1_2[cnt1_2];
                  time1_2[cnt1_2] = time;
                  DL1X2[cnt1_2] = convfunc12->GetBinContent(convfunc12->FindBin(time1_2[cnt1_2]));
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
      //hChCorr1->Fill(Ch1X1[cnt1_1],Ch1X2[cnt1_2]);
    }
    nX11 = cnt1_1;
    nX12 = cnt1_2;

    ///////////////////// Chamber1-YY' /////////////////////////////////////
    // Chamber 18 Y11-Y12
    //cout<< "ASD 18 Y11-Y12"<<endl;
    itr2->GetEntry(ievt);
    //itr2->GetEntry(ievt+dif2[ievt]);
    EvtTime2 = day2*1e6 + hour2*1e4 + min2*1e2 + sec2;
    EvtTimeDif2 = (day2-day2_ini)*24*60*60 + (hour2-hour2_ini)*60*60 + (min2-min2_ini)*60 + (sec2-sec2_ini);
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
    if (EvtTag2!=2) {
      for( int ich = 0; ich < 64; ich++){
        //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
        for( int ip = 0; ip < nPoints2; ip++){
          if(ip>minip && ip<maxip){
            double tmpQDC=Data2[ip*128+ich];
            unsigned short ftt2
              = ((trigTime2 & 0xFF00 ) >> 8 )
              + ((trigTime2 & 0x007F ) << 8 );

            if (tmpQDC > QDCCUT1){
              double time = (ftt2 - (Data2[ip*128+64+ich]&0x7FFF));
              //hisTDC2->Fill(ip,ich,fabs(time));
              hisQDCCh2->Fill(ip,tmpQDC,ich);
              hisQDC2->Fill(ip,tmpQDC);
              if(Data2[ip*128+64+ich] > 0) hisTDCHit2->Fill(ich);
              if(ich < 32) { 
                time = time - diftime;
                if(Data2[ip*128+64+ich] > 0 ) {
                  firedch2_1[cnt2_1] = 31-ich;
                  Ch1Y1[cnt2_1] = firedch2_1[cnt2_1];
                  time2_1[cnt2_1] = time;
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
                  time = time - diftime;
                  firedch2_2[cnt2_2] = 63-ich;
                  Ch1Y2[cnt2_2] = firedch2_2[cnt2_2];
                  time2_2[cnt2_2] = time;
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
    }
    nY11 = cnt2_1;
    nY12 = cnt2_2;

    ///////////////////// Chamber2-XX' /////////////////////////////////////
    //cout<< "ASD 16 X21-X22"<<endl;
    itr3->GetEntry(ievt);
    //itr3->GetEntry(ievt+dif3[ievt]);
    EvtTime3 = day3*1e6 + hour3*1e4 + min3*1e2 + sec3;
    EvtTimeDif3 = (day3-day3_ini)*24*60*60 + (hour3-hour3_ini)*60*60 + (min3-min3_ini)*60 + (sec3-sec3_ini);
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
    if (EvtTag3!=2) {
      for( int ich = 0; ich < 64; ich++){
        //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
        for( int ip = 0; ip < nPoints3; ip++){
          if(ip>minip && ip<maxip){
            double tmpQDC=Data3[ip*128+ich];
            unsigned short ftt3
              = ((trigTime3 & 0xFF00 ) >> 8 )
              + ((trigTime3 & 0x007F ) << 8 );

            if (tmpQDC > QDCCUT2){
              double time = (ftt3 - (Data3[ip*128+64+ich]&0x7FFF));
              //hisTDC3->Fill(ip,ich,fabs(time));
              hisQDCCh3->Fill(ip,tmpQDC,ich);
              hisQDC3->Fill(ip,tmpQDC);
              if(Data3[ip*128+64+ich] > 0) hisTDCHit3->Fill(ich);
              // X
              if(ich < 32) { 
                time = time - diftime;
                if(Data3[ip*128+64+ich] > 0) {
                  firedch3_1[cnt3_1] = 31-ich;
                  Ch2X1[cnt3_1] = firedch3_1[cnt3_1];
                  //firedch3_1[cnt3_1] = ich;
                  time3_1[cnt3_1] = time;
                  DL2X1[cnt3_1] = convfunc13->GetBinContent(convfunc13->FindBin(time3_1[cnt3_1]));
                  DT2X1[cnt3_1] = time3_1[cnt3_1];
                  //TimeDist3->Fill(DT2X1[cnt3_1]);
                  if(time3_1[cnt3_1] > 160) DL2X1[cnt3_1] = 2.5;
                  cout<<"Ch : "<<firedch3_1[cnt3_1]<<", DT2X1 : "<<DT2X1[cnt3_1]<<", DL2X1 : "<<DL2X1[cnt3_1]<<endl;
                  cnt3_1++;
                }
              }
              // X'
              if(ich >= 32) { 
                //time = time-mintime3_2;
                time = time - diftime;
                if(Data3[ip*128+64+ich] > 0) {
                  //	if(mintime3_2>time) mintime3_2 = time;
                  firedch3_2[cnt3_2] = 63-ich;
                  Ch2X2[cnt3_2] = firedch3_2[cnt3_2];
                  time3_2[cnt3_2] = time;
                  DL2X2[cnt3_2] = convfunc23->GetBinContent(convfunc23->FindBin(time3_2[cnt3_2]));
                  DT2X2[cnt3_2] = time3_2[cnt3_2];
                  //TimeDist3->Fill(DT2X2[cnt3_2]);
                  if(time3_2[cnt3_2] > 160) DL2X2[cnt3_2] = 2.5;
                  cout<<"Ch : "<<firedch3_2[cnt3_2]<<", DT2X2 : "<<DT2X2[cnt3_2]<<", DL2X2 : "<<DL2X2[cnt3_2]<<endl;
                  cnt3_2++;
                }
              }
            } // QDC cut
          } // ip cut 
        } // ip 
      } // ch
      hChCorr3->Fill(Ch2X1[0],Ch2X2[0]);
      //hChCorr3->Fill(Ch2X1[cnt3_1],Ch2X2[cnt3_2]);
    }
    nX21 = cnt3_1;
    nX22 = cnt3_2;

    ///////////////////// Chamber2-YY' /////////////////////////////////////
    //cout<< "ASD 18 Y21-Y22"<<endl;
    itr4->GetEntry(ievt);
    //itr4->GetEntry(ievt+dif4[ievt]);
    EvtTime4 = day4*1e6 + hour4*1e4 + min4*1e2 + sec4;
    EvtTimeDif4 = (day4-day4_ini)*24*60*60 + (hour4-hour4_ini)*60*60 + (min4-min4_ini)*60 + (sec4-sec4_ini);
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
    if (EvtTag4!=2) {
      for( int ich = 0; ich < 64; ich++){
        //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
        for( int ip = 0; ip < nPoints4; ip++){
          if(ip>minip && ip<maxip){
            double tmpQDC=Data4[ip*128+ich];
            unsigned short ftt4
              = ((trigTime4 & 0xFF00 ) >> 8 )
              + ((trigTime4 & 0x007F ) << 8 ); // trigTime4

            if (tmpQDC > QDCCUT2){
              double time = (ftt4 - (Data4[ip*128+64+ich]&0x7FFF));
              //hisTDC4->Fill(ip,ich,fabs(time));
              hisQDCCh4->Fill(ip,tmpQDC,ich);
              hisQDC4->Fill(ip,tmpQDC);
              if(Data4[ip*128+64+ich] > 0) hisTDCHit4->Fill(ich);
              // Y 
              if(ich < 32) { 
                time = time - diftime;
                if(Data4[ip*128+64+ich] > 0) {
                  firedch4_1[cnt4_1] = 31-ich;
                  Ch2Y1[cnt4_1] = firedch4_1[cnt4_1];
                  time4_1[cnt4_1] = time;
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
                time = time - diftime;
                if(Data4[ip*128+64+ich] > 0) {
                  firedch4_2[cnt4_2] = 63-ich;
                  Ch2Y2[cnt4_2] = firedch4_2[cnt4_2];
                  time4_2[cnt4_2] = time;
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
    }
    nY21 = cnt4_1;
    nY22 = cnt4_2;

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
      nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
      //cout<<"nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
      for(int i = 0; i < nX11; i++){
        for(int j = 0; j < nX12; j++){
          for(int k = 0; k < nX21; k++){
            for(int l = 0; l < nX22; l++){
              double time1 = DT1X1[i];
              double time2 = DT1X2[j];
              double time3 = DT2X1[k];
              double time4 = DT2X2[l];
              if(time1 < 0 || time2 < 0 || time3 < 0 || time4 < 0) continue;
              double tmax1 = time1 + time2;
              double tmax2 = time3 + time4;
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
              TimeMax11->Fill((time1+time3)/2+time2);
              TimeMax21->Fill((time2+time4)/2+time3);
              DriftVel11->Fill(2.5/((time1+time3)/2+time2)*1000.0);
              DriftVel21->Fill(2.5/((time2+time4)/2+time3)*1000.0);
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
              TimeMax12->Fill((time1+time3)/2+time2);
              TimeMax22->Fill((time2+time4)/2+time3);
              DriftVel12->Fill(2.5/((time1+time3)/2+time2)*1000.0);
              DriftVel22->Fill(2.5/((time2+time4)/2+time3)*1000.0);
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
  cout<<" Number of events with all 3 layers at X : "<<threefired<<endl;
  cout<<" Number of events firing 3 and 4 layers at X : "<<threefired+allfiredEvt<<endl;
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

  TimeMax11->Write();
  TimeMax21->Write();

  DriftVel11->Write();
  DriftVel21->Write();

  TimeCorr11->Write();
  TimeCorr21->Write();


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

  outfile->Write();
  outfile->Close();
  //cout<<"RunNumber : "<<RunNumber<<endl;

}
