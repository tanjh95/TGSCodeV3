// sg4ActTrackingFreeIO.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Wed Jun  8 11:48:50 2016
// Last Modified On: Wed Jun  8 11:50:28 2016
// Update Count    : 1
// 
#ifndef sg4ActTrackingFreeIO_hh 
#define sg4ActTrackingFreeIO_hh 

#include "G4ios.hh"
#include "globals.hh"


#include "G4UserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"

#include "sg4InfomationTrack.hh"


class sg4ActTrackingFreeIO: public G4UserTrackingAction
{
public:
  sg4ActTrackingFreeIO();
  ~sg4ActTrackingFreeIO();

public:
  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);



private:

};


#endif 
