// sg4Detector.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Wed Apr 27 09:23:55 2016
// Last Modified On: Fri May 27 20:22:00 2016
// Update Count    : 248
// 
// sg4Detector.cc --- 
// 
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UserLimits.hh"
#include "G4AutoDelete.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4PSEnergyDeposit3D.hh"
#include "G4PSNofStep3D.hh"
#include "G4PSCellFlux3D.hh"
#include "G4PSPassageCellFlux3D.hh"
#include "G4PSFlatSurfaceFlux3D.hh"
#include "G4PSFlatSurfaceCurrent3D.hh"
#include "G4SDParticleWithEnergyFilter.hh"
#include "G4SDParticleFilter.hh"
#include "G4SDChargedFilter.hh"
#include "G4SDNeutralFilter.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "sg4Detector.hh"
#include <stdio.h>
#include <iostream>

const double PI= 3.14159265358979323846;
sg4Detector::sg4Detector(G4String fn)
  : G4VUserDetectorConstruction(),checkOverlaps(false),logicWorld(0)//checkOverlaps(true),true和false控制是否终端输出overlaps
{
  fnInput=fn;
  OpticalInputFile=ysongMsg::ReadValue<G4String>("OpticalFile",fnInput);
  //KitOpt=new sg4KitMatOptical(OpticalInputFile); tan 5.30 decrease
  G4cout<<"creating detector construction..."<<G4endl;
	par.Energycut=0;
	par.dBarrel=150*mm;  
par.xBarrel=-50*mm;//changed by sh
	par.dDet=10*mm;
	par.xDet=300*mm;
	par.dVoxel=50*mm;//changed by sh
par.Degree=0;//changed by sh
	par.NbVoxel=9;//changed by sh
	par.abun=0.96;
	par.Bcon=0.1;
	par.Gdcon=0.03;
}

sg4Detector::~sg4Detector()
{
  G4cout<<"deleting detector construction..."<<G4endl;
}

