// sg4ActionInitialization.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Tue Apr 26 16:29:03 2016
// Last Modified On: Tue Apr 26 16:31:56 2016
// Update Count    : 2
// 
#ifndef sg4ActionInitialization_hh
#define sg4ActionInitialization_hh

#include "G4VUserActionInitialization.hh"

using namespace std;

/// Action initialization class.
class sg4ActionInitialization : public G4VUserActionInitialization
{
public:
  sg4ActionInitialization();
  virtual ~sg4ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

};

#endif
