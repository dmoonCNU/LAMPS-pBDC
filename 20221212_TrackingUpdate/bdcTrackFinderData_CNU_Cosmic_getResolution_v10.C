#include <TMath.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TBranch.h>
#include <TNtuple.h>
#include <TArc.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
#include <Math/Vector3D.h>
#include <Fit/Fitter.h>

#include <cassert>

// bdcTrackFinderData_CNU_Cosmic_getResolution_v9 : input data track information with real bdc information
// apply the dimension of Sejong Univ experiment
// Only full tracking but X is not corrected yet.

using namespace ROOT::Math;

double pi = TMath::Pi();
double pirad = pi/180;			// angle to radian cos(30) >> cos(30*pirad)
double radpi = 180/pi;			// radian to angle 
double distanceChamber = 10;	//chamber distance
double Xwirestart=0.;			// first signal wire(on X' plane) position (mm)
double Ywirestart=0.;			// first signal wire(on Y' plane) position (mm)
double FLH = 15;				//first layer height

//int RunNumber = 9999; //RunNumber list : 520 530 531 532 533 534 550 560 561 9999 (all)

const bool XTrack = true;
const bool YTrack = true;
const bool fulltracking = true;
const bool getresolution = false;
//const bool savepng = true; 
const bool savepng = false;
int Nmax = 1000;
bool corr_ = true; // cut time correlation
//bool corr_ = false; // cut time correlation
bool angleCut_ = false;

const bool nodrawcan = true;
// define the parametric line equation
void line(double t, const double *p, double &x, double &y) {
  // a parametric line is define from 6 parameters but 4 are independent
  // x0,y0,z0,z1,y1,z1 which are the coordinates of two points on the line
  // can choose z0 = 0 if line not parallel to x-y plane and z1 = 1;
  y = p[0]*t + p[1];
  x = t;
}


bool first = true;

// function Object to be minimized
struct SumDistance2 {
  // the TGraph is a data member of the object
  TGraph *fGraph;

  SumDistance2(TGraph *g) : fGraph(g) {}

  // calculate distance line-point
  double distance2(double x,double y,double z, const double *p) {
    // distance line point is D= | (xp-x0) cross  ux |
    // where ux is direction of line and x0 is a point in the line (like t = 0)
    XYZVector xp(x,y,0);
    XYZVector x0(0.0, p[1], 0. );
    XYZVector x1(1.0, p[0] + p[1], 0 );
    //cout<<"dis :: x : "<<x<<", y : "<<y<<", z : "<<z<<", par0 : "<<p[0]<<", par1 : "<<p[1]<<endl;
    XYZVector u = (x1-x0).Unit();
    //cout<<"dhmoon chk theta xp : "<<tan(xp.Phi())<<endl;
    //cout<<"dhmoon chk theta xp-x0 : "<<tan((xp-x0).Phi())<<endl;
    //cout<<"dhmoon chk theta u : "<<tan(u.Phi())<<endl;
    double d2 = ((xp-x0).Cross(u)).Mag2();
    //cout<<"d2 : "<<d2<<endl;
    return d2;
  }

  // implementation of the function to be minimized
  double operator() (const double *par) {
    assert(fGraph != 0);
    double * x = fGraph->GetX();
    double * y = fGraph->GetY();
    int npoints = fGraph->GetN();
    double sum = 0;
    for (int i  = 0; i < npoints; ++i) {
      double d = distance2(x[i],y[i],0,par);
      //cout<<"x["<<i<<"] : "<<x[i]<<", y["<<i<<"] : "<<y[i]<<endl;
      sum += d;
      //cout<<"d : "<<d<<", par0 : "<<par[0]<<", par1 : "<<par[1]<<endl;
    }
    if (first) {
      std::cout << "Total Initial distance square = " << sum << std::endl;
    }
    first = false;
    return sum;
  }

};


void getLine(double x1, double y1, double x2, double y2, double &a, double &b, double &c);
double dist(double pointX, double pointY, double lineX1, double lineY1, double lineX2, double lineY2);

void trackFinderX2(float dataCh1X1, float dataDl1X1, float dataCh1X2, float dataDl1X2, float dataCh2X1, float dataDl2X1, float dataCh2X2, float dataDl2X2, float dataDt1X1, float dataDt1X2, float dataDt2X1, float dataDt2X2, int ievt, int tracknum, double *pars, double *dts);
void trackFinderY2(float dataCh1Y1, float dataDl1Y1, float dataCh1Y2, float dataDl1Y2, float dataCh2Y1, float dataDl2Y1, float dataCh2Y2, float dataDl2Y2, float dataDt1Y1, float dataDt1Y2, float dataDt2Y1, float dataDt2Y2, int ievt, int tracknum, double *pars, double *dts);

