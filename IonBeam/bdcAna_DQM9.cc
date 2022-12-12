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
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"

using namespace std;


int main( int  argc, char* argv[] ){
  std::cout<< argc << " " << argv[0] << " : " << argv[1] << " initial : " << argv[2] << std::endl; 
  std::string filename = argv[1];
  int inevt=atoi(argv[2]);
  if (inevt<0) inevt=0;
  std::cout << "Read : " << filename << std::endl; 
  TApplication* app = new TApplication("app",&argc,argv ); 

  TFile* itf = new TFile(filename.c_str());
  TTree* itr = (TTree*)itf->Get("DataTree");
  Int_t EventNum;
  UShort_t type;
  UShort_t ver;
  UShort_t id;
  UShort_t trigTime;
  UShort_t dataLen;
  UInt_t   trigCount;
  UInt_t   eventNum;
  UInt_t   spillNum;
  Int_t    DataLength;  
  UShort_t Data[128000];
  Int_t    TrigCount;
  UShort_t eNum;
  UShort_t sNum;
  itr->SetBranchAddress("EventNum" ,&EventNum );
  itr->SetBranchAddress("type"     ,&type     );
  itr->SetBranchAddress("ver"      ,&ver      );
  itr->SetBranchAddress("id"       ,&id       );
  itr->SetBranchAddress("trigTime" ,&trigTime );
  itr->SetBranchAddress("dataLen"  ,&dataLen  );
  itr->SetBranchAddress("trigCount",&trigCount);
  itr->SetBranchAddress("eventNum" ,&eventNum );
  itr->SetBranchAddress("spillNum" ,&spillNum );

  itr->SetBranchAddress("DataLength",&DataLength);
  itr->SetBranchAddress("Data"      ,Data       );
  itr->SetBranchAddress("TrigCount" ,&TrigCount );
  itr->SetBranchAddress("eNum"      ,&eNum      );
  itr->SetBranchAddress("sNum"      ,&sNum      );

  //TCanvas* can = new TCanvas("can","can",800,800);
  TCanvas* can = new TCanvas("can","can",1200,800);
  can->Divide(3,2);

  TGraph* grQDC[64];
  TGraph* grTDC[64];
  for( int i = 0; i< 64; i++){
    grQDC[i] = new TGraph();
    grTDC[i] = new TGraph();
    grQDC[i]->SetMarkerStyle(i%8+20);
    grTDC[i]->SetMarkerStyle(i%8+20);
    grQDC[i]->SetMarkerColor(i/8+20);
    grTDC[i]->SetMarkerColor(i/8+20);
  }
  /*
     TH2D* hisQDC = new TH2D("hisQDC","hisQDC;time;ch",64,0,64,64,0,64);  
     TH1D* hisQDCSum = new TH1D("hisQDCSum","hisQDCSum;ch",64,0,64);
     TH2D* hisTDC = new TH2D("hisTDC","hisTDC;time;ch",64,0,64,64,0,64); 
     TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",64,0,64,400,-200,200);
     */
  TH2D* hisQDC = new TH2D("hisQDC","hisQDC;time;ch",128,0,128,64,0,64);  
  TH1D* hisQDCSum = new TH1D("hisQDCSum","hisQDCSum;ch",64,0,64);
  //###TH2D* hisTDC = new TH2D("hisTDC","hisTDC;time;ch",20,40,60,64,0,64); 
  TH2D* hisTDC = new TH2D("hisTDC","hisTDC;time;ch",128,0,128,64,0,64); 
  //###TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",20,40,60,800,0,800);
  //######    TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",128,0,128,800,0,800);
  TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",128,0,128,600,-100,500);
  TH2D* hisXYs = new TH2D("hisXYs","hisXYs;Ch X;Ch Y",33,0,33,33,0,33);
  TH1D* hisTDCDis = new TH1D("hisTDCDis",";time (ns); Counts",300,1850,2150);
  //TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",128,0,128,800,0,800);
  //TH2D* hisWave= new TH2D("hisWave","hisWave;time;QDC",128,0,128,1000,-200,800);


  std::cout << "itr->GetEntries() : " << itr->GetEntries() << std::endl;
  std::cout << "inevt : " << inevt << std::endl;

  double QDCCUT = 320;
  for( int ievt = inevt; ievt < itr->GetEntries(); ievt++){
    itr->GetEntry(ievt);
    hisQDC->Reset();
    hisTDC->Reset();
    hisWave->Reset();
    hisQDCSum->Reset();
    hisXYs->Reset();
    hisTDCDis->Reset();

    Int_t nPoints = DataLength / 128;
    Double_t QDCSum[64]={0};
    //std::cout<< "point" << std::endl;
    std::cout<< "Event : " << ievt << " !!!"<<std::endl;
    int firedch1[20] = {0};
    int firedch2[20] = {0};
    int cnt1 = 0;
    int cnt2 = 0;
    for( int ich = 0; ich < 64; ich++){
      //           if (ievt%64!=ich) continue;
      //###                for (int ich = 38; ich < 39; ich++) {
      //if(ich == 0 || ich == 31 || ich == 32 || ich == 63) continue;
      for( int ip = 0; ip < nPoints; ip++){

        double tmpQDC=Data[ip*128+ich]-QDCCUT;
        unsigned short ftt
          = ((trigTime & 0xFF00 ) >> 8 )
          + ((trigTime & 0x007F ) << 8 );

        if(!(Data[ip*128+64+ich] > 0 )) continue;

        //###if (tmpQDC > 280){
        //if(!(ip>44 && ip<48)) continue; 
        //if(!(ip>44 && ip<48)) continue; 
        hisQDC->Fill(ip,ich,tmpQDC);
        hisTDC->Fill(ip,ich,Data[ip*128+64+ich]);

        //hisWave->Fill(ip,Data[ip*128+ich]-Data[ich]);
        hisWave->Fill(ip,tmpQDC);
        //###                    QDCSum[ich] += tmpQDC-280;
        //###                    QDCSum[ich] += tmpQDC-ped[ich]*100/nPoints;
        QDCSum[ich] += tmpQDC;
        //      if(ich < 32 && ip>44 && ip<48) {
        if(Data[ip*128+64+ich] > 0 ) {
          firedch1[cnt1] = ich;
          double time1 = (ftt - (Data[ip*128+64+ich]&0x7FFF));
          if(time1 < 0) time1 = time1+32767;
          cnt1++;
        }
        //      }
        //###                    if(ich >= 32 && ip>44 && ip<48) {
        if(Data[ip*128+64+ich] > 0 ) {
          firedch2[cnt2] = ich;
          double time2 = (ftt - (Data[ip*128+64+ich]&0x7FFF));
          if(time2 < 0) time2 = time2+32767;
          //if(time2 < 0) cout<<"Minus Time ??? ftt : "<<ftt<<", TDC 2 : "<<(Data[ip*128+64+ich]&0x7FFF)<<endl;
          cnt2++;
        }
        //###                    }
        if( (Data[ip*128+64+ich] &0x7FFF)  != 0 ){
          double time = (ftt - (Data[ip*128+64+ich]&0x7FFF));
          if(time < 0) time = time + 32767;
          hisTDCDis->Fill(time);
        }

        //###}
      }
      hisQDCSum->Fill(ich, QDCSum[ich]);
    }

    cout<<"# of ch 1 : "<<cnt1<<", # of ch 2 : "<<cnt2<<endl;
    for(int ich1 = 0; ich1 < cnt1; ich1++){ 
      for(int ich2 = 0; ich2 < cnt2; ich2++){
        //cout<<"ich1 : "<<firedch1[ich1]<<", ich2 : "<<firedch2[ich2]-32<<endl;
        //if(firedch1[ich1] == 0 || firedch2[ich2] == 0) continue;
        //if(firedch1[ich1] == 30 || firedch2[ich2] == 63) continue;
        hisXYs->Fill(firedch1[ich1],(31-(firedch2[ich2]-32)));
      }
    }
    cout<<"# of 2D Hits : "<<hisXYs->GetEntries()<<endl;


    //std::cout << "QCDSum : " << QDCSum[52] << std::endl;//21
    /*
       for (int j=0;j<64;j++) {
       std::cout << j << " - " << hisQDCSum->GetBinContent(j+1)/100 << std::endl;
       }
       */
    gStyle->SetPalette(kRainBow);
    can->cd(1);
    gPad->SetGridx();
    gPad->SetGridy();    
    gPad->SetLogz(0);
    double zmax = hisQDC->GetMaximum();
    double zmin = hisQDC->GetMinimum();
    hisQDC->GetZaxis()->SetRangeUser(zmin,zmax);

    hisQDC->Draw("colz");
    can->cd(2);
    gPad->SetGridx();
    gPad->SetGridy();
    hisTDC->Draw("colz");
    can->cd(3);
    gPad->SetGridx();
    gPad->SetGridy();
    hisXYs->Draw("colz");
    can->cd(4);
    gPad->SetGridx();
    gPad->SetGridy();
    hisQDCSum->Draw("HIST");
    can->cd(5);
    gPad->SetGridx();
    gPad->SetGridy();
    hisWave->Draw("colz");

    can->cd(6);
    gPad->SetGridx();
    gPad->SetGridy();
    gPad->SetLogy();
    hisTDCDis->Draw("E");

    can->Modified();
    can->Update();
    gSystem->ProcessEvents();
    getchar(); 
    }

    app->Run();

}
