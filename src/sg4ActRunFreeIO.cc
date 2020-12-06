// sg4ActRunFreeIO.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Fri May 27 19:52:22 2016
// Last Modified On: Fri May 27 20:33:30 2016
// Update Count    : 11
// 

#include "sg4ActRunFreeIO.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

sg4ActRunFreeIO::sg4ActRunFreeIO()
{
  pData=sg4DataFreeIO::Instance();

  G4cout<<":-)creating sg4ActRunFreeIO..."<<G4endl;
}


sg4ActRunFreeIO::~sg4ActRunFreeIO()
{
  
  G4cout<<":-)deleting sg4ActRunFreeIO..."<<G4endl;
}

void sg4ActRunFreeIO::BeginOfRunAction(const G4Run* /*run*/)
{
  pData->OpenFile();
  //check the name in function sg4ActEventSD::FillOneHitCollection
}

void sg4ActRunFreeIO::EndOfRunAction(const G4Run* /*run*/)
{
  //G4cout<<"22222222222"<<G4endl;
 pData->CloseFile();

}
