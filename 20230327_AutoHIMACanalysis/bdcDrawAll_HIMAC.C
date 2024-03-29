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

void set_plot_style()
{
	const Int_t NRGBs = 5;
	const Int_t NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
}

//void bdcDrawAll_HIMAC(int locano=2, int RunNo=3067, int QDCopt=0){
//void bdcDrawAll_HIMAC(int locano=2, int RunNo=3067, int QDCopt=1){

void bdcDrawAll_HIMAC(int locano=___LOCANO___, int RunNo=___RUNNUMBER___, int QDCopt=___QDCOPT___, int maxip=___MAXIP___, int minip=___MINIP___){

//sed -i '.bak' -e "s,___LOCA___,$loca,g" -e "s,___RUNNUMBER___,$RunNumber,g" -e "s,___LOCANO___,$locano,g" *.C -e "s,___QDCOPT___,$QDCopt,g" -e "s,___T0OPT___,$t0opt,g" -e "s,___TDOPT___,$tdopt,g" -e "s,___HITOPT___,$hitopt,g" -e "s,___CHOPT___,$chopt,g" -e "s,___CENTOPT___,$centopt,g" -e "s,___PEDOPT___,$pedopt,g" *.C -e "s,___MINIP___,$minip,g" -e "s,___MAXIP___,$maxip,g" -e "s,___SAVEPNG___,$savepng,g" -e "s,___CORR___,$corr_,g" -e "s,___NSIGMA___,$nsigma,g" -e "s,___ANGLECUT___,$angleCut_,g" -e "s,___MINANG___,$minang,g" -e "s,___MAXANG___,$maxang,g" -e "s,___LTOPT___,$ltopt,g" -e "s,___LTCH___,$ltch,g" -e "s,___RMK___,$rmk,g" *.C

	gROOT->Macro("~/rootlogon.C");
	gStyle->SetOptStat(0);
	gStyle->SetPadRightMargin(0.1);

	TFile* fout = new TFile("bdcDrawAll_KOMAC_getped.root","RECREATE");

	TH1D* hped[3];
	for (int ASDNo = 0;ASDNo<3;ASDNo++){

		hped[ASDNo]= new TH1D(Form("hped_ASD%d",ASDNo+16),";Ch;Average Ped",64,0,64);

		//TFile* itf = new TFile(Form("%s/%d_ASD%d.root",loca.Data(),RunNo,ASDNo+16),"READ");

/*		
		   TFile* itf;
		   if (locano==1) itf = new TFile(Form("~/Research_2023/202302HIMACBeamTest/AllData/1_Proton100MeV/Data/%d_ASD%d.root",RunNo,ASDNo+16),"READ");
		   else if (locano==2) itf = new TFile(Form("~/Research_2023/202302HIMACBeamTest/AllData/2_Carbon200MeV/Data/%d_ASD%d.root",RunNo,ASDNo+16),"READ"); 
		   else if (locano==3) itf = new TFile(Form("~/Research_2023/202304CosmicCNU/Data/%d_ASD%d.root",RunNo,ASDNo+16),"READ"); 
*/
		TFile* itf = new TFile(Form("___LOCA___/%d_ASD%d.root",RunNo,ASDNo+16),"READ");

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

		//TCanvas* can = new TCanvas("can","can",0,66,1400,700);
		//TCanvas* can = new TCanvas("can","can",0,66,1000,600);
		//can->Divide(4,2);
		TCanvas* can = new TCanvas("can","can",0,66,1650,700);
		can->Divide(5,2);

		TH2D* hisQDC1= new TH2D("hisQDC1","hisQDC1;IP (~32 ns);QDC",10,0,10,800,0,800);
		TH2D* hisQDC2= new TH2D("hisQDC2","hisQDC2;IP (~32 ns);QDC",10,0,10,800,0,800);

		TH1D* hisTDC1 = new TH1D("hisTDC1" ,"hisTDC1;channel;TDC Hit",64,0,64);
		TH1D* hisTDC2 = new TH1D("hisTDC2" ,"hisTDC2;channel;TDC Hit",64,0,64);

		TH1D* hisQDCDist1= new TH1D("hisQDCDist1","hisQDCDist1;QDC;Entries",800,0,800);
		TH1D* hisQDCDist2= new TH1D("hisQDCDist2","hisQDCDist2;QDC;Entries",800,0,800);

		TH1D* hNHits1 = new TH1D("hNHits1",";# of hits;Counts",10,0,10);
		TH1D* hNHits2 = new TH1D("hNHits2",";# of hits;Counts",10,0,10);

		TH2D* hChXY1 = new TH2D("hChXY1",";X;X'",32,0,32,32,0,32);
		TH2D* hChXY2 = new TH2D("hChXY2",";X;X'",32,0,32,32,0,32);

		TH2D* hNHitsCh1 = new TH2D("hNHitsCh1",";channel;# of hits",64,0,64,10,0,10);
		TH2D* hNHitsCh2 = new TH2D("hNHitsCh2",";channel;# of hits",64,0,64,10,0,10);

//////////////////////////////////////////////////////////////////////////////////////

		TH1D* hQDC1 = new TH1D("hQDC1",";QDC;Counts",500,0,1000);
		TH1D* hIpTime = new TH1D("hIpTime",";ip;Counts",120,0,120);
		TH1D* hIpTimeQDC = new TH1D("hIpTimeQDC",";ip;QDC",120,0,120);
		TH2D* hIpTimeQDC2 = new TH2D("hIpTimeQDC2",";ip;QDC",120,0,120,800,0,800);

		TH1D* hQDCPeak1 = new TH1D("hQDCPeak1",";IP;Average QDC",10,0,10);
		TH1D* hQDCPeak2 = new TH1D("hQDCPeak2",";IP;Average QDC",10,0,10);
		TH1D* hQDCPed1 = new TH1D("hQDCPed1",";IP;Average QDC",10,0,10);
		TH1D* hQDCPed2 = new TH1D("hQDCPed2",";IP;Average QDC",10,0,10);

		TH1D* hQDCPeak11 = new TH1D("hQDCPeak11",";IP;Second peak",2000,0.05,1.05);

		for (int i=0;i<10;i++) {
			hQDCPeak1->SetBinContent(i+1,0);
			hQDCPeak2->SetBinContent(i+1,0);
		}

		TLatex *lt1 = new TLatex();
		lt1->SetNDC();

		int Eff1=0;
		int Eff=0;
		int lastTDC1=0;
		int nHits1 = 0;
		int nHits2 = 0;
		int cnt1 = 0;
		int cnt2 = 0;
//		int ch11 = 0;
//		int ch12 = 0;
//		int ch21 = 0;
//		int ch22 = 0;
/*		
		int minip = 91;
		int maxip = 94;

		minip = -1;
		maxip = 10;
*/

		double QDCcut = 320; //460; // 300 : 0800 ASD 16, 360 : 0C00 ASD 16
							 //double QDCcut = 600; //460; // 300 : 0800 ASD 16, 360 : 0C00 ASD 16
		QDCcut = 0.0;
		double QDCMax = 560;
		QDCMax = 0;


		int QDCPeak1=0;
		int QDCPeak2=0;
		int QDCPed1=0;
		int QDCPed2=0;


		int QDCPeak1Ch[3]={16,15,16};
		int QDCPeak2Ch[3]={48,48,48};


		for( int ievt = 0; ievt < itr->GetEntries(); ievt++){
			//for( int ievt =19; ievt < 20; ievt++)

			int ch11[32]={0};
			int ch12[32]={0};
			int ch21[32]={0};
			int ch22[32]={0};

			bool passed = false;
			itr->GetEntry(ievt);
			//if(ievt == 10) break;

			//cout<<"DataLength : "<<DataLength<<endl;
			Int_t nPoints = DataLength / 128;
			//cout<<"nPoints : "<<nPoints<<endl;
			bool isFired1=false;
			bool isFired=false;
			bool QDCPeak1done=false;
			bool QDCPeak2done=false;
			bool QDCPed1done=false;
			bool QDCPed2done=false;

			bool isTDC1=false;
			bool isTDC2=false;

			for( int ich = 0; ich < 64; ich++){
				//if((ich > 30 && ich < 34)) continue;
				//if((ich > 30 && ich < 33)) continue;

				for( int ip = 0; ip < nPoints; ip++){
					double tmpQDC=Data[ip*128+ich];
					//					if(!(ip > minip && ip < maxip)) continue;
					//					if (!( Data[ip*128+64+ich] > 0)) continue;

					//if(!(tmpQDC > 330)) continue;
					//					if ( Data[ip*128+64+ich] > 0) hisQDC1->Fill(ip,tmpQDC);

					// Nocut option Pad 1-5
					if (QDCopt==1) {hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC);}
					else if (QDCopt==2) {
						if ( Data[ip*128+64+ich] > 0) {hisQDC1->Fill(ip,tmpQDC);hisQDCDist1->Fill(tmpQDC);}
					}
					if ( Data[ip*128+64+ich] > 0) {
						hisTDC1->Fill( ich );
						if(ich < 32){
							if (QDCPeak1Ch[ASDNo]-2<=ich && ich<=QDCPeak1Ch[ASDNo]+2) isTDC1=true;
							ch11[ich]=1;
						}else{
							if (QDCPeak2Ch[ASDNo]-2<=ich && ich<=QDCPeak2Ch[ASDNo]+2) isTDC2=true;
							ch12[ich-31]=1;
						} 
						cnt1++;
					}


					//cut option Pad 6-10

					if(!(ip > minip && ip < maxip)) continue;
					if (!( Data[ip*128+64+ich] > 0)) continue;
					//if(!(tmpQDC > 330)) continue;
					if (!(tmpQDC > QDCcut)) continue;


					hisTDC1->Fill( ich );
					hisQDCDist2->Fill(tmpQDC);
					hQDC1->Fill(tmpQDC);
					hIpTime->Fill(ip);
					hIpTimeQDC2->Fill(ip,tmpQDC);
					if ((ievt-lastTDC1)<=10) lastTDC1=ievt;
					isFired1=true;

					hisQDC2->Fill(ip,tmpQDC);
					if(ich < 32){
						ch21[ich]=1;
						if (ich==QDCPeak1Ch[ASDNo]) {
							if (!(QDCPeak1done)) {
								QDCPeak1++;
								for (int ipk=0;ipk<nPoints;ipk++){
									double tmpQDC2=Data[ipk*128+ich];
									hQDCPeak1->SetBinContent(ipk+1,(tmpQDC2+hQDCPeak1->GetBinContent(ipk+1)*(QDCPeak1-1))/QDCPeak1);
									//###if (QDCPeak1<5) std::cout << ievt << " : " << QDCPeak1 << " - " << ipk << " - " << tmpQDC2 << " - " << hQDCPeak1->GetBinContent(ipk+1) << std::endl;
								}
								QDCPeak1done=true;
							}
						}
					}else{
						ch22[ich-31]=1;
						if (ich==QDCPeak2Ch[ASDNo]) {
							if (!(QDCPeak2done)) {
								QDCPeak2++;
								for (int ipk=0;ipk<nPoints;ipk++){
									double tmpQDC2=Data[ipk*128+ich];
									//hQDCPeak2->SetBinContent(ipk+1,(tmpQDC2+hQDCPeak2->GetBinContent(ipk+1)*(QDCPeak2-1))/QDCPeak2);
									//	if (QDCPeak2<5) std::cout << QDCPeak2 << " - " << ipk << " - " << tmpQDC2 << " - " << hQDCPeak2->GetBinContent(ipk+1) << std::endl;
								}
								QDCPeak2done=true;
							}
						}
					} 
					hisTDC2->Fill( ich );
					isFired=true;
					cnt2++;

				}//ip
				if (ich==QDCPeak1Ch[ASDNo] && !QDCPed1done && !isTDC1) {
					QDCPed1++;
					for (int ipk=0;ipk<nPoints;ipk++){
						double tmpQDC2=Data[ipk*128+ich];
						hQDCPed1->SetBinContent(ipk+1,(tmpQDC2+hQDCPed1->GetBinContent(ipk+1)*(QDCPed1-1))/QDCPed1);
						//if (QDCPed1<5) std::cout << QDCPed1 << " - " << ipk << " - " << tmpQDC2 << " - " << hQDCPed1->GetBinContent(ipk+1) << std::endl;
					}
					QDCPed1done=true;

				}
				if (ich==QDCPeak2Ch[ASDNo] && !QDCPed2done && !isTDC2) {
					QDCPed2++;
					for (int ipk=0;ipk<nPoints;ipk++){
						double tmpQDC2=Data[ipk*128+ich];
						//hQDCPed2->SetBinContent(ipk+1,(tmpQDC2+hQDCPed2->GetBinContent(ipk+1)*(QDCPed2-1))/QDCPed2);
						//###if (QDCPed2<5) std::cout << QDCPed2 << " - " << ipk << " - " << tmpQDC2 << " - " << hQDCPed2->GetBinContent(ipk+1) << std::endl;
					}
					QDCPed2done=true;

				}

			}//ich
			double maxtmp=-999;
			int maxch=-9;
			/*		   for (int i=0;i<64;i++) {
			//std::cout << "CH " << i << " - " << hisTDC1->GetBinContent(i+1) << std::endl;
			if (maxtmp<hisTDC1->GetBinContent(i+1)) {maxtmp=hisTDC1->GetBinContent(i+1);maxch=i;}
			}
			 */
			for (int i=0;i<32;i++) {
				if (ch11[i]==0) continue;
				for (int j=0;j<32;j++) {

					if (ch12[j]==0) continue;
					hChXY1->Fill(i, j);
				}
			}
			for (int i=0;i<32;i++) {
				if (ch21[i]==0) continue;
				for (int j=0;j<32;j++) {

					if (ch22[j]==0) continue;
					hChXY2->Fill(i, j);
				}
			}

			//hChXY1->Fill(ch11, ch12);
			//hChXY2->Fill(ch21, ch22);
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
			//hNHits2->Fill(nHits2);
			if (nHits2>0) hNHits2->Fill(nHits2);

			hQDCPeak11->Fill((Data[4*128+(QDCPeak1Ch[ASDNo])]-200)/(Data[6*128+(QDCPeak1Ch[ASDNo])]-200));

		}//ievt
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
		//###lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1380 at ASD 16 DAC : 0C00");
		//lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1420 at ASD 16 DAC : 0800");
		//lt1->DrawLatex(0.2, 0.9, "HV C-1415 A-1375 at ASD 18");

				can->cd(2);
		hisTDC1->Draw("E");
		lt1->DrawLatex(0.2, 0.17, "After removing pedstal");

		can->cd(3);
		//hisTDC1->Draw("E");
		gPad->SetLogy();
		hisQDCDist1->Draw("e");

		can->cd(4);
		hNHits1->Draw("E");
		lt1->DrawLatex(0.6, 0.80, Form("Mean : %0.2f", hNHits1->GetMean()));

		can->cd(5);
		hChXY1->Draw("colz");

		can->cd(6);
		gPad->SetLogz();
		hisQDC2->Draw("colz");
		//###lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1380 at ASD 16 DAC : 0C00");
		//lt1->DrawLatex(0.2, 0.9, "HV C-1420 A-1420 at ASD 16 DAC : 0800");
		//lt1->DrawLatex(0.2, 0.9, "HV C-1415 A-1375 at ASD 18");
		lt1->DrawLatex(0.2, 0.17, "After removing pedstal");

		can->cd(7);
		hisTDC2->Draw("E");
		lt1->DrawLatex(0.2, 0.17, "After removing pedstal");

		can->cd(8);
		//hisTDC1->Draw("E");
		gPad->SetLogy();
		hisQDCDist2->Draw("e");

		can->cd(9);
		hNHits2->Draw("E");
		lt1->DrawLatex(0.6, 0.80, Form("Mean : %0.2f", hNHits1->GetMean()));

		can->cd(10);
		hChXY2->Draw("colz");

		/////////////////////////////////////
		can->SaveAs(Form("komac_ana_%d_%d.png",RunNo,ASDNo)); 
		//can->SaveAs("220526_Cosmic_c1430_a1430_0C00_evt30k_t106_ASD19.png");
		//can->SaveAs("220526_Cosmic_c1430_a1430_0C00_evt30k_t106_ASD18.png");
		//can->SaveAs("220526_Cosmic_c1430_a1430_0C00_evt30k_t106_ASD17.png");
		//can->SaveAs("220526_Cosmic_c1430_a1430_0C00_evt30k_t106_ASD16.png");


		TCanvas *c1 = new TCanvas("c1","",1200,400);
		c1->Divide(3,1);
		c1->cd(1);
		hQDC1->Draw();

		c1->cd(2);
		hIpTime->Draw();
		c1->cd(3);
		hIpTimeQDC2->Draw("colz");
		//hIpTimeQDC->Draw();

		TCanvas *c2 = new TCanvas("c2","",800,400);
		c2->Divide(3);
		c2->cd(1);
		hQDCPed1->SetLineColor(kAzure);

		hQDCPeak1->Draw();
		hQDCPed1->Draw("same");
		c2->cd(2);
		hQDCPed2->SetLineColor(kAzure);

		hQDCPeak2->Draw();
		hQDCPed2->Draw("same");
		c2->cd(3);
		hQDCPeak11->Draw();
		c2->cd();
		c2->SaveAs(Form("komac_QDCpeak_%d_%d.png",RunNo,ASDNo)); 

		/*
		   c1->SaveAs(Form("komac_total_%d_%d.png",RunNo,ASDNo));
		   for (int i=0;i<64;i++) {
		   std::cout << "CH " << i << " - " << hisTDC1->GetBinContent(i+1) << std::endl;
		   }
		 */
	}
	fout->cd();
	for (int i=0;i<3;i++) {
		hped[i]->Write();
	}
	fout->Close();
}
