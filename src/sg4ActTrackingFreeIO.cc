// sg4ActTrackingFreeIO.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Wed Jun  8 11:49:29 2016
// Last Modified On: Wed Jun  8 11:57:14 2016
// Update Count    : 4
// 





#include "sg4ActTrackingFreeIO.hh"
#include "sg4DataFreeIO.hh"




//iILl10Oo2.iILl10Oo3.iILl10Oo4.iILl10Oo5.iILl10Oo6.iILl10Oo

sg4ActTrackingFreeIO::sg4ActTrackingFreeIO()
{
  
  G4cout<<"creating sg4ActTrackingFreeIO... "<<G4endl;
}

sg4ActTrackingFreeIO::~sg4ActTrackingFreeIO()
{  
 
  G4cout<<"deleting sg4ActTrackingFreeIO... "<<G4endl;
}


//iILl10Oo2.iILl10Oo3.iILl10Oo4.iILl10Oo5.iILl10Oo6.iILl10Oo
void sg4ActTrackingFreeIO::PreUserTrackingAction(const G4Track* 
						   // aTrack
)
{
 

}

void sg4ActTrackingFreeIO::PostUserTrackingAction(const G4Track* aTrack)
{   
  //save information by FreeIO
  sg4DataFreeIO* pdata=sg4DataFreeIO::Instance();
  G4String nameParticle=aTrack->GetDefinition()->GetParticleName();
  G4String nameVolPhy=aTrack->GetVolume()->GetName(); 
  if( nameParticle=="opticalphoton" 
      && nameVolPhy=="pmt"
      ){ 
    G4int evt=G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    pdata->InsertSeparator(-2); //block separator
    pdata->RecordValue(evt, "evt");
    pdata->InsertSeparator(-1); //line separator
    const sg4InfomationTrack* pinfo=(sg4InfomationTrack*)(aTrack->GetUserInformation());
    if(pinfo){//to avoid null track information
      const vector< shared_ptr<TrackAncestor> >& acs=pinfo->GetvAncestor();
      for(size_t i=0; i<acs.size(); i++){
	pdata->RecordValue((*acs[i]).id, "trkid");
	pdata->RecordValue((*acs[i]).name, "trkname");
	pdata->RecordValue((*acs[i]).creator, "creator");
	pdata->InsertSeparator(-1);
      }
      pdata->FillOneBlock();
    } 
  }
  
}





