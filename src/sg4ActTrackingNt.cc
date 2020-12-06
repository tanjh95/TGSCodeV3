// sg4ActTrackingNt.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Fri May 27 20:03:53 2016
// Last Modified On: Tue May 31 18:00:09 2016
// Update Count    : 7
// 



#include "sg4ActTrackingNt.hh"

//iILl10Oo2.iILl10Oo3.iILl10Oo4.iILl10Oo5.iILl10Oo6.iILl10Oo

sg4ActTrackingNt::sg4ActTrackingNt()
{
  mngTrk=sg4DataManager::Instance();
  G4cout<<"creating sg4ActTrackingNt... "<<G4endl;
}

sg4ActTrackingNt::~sg4ActTrackingNt()
{  
 
  G4cout<<"deleting sg4ActTrackingNt... "<<G4endl;
}


//iILl10Oo2.iILl10Oo3.iILl10Oo4.iILl10Oo5.iILl10Oo6.iILl10Oo
void sg4ActTrackingNt::PreUserTrackingAction(const G4Track* aTrack)
{
  //It is only required that the diff data with diff types "Record" 
  //in the same order as the "column" format file given 
  //yushousong.20160510
  aHit.RecordValue(aTrack->GetDefinition()->GetParticleName());
  aHit.RecordValue(G4EventManager::GetEventManager()
		   ->GetConstCurrentEvent()->GetEventID());
  aHit.RecordValue(aTrack->GetTrackID());
  aHit.RecordValue(aTrack->GetGlobalTime());
  aHit.RecordValue(aTrack->GetKineticEnergy());
  aHit.RecordValue(aTrack->GetVolume()->GetName());
  aHit.RecordValue(aTrack->GetVolume()->GetCopyNo());  
  G4ThreeVector vtmp=aTrack->GetPosition();
  aHit.RecordValue(vtmp[0]);
  aHit.RecordValue(vtmp[1]);
  aHit.RecordValue(vtmp[2]);
  vtmp=aTrack->GetMomentumDirection();
  aHit.RecordValue(vtmp[0]);
  aHit.RecordValue(vtmp[1]);
  aHit.RecordValue(vtmp[2]);

}

void sg4ActTrackingNt::PostUserTrackingAction(const G4Track* aTrack)
{  
  G4String nameParticle=aTrack->GetDefinition()->GetParticleName();
  G4String nameVolPhy=aTrack->GetVolume()->GetName();  
  if( nameParticle=="opticalphoton" 
      && nameVolPhy=="pmt"
      ){ 
    aHit.RecordValue(aTrack->GetGlobalTime());
    aHit.RecordValue(aTrack->GetKineticEnergy());
    aHit.RecordValue(aTrack->GetVolume()->GetName());
    aHit.RecordValue(aTrack->GetVolume()->GetCopyNo());  
    G4ThreeVector vtmp=aTrack->GetPosition();
    aHit.RecordValue(vtmp[0]);
    aHit.RecordValue(vtmp[1]);
    aHit.RecordValue(vtmp[2]);
    vtmp=aTrack->GetMomentumDirection();
    aHit.RecordValue(vtmp[0]);
    aHit.RecordValue(vtmp[1]);
    aHit.RecordValue(vtmp[2]);
    //
    
  //
    mngTrk->FillOneNtRow("StepTree", aHit.GetBufInt(), aHit.GetBufDbl(), aHit.GetBufStr());
  
  // 
   
  }

  aHit.Reset(); //Never forget!
}

