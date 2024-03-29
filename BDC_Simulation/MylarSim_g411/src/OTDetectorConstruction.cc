#include "OTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

OTDetectorConstruction::OTDetectorConstruction()
: G4VUserDetectorConstruction()
{
}

OTDetectorConstruction::~OTDetectorConstruction()
{
}

G4VPhysicalVolume* OTDetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();


  // -----------------------------------------------------
  // World

  // Define vacuum
  G4double A, Z;
  G4int natoms, nel;
  G4Element* elN  = new G4Element("Nitrogen","N",  Z=7.,  A= 14.00674*g/mole);
  G4Element* elO  = new G4Element("Oxygen",  "O",  Z=8.,  A= 15.9994*g/mole);

  G4double density = 1.e-25*g/cm3;
  G4Material* Vacuum = new G4Material("Vacuum", density, nel=2);
  Vacuum-> AddElement(elN, .7);
  Vacuum-> AddElement(elO, .3);

  G4Material* world_mat = nist -> FindOrBuildMaterial("Vacuum");

  //G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
  G4double world_size = 100*mm;

  G4Box* solidWorld =    
    new G4Box("World",                       // its name
              0.5*world_size,                // half x
              0.5*world_size,                // half y
              0.5*world_size);               // half z
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking


  // -----------------------------------------------------
  // Detector

  G4Material* detector_mat = nist -> FindOrBuildMaterial("G4_MYLAR");
  //G4Material* detector_mat = nist -> FindOrBuildMaterial("G4_WATER");
  G4double detector_size = 20*mm;
  G4double detector_offset_z = 30*mm;

  G4Box* solidDetector =    
    new G4Box("Detector",
              0.5*detector_size,
              0.5*detector_size,
              0.5*0.001*detector_size);
      
  G4LogicalVolume* logicDetector =                         
    new G4LogicalVolume(solidDetector,
                        detector_mat,
                        "Detector");
                                   
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,detector_offset_z),
                      logicDetector,
                      "Detector",
                      logicWorld,
                      false,
                      1,
                      true);

  return physWorld;
}
