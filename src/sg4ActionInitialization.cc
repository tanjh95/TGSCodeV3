// sg4ActionInitialization.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Tue Apr 26 16:30:48 2016
// Last Modified On: Wed Jun  8 11:56:03 2016
// Update Count    : 90
// 
#include "sg4ActionInitialization.hh"

#include "sg4ActRunTimer.hh"

#include "sg4ActsRun.hh"
#include "sg4ActsEvent.hh"
#include "sg4ActsTracking.hh"

#include "sg4ActPrimary.hh"

#include "sg4ActTrackingNt.hh"
#include "sg4ActEventSD.hh"
#include "sg4ActRunNt.hh"

#include "sg4ActTrackingAncestor.hh"
#include "sg4ActTrackingFreeIO.hh"
#include "sg4ActRunFreeIO.hh"


// #include ".hh"
// #include ".hh"


sg4ActionInitialization::sg4ActionInitialization()
 : G4VUserActionInitialization()
{
  //write=new DataWrite;
}

sg4ActionInitialization::~sg4ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........

void sg4ActionInitialization::BuildForMaster() const
{
  //For master
  //record time 
  sg4ActsRun* actsRun=new sg4ActsRun;
  actsRun->AddAct(new sg4ActRunTimer);
  SetUserAction(actsRun);
}

void sg4ActionInitialization::Build() const
{
  //mandatory
  SetUserAction(new sg4ActPrimary("input.txt"));
 
  sg4ActsRun* actsRun=new sg4ActsRun;
  sg4ActsEvent* actsEvent=new sg4ActsEvent;
  sg4ActsTracking* actsTracking=new sg4ActsTracking;
  
  // //ntuple
  actsRun->AddAct(new sg4ActRunNt());//
  actsEvent->AddAct(new sg4ActEventSD());//
  actsTracking->AddAct(new sg4ActTrackingNt());
  
  //append track information
  actsTracking->AddAct(new sg4ActTrackingAncestor());
  
  //free io
  actsRun->AddAct(new sg4ActRunFreeIO());
  actsTracking->AddAct(new sg4ActTrackingFreeIO());


  
  //
  SetUserAction(actsRun);
  SetUserAction(actsEvent);
  SetUserAction(actsTracking);


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo
}  

