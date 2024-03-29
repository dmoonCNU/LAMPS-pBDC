#include <iostream>
#include <cstdlib>

#include <TCanvas.h>
#include <TROOT.h>
#include <TApplication.h>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewMedium.hh"

using namespace Garfield;

int main(int argc, char * argv[]) {

  TApplication app("app", &argc, argv);
 
  // Setup the gas.
  MediumMagboltz gas;
 // gas.LoadGasFile("iC4H10_0_500000_100torr.gas");
  gas.LoadGasFile("P10_test.gas");
  //gas.LoadGasFile("P10_0_500000_314.gas");
  const std::string path = std::getenv("GARFIELD_INSTALL");
  gas.LoadIonMobility(path + "/share/Garfield/Data/IonMobility_Ar+_Ar.txt");
  gas.PrintGas();

  ViewMedium view;
  view.SetMedium(&gas);
//  view.SetMagneticField(2.);
  
  TCanvas cV("cV", "", 600, 600);
  view.SetCanvas(&cV);
  view.PlotElectronVelocity('e');

  TCanvas cD("cD", "", 600, 600);
  view.SetCanvas(&cD);
  view.PlotElectronDiffusion('e');

  TCanvas cT("cT", "", 600, 600);
  view.SetCanvas(&cT);
  view.PlotElectronTownsend('e');

  TCanvas cA("cA", "", 600, 600);
  view.SetCanvas(&cA);
  view.PlotElectronAttachment('e');

  app.Run(true);

}
