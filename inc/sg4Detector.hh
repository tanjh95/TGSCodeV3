// sg4Detector.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Wed Apr 27 09:24:02 2016
// Last Modified On: Wed May 11 15:46:29 2016
// Update Count    : 33
// 

#ifndef sg4Detector_hh
#define sg4Detector_hh

#include "sg4SD.hh"//
#include "ysongMsg.hh"//填卡式读取数据
#include "sg4EMFieldBuilder.hh"//
#include "sg4EMField.hh"//
#include "sg4KitMatOptical.hh"

#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// class description:
//
//  This is the abstract base class of the user's mandatory initialization class
// for detector setup. It has only one pure virtual method Construct() which is
// invoked by G4RunManager when it's Initialize() method is invoked.
//  The Construct() method must return the G4VPhysicalVolume pointer which represents
// the world volume.
//
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4VisAttributes;
struct Parameter{
int Energycut;
G4double dVoxel;
G4double dBarrel;
G4double xBarrel;
G4double yBarrel;
G4double dDet;
G4double xDet;
G4double Degree;
G4int NbVoxel;
G4double abun;
G4double Bcon;
G4double Gdcon;

};
class sg4Detector: public G4VUserDetectorConstruction
{
public:
  sg4Detector(G4String fn="input.txt");
  virtual ~sg4Detector();

public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  //virtual void ConstructSDandField();
  //This method is used in multi-threaded applications to build
  //per-worker non-shared objects: SensitiveDetectors and Field managers
  
// void ResetMaterial();
private:
  void DefineMaterial();
  void DefineVolume();
  void DefineOpticalMPT();//
  void DefineSurf();//
  void DefineOneSD(G4LogicalVolume* lv);//

 
private: 
  G4String fnInput;
  G4String OpticalInputFile;
  sg4KitMatOptical *KitOpt;

  G4bool checkOverlaps; // Option to switch on/off checking of volumes overlaps
  G4LogicalVolume* logicWorld;
  G4VPhysicalVolume* physiWorld;
  G4VPhysicalVolume* physiVoxel;
  G4LogicalVolume* logicBarrel;
  G4VPhysicalVolume* physiBarrel;
  G4LogicalVolume* logicDet;
  G4VPhysicalVolume* physiDet;
  G4LogicalVolume* logicCol;
  G4VPhysicalVolume* physiCol;
  G4LogicalVolume* logicSLD;
  G4VPhysicalVolume* physiSLD;
    
//----------Materials-----------
  G4Material* Air;
  G4Material* vacuum;
  G4Material* LiO2;
  G4Material* Al2O3;
  G4Material* SiO2;
  G4Material* B2O3;
  G4Material* Gd2O3;
  G4Material* PbO;
  G4Material* BiO;
  G4Material* Na2O;
  G4Material* Cs2O;
  G4Material* BaO;
  G4Material* TiO2;
  G4Material* G4_Pb;
  G4Material* G4_Cu;
  G4Material* G4_Al;
  G4Material* G4_Ge;
  G4Material* G4_WATER;
  G4Material* Concrete;
  Parameter par; 
};

#endif 
