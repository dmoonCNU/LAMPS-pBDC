#include "TFile.h"
#include "TROOT.h"
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
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLatex.h"

using namespace std;

void bdcDrawAll(){
  gROOT->Macro("~/rootlogon.C");
  gStyle->SetOptStat(0);
  gStyle->SetPadRightMargin(0.1);

  //TFile* itf = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD16.root","READ");
  //TFile* itf = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD17.root","READ");
  //TFile* itf = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD18.root","READ");
  TFile* itf = new TFile("../220601_Cosmic_c1430_a1430_0C00_evt10k_PMTCoin_Delay180ns_expset_KOMACset_t101_ASD19.root","READ");
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

  TCanvas* can = new TCanvas("can","can",0,66,1400,700);
  //TCanvas* can = new TCanvas("can","can",0,66,1000,600);
  can->Divide(4,2);

  TH2D* hisQDC1= new TH2D("hisQDC1","hisQDC1;time;QDC",11,0,11,800,200,800);
  TH2D* hisQDC2= new TH2D("hisQDC2","hisQDC2;time;QDC",11,0,11,800,200,800);
  TH1D* hisTDC1 = new TH1D("hisTDC1" ,"hisTDC1;channel;TDC Hit",64,0,64);
  TH1D* hisTDC2 = new TH1D("hisTDC2" ,"hisTDC2;channel;TDC Hit",64,0,64);

  TH2D* hNHitsCh1 = new TH2D("hNHitsCh1",";channel;# of hits",64,0,64,100,0,1000);
  TH2D* hNHitsCh2 = new TH2D("hNHitsCh2",";channel;# of hits",64,0,64,10,0,10);

  TH1D* hNHits1 = new TH1D("hNHits1",";# of hits;Counts",10,0,10);
  TH1D* hNHits2 = new TH1D("hNHits2",";# of hits;Counts",10,0,10);

  TH2D* hChXY1 = new TH2D("hChXY1",";X;X'",32,0,32,32,0,32);
  TH2D* hChXY2 = new TH2D("hChXY2",";X;X'",32,0,32,32,0,32);

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();

  int Eff1=0;
  int Eff=0;
  int lastTDC1=0;
  int nHits1 = 0;
  int nHits2 = 0;
  int cnt1 = 0;
  int cnt2 = 0;
  int ch11 = 0;
  int ch12 = 0;
  int ch21 = 0;
  int ch22 = 0;
  double QDCcut = 360; // 300 : 0800 ASD 16, 360 : 0C00 ASD 16
  for( int ievt = 0; ievt < itr->GetEntries(); ievt++){
    itr->GetEntry(ievt);

    Int_t nPoints = DataLength / 128;
    bool isFired1=false;
    bool isFired=false;
    for( int ich = 0; ich < 64; ich++){
      for( int ip = 0; ip < nPoints; ip++){
        double tmpQDC=Data[ip*128+ich];

        if ( Data[ip*128+64+ich] > 0) hisQDC1->Fill(ip,tmpQDC);
        if ( Data[ip*128+64+ich] > 0) {
          hisTDC1->Fill( ich );
          if(ich < 32){
            ch11 = ich;
          }else{
            ch12 = 64-ich;
          } 
          if ((ievt-lastTDC1)<=10) lastTDC1=ievt;
          isFired1=true;
          cnt1++;
        }

        if (tmpQDC > QDCcut){ 
          if(!(ip > 2 && ip < 8)) continue;

          if (Data[ip*128+64+ich] > 0) { // when TDC exists
            
            hisQDC2->Fill(ip,tmpQDC);
            if(Data[ip*128+64+ich] > 0 ) {
              if(ich < 32){
                ch21 = ich;
              }else{
                ch22 = 64-ich;
              } 
              hisTDC2->Fill( ich );
              isFired=true;
              cnt2++;
            }
          }
        }
      }

    }
    hChXY1->Fill(ch11, ch12);
    hChXY2->Fill(ch21, ch22);
    nHits1=cnt1;
    nHits2=cnt2;
    cnt1 = 0;
    cnt2 = 0;
    //cout<<"nHits 1 : "<<nHits1<<", nHits 2 : "<<nHits2<<endl;
    //hNHitsCh1->Fill(ich,nHits1);
    //hNHitsCh2->Fill(ich,nHits2);
    if (isFired1) Eff1++;
    if (isFired) Eff++;
    hNHits1->Fill(nHits1);
    hNHits2->Fill(nHits2);
  }

  std::cout << "Num. of Trig. : " << itr->GetEntries() << std::endl;
  std::cout << "Entry Num. of TDC1: " << hisTDC1->GetEntries() << std::endl;
  std::cout << "Entry Num. of TDC2: " << hisTDC2->GetEntries() << std::endl;
  std::cout << "Num. of triggered events (TDC1 fired) " << Eff1 << std::endl;
  std::cout << "Num. of triggered events (TDC2 fired) " << Eff << std::endl;
  std::cout << "Last TDC1 fired event (TDC1 fired) " << lastTDC1 << std::endl;
  std::cout << "Efficiency 1 : " << (double) Eff / itr->GetEntries() << std::endl;
  std::cout << "Efficiency 2 : " << (double) Eff1 / itr->GetEntries() << std::endl;

  //set_plot_style();
  gStyle->SetCanvasPreferGL(1);
  //gStyle->CreateGradientColorTable();

  can->cd(1);
  gPad->SetLogz();
  hisQDC1->Draw("colz");
  lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1380 at ASD 16 DAC : 0C00");
  //lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1420 at ASD 16 DAC : 0800");
  //lt1->DrawLatex(0.2, 0.9, "HV C-1415 A-1375 at ASD 18");

  can->cd(2);
  hisTDC1->Draw("E");

  can->cd(3);
  hNHits1->Draw("E");
  lt1->DrawLatex(0.6, 0.80, Form("Mean : %0.2f", hNHits1->GetMean()));

  can->cd(4);
  hChXY1->Draw("colz");

  can->cd(5);
  gPad->SetLogz();
  hisQDC2->Draw("colz");
  lt1->DrawLatex(0.2, 0.17, "After removing pedstal");

  can->cd(6);
  hisTDC2->Draw("E");
  lt1->DrawLatex(0.2, 0.17, "After removing pedstal");

  can->cd(7);
  hNHits2->Draw("E");
  lt1->DrawLatex(0.4, 0.9, "After removing pedstal");
  lt1->DrawLatex(0.6, 0.80, Form("Mean : %0.2f", hNHits2->GetMean()));

  can->cd(8);
  hChXY2->Draw("colz");

  can->SaveAs("220621_Cosmic_c1430_a1430_0C00_evt30k_t101_ASD19.png");
  //can->SaveAs("220621_Cosmic_c1430_a1430_0C00_evt30k_t101_ASD18.png");
  //can->SaveAs("220621_Cosmic_c1430_a1430_0C00_evt30k_t101_ASD17.png");
  //can->SaveAs("220621_Cosmic_c1430_a1430_0C00_evt30k_t101_ASD16.png");


}
