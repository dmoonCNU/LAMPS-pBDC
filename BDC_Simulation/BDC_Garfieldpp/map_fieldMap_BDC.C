#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <array>
#include <TROOT.h>
#include <TFile.h>
#include <TH2.h>
#include <TApplication.h>

#include "Garfield/ViewCell.hh"
#include "Garfield/ViewIsochrons.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/FundamentalConstants.hh"

using namespace Garfield;

int main(int argc, char * argv[]) {
  TApplication app("app", &argc, argv);

  // Wire diameters [cm].
  // Sense wires.
  constexpr double ds = 0.0020;
  // Cathode wires.
  constexpr double dc = 0.0080;

  // Setup the gas.
  MediumMagboltz gas;
  const std::string garfpath = std::getenv("GARFIELD_HOME");
  //	gas.LoadGasFile(garfpath + "/Examples/BDC/bdc/p10_100V_100000V_5T.gas");
  //gas.LoadGasFile(garfpath + "/build/Examples/GasFile/P10_0_100000.gas");
  gas.LoadGasFile("P10_0_500000.gas");
  gas.LoadIonMobility(garfpath + "/Data/IonMobility_Ar+_Ar.txt");
  gas.PrintGas();
  ComponentAnalyticField cmpe;
  cmpe.SetMedium(&gas);

  /*
  // Add the sense (anode) wires.
  constexpr double xs = 0.;
  constexpr double ys = 0.;
  double wHV = -1400; //-600;
  double pHV = -1400; //-600;
  cmpe.AddWire(xs, ys, ds, 0., "s0");
  cmpe.AddWire(xs+0.5,ys,ds,0.,"s0");
  cmpe.AddWire(xs-0.5,ys,ds,0.,"s0");
  // Add the cathode wires.
  constexpr double xc = 0.25;
  constexpr double yc = 0.;
  cmpe.AddWire(-xc, yc, dc, wHV, "c0");
  cmpe.AddWire(xc,  yc, dc, wHV, "c0");
  cmpe.AddWire(-xc-0.5,yc,dc,wHV,"c0");
  cmpe.AddWire(xc+0.5,yc,dc,wHV, "c0");
  // Add the planes.
  constexpr double yp = 0.25; 
  cmpe.AddPlaneY(yp, pHV, "p");
  cmpe.AddPlaneY(-yp, pHV, "q");
  */

  
  // Wire radius [cm]
  const double rWireS = 20.e-6;
  const double rWireP = 80.e-6;
  // Outer radius of the tube [cm]
  const double wdrift = 0.25;
  //const double wdrift = 20.e-3;
  // Voltages
  const double vWire = -1400.;
  const double vPlane = -1400.;
  // Add the signal wire in the centre.
  cmpe.AddWire(0, 0, 2 * rWireS, 0, "sw");
  // Add the potential wire 
  cmpe.AddWire(wdrift, 0, 2 * rWireP, vWire, "pw");
  cmpe.AddWire(-wdrift, 0, 2 * rWireP, vWire, "pw");
  // Add the plane.
  cmpe.AddPlaneY(wdrift,vPlane,"pp");
  cmpe.AddPlaneY(-wdrift,vPlane,"np");
  // Request calculation of the weighting field. 
  //cmpe.AddReadout("s");


  const double ymin = -0.3; 
  const double xmin = -0.3; 
  const double ymax =  0.3;
  const double xmax =  0.3;
  ViewCell cellView;
  cellView.SetComponent(&cmpe);
  // cellView.SetArea(xmin, ymin, xmax, ymax);
  cellView.SetArea(-0.3,-0.3,0.3,0.3);

  ViewField fieldView;
  fieldView.SetComponent(&cmpe);
  fieldView.SetArea(-0.3, -0.3, 0.3, 0.3);
  //fieldView.SetArea(xmin, -0.75, xmax, 0.75);
  // fieldView.SetVoltageRange(-2000., 0);

  ViewIsochrons isoView;
  isoView.SetComponent(&cmpe);
  // isoView.SetArea(xmin, ymin, xmax, ymax);
  isoView.SetArea(-0.3,-0.3,0.3,0.3);
  //Loop around the sense wire and take a list of
  std::vector<std::array<double, 3> > points;
  unsigned int nPoints = 72;
  for(unsigned int i = 0; i < nPoints; ++i) {
    const double phi = i *TwoPi / nPoints;
    const double r0 = 0.51 * ds;
    const double x0 = r0 * cos(phi);
    const double y0 = r0 * sin(phi);
    std::array<double, 3> p0 = {x0,y0,0.};
    points.push_back(std::move(p0));
  }
  /*for(unsigned int i = 0; i < nPoints; ++i) {
    const double phi = i *TwoPi / nPoints;
    const double r0 = 0.51 * ds;
    const double x0 = 0.5 + r0 * cos(phi);
    const double y0 = r0 * sin(phi);
    std::array<double, 3> p0 = {x0,y0,0.};
    points.push_back(std::move(p0));
    } 
    for(unsigned int i = 0; i < nPoints; ++i) {
    const double phi = i *TwoPi / nPoints;
    const double r0 = 0.51 * ds;
    const double x0 = -0.5 + r0 * cos(phi);
    const double y0 = r0 * sin(phi);
    std::array<double, 3> p0 = {x0,y0,0.};
    points.push_back(std::move(p0));
    }*/
  isoView.DriftElectrons(true);
  isoView.PlotIsochrons(5., points);
  cellView.SetCanvas(isoView.GetCanvas());
  cellView.Plot2d();

  //	TCanvas* cvs = new TCanvas("cvs","",600,600);
  //	fieldView.SetCanvas(cvs);
  //	fieldView.EnableAutoRange(false);
  //	fieldView.SetElectricFieldRange(1000,6000);
  //	fieldView.SetNumberOfContours(100);
  //	fieldView.PlotContour("e");
  //	fieldView.Plot("e","surf3");

  app.Run(true);
}
