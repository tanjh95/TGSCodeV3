// sg4ActTrackingNt.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Fri May 27 20:03:48 2016
// Last Modified On: Tue May 31 18:00:21 2016
// Update Count    : 2
// 


#ifndef sg4ActTrackingNt_hh
#define sg4ActTrackingNt_hh

#include "G4ios.hh"
#include "globals.hh"


#include "G4UserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"

#include "ysongMsg.hh" 
#include "sg4Hit.hh"
#include "sg4DataManager.hh"

#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

//iILl10Oo2.iILl10Oo3.iILl10Oo4.iILl10Oo5.iILl10Oo6.iILl10Oo
class sg4ActTrackingNt : public G4UserTrackingAction
{
public:
  sg4ActTrackingNt();
  ~sg4ActTrackingNt();

public:
  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);



private:
  sg4Hit aHit;
  sg4DataManager* mngTrk;
};



#endif