G4VPhysicalVolume* sg4Detector::Construct()
{
  DefineMaterial();
  DefineVolume();//-------------------- 
  return physiWorld;  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sg4Detector::ConstructSDandField()
{
  DefineOneSD(logicDet);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sg4Detector::DefineMaterial()
{ 
  //在这里先定义所有可能用到的材料
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  //调用G4自身定义好的材料
  Air=nist->FindOrBuildMaterial("G4_AIR");
  G4_WATER=nist->FindOrBuildMaterial("G4_WATER");
  G4_Pb=nist->FindOrBuildMaterial("G4_Pb");
  nist->FindOrBuildMaterial("G4_H");
  G4_Al=nist->FindOrBuildMaterial("G4_Al");
  G4_Cu=nist->FindOrBuildMaterial("G4_Cu");
  //G4_Gd=nist->FineOrBuildMaterial("G4_Gd");
  // Liquid argon material
    G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density;
    // Vacuum
  vacuum= new G4Material("vacuum", z=1., a=1.01*g/mole,density= universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);

  G4Element* Gd=new G4Element("gali","Gd",64,157.3*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8.,a= 15.9994*g/mole); 

  Gd2O3=new G4Material ("Gd2O3",7.41*g/cm3,2);
  Gd2O3->AddElement(Gd,2);
  Gd2O3->AddElement(O,3);

  //----------------------------------------------------------
  
 // Print materials，运行时在终端输出材料信息
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
    /////MCP Material Version2 for 北方夜视
  Al2O3=nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  SiO2=nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
void sg4Detector::DefineVolume()
{
    G4double dworld = 400*mm;
  G4Box* solidWorld = new G4Box("world", dworld, dworld, dworld); //its size
  logicWorld = new G4LogicalVolume(solidWorld,          //its solid
				   vacuum,           //its material
				   "world");            //its name 
  physiWorld = new G4PVPlacement(0,                     //no rotatio
				 G4ThreeVector(),       //at (0,0,0)
				 logicWorld,            //its logical volume
				 "world",               //its name
				 0,                     //its mother  volume
				 false,                 //no boolean operation
				 0,                     //copy number
				 checkOverlaps);        //overlaps checking

//waste barrel
 double dVoxel=par.dVoxel, dBarrel=par.dBarrel,dDet=par.dDet, xDet=par.xDet,xBarrel=par.xBarrel;
 G4Box* solidBarrel=new G4Box("Barrel",dBarrel/2,dBarrel/2,dBarrel/2);
 logicBarrel=new G4LogicalVolume(solidBarrel,vacuum,"logicBarrel");
 G4RotationMatrix* rot=new G4RotationMatrix;
 rot->rotateY(par.Degree*deg);
 physiBarrel=new G4PVPlacement(
				rot,
				G4ThreeVector(xBarrel,0,0),
				logicBarrel,
				"physiBarrel",
				logicWorld,
				false,
				0,
				checkOverlaps
				);

 G4Box* solidVoxel=new G4Box("voxel",dVoxel/2,dVoxel/2,dVoxel/2);
 G4LogicalVolume* logicVoxel[par.NbVoxel];
 G4VPhysicalVolume* physiVoxel[par.NbVoxel];
 char str[20],str1[20];  
 double posMat1[par.NbVoxel],posMat2[par.NbVoxel];
 for(int k=0;k<par.NbVoxel;k++){
	//posMat1
	if(k%3==0){posMat1[k]=-dVoxel;}
	if(k%3==1){posMat1[k]=0;}
	if(k%3==2){posMat1[k]=dVoxel;}
	//posMat2
	if(k<3){posMat2[k]=dVoxel;}
	if(k>=3&&k<6){posMat2[k]=0;}
	if(k>=6){posMat2[k]=-dVoxel;}
 }
 for(int j=1;j<=par.NbVoxel;j++)
	{
	double x=0, z=0;
       	 sprintf (str,"V%d",j); 
	 sprintf(str1,"logicVoxel%d",j);
	 /*
		if(j==5){
              logicVoxel[j]=new G4LogicalVolume(solidVoxel,G4_WATER,str1);
//              logicVoxel[j]=new G4LogicalVolume(solidVoxel,vacuum,str1);

			}
		if(j==4||j==6){
           logicVoxel[j]=new G4LogicalVolume(solidVoxel,G4_WATER,str1);
//      logicVoxel[j]=new G4LogicalVolume(solidVoxel,vacuum,str1);

				}
		if((j>=1&&j<=3)||(j>=7&&j<=9)){
		logicVoxel[j]=new G4LogicalVolume(solidVoxel,G4_WATER,str1); //G4_WATER
//	    logicVoxel[j]=new G4LogicalVolume(solidVoxel,vacuum,str1);
		}
		*/
		 logicVoxel[j]=new G4LogicalVolume(solidVoxel,vacuum,str1);
		x=posMat1[j-1],z=posMat2[j-1];
                physiVoxel[j]= new G4PVPlacement(0,                     //rotation
  					 G4ThreeVector(x,0,z),  //注意单位 x y算出来是mm
  					 logicVoxel[j],          //its logical volume
  					 str,                 //its name
  					 logicBarrel,            //its mother volume
  					 false,                 //no boolean
  					 0,                     // copy number
  					 checkOverlaps);        //???
		  G4VisAttributes*CuBoxVisAtt1= new G4VisAttributes(G4Colour(1.0,1.0,0.0));//yellow
    //  G4VisAttributes*CuBoxVisAtt1= new G4VisAttributes(G4Colour(0.0,0.0,0.0));//black

      logicVoxel[j]->SetVisAttributes(CuBoxVisAtt1);

	}	
  G4Tubs* solidDet=new G4Tubs("HPGE",0.0,dDet/2,0.5*mm,0,2*PI);
 logicDet=new G4LogicalVolume(solidDet,Gd2O3,"logicDet");

// logicDet=new G4LogicalVolume(solidDet,vacuum,"logicDet");
 physiDet=new G4PVPlacement(
				0,
				G4ThreeVector(0,0,xDet),
//				G4ThreeVector(0,0,-50),
				logicDet,
				"physiDet",
				logicWorld,
				false,
				0,
				checkOverlaps
				);


  	  logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

    
if(par.Energycut==1){    
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250.*eV,1.*GeV);
 //根据目前理解，SetEnergyRange和SetProductionCut是两个产物截断的机制，当SetProductionCut的值对应的能量低于990eV时，需要使用SetEnergyRange来设置截断能量，因此
 //SetEnergyRange的能量最低值不低于990eV。
}
  G4ProductionCuts* cuts = new G4ProductionCuts();
  G4double defCut = 10*nanometer;
  cuts->SetProductionCut(defCut,"gamma");
  cuts->SetProductionCut(defCut,"e-");
  cuts->SetProductionCut(defCut,"e+");
  cuts->SetProductionCut(defCut,"alpha");
  cuts->SetProductionCut(defCut,"proton");
 
}

void sg4Detector::DefineOneSD(G4LogicalVolume* lv)
{
  if(!lv){
    G4cout<<"$$No given logical volume, no SD built"<<G4endl;
    return;
  }
  int i=0;
  if(i==0){
  G4SDManager* SDman=G4SDManager::GetSDMpointer();
  sg4SD* sd1=new sg4SD(lv->GetName()); //
  SDman->AddNewDetector(sd1);
  lv->SetSensitiveDetector(sd1);
  i=1;
  }
}

