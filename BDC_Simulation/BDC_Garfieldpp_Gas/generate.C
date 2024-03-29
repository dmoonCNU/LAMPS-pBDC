#include <iostream>

#include "Garfield/MediumMagboltz.hh"
#include "Garfield/FundamentalConstants.hh"

using namespace Garfield;

int main(int argc, char * argv[]) {

  const double pressure =  AtmosphericPressure;
  const double temperature = 293.15;
 
  // Setup the gas.
  MediumMagboltz gas;
  gas.SetComposition("Ar", 90., "CH4", 10.);
  gas.SetTemperature(temperature);
  gas.SetPressure(pressure);

  // Set the field range to be covered by the gas table. 
  const size_t nE = 30;
  const double emin =    10.;
  const double emax = 500000.;
  // Flag to request logarithmic spacing.
  constexpr bool useLog = true;
  gas.SetFieldGrid(emin, emax, nE, useLog); 

  const int ncoll = 10;
  // Run Magboltz to generate the gas table.
 // gas.EnablePenningTransfer(0.2,0,"ar");
  gas.GenerateGasTable(ncoll);

  // Save the table. 
  gas.WriteGasFile("P10_500000_1atm.gas");

}