// create Track tree to keep track information, gradient, intersection, event time
// This version is CNU cosmic data analysis on 20221125
void bdcTrackFinderData_CNU_Cosmic_getResolution_v10()
{
  gROOT->Macro("~/rootlogon.C");
  gStyle->SetPadLeftMargin(0.05);
  gStyle->SetTitleYOffset(0.4);
  //gStyle->SetOptFit(0);

  bool onlyx = false; //true;
                      //bool onlyx = true; //false; //true;
  gSystem->mkdir(Form("figs"), kTRUE);
  //int RunNumber = 561; //RunNumber list : 520 530 531 532 533 534 550 560 561

  TFile *data = new TFile("tTrackTree_BDC_Run_Cosmic_CNU_1430_v15.root","READ");

  TTree *myTree = (TTree*) data->Get("bdcTree");

  const int nArr = 3000;
  // Declaration of leaf types
  Int_t           numEvt;
  Int_t           nX11;
  Int_t           nX12;
  Int_t           nX21;
  Int_t           nX22;
  Int_t           nX11_1;
  Int_t           nX11_2;
  Int_t           nX12_1;
  Int_t           nX12_2;
  Int_t           nX21_1;
  Int_t           nX21_2;
  Int_t           nX22_1;
  Int_t           nX22_2;
  Int_t           nY11;
  Int_t           nY12;
  Int_t           nY21;
  Int_t           nY22;
  Int_t           nY11_1;
  Int_t           nY11_2;
  Int_t           nY12_1;
  Int_t           nY12_2;
  Int_t           nY21_1;
  Int_t           nY21_2;
  Int_t           nY22_1;
  Int_t           nY22_2;
  Int_t           Ch1X1[nArr];   //[nX11]
  Int_t           Ch1X2[nArr];   //[nX12]
  Int_t           Ch2X1[nArr];   //[nX21]
  Int_t           Ch2X2[nArr];   //[nX22]
  Double_t        DL1X1[nArr];   //[nX11]
  Double_t        DL1X2[nArr];   //[nX12]
  Double_t        DL2X1[nArr];   //[nX21]
  Double_t        DL2X2[nArr];   //[nX22]
  Int_t           Ch1Y1[nArr];   //[nX11]
  Int_t           Ch1Y2[nArr];   //[nX12]
  Int_t           Ch2Y1[nArr];   //[nX21]
  Int_t           Ch2Y2[nArr];   //[nX22]
  Double_t        DL1Y1[nArr];   //[nX11]
  Double_t        DL1Y2[nArr];   //[nX12]
  Double_t        DL2Y1[nArr];   //[nX21]
  Double_t        DL2Y2[nArr];   //[nX22]
  Double_t        DT1X1[nArr];   //[nX11]
  Double_t        DT1X2[nArr];   //[nX12]
  Double_t        DT2X1[nArr];   //[nX21]
  Double_t        DT2X2[nArr];   //[nX22]
  Double_t        DT1Y1[nArr];   //[nX11]
  Double_t        DT1Y2[nArr];   //[nX12]
  Double_t        DT2Y1[nArr];   //[nX21]
  Double_t        DT2Y2[nArr];   //[nX22]


  // List of branches
  TBranch        *b_numEvt;   //!
  TBranch        *b_nX11;   //!
  TBranch        *b_nX12;   //!
  TBranch        *b_nX21;   //!
  TBranch        *b_nX22;   //!
  TBranch        *b_nY11;   //!
  TBranch        *b_nY12;   //!
  TBranch        *b_nY21;   //!
  TBranch        *b_nY22;   //!
  TBranch        *b_Ch1X1;   //!
  TBranch        *b_Ch1X2;   //!
  TBranch        *b_Ch2X1;   //!
  TBranch        *b_Ch2X2;   //!
  TBranch        *b_DL1X1;   //!
  TBranch        *b_DL1X2;   //!
  TBranch        *b_DL2X1;   //!
  TBranch        *b_DL2X2;   //!
  TBranch        *b_Ch1Y1;   //!
  TBranch        *b_Ch1Y2;   //!
  TBranch        *b_Ch2Y1;   //!
  TBranch        *b_Ch2Y2;   //!
  TBranch        *b_DL1Y1;   //!
  TBranch        *b_DL1Y2;   //!
  TBranch        *b_DL2Y1;   //!
  TBranch        *b_DL2Y2;   //!
  TBranch        *b_DT1X1;   //!
  TBranch        *b_DT1X2;   //!
  TBranch        *b_DT2X1;   //!
  TBranch        *b_DT2X2;   //!
  TBranch        *b_DT1Y1;   //!
  TBranch        *b_DT1Y2;   //!
  TBranch        *b_DT2Y1;   //!
  TBranch        *b_DT2Y2;   //!



  myTree->SetBranchAddress("numEvt", &numEvt, &b_numEvt);
  myTree->SetBranchAddress("nX11", &nX11, &b_nX11);
  myTree->SetBranchAddress("nX12", &nX12, &b_nX12);
  myTree->SetBranchAddress("nX21", &nX21, &b_nX21);
  myTree->SetBranchAddress("nX22", &nX22, &b_nX22);
  myTree->SetBranchAddress("nY11", &nY11, &b_nY11);
  myTree->SetBranchAddress("nY12", &nY12, &b_nY12);
  myTree->SetBranchAddress("nY21", &nY21, &b_nY21);
  myTree->SetBranchAddress("nY22", &nY22, &b_nY22);
  myTree->SetBranchAddress("Ch1X1", Ch1X1, &b_Ch1X1);
  myTree->SetBranchAddress("Ch1X2", Ch1X2, &b_Ch1X2);
  myTree->SetBranchAddress("Ch2X1", Ch2X1, &b_Ch2X1);
  myTree->SetBranchAddress("Ch2X2", Ch2X2, &b_Ch2X2);
  myTree->SetBranchAddress("DL1X1", DL1X1, &b_DL1X1);
  myTree->SetBranchAddress("DL1X2", DL1X2, &b_DL1X2);
  myTree->SetBranchAddress("DL2X1", DL2X1, &b_DL2X1);
  myTree->SetBranchAddress("DL2X2", DL2X2, &b_DL2X2);
  myTree->SetBranchAddress("Ch1Y1", Ch1Y1, &b_Ch1Y1);
  myTree->SetBranchAddress("Ch1Y2", Ch1Y2, &b_Ch1Y2);
  myTree->SetBranchAddress("Ch2Y1", Ch2Y1, &b_Ch2Y1);
  myTree->SetBranchAddress("Ch2Y2", Ch2Y2, &b_Ch2Y2);
  myTree->SetBranchAddress("DL1Y1", DL1Y1, &b_DL1Y1);
  myTree->SetBranchAddress("DL1Y2", DL1Y2, &b_DL1Y2);
  myTree->SetBranchAddress("DL2Y1", DL2Y1, &b_DL2Y1);
  myTree->SetBranchAddress("DL2Y2", DL2Y2, &b_DL2Y2);
  myTree->SetBranchAddress("DT1X1", DT1X1, &b_DT1X1);
  myTree->SetBranchAddress("DT1X2", DT1X2, &b_DT1X2);
  myTree->SetBranchAddress("DT2X1", DT2X1, &b_DT2X1);
  myTree->SetBranchAddress("DT2X2", DT2X2, &b_DT2X2);
  myTree->SetBranchAddress("DT1Y1", DT1Y1, &b_DT1Y1);
  myTree->SetBranchAddress("DT1Y2", DT1Y2, &b_DT1Y2);
  myTree->SetBranchAddress("DT2Y1", DT2Y1, &b_DT2Y1);
  myTree->SetBranchAddress("DT2Y2", DT2Y2, &b_DT2Y2);



  TH1D* Xchdiff1 = new TH1D("Xchdiff1" ,"Xchdiff1;difference;count",80,-40,40);
  TH1D* Xchdiff2 = new TH1D("Xchdiff2" ,"Xchdiff2;difference;count",80,-40,40);
  TH1D* Xchdiff3 = new TH1D("Xchdiff3" ,"Xchdiff3;difference;count",80,-40,40);
  TH1D* Xchdiff4 = new TH1D("Xchdiff4" ,"Xchdiff4;difference;count",80,-40,40);

  TH1D* Ychdiff1 = new TH1D("Ychdiff1" ,"Ychdiff1;difference;count",80,-40,40);
  TH1D* Ychdiff2 = new TH1D("Ychdiff2" ,"Ychdiff2;difference;count",80,-40,40);
  TH1D* Ychdiff3 = new TH1D("Ychdiff3" ,"Ychdiff3;difference;count",80,-40,40);
  TH1D* Ychdiff4 = new TH1D("Ychdiff4" ,"Ychdiff4;difference;count",80,-40,40);

  // definition of output file
  //TFile *outfile = new TFile("bdcAnaTrack_Data_SJ_Run_All_20210731.root","RECREATE");
  TFile *outfile = new TFile("bdcAnaTrack_Data_CNU_Cosmic_Run_getResolution_v10.root","RECREATE");


  TTree *trkTree = new TTree("trkTree","BDC Track Tree");
  const int nArr2 = 100; // number of array
  int Event = 0; // event number of track tree
  int trkNumX = 0; // number of track in each event at X
  int trkNumY = 0; // number of track in each event at Y
  double Xgrad[nArr2] = {0.0}, Xc[nArr2] = {0.0};
  double Ygrad[nArr2] = {0.0}, Yc[nArr2] = {0.0};
  int Ych1[30] = {-999};
  int Ych2[30] = {-999};
  int Ych3[30] = {-999};
  int Ych4[30] = {-999};

  int Xch1[30] = {-999};
  int Xch2[30] = {-999};
  int Xch3[30] = {-999};
  int Xch4[30] = {-999};

  // Trigger time
  double Zgrad_X[nArr2] = {0.0};
  double Zc_X[nArr2] = {0.0};
  double Zgrad_Y[nArr2] = {0.0};
  double Zc_Y[nArr2] = {0.0};
  double Xchi2[nArr2] = {0.};
  double Ychi2[nArr2] = {0.};

  trkTree->Branch("Event",&Event,"Event/I");
  trkTree->Branch("trckNumX",&trkNumX,"trkNumX/I");
  trkTree->Branch("trckNumY",&trkNumY,"trkNumY/I");
  trkTree->Branch("Xgrad",&Xgrad,"Xgrad[trkNumX]/D");
  trkTree->Branch("Ygrad",&Ygrad,"Ygrad[trkNumY]/D");
  trkTree->Branch("Xc",&Xc,"Xc[trkNumX]/D");
  trkTree->Branch("Yc",&Yc,"Yc[trkNumY]/D");
  trkTree->Branch("Xchi2",&Xchi2,"Xchi2[trkNumX]/D");
  trkTree->Branch("Ychi2",&Ychi2,"Ychi2[trkNumY]/D");
  trkTree->Branch("Zgrad_X",&Zgrad_X,"Zgrad_X[trkNumX]/D"); //added
  trkTree->Branch("Zgrad_Y",&Zgrad_Y,"Zgrad_Y[trkNumY]/D"); //added
  trkTree->Branch("Zc_X",&Zc_X,"Zc_X[trkNumX]/D"); //added
  trkTree->Branch("Zc_Y",&Zc_Y,"Zc_Y[trkNumY]/D"); //added



  ///////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////
  int NumEvt = myTree->GetEntries();
  cout<<" Number of Events : "<<NumEvt<<endl;
  double retrack[7000][5] = {-1000};

  // 55-95
  double cormax = 105;
  double cormin = 45;
  cormax = 110; // No Time Zero Loose
  cormin = 60; // No Time Zero Losse
  //cormax = 105; // No Time Zero Tight
  //cormin = 65; // No Time Zero Tight
  cormax = 102; // Time Zero 
  cormin = 56; // Time Zero

  int nlbin = 32;
  TH1F *hXL1 = new TH1F("hXL1",";fired Channels at X1;Counts",nlbin,0,32);
  TH1F *hXL2 = new TH1F("hXL2",";fired Channels at X2;Counts",nlbin,0,32);
  TH1F *hXL3 = new TH1F("hXL3",";fired Channels at X3;Counts",nlbin,0,32);
  TH1F *hXL4 = new TH1F("hXL4",";fired Channels at X4;Counts",nlbin,0,32);

  TH1F *hYL1 = new TH1F("hYL1",";fired Channels at Y1;Counts",nlbin,0,32);
  TH1F *hYL2 = new TH1F("hYL2",";fired Channels at Y2;Counts",nlbin,0,32);
  TH1F *hYL3 = new TH1F("hYL3",";fired Channels at Y3;Counts",nlbin,0,32);
  TH1F *hYL4 = new TH1F("hYL4",";fired Channels at Y4;Counts",nlbin,0,32);

  TH1F *hAngX = new TH1F("hAngX",";Angle(#theta) at X;counts",300,-100,100);
  TH1F *hAngY = new TH1F("hAngY",";Angle(#theta) at Y;counts",300,-100,100);

  TH1F *hChiX = new TH1F("hChiX",";chisqaure;counts",100,0,10);
  TH1F *hChiY = new TH1F("hChiY",";chisqaure;counts",100,0,10);

  TH2F *hAngChiX = new TH2F("hAngChiX",";angle (deg);chisqaure",60,-60,60,100,0,10);
  TH2F *hAngChiY = new TH2F("hAngChiY",";angle (deg);chisqaure",60,-60,60,100,0,10);

  TH2F *hTimeChiX1 = new TH2F("hTimeChiX1",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiX2 = new TH2F("hTimeChiX2",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiX3 = new TH2F("hTimeChiX3",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiX4 = new TH2F("hTimeChiX4",";time (ns);chisqaure",100,0,100,100,0,10);

  TH2F *hTimeChiY1 = new TH2F("hTimeChiY1",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiY2 = new TH2F("hTimeChiY2",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiY3 = new TH2F("hTimeChiY3",";time (ns);chisqaure",100,0,100,100,0,10);
  TH2F *hTimeChiY4 = new TH2F("hTimeChiY4",";time (ns);chisqaure",100,0,100,100,0,10);

  TH2F *hDLChiX1 = new TH2F("hDLChiX1",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiX2 = new TH2F("hDLChiX2",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiX3 = new TH2F("hDLChiX3",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiX4 = new TH2F("hDLChiX4",";drift length (mm);chisqaure",100,0,2.5,100,0,10);

  TH2F *hDLChiY1 = new TH2F("hDLChiY1",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiY2 = new TH2F("hDLChiY2",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiY3 = new TH2F("hDLChiY3",";drift length (mm);chisqaure",100,0,2.5,100,0,10);
  TH2F *hDLChiY4 = new TH2F("hDLChiY4",";drift length (mm);chisqaure",100,0,2.5,100,0,10);

  TH2F *hZgrdChiX = new TH2F("hZgrdChiX",";z gradient;chisqaure",100,-1,1,100,0,10);
  TH2F *hZgrdChiY = new TH2F("hZgrdChiY",";z gradient;chisqaure",100,-1,1,100,0,10);

  TH2F *hAngDifX = new TH2F("hAngDifX",";angle (deg);difference (cm)",240,-60,60,300,-3.0,3.0);
  TH2F *hAngDifY = new TH2F("hAngDifY",";angle (deg);difference (cm)",240,-60,60,300,-3.0,3.0);

  TH2F *hChiDifX = new TH2F("hChiDifX",";chisqaure;difference (cm)",100,0,10,300,-3.0,3.0);
  TH2F *hChiDifY = new TH2F("hChiDifY",";chisqaure;difference (cm)",100,0,10,300,-3.0,3.0);


  TH1D* TimeMaxX11 = new TH1D("TimeMaxX11",";time;Counts",500,0,500);
  TH1D* TimeMaxX21 = new TH1D("TimeMaxX21",";time;Counts",500,0,500);
  TH1D* DriftVelX11 = new TH1D("DriftVelX11",";Velocity (#mum/ns);Counts",100,0,100);
  TH1D* DriftVelX21 = new TH1D("DriftVelX21",";Velocity (#mum/ns);Counts",100,0,100);


  TH1D* TimeMaxY11 = new TH1D("TimeMaxY11",";time;Counts",500,0,500);
  TH1D* TimeMaxY21 = new TH1D("TimeMaxY21",";time;Counts",500,0,500);
  TH1D* DriftVelY11 = new TH1D("DriftVelY11",";Velocity (#mum/ns);Counts",100,0,100);
  TH1D* DriftVelY21 = new TH1D("DriftVelY21",";Velocity (#mum/ns);Counts",100,0,100);

  TH2F *hBeamSpot1 = new TH2F("hBeamSpot1","Beam Spot at Top;X (mm);Y (mm)",240,-40,200,240,-40,200);
  TH2F *hBeamSpot2 = new TH2F("hBeamSpot2","Beam Spot at Middle;X (mm);Y (mm)",240,-40,200,240,-40,200);
  TH2F *hBeamSpot3 = new TH2F("hBeamSpot3","Beam Spot at Bottom;X (mm);Y (mm)",240,-40,200,240,-40,200);

  TH1F *hPosX1 = new TH1F("hPosX1","Beam Spot at X;X (mm);Counts",200,0,200);
  TH1F *hPosX2 = new TH1F("hPosX2","Beam Spot at X;X (mm);Counts",200,0,200);
  TH1F *hPosX3 = new TH1F("hPosX3","Beam Spot at X;X (mm);Counts",200,0,200);
  TH1F *hPosY1 = new TH1F("hPosY1","Beam Spot at Y;Y (mm);Counts",200,0,200);
  TH1F *hPosY2 = new TH1F("hPosY2","Beam Spot at Y;Y (mm);Counts",200,0,200);
  TH1F *hPosY3 = new TH1F("hPosY3","Beam Spot at Y;Y (mm);Counts",200,0,200);

  TH2F *hPadX = new TH2F("hPadX",";x (mm) ;z (mm) ",200,0.0,165.0,165,0.0,1000.0);
  hPadX->GetXaxis()->CenterTitle();
  hPadX->GetYaxis()->CenterTitle();

  TH2F *hPadY = new TH2F("hPadY",";y (mm) ;z (mm) ",200,0.0,165.0,165,0.0,1000.0);
  hPadY->GetYaxis()->CenterTitle();
  hPadY->GetYaxis()->CenterTitle();


  TCanvas *c1 = new TCanvas("c1","",1500,330);
  //TCanvas *c1 = new TCanvas("c1","",1500,880);

  int maxevt = NumEvt;
  int nlayers = 4;
  Double_t		ds1[nArr]={-999.0};
  Double_t		ds2[nArr]={-999.0};
  Double_t		ds3[nArr]={-999.0};
  Double_t		ds4[nArr]={-999.0};


  TH1F *hDisY[4];
  TH1F *hDisX[4];
  TH1F *hDisY2[4];
  TH1F *hDisX2[4];
  TH1F *hDisY3[4];
  TH1F *hDisX3[4];
  TH2F *hDistVsTimeY[4];
  TH2F *hDistVsTimeX[4];
  for(int i = 0; i < nlayers; i++){
    hDisY[i] = new TH1F(Form("hDisY_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDisX[i] = new TH1F(Form("hDisX_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDisY2[i] = new TH1F(Form("hDisY2_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDisX2[i] = new TH1F(Form("hDisX2_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDisY3[i] = new TH1F(Form("hDisY3_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDisX3[i] = new TH1F(Form("hDisX3_%d",i),";difference (mm);Counts",600,-3.0,3.0);
    hDistVsTimeX[i] = new TH2F(Form("hDistVsTimeX_%d",i),";time (ns);Difference (mm)", 150, 0, 150, 100, -2.0, 2.0);
    hDistVsTimeY[i] = new TH2F(Form("hDistVsTimeY_%d",i),";time (ns);Difference (mm)", 150, 0, 150, 100, -2.0, 2.0);
  }



  if(savepng == true) maxevt = Nmax;
  int eventCnt = 0;
  int eventChk = 0;
  int ievtpre=0;
  for(int ievt = 0; ievt < maxevt; ievt++){
    //int ievt = 70;
    myTree->GetEntry(ievt);
    float dataCh1X1[nArr] = {-999.0};
    float dataCh1X2[nArr] = {-999.0};
    float dataCh2X1[nArr] = {-999.0};
    float dataCh2X2[nArr] = {-999.0};
    float dataDl1X1[nArr] = {-999.0};
    float dataDl1X2[nArr] = {-999.0};
    float dataDl2X1[nArr] = {-999.0};
    float dataDl2X2[nArr] = {-999.0};
    float dataDt1X1[nArr] = {-999.0};
    float dataDt1X2[nArr] = {-999.0};
    float dataDt2X1[nArr] = {-999.0};
    float dataDt2X2[nArr] = {-999.0};


    float dataCh1Y1[nArr] = {-999.0};
    float dataCh1Y2[nArr] = {-999.0};
    float dataCh2Y1[nArr] = {-999.0};
    float dataCh2Y2[nArr] = {-999.0};
    float dataDl1Y1[nArr] = {-999.0};
    float dataDl1Y2[nArr] = {-999.0};
    float dataDl2Y1[nArr] = {-999.0};
    float dataDl2Y2[nArr] = {-999.0};
    float dataDt1Y1[nArr] = {-999.0};
    float dataDt1Y2[nArr] = {-999.0};
    float dataDt2Y1[nArr] = {-999.0};
    float dataDt2Y2[nArr] = {-999.0};


    cout<<" "<<endl;
    cout<<"Event : "<<ievt<<endl;

    //	if(ievt % 100 == 0) cout<<"Event : "<<ievt<<" "<<100*ievt/(myTree->GetEntries())<<" (%)"<<endl;
    cout<<"Stage 1 X, nX11 : "<<nX11<<" nX12 : "<<nX12<<" nX21 : "<<nX21<<" nX22 : "<<nX22<<endl;
    cout<<"Stage 1 Y, nY11 : "<<nY11<<" nY12 : "<<nY12<<" nY21 : "<<nY21<<" nY22 : "<<nY22<<endl;

    Event = ievt;
    if(!(nX11 > 0 && nX12 > 0 && nX21 > 0 && nX22 > 0)) {
      cout<<"Not fired all layer and don't need this event !!!"<<endl;
      continue;
    }
    eventCnt++;
    for(int j = 0; j < nX11; j++){
      cout<<"Ch1X1 : "<<Ch1X1[j]<<" DL1X1 : "<<DL1X1[j]<<endl;
      dataCh1X1[j] = Ch1X1[j];
      dataDl1X1[j] = DL1X1[j];
      dataDt1X1[j] = DT1X1[j];
    }
    for(int j = 0; j < nX12; j++){
      cout<<"Ch1X2 : "<<Ch1X2[j]<<" DL1X2 : "<<DL1X2[j]<<endl;
      dataCh1X2[j] = Ch1X2[j];
      dataDl1X2[j] = DL1X2[j];
      dataDt1X2[j] = DT1X2[j];
    }
    for(int j = 0; j < nX21; j++){
      cout<<"Ch2X1 : "<<Ch2X1[j]<<" DL2X1 : "<<DL2X1[j]<<endl;
      dataCh2X1[j] = Ch2X1[j];
      dataDl2X1[j] = DL2X1[j];
      dataDt2X1[j] = DT2X1[j];
    }
    for(int j = 0; j < nX22; j++){
      cout<<"Ch2X2 : "<<Ch2X2[j]<<" DL2X2 : "<<DL2X2[j]<<endl;
      dataCh2X2[j] = Ch2X2[j];
      dataDl2X2[j] = DL2X2[j];
      dataDt2X2[j] = DT2X2[j];
    }
    if(onlyx == false){
      for(int j = 0; j < nY11; j++){
        cout<<"Ch1Y1 : "<<Ch1Y1[j]<<" DL1Y1 : "<<DL1Y1[j]<<endl;
        dataCh1Y1[j] = Ch1Y1[j];
        dataDl1Y1[j] = DL1Y1[j];
        dataDt1Y1[j] = DT1Y1[j];
      }

      for(int j = 0; j < nY12; j++){
        cout<<"Ch1Y2 : "<<Ch1Y2[j]<<" DL1Y2 : "<<DL1Y2[j]<<endl;
        dataCh1Y2[j] = Ch1Y2[j];
        dataDl1Y2[j] = DL1Y2[j];
        dataDt1Y2[j] = DT1Y2[j];
      }

      for(int j = 0; j < nY21; j++){
        cout<<"Ch2Y1 : "<<Ch2Y1[j]<<" DL2Y1 : "<<DL2Y1[j]<<endl;
        dataCh2Y1[j] = Ch2Y1[j];
        dataDl2Y1[j] = DL2Y1[j];
        dataDt2Y1[j] = DT2Y1[j];
      }

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      for(int j = 0; j < nY22; j++){
        cout<<"Ch2Y2 : "<<Ch2Y2[j]<<" DL2Y2 : "<<DL2Y2[j]<<endl;
        dataCh2Y2[j] = Ch2Y2[j];
        dataDl2Y2[j] = DL2Y2[j];
        dataDt2Y2[j] = DT2Y2[j];
      }
      cout<<"dmoon chk 1 : "<<dataCh1Y1[0]<<", 2 :"<<dataCh1Y2[0]<<", 3 : "<<dataCh2Y1[0]<<", 4 : "<<dataCh2Y2[0]<<endl;
    }

    int tracknum=0;
    int YCH11 = 0;
    int YCH12 = 0;
    int YCH21 = 0;
    int YCH22 = 0;
    double YDT11 = 0.0;
    double YDT12 = 0.0;
    double YDT21 = 0.0;
    double YDT22 = 0.0;
    double YPR11 = 0.0;
    double YPR12 = 0.0;
    double YPR21 = 0.0;
    double YPR22 = 0.0;
    double YPR211 = 0.0;
    double YPR212 = 0.0;
    double YPR221 = 0.0;
    double YPR222 = 0.0;
    double XPos1 = 0.0; // X position of Top for Chamber
    double XPos2 = 0.0; // X position of Middle for Chamber
    double XPos3 = 0.0; // X position of Bottom for Chamber
    double YPos1 = 0.0; // Y position of Top for Chamber
    double YPos2 = 0.0; // Y position of Middle for Chamber
    double YPos3 = 0.0; // Y position of Bottom for Chamber
    //if(ievt != 126) continue;
    if(onlyx == false){
      if(dataCh1Y1[0] != -999.0 && dataCh1Y2[0] != -999.0){
        if(dataCh2Y1[0] != -999.0 && dataCh2Y2[0] != -999.0) {
          cout<<"working Y !!! "<<ievt<<endl;
          double repars[9] = {0.0};
          double rediff = 100000.;
          double rsdtmp[10] = {0.0};
          int goodtrack = 0;
          if(nY11<5 && nY21<5)
          {
            for(int Y11 = 0; Y11<nY11;Y11++)
            {
              for(int Y12 = 0; Y12<nY12;Y12++)
              {
                int datadiff1 = dataCh1Y2[Y12]-dataCh1Y1[Y11];
                if(datadiff1>=0 && datadiff1<=1)
                {
                  for(int Y21 = 0;Y21<nY21;Y21++)
                  {
                    for(int Y22=0;Y22<nY22;Y22++)
                    {
                      int datadiff2 = dataCh2Y2[Y22]-dataCh2Y1[Y21];
                      if(datadiff2>=0 && datadiff2<=1)
                      {
                        if(dataCh1Y1[Y11] - dataCh2Y1[Y21] != 0) continue;
                        if(dataCh1Y2[Y12] - dataCh2Y2[Y22] != 0) continue;
                        Ych1[tracknum] = dataCh1Y1[Y11];
                        Ych2[tracknum] = dataCh1Y2[Y12];
                        Ych3[tracknum] = dataCh2Y1[Y21];
                        Ych4[tracknum] = dataCh2Y2[Y22];
                        double pars[16] = {0.0}; // distances at each layer
                        double pars1[16] = {0.0}; // distances at each layer
                        double dts[6] = {0.0};
                        double dts1[6] = {0.0};
                        cout<<"Fired Channel Y : "<<dataCh1Y1[Y11]<<" "<<dataCh1Y2[Y12]<<" "<<dataCh2Y1[Y21]<<" "<<dataCh2Y2[Y22]<<endl;
                        //if(fabs(dataCh1Y1[Y11] - dataCh2Y2[Y22]) > 1) continue; 
                        if(fulltracking){
                          if(dataDt1Y1[Y11] < 0 || dataDt1Y2[Y12] < 0 || dataDt2Y1[Y21] < 0 || dataDt2Y2[Y22] < 0) continue;
                          double tmax1 = dataDt1Y1[Y11] + dataDt1Y2[Y12]; 
                          double tmax2 = dataDt2Y1[Y21] + dataDt2Y2[Y22]; 
                          double tmax3 = dataDt1Y2[Y12] + dataDt2Y1[Y21]; 
                          double tmax4 = dataDt1Y1[Y11] + dataDt2Y2[Y22]; 
                          if(corr_ == true) {
                            if(tmax1 > cormax) continue;
                            if(tmax1 < cormin) continue;
                            if(tmax2 > cormax)  continue;
                            if(tmax2 < cormin)  continue;
                            if(tmax3 > cormax)  continue;
                            if(tmax3 < cormin)  continue;
                          }
                          //if(tmax4 > 80)  continue;
                          //if(tmax4 < 40)  continue;
                          trackFinderY2(dataCh1Y1[Y11], dataDl1Y1[Y11], dataCh1Y2[Y12], dataDl1Y2[Y12], dataCh2Y1[Y21], 
                              dataDl2Y1[Y21], dataCh2Y2[Y22], dataDl2Y2[Y22], dataDt1Y1[Y11], dataDt1Y2[Y12], dataDt2Y1[Y21], dataDt2Y2[Y22], 
                              ievt, tracknum, pars, dts);
                          if(tracknum==0)
                          {
                            Ygrad[0] = pars[0];
                            Yc[0] = pars[1];
                            Zgrad_Y[0] = 1/Ygrad[0]; //added
                            Zc_Y[0] = -pars[1]/Ygrad[0]; //added
                            rediff = pars[10];
                            Ychi2[0] = pars[10];
                            goodtrack = tracknum;
                            YCH11 = dataCh1Y1[Y11];
                            YCH12 = dataCh1Y2[Y12];
                            YCH21 = dataCh2Y1[Y21];
                            YCH22 = dataCh2Y2[Y22];
                            YDT11 = dataDt1Y1[Y11];
                            YDT12 = dataDt1Y2[Y12];
                            YDT21 = dataDt2Y1[Y21];
                            YDT22 = dataDt2Y2[Y22];
                            YPR11 = pars[2];
                            YPR12 = pars[3];
                            YPR21 = pars[4];
                            YPR22 = pars[5];
                            YPR211 = pars[6];
                            YPR212 = pars[7];
                            YPR221 = pars[8];
                            YPR222 = pars[9];
                            YPos1 = pars[12];
                            YPos2 = pars[13];
                            YPos3 = pars[14];
                          }

                          if(tracknum!=0 && rediff < pars[10])
                          {
                            Ygrad[0] = pars[0];
                            Zgrad_Y[0] = 1/Ygrad[0];
                            Yc[0] = pars[1];
                            Zc_Y[0] = -pars[1]/Ygrad[0];
                            rediff = pars[10];
                            Ychi2[0] = pars[10];
                            goodtrack = tracknum;
                            YCH11 = dataCh1Y1[Y11];
                            YCH12 = dataCh1Y2[Y12];
                            YCH21 = dataCh2Y1[Y21];
                            YCH22 = dataCh2Y2[Y22];
                            YDT11 = dataDt1Y1[Y11];
                            YDT12 = dataDt1Y2[Y12];
                            YDT21 = dataDt2Y1[Y21];
                            YDT22 = dataDt2Y2[Y22];
                            YPR11 = pars[2];
                            YPR12 = pars[3];
                            YPR21 = pars[4];
                            YPR22 = pars[5];
                            YPR211 = pars[6];
                            YPR212 = pars[7];
                            YPR221 = pars[8];
                            YPR222 = pars[9];
                            YPos1 = pars[12];
                            YPos2 = pars[13];
                            YPos3 = pars[14];
                          }
                        }
                        tracknum++;
                      }
                    }
                  }
                }
              }
            }
          }
        }

      }
    }// end Y
    trkNumY = tracknum;
    if(tracknum>1) trkNumY = 1;

    int tracknum1=0;
    int XCH11 = 0;
    int XCH12 = 0;
    int XCH21 = 0;
    int XCH22 = 0;
    double XDT11 = 0.0;
    double XDT12 = 0.0;
    double XDT21 = 0.0;
    double XDT22 = 0.0;
    double XPR11 = 0.0;
    double XPR12 = 0.0;
    double XPR21 = 0.0;
    double XPR22 = 0.0;
    double XPR211 = 0.0;
    double XPR212 = 0.0;
    double XPR221 = 0.0;
    double XPR222 = 0.0;
    //if(ievt != 126) continue;
    if(dataCh1X1[0] != -999.0 && dataCh1X2[0] != -999.0){
      if(dataCh2X1[0] != -999.0 && dataCh2X2[0] != -999.0) {
        cout<<"working X !!! "<<ievt<<endl;
        double repars[9] = {0.0};
        double rediff = 100000.;
        double rsdtmp[10] = {0.0};
        int goodtrack=-1;
        cout<<"Stage 2, nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
        if(!(nX11 == 1 && nX12 == 1 && nX21 == 1 && nX22 == 1)) continue;
        //nX11 = 1; nX12 = 1; nX21 = 1; nX22 = 1;
        cout<<"Stage 3, nX11 : "<<nX11<<", nX12 : "<<nX12<<", nX21 : "<<nX21<<", nX22 : "<<nX22<<endl;
        if(nX11<5 && nX21<5){
          for(int X11 = 0; X11<nX11;X11++)
          {
            for(int X12 = 0; X12<nX12;X12++)
            {
              int datadiff1 = dataCh1X2[X12]-dataCh1X1[X11];
              if(datadiff1>=0 && datadiff1<=1)
              {
                for(int X21 = 0;X21<nX21;X21++)
                {
                  for(int X22=0;X22<nX22;X22++)
                  {
                    int datadiff2 = dataCh2X2[X22]-dataCh2X1[X21];
                    if(datadiff2>=0 && datadiff2<=1)
                    {
                      if(dataCh1X1[X11] - dataCh2X1[X21] != 0) continue;
                      if(dataCh1X2[X12] - dataCh2X2[X22] != 0) continue;
                      Xch1[tracknum1] = dataCh1X1[X11];
                      Xch2[tracknum1] = dataCh1X2[X12];
                      Xch3[tracknum1] = dataCh2X1[X21];
                      Xch4[tracknum1] = dataCh2X2[X22];
                      double pars[15] = {0.0}; // distances at each layer
                      double pars1[15] = {0.0}; // distances at each layer
                      double dts[6] = {0.0};
                      double dts1[6] = {0.0};
                      cout<<"Fired Channel X : "<<dataCh1X1[X11]<<" "<<dataCh1X2[X12]<<" "<<dataCh2X1[X21]<<" "<<dataCh2X2[X22]<<endl;
                      //if(fabs(dataCh1X1[X11] - dataCh2X2[X22]) > 1) continue; 
                      if(fulltracking){
                        if(dataDt1X1[X11] < 0 || dataDt1X2[X12] < 0 || dataDt2X1[X21] < 0 || dataDt2X2[X22] < 0) continue;
                        double tmax1 = dataDt1X1[X11] + dataDt1X2[X12]; 
                        double tmax2 = dataDt2X1[X21] + dataDt2X2[X22]; 
                        double tmax3 = dataDt1X2[X12] + dataDt2X1[X21]; 
                        double tmax4 = dataDt1X1[X11] + dataDt2X2[X22]; 
                        cout<<"tmax1 : "<<tmax1<<", tmax2 : "<<tmax2<<", tmax3 : "<<tmax3<<endl;
                        cout<<"dt1X1 : "<<dataDt1X1[X11]<<", dt1X2 : "<<dataDt1X2[X12]<<", dt2X1 : "<<dataDt2X1[X21]<<", dt2X2 : "<<dataDt2X2[X22]<<endl;
                        if(corr_ == true) {
                          if(tmax1 > cormax) continue;
                          if(tmax1 < cormin) continue;
                          if(tmax2 > cormax)  continue;
                          if(tmax2 < cormin)  continue;
                          if(tmax3 > cormax)  continue;
                          if(tmax3 < cormin)  continue;
                        }
                        //if(tmax4 > 80)  continue;
                        //if(tmax4 < 40)  continue;
                        trackFinderX2(dataCh1X1[X11], dataDl1X1[X11], dataCh1X2[X12], dataDl1X2[X12], dataCh2X1[X21], 
                            dataDl2X1[X21], dataCh2X2[X22], dataDl2X2[X22], dataDt1X1[X11], dataDt1X2[X12], dataDt2X1[X21], dataDt2X2[X22], 
                            ievt, tracknum1, pars, dts);
                        if(tracknum1==0)
                        {
                          Xgrad[0] = pars[0];
                          Xc[0] = pars[1];
                          Zgrad_X[0] = 1/Xgrad[0]; //added
                          Zc_X[0] = -pars[1]/Xgrad[0]; //added
                          rediff = pars[10];
                          Xchi2[0] = pars[10];
                          goodtrack = tracknum1;
                          XCH11 = dataCh1X1[X11];
                          XCH12 = dataCh1X2[X12];
                          XCH21 = dataCh2X1[X21];
                          XCH22 = dataCh2X2[X22];
                          XDT11 = dataDt1X1[X11];
                          XDT12 = dataDt1X2[X12];
                          XDT21 = dataDt2X1[X21];
                          XDT22 = dataDt2X2[X22];
                          XPR11 = pars[2];
                          XPR12 = pars[3];
                          XPR21 = pars[4];
                          XPR22 = pars[5];
                          XPR211 = pars[6];
                          XPR212 = pars[7];
                          XPR221 = pars[8];
                          XPR222 = pars[9];
                          XPos1 = pars[12];
                          XPos2 = pars[13];
                          XPos3 = pars[14];
                        }

                        if(tracknum1!=0 && rediff < pars[10])
                        {
                          Xgrad[0] = pars[0];
                          Xc[0] = pars[1];
                          Zgrad_X[0] = 1/Xgrad[0]; //added
                          Zc_X[0] = -pars[1]/Xgrad[0]; //added
                          rediff = pars[10];
                          Xchi2[0] = pars[10];
                          goodtrack = tracknum1;
                          XCH11 = dataCh1X1[X11];
                          XCH12 = dataCh1X2[X12];
                          XCH21 = dataCh2X1[X21];
                          XCH22 = dataCh2X2[X22];
                          XDT11 = dataDt1X1[X11];
                          XDT12 = dataDt1X2[X12];
                          XDT21 = dataDt2X1[X21];
                          XDT22 = dataDt2X2[X22];
                          XPR11 = pars[2];
                          XPR12 = pars[3];
                          XPR21 = pars[4];
                          XPR22 = pars[5];
                          XPR211 = pars[6];
                          XPR212 = pars[7];
                          XPR221 = pars[8];
                          XPR222 = pars[9];
                          XPos1 = pars[12];
                          XPos2 = pars[13];
                          XPos3 = pars[14];
                        }

                      }
                      tracknum1++;
                    }
                  }
                }
              }
            }
          }
        } 
      }
    }// end X

    /////////////////////////////////////////////////

    cout<<"All fired event : "<<eventCnt<<endl;
    /////////////////////////////////////////////////
    cout<<"Number of track at Y : "<<tracknum<<endl;
    cout<<"Number of track at X : "<<tracknum1<<endl;
    trkNumX = tracknum1;
    if(tracknum1>1) trkNumX = 1;
    if(onlyx == true) trkNumY = 1;
    if ( trkNumX>0 || trkNumY>0 ) {
      cout<<"dhmoon chk 111 !!!"<<endl;
      ievtpre=ievt;
      if(trkNumX==0) {Xgrad[0] = 0; }
      if(trkNumY==0) {Ygrad[0] = 0; }
      trkTree->Fill();

      if(trkNumX>0){
        eventChk++;
        double angle = 0.0;
        if(atan(Xgrad[0])*180/pi > 0) angle = 90-atan(Xgrad[0])*180/pi;
        if(atan(Xgrad[0])*180/pi < 0) angle = -90-atan(Xgrad[0])*180/pi;
        cout<<"Histogram angle : "<<angle<<endl;
        //if(fabs(angle) > 30) continue;
        hAngX->Fill(angle);
        if(angleCut_ == true && fabs(angle) > 7) continue;
        //if(fabs(angle) > 10) continue;
        //if(fabs(Zgrad_X[0]) > 0.12) continue;
        //if(Xchi2[0] > 1.0) continue;
        hChiX->Fill(Xchi2[0]);
        hAngChiX->Fill(angle,Xchi2[0]);
        hZgrdChiX->Fill(Zgrad_X[0],Xchi2[0]);
        hAngDifX->Fill(angle,XPR221);
        hChiDifX->Fill(Xchi2[0],XPR221);
        hTimeChiX1->Fill(DT1X1[0],Xchi2[0]);
        hTimeChiX2->Fill(DT1X2[0],Xchi2[0]);
        hTimeChiX3->Fill(DT2X1[0],Xchi2[0]);
        hTimeChiX4->Fill(DT2X2[0],Xchi2[0]);
        hDLChiX1->Fill(DL1X1[0],Xchi2[0]);
        hDLChiX2->Fill(DL1X2[0],Xchi2[0]);
        hDLChiX3->Fill(DL2X1[0],Xchi2[0]);
        hDLChiX4->Fill(DL2X2[0],Xchi2[0]);
        //if(Xchi2[0] > 1.0) continue;
        //if(Xchi2[0] > 0.5) continue;
        hXL1->Fill(XCH11);
        hXL2->Fill(XCH12);
        hXL3->Fill(XCH21);
        hXL4->Fill(XCH22);
        hDisX[0]->Fill(XPR11);
        hDisX[1]->Fill(XPR12);
        hDisX[2]->Fill(XPR21);
        hDisX[3]->Fill(XPR22);
        hDisX2[0]->Fill(XPR211);
        hDisX2[1]->Fill(XPR212);
        hDisX2[2]->Fill(XPR221);
        hDisX2[3]->Fill(XPR222);
        hDistVsTimeX[0]->Fill(XDT11,XPR11);
        hDistVsTimeX[1]->Fill(XDT12,XPR12);
        hDistVsTimeX[2]->Fill(XDT21,XPR21);
        hDistVsTimeX[3]->Fill(XDT22,XPR22);

        double time1 = XDT11;
        double time2 = XDT12;
        double time3 = XDT21;
        double time4 = XDT22;

        TimeMaxX11->Fill((time1+time3)/2+time2);
        TimeMaxX21->Fill((time2+time4)/2+time3);
        DriftVelX11->Fill(2.5/((time1+time3)/2+time2)*1000.0);
        DriftVelX21->Fill(2.5/((time2+time4)/2+time3)*1000.0);

        hPosX1->Fill(XPos1);
        hPosX2->Fill(XPos2);
        hPosX3->Fill(XPos3);
      }
      if(trkNumY>0 && onlyx == false){
        double angle = 0.0;
        if(atan(Ygrad[0])*180/pi > 0) angle = 90-atan(Ygrad[0])*180/pi;
        if(atan(Ygrad[0])*180/pi < 0) angle = -90-atan(Ygrad[0])*180/pi;
        hAngY->Fill(angle);
        if(angleCut_ == true && fabs(angle) > 7) continue;
        //if(fabs(angle) > 7) continue;
        //if(Xchi2[0] > 1.0) continue;
        hAngChiY->Fill(angle,Ychi2[0]);
        hZgrdChiY->Fill(Zgrad_Y[0],Ychi2[0]);
        hAngDifY->Fill(angle,YPR221);
        hChiDifY->Fill(Ychi2[0],YPR221);
        hTimeChiY1->Fill(DT1Y1[0],Ychi2[0]);
        hTimeChiY2->Fill(DT1Y2[0],Ychi2[0]);
        hTimeChiY3->Fill(DT2Y1[0],Ychi2[0]);
        hTimeChiY4->Fill(DT2Y2[0],Ychi2[0]);
        hDLChiY1->Fill(DL1Y1[0],Ychi2[0]);
        hDLChiY2->Fill(DL1Y2[0],Ychi2[0]);
        hDLChiY3->Fill(DL2Y1[0],Ychi2[0]);
        hDLChiY4->Fill(DL2Y2[0],Ychi2[0]);
        hChiY->Fill(Ychi2[0]);
        hYL1->Fill(YCH11);
        hYL2->Fill(YCH12);
        hYL3->Fill(YCH21);
        hYL4->Fill(YCH22);
        hDisY[0]->Fill(YPR11);
        hDisY[1]->Fill(YPR12);
        hDisY[2]->Fill(YPR21);
        hDisY[3]->Fill(YPR22);
        hDisY2[0]->Fill(YPR211);
        hDisY2[1]->Fill(YPR212);
        hDisY2[2]->Fill(YPR221);
        hDisY2[3]->Fill(YPR222);
        hDistVsTimeY[0]->Fill(YDT11,YPR11);
        hDistVsTimeY[1]->Fill(YDT12,YPR12);
        hDistVsTimeY[2]->Fill(YDT21,YPR21);
        hDistVsTimeY[3]->Fill(YDT22,YPR22);

        double time1 = YDT11;
        double time2 = YDT12;
        double time3 = YDT21;
        double time4 = YDT22;

        TimeMaxY11->Fill((time1+time3)/2+time2);
        TimeMaxY21->Fill((time2+time4)/2+time3);
        DriftVelY11->Fill(2.5/((time1+time3)/2+time2)*1000.0);
        DriftVelY21->Fill(2.5/((time2+time4)/2+time3)*1000.0);
        hPosY1->Fill(YPos1);
        hPosY2->Fill(YPos2);
        hPosY3->Fill(YPos3);
      }
      hBeamSpot1->Fill(XPos1,YPos1);
      hBeamSpot2->Fill(XPos2,YPos2);
      hBeamSpot3->Fill(XPos3,YPos3);
    }
  }
  cout<<"Number of tracks : "<<eventChk<<endl;

  outfile->cd();
  trkTree->Write();
  auto can1 = new TCanvas();
  can1->SetTitle("XChannel difference");
  can1 -> Divide(2,2);
  can1->cd(1);
  Xchdiff1->Draw();
  can1->cd(2);
  Xchdiff2->Draw();
  can1->cd(3);
  Xchdiff3->Draw();
  can1->cd(4);
  Xchdiff4->Draw();
  auto can2 = new TCanvas();
  can2->SetTitle("YChannel difference");
  can2 -> Divide(2,2);
  can2->cd(1);
  //Ychdiff1->Draw();
  hBeamSpot1->Draw("colz");
  can2->cd(2);
  //Ychdiff2->Draw();
  hBeamSpot2->Draw("colz");
  can2->cd(3);
  //Ychdiff3->Draw();
  hBeamSpot3->Draw("colz");
  can2->cd(4);
  //Ychdiff4->Draw();

  hPosX1->Write();
  hPosX2->Write();
  hPosX3->Write();
  hPosY1->Write();
  hPosY2->Write();
  hPosY3->Write();

  hBeamSpot1->Write();
  hBeamSpot2->Write();
  hBeamSpot3->Write();

  TimeMaxX11->Write();
  TimeMaxX21->Write();
  DriftVelX11->Write();
  DriftVelX21->Write();


  TimeMaxY11->Write();
  TimeMaxY21->Write();
  DriftVelY11->Write();
  DriftVelY21->Write();


  hTimeChiX1->Write();
  hTimeChiX2->Write();
  hTimeChiX3->Write();
  hTimeChiX4->Write();

  hDLChiX1->Write();
  hDLChiX2->Write();
  hDLChiX3->Write();
  hDLChiX4->Write();


  hTimeChiY1->Write();
  hTimeChiY2->Write();
  hTimeChiY3->Write();
  hTimeChiY4->Write();

  hDLChiY1->Write();
  hDLChiY2->Write();
  hDLChiY3->Write();
  hDLChiY4->Write();



  hAngChiX->Write();
  hZgrdChiX->Write();
  hAngDifX->Write();
  hChiDifX->Write();


  hAngChiY->Write();
  hZgrdChiY->Write();
  hAngDifY->Write();
  hChiDifY->Write();


  hChiX->Write();
  hChiY->Write();

  hXL1->Write();
  hXL2->Write();
  hXL3->Write();
  hXL4->Write();

  hYL3->Write();
  hYL2->Write();
  hYL1->Write();
  hYL4->Write();

  hAngX->Write();
  hAngY->Write();

  hDisX[0]->Write();
  hDisX[1]->Write();
  hDisX[2]->Write();
  hDisX[3]->Write();
  hDisX2[0]->Write();
  hDisX2[1]->Write();
  hDisX2[2]->Write();
  hDisX2[3]->Write();
  hDistVsTimeX[0]->Write();
  hDistVsTimeX[1]->Write();
  hDistVsTimeX[2]->Write();
  hDistVsTimeX[3]->Write();

  hDisY[0]->Write();
  hDisY[1]->Write();
  hDisY[2]->Write();
  hDisY[3]->Write();
  hDisY2[0]->Write();
  hDisY2[1]->Write();
  hDisY2[2]->Write();
  hDisY2[3]->Write();
  hDistVsTimeY[0]->Write();
  hDistVsTimeY[1]->Write();
  hDistVsTimeY[2]->Write();
  hDistVsTimeY[3]->Write();

  outfile->Write();
  outfile->Close();


}


//////////////////////////////////////////////////////////////////////////////////////////


void trackFinderY2(float dataCh1Y1, float dataDl1Y1, float dataCh1Y2, float dataDl1Y2, float dataCh2Y1, float dataDl2Y1, float dataCh2Y2, float dataDl2Y2, float dataDt1Y1, float dataDt1Y2, float dataDt2Y1, float dataDt2Y2, int ievt, int tracknum, double *pars, double *dts){
  cout<<"Start track with y axis !!! "<<ievt<<" Event !!!"<<endl;
  TH2F *hPadY = new TH2F("hPadY",";y (mm) ;z (mm) ",175,-10,165,165,0,100.0);
  hPadY->GetYaxis()->CenterTitle();
  hPadY->GetXaxis()->CenterTitle();
  TH2F *hPadY1 = new TH2F("hPadY1",";y (mm) ;z (mm) ",175,-10,165,165,0.0,60.0);
  hPadY1->GetYaxis()->CenterTitle();
  hPadY1->GetXaxis()->CenterTitle();

  TCanvas *c2 = new TCanvas("c2","",1500,500);
  c2->cd();
  //c2->Divide(1,2);
  //c2->cd(1);
  hPadY->Draw();
  int firedChX[4] = {0};
  int firedChY[4] = {0, 1, 2, 3};

  int nlayer = 4; // number of layer (e.g 4 means xx'xx')
  int nwire = 6; //number of wire on each layer
  const int nwires = 32; //number of wire on each layer
                         // wire positions

  double wireX1[nwires] = {0.0}; 
  double wireX2[nwires] = {0.0}; 
  double wireX3[nwires] = {0.0}; 
  double wireX4[nwires] = {0.0}; 
  double wireY1[nwires] = {0.0}; 
  double wireY2[nwires] = {0.0}; 
  double wireY3[nwires] = {0.0}; 
  double wireY4[nwires] = {0.0}; 

  //double distanceChamber = 15.0;


  for(int iw = 0; iw < nwires; iw++){
    double cal1 = 0.0;
    double cal2 = 0.0;
    double cal3 = 0.0;
    double cal4 = 0.0;
    wireX1[iw] = iw*5.0 + Ywirestart+2.5+cal1; // y
    wireX2[iw] = iw*5.0 + Ywirestart	+cal2; // y'
    wireX3[iw] = iw*5.0 + Ywirestart+2.5+cal3; // y
    wireX4[iw] = iw*5.0 + Ywirestart	+cal4; // y'
    wireY1[iw] = FLH+10;
    wireY2[iw] = FLH+15;
    //wireY1[iw] = FLH+10;
    //wireY2[iw] = FLH+15;
    wireY3[iw] = distanceChamber+wireY1[iw];
    wireY4[iw] = distanceChamber+wireY2[iw];
  }

  double wireX[4][nwires] = {0.0};

  for(int iwx = 0 ; iwx < nwires; iwx++){
    wireX[0][iwx] = wireX1[iwx];
    wireX[1][iwx] = wireX2[iwx];
    wireX[2][iwx] = wireX3[iwx];
    wireX[3][iwx] = wireX4[iwx];
  }


  c2->SetGrid();
  TGraph *wire1 = new TGraph(nwires,wireX1,wireY1);
  TGraph *wire2 = new TGraph(nwires,wireX2,wireY2);
  TGraph *wire3 = new TGraph(nwires,wireX3,wireY3);
  TGraph *wire4 = new TGraph(nwires,wireX4,wireY4);
  wire1->SetMarkerStyle(20);
  wire1->SetMarkerColor(kRed+1);
  wire2->SetMarkerStyle(20);
  wire2->SetMarkerColor(kRed+1);
  wire3->SetMarkerStyle(20);
  wire3->SetMarkerColor(kRed+1);
  wire4->SetMarkerStyle(20);
  wire4->SetMarkerColor(kRed+1);

  wire1->Draw("pz same");
  wire2->Draw("pz same");
  wire3->Draw("pz same");
  wire4->Draw("pz same");

  firedChX[0] = dataCh1Y1;
  firedChX[1] = dataCh1Y2;
  firedChX[2] = dataCh2Y1;
  firedChX[3] = dataCh2Y2;

  //cout<<"dhmoon chk 1-1 firedChX11 : "<<firedChX[0]<<", firedChX12 : "<<firedChX[1]<<", firedChX21 : "<<firedChX[2]<<", firedChX22 : "<<firedChX[3]<<endl;

  double wireposx[4] = {0.0};
  double wireposy[4] = {0.0};

  // input fired wire postion
  wireposx[0] = wireX1[firedChX[0]];wireposy[0] = wireY1[firedChY[0]];
  wireposx[1] = wireX2[firedChX[1]];wireposy[1] = wireY2[firedChY[1]];
  wireposx[2] = wireX3[firedChX[2]];wireposy[2] = wireY3[firedChY[2]];
  wireposx[3] = wireX4[firedChX[3]];wireposy[3] = wireY4[firedChY[3]];
  cout<<"dhmoon chk 1-2 wireposx X11 : "<<wireposx[0]<<", wireposx X12 : "<<wireposx[1]<<", wireposx X21 : "<<wireposx[2]<<", wireposx X22 : "<<wireposx[3]<<endl;
  cout<<"dhmoon chk 1-2 wireposy X11 : "<<wireposy[0]<<", wireposy X12 : "<<wireposy[1]<<", wireposy X21 : "<<wireposy[2]<<", wireposy X22 : "<<wireposy[3]<<endl;

  double driftlth[4];
  double dlcal1 = -0.02;
  double dlcal2 = -0.02;
  double dlcal3 = -0.02;
  double dlcal4 = -0.02;

  driftlth[0] = dataDl1Y1+dlcal1;
  driftlth[1] = dataDl1Y2+dlcal2;
  driftlth[2] = dataDl2Y1+dlcal3;
  driftlth[3] = dataDl2Y2+dlcal4;

  for(int l = 0; l < nlayer; l++){
    if(driftlth[l] < 0) driftlth[l] = 0.02;
  }


  TArc *arc1 = new TArc(wireposx[0],wireposy[0],driftlth[0],0,360);
  TArc *arc2 = new TArc(wireposx[1],wireposy[1],driftlth[1],0,360);
  TArc *arc3 = new TArc(wireposx[2],wireposy[2],driftlth[2],0,360);
  TArc *arc4 = new TArc(wireposx[3],wireposy[3],driftlth[3],0,360);
  arc1->SetFillStyle(4000); // 0.571
  arc2->SetFillStyle(4000);
  arc3->SetFillStyle(4000);
  arc4->SetFillStyle(4000);
  arc1->SetLineColor(kAzure+1);
  arc2->SetLineColor(kAzure+1);
  arc3->SetLineColor(kAzure+1);
  arc4->SetLineColor(kAzure+1);
  arc1->SetLineStyle(2);
  arc2->SetLineStyle(2);
  arc3->SetLineStyle(2);
  arc4->SetLineStyle(2);
  arc1->SetLineWidth(4);
  arc2->SetLineWidth(4);
  arc3->SetLineWidth(4);
  arc4->SetLineWidth(4);

  arc1->Draw("");
  arc2->Draw("");
  arc3->Draw("");
  arc4->Draw("");


  // try with different seeding
  // find seeding position
  double seedx[4] = {0.0};
  double seedy[4] = {0.0};

  TF1 *seedStart[4];
  for(int i = 0; i < nlayer; i++){
    seedStart[i] = new TF1(Form("seedStart%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
  }

  double sdx1[4] = {0.0};
  double sdx2[4] = {0.0};
  for(int i = 0; i < 4; i++){
    sdx1[i] = wireposx[i] + driftlth[i];
    sdx2[i] = wireposx[i] - driftlth[i];
    //cout<<sdx1[i]<<"     "<<sdx2[i]<<endl;
  }
  for(int i=0;i<nlayer;i++)
  {
    seedy[i] = wireposy[i];
  }
  const int nSeeds = 16;
  TF1 *ls[nSeeds];
  TF1 *ls1[nSeeds];
  TGraph *gSd[nSeeds];
  TGraph *gSd1[nSeeds];
  double sChi2[nSeeds]={0.0};
  double rsdcbx[nSeeds][3] = {0.0};
  double rsdcby[nSeeds][3] = {0.0};
  for(int i = 0; i < nSeeds; i++){
    ls[i] = new TF1(Form("ls_%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
    ls1[i] = new TF1(Form("ls1_%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
  }

  // Y Seed Finder
  double sdcbx[nSeeds][4] = {0.0};
  int count = -1;
  for(int i=0;i<nSeeds;i++)
  {
    count = i;
    sdcbx[i][0] = sdx2[0];
    sdcbx[i][1] = sdx2[1];
    sdcbx[i][2] = sdx2[2];
    sdcbx[i][3] = sdx2[3];

    if( (count/8)>=1 )
    {
      count=count-8;
      sdcbx[i][3] = sdx1[3];
    }
    if( (count/4)>=1 )
    {
      count=count-4;
      sdcbx[i][2] = sdx1[2];
    }
    if( (count/2)>=1 )
    {
      count=count-2;
      sdcbx[i][1] = sdx1[1];
    }
    if ( count>=1 )
    {
      sdcbx[i][0] = sdx1[0];
    }

    double sdcbx2[4] = {0.0};
    for(int j = 0 ;j<4;j++)
    {
      sdcbx2[j] = sdcbx[i][j];
    }
    gSd[i] = new TGraph(4,seedy, sdcbx[i]);
    //gSd[i] = new TGraph(4,seedy, sdcbx2);
    //cout<<"Seed x : "<<sdcbx[i][0]<<", seed x 2 : "<<sdcbx2[0]<<", y : "<<seedy[0]<<endl;
    //cout<<"Seed x : "<<sdcbx[i][1]<<", seed x 2 : "<<sdcbx2[1]<<", y : "<<seedy[1]<<endl;
    //cout<<"Seed x : "<<sdcbx[i][2]<<", seed x 2 : "<<sdcbx2[2]<<", y : "<<seedy[2]<<endl;
    //cout<<"Seed x : "<<sdcbx[i][3]<<", seed x 2 : "<<sdcbx2[3]<<", y : "<<seedy[3]<<endl;

    gSd[i] -> Fit(ls[i],"rqm");
    sChi2[i] = ls[i] -> GetChisquare();
    rsdcbx[i][0] = sdcbx[i][0];
    rsdcbx[i][1] = sdcbx[i][1];
    rsdcbx[i][2] = sdcbx[i][3];
    rsdcby[i][0] = seedy[0];
    rsdcby[i][1] = seedy[1];
    rsdcby[i][2] = seedy[3];

    gSd1[i] = new TGraph(3,rsdcby[i],rsdcbx[i]);
    gSd1[i]->Fit(ls1[i],"rqm");

  }

  double tmp = 100000.0;
  int seedChis = 0;
  for(int i = 0; i < nSeeds; i++){
    cout<<"Start to select minimum chi2 : "<<sChi2[i]<<endl;
    if(tmp > sChi2[i]) {
      tmp = sChi2[i];
      //cout<<"i : "<<i<<", chi2 : "<<sChi2[i]<<endl;
      seedChis = i;
    }else{
      tmp = tmp; 
    }
    //tmp = 5.0;
  }

  cout<<"Seed Chisquare Number : "<<seedChis<<endl;


  seedx[0] = sdcbx[seedChis][0];
  seedx[1] = sdcbx[seedChis][1];
  seedx[2] = sdcbx[seedChis][2];
  seedx[3] = sdcbx[seedChis][3];
  pars[10] = sChi2[seedChis];
  pars[11] = seedChis;
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  TF1 *lineSeed = new TF1("lineSeed","[0]*x+[1]",-100000000.0,100000000.0);
  lineSeed->SetLineColor(kRed+1);
  lineSeed->SetLineStyle(4);
  lineSeed->SetLineWidth(4);

  TGraph *grSeed = new TGraph(4,seedy,seedx);
  grSeed->SetMarkerColor(kRed+2);
  grSeed->SetMarkerStyle(25);
  grSeed->SetMarkerSize(2.0);
  grSeed->Fit(lineSeed,"rqm");
  //pars[0]=lineSeed->GetParameter(0);
  //pars[1]=lineSeed->GetParameter(1);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  double reseedx[3] = {0.0};
  double reseedy[3] = {0.0};
  reseedx[0] = seedx[0];
  reseedx[1] = seedx[1];
  reseedx[2] = seedx[3];
  reseedy[0] = seedy[0];
  reseedy[1] = seedy[1];
  reseedy[2] = seedy[3];

  TF1 *lineSeed1 = new TF1("lineSeed1","[0]*x+[1]",-100000000.0,100000000.0);
  lineSeed1->SetLineColor(kRed+1);
  lineSeed1->SetLineStyle(4);
  lineSeed1->SetLineWidth(4);

  TGraph *grSeed1 = new TGraph(3,reseedy,reseedx);
  grSeed1->SetMarkerColor(kRed+2);
  grSeed1->SetMarkerStyle(25);
  grSeed1->SetMarkerSize(2.0);
  grSeed1->Fit(lineSeed1,"rqm");

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TLegend *leg1 = new TLegend(0.50,0.46,0.80,0.64);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetTextSize(0.03);



  TF1 *bdcTrack = new TF1("bdcTrack","[0]*x+[1]",-100000000.0,100000000.0);
  bdcTrack->SetLineColor(kRed+1);
  bdcTrack->SetLineStyle(4);
  bdcTrack->SetLineWidth(4);

  bdcTrack->SetParameter(0, 1.0/lineSeed->GetParameter(0));
  bdcTrack->SetParameter(1, -lineSeed->GetParameter(1)/lineSeed->GetParameter(0));

  pars[0]=bdcTrack->GetParameter(0);
  pars[1]=bdcTrack->GetParameter(1);
  //cout<<"dhmoon FinderY2 grad : "<<pars[0]<<endl;

  TF1 *bdcTrack_3p = new TF1("bdcTrack_3p","[0]*x+[1]",-100000000.0,100000000.0);
  bdcTrack_3p->SetLineColor(kRed+1);
  bdcTrack_3p->SetLineStyle(4);
  bdcTrack_3p->SetLineWidth(4);

  bdcTrack_3p->SetParameter(0, 1.0/lineSeed1->GetParameter(0));
  bdcTrack_3p->SetParameter(1, -lineSeed1->GetParameter(1)/lineSeed1->GetParameter(0));

  double angle1 = 0.0;
  double grd1 = 0.0;
  grd1 = 1.0/lineSeed->GetParameter(0);
  if(atan(grd1)*180/pi > 0) angle1 = 90-atan(grd1)*180/pi;
  if(atan(grd1)*180/pi < 0) angle1 = -90-atan(grd1)*180/pi;


  double angle2 = 0.0;
  double grd2 = 0.0;
  grd2 = 1.0/lineSeed1->GetParameter(0);
  if(atan(grd2)*180/pi > 0) angle2 = 90-atan(grd2)*180/pi;
  if(atan(grd2)*180/pi < 0) angle2 = -90-atan(grd2)*180/pi;

  cout<<"Angle with 4p at Y : "<<angle1<<endl;
  cout<<"Angle with 3p at Y : "<<angle2<<endl;


  double distances[4];
  double distances1[4];
  // reconstructed drift length
  double recodriftlth[4];
  for(int i = 0; i < nlayer; i++){
    recodriftlth[i] = dist(wireposx[i],wireposy[i],2,bdcTrack->Eval(2),4,bdcTrack->Eval(4));
    distances[i] = recodriftlth[i] - driftlth[i];;
    distances1[i] = fabs(lineSeed->Eval(seedy[i])-wireposx[i]) - driftlth[i];;
    cout<<"Y distances["<<i<<"] : "<<distances[i]<<" distance 1 : "<<distances1[i]<<endl;
    pars[i+2] = distances1[i];
    //pars[i+2] = recodriftlth[i] - driftlth[i]; // for resolution
  }

  cout<<""<<endl;

  // line Y - seedx
  double distances2[4];
  double distances3[4];
  double recodriftlth2[4];
  for(int i = 0; i < nlayer; i++){
    recodriftlth2[i] = dist(wireposx[i],wireposy[i], 2,bdcTrack_3p->Eval(2),4,bdcTrack_3p->Eval(4));
    distances2[i] = recodriftlth2[i] - driftlth[i];;
    distances3[i] = fabs(lineSeed1->Eval(seedy[i])-wireposx[i]) - driftlth[i];;
    cout<<"Y distances2["<<i<<"] : "<<distances2[i]<<", distance3 : "<<distances3[i]<<endl;
    pars[i+6] = distances3[i];
  }



  dts[0] = dataDt1Y1;
  dts[1] = dataDt1Y2;
  dts[2] = dataDt2Y1;
  dts[3] = dataDt2Y2;



  c2->cd(2);
  hPadY1->Draw();
  wire1->SetMarkerSize(0.5);
  wire2->SetMarkerSize(0.5);
  wire3->SetMarkerSize(0.5);
  wire4->SetMarkerSize(0.5);

  wire1->Draw("pz same");
  wire2->Draw("pz same");
  wire3->Draw("pz same");
  wire4->Draw("pz same");

  arc1->Draw("");
  arc2->Draw("");
  arc3->Draw("");
  arc4->Draw("");

  bdcTrack->SetLineStyle(1);
  bdcTrack->SetLineWidth(3);
  bdcTrack->Draw("same");

  pars[12] = bdcTrack->GetX(wireposy[3]); 
  pars[13] = bdcTrack->GetX((wireposy[0]+wireposy[3])/2);
  pars[14] = bdcTrack->GetX(wireposy[0]);


  //pars[12] = lineSeed->Eval(seedy[3]); 
  //pars[13] = lineSeed->Eval((seedy[0]+seedy[3])/2);
  //pars[14] = lineSeed->Eval(seedy[0]);

  cout<<"Track position at Top Y : "<<pars[12]<<", seedx 3 : "<<seedy[3]<<endl;
  cout<<"Track position at Mid Y : "<<pars[13]<<", seedx 1 : "<<(seedy[0]+seedy[3])/2<<endl;
  cout<<"Track position at Bot Y : "<<pars[14]<<", seedx 0 : "<<seedy[0]<<endl;

  if(savepng){
    TLatex *lt1 = new TLatex();
    lt1->SetNDC();
    double angle = 0.0;
    if(atan(pars[0])*180/pi > 0) angle = 90-atan(pars[0])*180/pi;
    if(atan(pars[0])*180/pi < 0) angle = -90-atan(pars[0])*180/pi;
    lt1->DrawLatex(0.8,0.75,Form("Angle : %0.3f", angle ));
    lt1->DrawLatex(0.8,0.8,Form("#chi^{2} : %0.3f", lineSeed->GetChisquare() ));
    c2->SaveAs(Form("figs/plot_track_Y2_%d_%d.png",ievt,tracknum));
  }
  if(nodrawcan)
  {
    delete c2;
    delete hPadY;
    delete hPadY1;
  }
}


void trackFinderX2(float dataCh1X1, float dataDl1X1, float dataCh1X2, float dataDl1X2, float dataCh2X1, float dataDl2X1, float dataCh2X2, float dataDl2X2, float dataDt1X1, float dataDt1X2, float dataDt2X1, float dataDt2X2, int ievt, int tracknum, double *pars, double *dts){
  cout<<"Start track with x axis at "<<ievt<<" Event !!!"<<endl;
  //cout<<"Channel X11 : "<<dataCh1X1<<", X12 : "<<dataCh1X2<<", X21 : "<<dataCh2X1<<", X22 : "<<dataCh1X2<<endl;
  //cout<<"Drift Length DL11 : "<<dataDl1X1<<", DL12 : "<<dataDl1X2<<", DL21 : "<<dataDl2X1<<", DL22 : "<<dataDl2X2<<endl;
  TH2F *hPadX = new TH2F("hPadX",";x (mm) ;z (mm) ",175,-10.0,165,165,0,100.0);
  hPadX->GetYaxis()->CenterTitle();
  hPadX->GetXaxis()->CenterTitle();
  TH2F *hPadX1 = new TH2F("hPadX1",";x (mm) ;z (mm) ",175,-10,165,165,0.0,60.0);
  hPadX1->GetYaxis()->CenterTitle();
  hPadX1->GetXaxis()->CenterTitle();

  TCanvas *c1 = new TCanvas("c1","",1500,500);
  //c1->Divide(1,2);
  c1->cd();
  //c1->cd(1);
  hPadX->Draw();
  int firedChX[4] = {0};
  int firedChY[4] = {0, 1, 2, 3};

  int nlayer = 4; // number of layer (e.g 4 means xx'xx')
  int nwire = 6; //number of wire on each layer
  const int nwires = 32; //number of wire on each layer
                         // wire positions

  double wireX1[nwires] = {0.0}; 
  double wireX2[nwires] = {0.0}; 
  double wireX3[nwires] = {0.0}; 
  double wireX4[nwires] = {0.0}; 
  double wireY1[nwires] = {0.0}; 
  double wireY2[nwires] = {0.0}; 
  double wireY3[nwires] = {0.0}; 
  double wireY4[nwires] = {0.0}; 

  //double distanceChamber = 15.0;


  for(int iw = 0; iw < nwires; iw++){
    double cal1 = 0.0;
    double cal2 = 0.0;
    double cal3 = 0.0;
    double cal4 = 0.0;

    wireX1[iw] = iw*5.0 + Xwirestart+2.5+cal1; // y
    wireX2[iw] = iw*5.0 + Xwirestart+0.	+cal2; // y'
    wireX3[iw] = iw*5.0 + Xwirestart+2.5+cal3; // y
    wireX4[iw] = iw*5.0 + Xwirestart+0.	+cal4; // y'
    wireY1[iw] = FLH;
    wireY2[iw] = FLH+5.0; // 5.0
    wireY3[iw] = distanceChamber+wireY1[iw];
    wireY4[iw] = distanceChamber+wireY2[iw];
  }

  double wireX[4][nwires] = {0.0};

  for(int iwx = 0 ; iwx < nwires; iwx++){
    wireX[0][iwx] = wireX1[iwx];
    wireX[1][iwx] = wireX2[iwx];
    wireX[2][iwx] = wireX3[iwx];
    wireX[3][iwx] = wireX4[iwx];
  }


  c1->SetGrid();
  TGraph *wire1 = new TGraph(nwires,wireX1,wireY1);
  TGraph *wire2 = new TGraph(nwires,wireX2,wireY2);
  TGraph *wire3 = new TGraph(nwires,wireX3,wireY3);
  TGraph *wire4 = new TGraph(nwires,wireX4,wireY4);
  wire1->SetMarkerStyle(20);
  wire1->SetMarkerColor(kRed+1);
  wire2->SetMarkerStyle(20);
  wire2->SetMarkerColor(kRed+1);
  wire3->SetMarkerStyle(20);
  wire3->SetMarkerColor(kRed+1);
  wire4->SetMarkerStyle(20);
  wire4->SetMarkerColor(kRed+1);

  wire1->Draw("pz same");
  wire2->Draw("pz same");
  wire3->Draw("pz same");
  wire4->Draw("pz same");

  firedChX[0] = dataCh1X1;
  firedChX[1] = dataCh1X2;
  firedChX[2] = dataCh2X1;
  firedChX[3] = dataCh2X2;

  //cout<<"dhmoon chk 1-1 firedChX11 : "<<firedChX[0]<<", firedChX12 : "<<firedChX[1]<<", firedChX21 : "<<firedChX[2]<<", firedChX22 : "<<firedChX[3]<<endl;

  double wireposx[4] = {0.0};
  double wireposy[4] = {0.0};

  // input fired wire postion
  wireposx[0] = wireX1[firedChX[0]];wireposy[0] = wireY1[firedChY[0]];
  wireposx[1] = wireX2[firedChX[1]];wireposy[1] = wireY2[firedChY[1]];
  wireposx[2] = wireX3[firedChX[2]];wireposy[2] = wireY3[firedChY[2]];
  wireposx[3] = wireX4[firedChX[3]];wireposy[3] = wireY4[firedChY[3]];
  cout<<"dhmoon chk 1-2 wireposX11 : "<<wireposx[0]<<", wireposX12 : "<<wireposx[1]<<", wireposX21 : "<<wireposx[2]<<", wireposX22 : "<<wireposx[3]<<endl;
  cout<<"dhmoon chk 1-3 wireposX11 : "<<wireposy[0]<<", wireposX12 : "<<wireposy[1]<<", wireposX21 : "<<wireposy[2]<<", wireposX22 : "<<wireposy[3]<<endl;

  double driftlth[4];
  double dlcal1 = -0.02;
  double dlcal2 = -0.02;
  double dlcal3 = -0.02;
  double dlcal4 = -0.02;

  driftlth[0] = dataDl1X1+dlcal1;
  driftlth[1] = dataDl1X2+dlcal2;
  driftlth[2] = dataDl2X1+dlcal3;
  driftlth[3] = dataDl2X2+dlcal4;

  for(int l = 0; l < nlayer; l++){
    if(driftlth[l] < 0) driftlth[l] = 0.02;
  }

  TArc *arc1 = new TArc(wireposx[0],wireposy[0],driftlth[0],0,360);
  TArc *arc2 = new TArc(wireposx[1],wireposy[1],driftlth[1],0,360);
  TArc *arc3 = new TArc(wireposx[2],wireposy[2],driftlth[2],0,360);
  TArc *arc4 = new TArc(wireposx[3],wireposy[3],driftlth[3],0,360);
  arc1->SetFillStyle(4000); // 0.571
  arc2->SetFillStyle(4000);
  arc3->SetFillStyle(4000);
  arc4->SetFillStyle(4000);
  arc1->SetLineColor(kAzure+1);
  arc2->SetLineColor(kAzure+1);
  arc3->SetLineColor(kAzure+1);
  arc4->SetLineColor(kAzure+1);
  arc1->SetLineStyle(2);
  arc2->SetLineStyle(2);
  arc3->SetLineStyle(2);
  arc4->SetLineStyle(2);
  arc1->SetLineWidth(2);
  arc2->SetLineWidth(2);
  arc3->SetLineWidth(2);
  arc4->SetLineWidth(2);

  arc1->Draw("");
  arc2->Draw("");
  arc3->Draw("");
  arc4->Draw("");


  // try with different seeding
  // find seeding position
  double seedx[4] = {0.0};
  double seedy[4] = {0.0};

  TF1 *seedStart[4];
  for(int i = 0; i < nlayer; i++){
    seedStart[i] = new TF1(Form("seedStart%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
  }
  for(int i=0;i<nlayer;i++)
  {
    seedy[i] = wireposy[i];
  }
  double sdx1[4] = {0.0};
  double sdx2[4] = {0.0};
  for(int i = 0; i < 4; i++){
    sdx1[i] = wireposx[i] + driftlth[i];
    sdx2[i] = wireposx[i] - driftlth[i];
  }

  for(int i=0;i<nlayer;i++)
  {
    seedy[i] = wireposy[i];
  }

  const int nSeeds = 16;
  TF1 *ls[nSeeds];
  TF1 *ls1[nSeeds];
  TGraph *gSd[nSeeds];
  TGraph *gSd1[nSeeds];
  double sChi2[nSeeds]={-1};
  double rsdcbx[nSeeds][3] = {0.0};
  double rsdcby[nSeeds][3] = {0.0};
  for(int i = 0; i < nSeeds; i++){
    ls[i] = new TF1(Form("ls_%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
    ls1[i] = new TF1(Form("ls1_%d",i),"[0]*x+[1]",-100000000.0,100000000.0);
  }

  // X Seed Finder
  double sdcbx[nSeeds][4] = {0.0};
  int count = -1;
  for(int i=0;i<nSeeds;i++)
  {
    count = i;
    sdcbx[i][0] = sdx2[0];
    sdcbx[i][1] = sdx2[1];
    sdcbx[i][2] = sdx2[2];
    sdcbx[i][3] = sdx2[3];

    if( (count/8)>=1 )
    {
      count=count-8;
      sdcbx[i][3] = sdx1[3];
    }
    if( (count/4)>=1 )
    {
      count=count-4;
      sdcbx[i][2] = sdx1[2];
    }
    if( (count/2)>=1 )
    {
      count=count-2;
      sdcbx[i][1] = sdx1[1];
    }
    if ( count>=1 )
    {
      sdcbx[i][0] = sdx1[0];
    }

    gSd[i] = new TGraph(4,seedy,sdcbx[i]);
    //gSd[i] = new TGraph(4,sdcbx[i],seedy);
    gSd[i] -> Fit(ls[i],"rqm");
    sChi2[i] = ls[i] -> GetChisquare();

    rsdcbx[i][0] = sdcbx[i][0];
    rsdcbx[i][1] = sdcbx[i][1];
    rsdcbx[i][2] = sdcbx[i][3];
    rsdcby[i][0] = seedy[0];
    rsdcby[i][1] = seedy[1];
    rsdcby[i][2] = seedy[3];

    gSd1[i] = new TGraph(3,rsdcby[i],rsdcbx[i]);
    //gSd1[i] = new TGraph(3,rsdcbx[i],rsdcby[i]);
    gSd1[i]->Fit(ls1[i],"rqm");

  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  double tmp = 100000.0;
  int seedChis = 0;
  for(int i = 0; i < nSeeds; i++){
    //cout<<"Start to select minimum chi2 : "<<sChi2[i]<<endl;
    if(tmp > sChi2[i]) {
      tmp = sChi2[i];
      //cout<<"i : "<<i<<", chi2 : "<<sChi2[i]<<endl;
      seedChis = i;
    }else{
      tmp = tmp; 
    }
    //tmp = 5.0;
  }

  cout<<"Seed Chisquare Number : "<<seedChis<<endl;


  seedx[0] = sdcbx[seedChis][0];
  seedx[1] = sdcbx[seedChis][1];
  seedx[2] = sdcbx[seedChis][2];
  seedx[3] = sdcbx[seedChis][3];
  pars[10] = sChi2[seedChis];
  pars[11] = seedChis;
  //////////////////////////////////////////////////////////////////////////////////////////////////////  

  TF1 *lineSeed = new TF1("lineSeed","[0]*x+[1]",-100000000.0,100000000.0);
  lineSeed->SetLineColor(kRed+1);
  lineSeed->SetLineStyle(4);
  lineSeed->SetLineWidth(4);

  TGraph *grSeed = new TGraph(4,seedy,seedx);
  //TGraph *grSeed = new TGraph(4,seedx,seedy);
  grSeed->SetMarkerColor(kRed+2);
  grSeed->SetMarkerStyle(25);
  grSeed->SetMarkerSize(2.0);
  grSeed->Fit(lineSeed,"rqm");
  //pars[0]=lineSeed->GetParameter(0);
  //pars[1]=lineSeed->GetParameter(1);

  //////////////////////////////////////////////////////////////////////////////////////////////////
  double reseedx[3] = {0.0};
  double reseedy[3] = {0.0};
  reseedx[0] = seedx[0];
  reseedx[1] = seedx[1];
  reseedx[2] = seedx[3];
  reseedy[0] = seedy[0];
  reseedy[1] = seedy[1];
  reseedy[2] = seedy[3];

  TF1 *lineSeed1 = new TF1("lineSeed1","[0]*x+[1]",-100000000.0,100000000.0);
  lineSeed1->SetLineColor(kRed+1);
  lineSeed1->SetLineStyle(4);
  lineSeed1->SetLineWidth(4);

  TGraph *grSeed1 = new TGraph(3,reseedy,reseedx);
  //TGraph *grSeed1 = new TGraph(3,reseedx,reseedy);
  grSeed1->SetMarkerColor(kRed+2);
  grSeed1->SetMarkerStyle(25);
  grSeed1->SetMarkerSize(2.0);
  grSeed1->Fit(lineSeed1,"rqm");

  ////

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TLegend *leg1 = new TLegend(0.50,0.46,0.80,0.64);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetTextSize(0.03);
  //leg1->AddEntry(seedStart[seedNum],"fit with starting seed","L");
  //leg1->AddEntry(lineSeed,"fit with final seed","L");
  //leg1->AddEntry(lineChi2,"Reconstructed trajectory","L");
  //leg1->Draw("same");

  //lineSeed->Draw("same");


  TF1 *bdcTrack = new TF1("bdcTrack","[0]*x+[1]",-100000000.0,100000000.0);
  bdcTrack->SetLineColor(kRed+1);
  bdcTrack->SetLineStyle(4);
  bdcTrack->SetLineWidth(4);
  //cout<<"dhmoon FinderX2 grad 1 : "<<lineSeed->GetParameter(0)<<endl;

  bdcTrack->SetParameter(0, 1.0/lineSeed->GetParameter(0));
  bdcTrack->SetParameter(1, -lineSeed->GetParameter(1)/lineSeed->GetParameter(0));

  pars[0]=bdcTrack->GetParameter(0);
  pars[1]=bdcTrack->GetParameter(1);
  //cout<<"dhmoon FinderX2 grad 2 : "<<pars[0]<<endl;

  TF1 *bdcTrack_3p = new TF1("bdcTrack_3p","[0]*x+[1]",-100000000.0,100000000.0);
  bdcTrack_3p->SetLineColor(kRed+1);
  bdcTrack_3p->SetLineStyle(4);
  bdcTrack_3p->SetLineWidth(4);

  bdcTrack_3p->SetParameter(0, 1.0/lineSeed1->GetParameter(0));
  bdcTrack_3p->SetParameter(1, -lineSeed1->GetParameter(1)/lineSeed1->GetParameter(0));

  double angle1 = 0.0;
  double grd1 = 0.0;
  grd1 = 1.0/lineSeed->GetParameter(0);
  if(atan(grd1)*180/pi > 0) angle1 = 90-atan(grd1)*180/pi;
  if(atan(grd1)*180/pi < 0) angle1 = -90-atan(grd1)*180/pi;


  double angle2 = 0.0;
  double grd2 = 0.0;
  grd2 = 1.0/lineSeed1->GetParameter(0);
  if(atan(grd2)*180/pi > 0) angle2 = 90-atan(grd2)*180/pi;
  if(atan(grd2)*180/pi < 0) angle2 = -90-atan(grd2)*180/pi;

  cout<<"Angle with 4p at X : "<<angle1<<endl;
  cout<<"Angle with 3p at X : "<<angle2<<endl;


  double distances[4];
  double distances1[4];
  // reconstructed drift length
  double recodriftlth[4];
  for(int i = 0; i < nlayer; i++){
    recodriftlth[i] = dist(wireposy[i],wireposx[i],2,lineSeed->Eval(2),4,lineSeed->Eval(4));
    //recodriftlth[i] = dist(wireposx[i],wireposy[i],2,bdcTrack->Eval(2),4,bdcTrack->Eval(4));
    distances[i] = recodriftlth[i] - driftlth[i];;
    distances1[i] = fabs(lineSeed->Eval(seedy[i])-wireposx[i]) - driftlth[i];;
    cout<<"X distances["<<i<<"] : "<<distances[i]<<" distance 1 : "<<distances1[i]<<", difference : "<<fabs(distances[i])-fabs(distances1[i])<<endl;
    //pars[i+2] = distances1[i];
    pars[i+2] = distances1[i];
    //pars[i+2] = recodriftlth[i] - driftlth[i]; // for resolution
  }

  cout<<""<<endl;

  // line X - seedx
  double distances2[4];
  double distances3[4];
  double recodriftlth2[4];
  for(int i = 0; i < nlayer; i++){
    recodriftlth2[i] = dist(wireposy[i],wireposx[i], 2,lineSeed1->Eval(2),4,lineSeed1->Eval(4));
    //recodriftlth2[i] = dist(wireposx[i],wireposy[i], 2,bdcTrack_3p->Eval(2),4,bdcTrack_3p->Eval(4));
    distances2[i] = recodriftlth2[i] - driftlth[i];;
    distances3[i] = fabs(lineSeed1->Eval(seedy[i])-wireposx[i]) - driftlth[i];;
    cout<<"X distances2["<<i<<"] : "<<distances2[i]<<", distance3 : "<<distances3[i]<<", difference : "<<fabs(distances2[i])-fabs(distances3[i])<<endl;
    pars[i+6] = distances3[i];
  }
  // 0,1 -> 기울기,절편 2,3,4,5 -> 4개 full track에서의 distance, 6,7,(8),9 -> 3개 사용한 track에서의 distance (8) => resolution


  dts[0] = dataDt1X1;
  dts[1] = dataDt1X2;
  dts[2] = dataDt2X1;
  dts[3] = dataDt2X2;


  c1->cd(2);
  hPadX1->Draw();
  wire1->SetMarkerSize(0.5);
  wire2->SetMarkerSize(0.5);
  wire3->SetMarkerSize(0.5);
  wire4->SetMarkerSize(0.5);

  wire1->Draw("pz same");
  wire2->Draw("pz same");
  wire3->Draw("pz same");
  wire4->Draw("pz same");

  arc1->SetLineStyle(1);
  arc2->SetLineStyle(1);
  arc3->SetLineStyle(1);
  arc4->SetLineStyle(1);

  arc1->Draw("");
  arc2->Draw("");
  arc3->Draw("");
  arc4->Draw("");

  bdcTrack->SetLineStyle(1);
  bdcTrack->SetLineWidth(3);
  bdcTrack->Draw("same");

  pars[12] = bdcTrack->GetX(seedy[3]); 
  pars[13] = bdcTrack->GetX((seedy[0]+seedy[3])/2);
  pars[14] = bdcTrack->GetX(seedy[0]);


  //pars[12] = lineSeed->Eval(seedy[3]); 
  //pars[13] = lineSeed->Eval((seedy[0]+seedy[3])/2);
  //pars[14] = lineSeed->Eval(seedy[0]);


  //cout<<"Seed x1 : "<<seedx[0]<<", x2 : "<<seedx[1]<<", x3 : "<<seedx[2]<<", x4 : "<<seedx[3]<<endl;
  //cout<<"Seed y1 : "<<seedy[0]<<", y2 : "<<seedy[1]<<", y3 : "<<seedy[2]<<", y4 : "<<seedy[3]<<endl;

  //cout<<"Track x1 : "<<bdcTrack->GetX(seedy[3])<<", 2 : "<<bdcTrack->GetX(seedy[2])<<", 3 : "<<bdcTrack->GetX(seedy[1])<<", 4 : "<<bdcTrack->GetX(seedy[0])<<endl;
  //cout<<"Track y1 : "<<bdcTrack->GetX(seedx[3])<<", 2 : "<<bdcTrack->GetX(seedx[2])<<", 3 : "<<bdcTrack->GetX(seedx[1])<<", 4 : "<<bdcTrack->GetX(seedx[0])<<endl;

  //cout<<"Track x1' : "<<lineSeed->Eval(seedy[3])<<", 2 : "<<lineSeed->Eval(seedy[2])<<", 3 : "<<lineSeed->Eval(seedy[1])<<", 4 : "<<lineSeed->Eval(seedy[0])<<endl;
  //cout<<"Track y1' : "<<lineSeed->Eval(seedx[3])<<", 2 : "<<lineSeed->Eval(seedx[2])<<", 3 : "<<lineSeed->Eval(seedx[1])<<", 4 : "<<lineSeed->Eval(seedx[0])<<endl;

  cout<<"Track position at Top X : "<<pars[12]<<", seedx 3 : "<<seedy[3]<<endl;
  cout<<"Track position at Mid X : "<<pars[13]<<", seedx 1 : "<<(seedy[0]+seedy[3])/2<<endl;
  cout<<"Track position at Bot X : "<<pars[14]<<", seedx 0 : "<<seedy[0]<<endl;
  if(savepng)
  {
    TLatex *lt1 = new TLatex();
    lt1->SetNDC();
    //cout<<"Chi2 1 : "<<bdcTrack->GetChisquare()<<endl;
    //cout<<"Chi2 2 : "<<lineSeed->GetChisquare()<<endl;
    double angle = 0.0;
    if(atan(pars[0])*180/pi > 0) angle = 90-atan(pars[0])*180/pi;
    if(atan(pars[0])*180/pi < 0) angle = -90-atan(pars[0])*180/pi;
    lt1->DrawLatex(0.8,0.8,Form("#chi^{2} : %0.3f", lineSeed->GetChisquare() ));
    lt1->DrawLatex(0.8,0.75,Form("Angle : %0.3f", angle ));
    //bdcTrack->Draw("same");
    //lineSeed->Draw("same");
    c1->SaveAs(Form("figs/plot_track_X2_%d_%d.png",ievt,tracknum));
    //c1->SaveAs(Form("figs/plot_track_X2_%d_%d.pdf",ievt,tracknum));
    //c1->SaveAs(Form("figs/plot_track_X2_%d_%d.C",ievt,tracknum));
  } 
  if(nodrawcan)
  {
    delete c1;
    delete hPadX;
    delete hPadX1;
  }
}




void getLine(double x1, double y1, double x2, double y2, double &a, double &b, double &c)
{
  // (x- p1X) / (p2X - p1X) = (y - p1Y) / (p2Y - p1Y) 
  a = y1 - y2; // Note: this was incorrectly "y2 - y1" in the original answer
  b = x2 - x1;
  c = x1 * y2 - x2 * y1;
}

double dist(double pointX, double pointY, double lineX1, double lineY1, double lineX2, double lineY2)
{
  double a, b, c;
  getLine(lineX1, lineY1, lineX2, lineY2, a, b, c);
  XYZVector xp(a,b,0);
  //cout<<"dhmoon dist angle : "<<tan(xp.Phi())<<endl;
  //cout<<"a : "<<a<<", b : "<<b<<", c : "<<c<<endl;
  return abs(a * pointX + b * pointY + c) / sqrt(a * a + b * b);
}


