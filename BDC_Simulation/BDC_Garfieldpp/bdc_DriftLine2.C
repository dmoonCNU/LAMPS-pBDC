#include <iostream>
#include <fstream>
#include <cstdlib>

#include <TCanvas.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TRandom.h>

#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewSignal.hh"

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewIsochrons.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/Plotting.hh"
#include "Garfield/AvalancheMC.hh"

#include "TFile.h"
#include "TH2F.h"

using namespace Garfield;
using namespace std;

bool readTransferFunction(Sensor& sensor) {

  std::ifstream infile;
  infile.open("mdt_elx_delta.txt", std::ios::in);
  if (!infile) {
    std::cerr << "Could not read delta response function.\n";
    return false;
  }
  std::vector<double> times;
  std::vector<double> values;
  while (!infile.eof()) {
    double t = 0., f = 0.;
    infile >> t >> f;
    if (infile.eof() || infile.fail()) break;
    times.push_back(1.e3 * t);
    values.push_back(f);
  }
  infile.close();
  sensor.SetTransferFunction(times, values);
  return true;
}

int main(int argc, char * argv[]) {

  TApplication app("app", &argc, argv);
  // MC setup
  bool avalOn = true; // avalanche mode on
  bool singleEvt = true; // run single event
  double vMax = -1400;
  int nTrk = 10;
 
  // Make a gas medium.
  MediumMagboltz gas;
  gas.LoadGasFile("P10_0_500000.gas");
  //gas.LoadGasFile("ar_93_co2_7_3bar.gas");
  auto installdir = std::getenv("GARFIELD_INSTALL");
  if (!installdir) {
    std::cerr << "GARFIELD_INSTALL variable not set.\n";
    return 1;
  }
  const std::string path = installdir;
  gas.LoadIonMobility(path + "/share/Garfield/Data/IonMobility_Ar+_Ar.txt");

  // Make a component with analytic electric field.
  ComponentAnalyticField cmp;
  cmp.SetMedium(&gas);
  
  // Wire radius [cm]
  const double rWireS = 0.002; //20.e-5; //20.e-6;
  const double rWireP = 0.008; //80.e-5; //80.e-6;
  // Outer radius of the tube [cm]
  const double wdrift = 0.25;
  //const double wdrift = 20.e-3;
  // Voltages
  const double vWire = vMax;
  const double vPlane = vMax; //-1350.;
  // Add the signal wire in the centre.
  cmp.AddWire(0, 0, 2 * rWireS, 0, "sw");
  // Add the potential wire 
  cmp.AddWire(wdrift, 0, 2 * rWireP, vWire, "pw");
  cmp.AddWire(-wdrift, 0, 2 * rWireP, vWire, "pw");
  // Add the plane.
  cmp.AddPlaneY(wdrift,vPlane,"pp");
  cmp.AddPlaneY(-wdrift,vPlane,"np");
  // Request calculation of the weighting field. 
  cmp.AddReadout("sw");
 
  // Make a sensor.
  Sensor sensor;
  sensor.AddComponent(&cmp);
  sensor.AddElectrode(&cmp, "sw");
  
  // Set the signal time window.
  const double tstep = 0.5;
  const double tmin = -0.5 * tstep;
  const unsigned int nbins = 1000;
  sensor.SetTimeWindow(tmin, tstep, nbins);
  // Set the delta reponse function.
  if (!readTransferFunction(sensor)) return 0;
  sensor.ClearSignal();

  // Set up Heed.
  TrackHeed track;
  track.SetParticle("muon");
  track.SetEnergy(4.e9);
  //track.SetEnergy(170.e9);
  track.SetSensor(&sensor);

  // RKF integration.
  DriftLineRKF drift;
  drift.SetSensor(&sensor);
  drift.SetGainFluctuationsPolya(0., 20000.);
  //drift.EnableIonTail();
 
  // Add avalance mode
  AvalancheMicroscopic aval;
  aval.SetSensor(&sensor);
  aval.EnableSignalCalculation();
  //aval.EnableMagneticField();


  TCanvas* cD = nullptr;
  ViewCell cellView;
  ViewDrift driftView;
  bool plotDrift = singleEvt; //true;
  if (plotDrift) {
    cD = new TCanvas("cD", "", 600, 600);
    cellView.SetArea(-0.3,-0.3,0.3,0.3);
    cellView.SetCanvas(cD);
    cellView.SetComponent(&cmp);
    driftView.SetArea(-0.3,-0.3,0.3,0.3);
    driftView.SetCanvas(cD);
    drift.EnablePlotting(&driftView);
    track.EnablePlotting(&driftView);
    if(avalOn) aval.EnablePlotting(&driftView);
    
  }
 
  
  TCanvas* cS = nullptr;
  ViewSignal signalView;
  bool plotSignal = singleEvt; //true;
  //constexpr bool plotSignal = false; //true;
  if (plotSignal) {
    cS = new TCanvas("cS", "", 604,0,576,600);
    signalView.SetCanvas(cS);
    signalView.SetSensor(&sensor);
    signalView.SetLabelY("signal [fC]");
  } 

  ViewField fieldView;
  fieldView.SetComponent(&cmp);
  //fieldView.SetArea(0.5, -0.75, 0.5, 0.75);

  ViewIsochrons isoView;
  isoView.SetComponent(&cmp);
  isoView.SetArea(-0.3,-0.3,0.3,0.3);

  std::vector<std::array<double, 3> > points;

  TH1F *hElecPosX = new TH1F("hElecPosX",";x (cm); Counts",300,0,0.30);
  TH1F *hTime = new TH1F("hTime",";time (ns); Counts",200,0,200);
  TH1F *hDrTime = new TH1F("hDrTime",";time (ns); Counts",200,0,200);
  TH1F *hDrVel = new TH1F("hDrVel",";drift velocity (#mum/ns); Counts",100,0,100);
  TH1F *hPrElec = new TH1F("hPrElec",";number of primary electrons; Counts",30,0,30);
  TH2F *hRTFunc = new TH2F("hRTFunc",";time (ns);drift length (#mum);",150,0,150,250,0,2.5);
  const double x0 = 0.12; 
  const double y0 = -0.25; //0.24; 
  unsigned int nTracks = nTrk;
  if(singleEvt) nTracks = 1;
  double rx = 0;
  double drtime = 0.0;
  for (unsigned int j = 0; j < nTracks; ++j) {
    sensor.ClearSignal();
    gRandom -> SetSeed(time(0));
    rx = gRandom->Uniform(0.02, 0.25);
    hElecPosX->Fill(rx);
    cout<<"dhmoon "<<j<<"-th event, randome x : "<<rx<<endl;
    //track.NewTrack(0.15, -0.25, 0, 0, 0, 1, 0); // track with traveling to y-axis starting at position of random x, -0.25 
    track.NewTrack(rx, 0.25, 0, 0, 0, -1, 0); // track with traveling to y-axis starting at position of random x, -0.25 
    //track.NewTrack(rx, -0.25, 0, 0, 0, 1, 0); // track with traveling to y-axis starting at position of random x, -0.25 
    //track.NewTrack(0.2, -0.25, 0, 0, 0, 1, 0); // track with traveling to y-axis starting at position of 0.2, -0.25 
    //track.NewTrack(x0, y0, 0, 0, 1, 10, 0); // track with some angle
    double xc = 0., yc = 0., zc = 0., tc = 0., ec = 0., extra = 0.;
    int nc = 0;
    int ne = 0; // add number of electrons
    double dts = 0.0;
    while (track.GetCluster(xc, yc, zc, tc, nc, ec, extra)) {
      hTime->Reset();
      //cout<<"dhmoon nc 1 : "<<nc<<endl;
      for (int k = 0; k < nc; ++k) {
        double xe = 0., ye = 0., ze = 0., te = 0., ee = 0.;
        double dx = 0., dy = 0., dz = 0.;
        double dxe, dye, dze;
        track.GetElectron(k, xe, ye, ze, te, ee, dx, dy, dz);
        drift.DriftElectron(xe, ye, ze, te);
        double dxe2 = 0., dye2 = 0., dze2 = 0., dte2 = 0.;
        drift.GetDriftLinePoint(nc, dxe2, dye2, dze2, dte2);
        cout<<"dhMoon test :: dxe : "<<dxe2<<", dye : "<<dye2<<", dze : "<<dze2<<", dte : "<<dte2<<endl;
        //drift.GetDriftLinePoint(const int i, double& x, double& y, double& z, double& t);
        cout<<"test : "<<drift.GetNumberOfDriftLinePoints()<<endl;
        //int lpt =  GetNumberOfDriftLinePoints();
        //cout<<"number of drift line : "<<lpt<<endl;
        double x0, y0, z0, t0, e0;
        double x1, y1, z1, t1, e1;
        int status = 0;
        //int status = 0;
        drift.GetEndPoint(x1, y1, z1, t1, status);
        cout<<"dhMoon drift line :: x1 : "<<x1<<", y1 : "<<y1<<", z1 : "<<z1<<", t1 : "<<t1<<", status : "<<status<<endl;
        if(avalOn) aval.AvalancheElectron(xe, ye, ze, te, 0.1, dxe, dye, dze);
        //int status;
        if(avalOn) aval.GetElectronEndpoint(0, x0, y0, z0, t0, e0, x1, y1, z1, t1, e1, status);
        cout<<"t0 : "<<t0<<", t1 : "<<t1<<", te : "<<te<<", tc : "<<tc<<", drift time : "<<t1-tc<<endl;

        //dts = t1-tc;
        //hTime->Fill(dts);
        dts = t1-tc;
      }
      //cout<<"dhmoon nc 2 : "<<nc<<endl;
      hTime->Fill(dts);
      //cout<<"dhmoon Drift time : "<<drtime<<endl;
      //drtime = hTime->GetMean();
      //hDrTime->Fill(drtime);
      ne++;
    }
    drtime = hTime->GetMean();
    double dtmin = hTime->GetMinimumBin();
    int dtxmin = 0;
    for(int i = 1; i < hTime->GetNbinsX(); i++){ 
      //cout<<hTime->GetBinContent(i)<<endl; 
      if(hTime->GetBinContent(i) > 0){
        cout<<"No Zero bin : "<<i<<endl; 
        dtxmin = i;
        break;
      }
    }
    cout<<"dhmoon Drift time : "<<drtime<<", drift velocity : "<<rx/dtxmin*10000<<endl;
    hRTFunc->Fill(dtxmin,rx*10);
    //cout<<"dhmoon Drift time : "<<drtime<<", min bin : "<<dtmin<<", min x bin : "<<dtxmin<<endl;
    hDrTime->Fill(dtxmin);
    hDrVel->Fill(rx/dtxmin*10000);
    cout<<"dhmoon Number of primary electrons : "<<ne<<endl;
    hPrElec->Fill(ne);
    if (plotDrift) {
      //cD->Clear();
      constexpr bool twod = true;
      constexpr bool drawaxis = true; //false;
      cellView.Plot2d();
      driftView.Plot(twod, drawaxis);
      cellView.Plot2d();
    }
    sensor.ConvoluteSignals();
    int nt = 0;
    if (!sensor.ComputeThresholdCrossings(-2., "sw", nt)) continue;
    if (plotSignal) signalView.PlotSignal("sw");
  }

  TFile *out = new TFile("out_sim_muon.root","RECREATE");
  out->cd();
  hTime->Write();
  hDrTime->Write();
  hPrElec->Write();
  hDrVel->Write();
  hElecPosX->Write();
  hRTFunc->Write();
  out->Close();
  if(singleEvt) app.Run(kTRUE);

  cout<<"dhmoon Simulation is over !!!"<<endl;
}
