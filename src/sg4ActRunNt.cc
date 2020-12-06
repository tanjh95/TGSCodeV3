// sg4ActRunNt.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Tue Apr 26 09:57:49 2016
// Last Modified On: Tue May 31 17:39:34 2016
// Update Count    : 43
// 
#include "sg4ActRunNt.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

sg4ActRunNt::sg4ActRunNt()
{
  mngSD=sg4DataManager::Instance();

  G4cout<<":-)creating sg4ActRunNt..."<<G4endl;
}


sg4ActRunNt::~sg4ActRunNt()
{
  
  G4cout<<":-)deleting sg4ActRunNt..."<<G4endl;
}

void sg4ActRunNt::BeginOfRunAction(const G4Run* /*run*/)
{
  mngSD->OpenFile();
  
  //G4cout<<"333333333333"<<G4endl;

  mngSD->CreatNtuple("t");

  // mngSD->CreatNtuple("SDTree");
  mngSD->CreatNtuple("StepTree");
  //G4cout<<"4444444444"<<G4endl;
  //check the name in function sg4ActEventSD::FillOneHitCollection
}

void sg4ActRunNt::EndOfRunAction(const G4Run* /*run*/)
{
  mngSD->WriteNtCloseFile();

}
