#include <iostream>
#include <fstream>
#include <cstdlib>

#include <TCanvas.h>
#include <TROOT.h>
#include <TApplication.h>

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
  const double vWire = -1350.;
  const double vPlane = -1350; //-1350.;
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
  //drift.SetGainFluctuationsPolya(0., 20000.);
  //drift.EnableIonTail();
 
  TCanvas* cD = nullptr;
  ViewCell cellView;
  ViewDrift driftView;
  constexpr bool plotDrift = true;
  if (plotDrift) {
    cD = new TCanvas("cD", "", 600, 600);
    cellView.SetArea(-0.3,-0.3,0.3,0.3);
    cellView.SetCanvas(cD);
    cellView.SetComponent(&cmp);
    driftView.SetArea(-0.3,-0.3,0.3,0.3);
    driftView.SetCanvas(cD);
    //driftView.SetLabelX("test");
    drift.EnablePlotting(&driftView);
    track.EnablePlotting(&driftView);
  }
 
  
  TCanvas* cS = nullptr;
  ViewSignal signalView;
  constexpr bool plotSignal = true; //false; //true;
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

  const double x0 = 0.12; 
  const double y0 = -0.25; //0.24; 
  const unsigned int nTracks = 1;
  for (unsigned int j = 0; j < nTracks; ++j) {
    sensor.ClearSignal();
    track.NewTrack(x0, y0, 0, 0, 1, 10, 0);
    //track.NewTrack(x0, y0, 0, 0, 0, 1, 0);
    double xc = 0., yc = 0., zc = 0., tc = 0., ec = 0., extra = 0.;
    int nc = 0;
    int ne = 0; // add number of electrons
    while (track.GetCluster(xc, yc, zc, tc, nc, ec, extra)) {
      for (int k = 0; k < nc; ++k) {
        double xe = 0., ye = 0., ze = 0., te = 0., ee = 0.;
        double dx = 0., dy = 0., dz = 0.;
        track.GetElectron(k, xe, ye, ze, te, ee, dx, dy, dz);
        drift.DriftElectron(xe, ye, ze, te);
      }
      ne++;
      //std::cout<<"Number of primary electrons : "<<nc<<std::endl;
    }
    //std::cout<<"Number of primary electrons : "<<nc<<std::endl;
    cout<<"Number of primary electrons : "<<ne<<endl;
    if (plotDrift) {
      //cD->Clear();
      constexpr bool twod = true;
      constexpr bool drawaxis = true; //false;
      cellView.Plot2d();
      //cellView.Plot2d();
      driftView.Plot(twod, drawaxis);
      cellView.Plot2d();
    }
    sensor.ConvoluteSignals();
    int nt = 0;
    if (!sensor.ComputeThresholdCrossings(-2., "sw", nt)) continue;
    if (plotSignal) signalView.PlotSignal("sw");
  }
  /*
  //isoView.DriftElectrons(true);
  //isoView.PlotIsochrons(5., points);
  //cellView.SetCanvas(isoView.GetCanvas());
  //cellView.Plot2d();

  */
  app.Run(kTRUE);

}
