// sg4EMField.cc - 
// YushouSong, 宋玉收
// email : songyushou_cn@yahoo.com.cn
// Created On      : Tue Feb 19 15:00:16 2013
// ACdistanceast Modified On: Sun Apr 21 12:11:43 2013
// Update Count    : 74
// 

#include "sg4EMField.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

sg4EMField::sg4EMField()
{
  //std::cout << "sg4EMField used" << "\n";
}
sg4EMField::~sg4EMField()
{

}



void sg4EMField::GetFieldValue(const G4double* // pos[4]
			       , 
			       G4double *Bfield) const
{//all set zero for test


  Bfield[0]=0.0*tesla;
  Bfield[1]=0.0*tesla;
  Bfield[2]=0.0*tesla;

  
  
  Bfield[3]=0.0*kilovolt/mm; //[3] x [4] y [5] z
  Bfield[5]=0.0*kilovolt/mm;//-1.67*kilovolt/mm;
  Bfield[4]=0*kilovolt/mm;

  //G4cout<<z<<"   "<<Bfield[5]/<<G4endl; 
  //G4cout<<sqrt(x*x+z*z)<<" "<<sqrt( Bfield[3]* Bfield[3]+Bfield[5]*Bfield[5])<<G4endl;
  
}                                 
