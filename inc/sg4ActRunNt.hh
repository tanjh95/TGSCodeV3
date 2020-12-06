// sg4ActRunNt.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Tue Apr 26 09:59:15 2016
// Last Modified On: Tue May 10 15:45:46 2016
// Update Count    : 12
// 

#ifndef sg4ActRunNt_hh
#define sg4ActRunNt_hh

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ios.hh"

#include <cstring>

#include "sg4DataManager.hh"


class sg4ActRunNt : public G4UserRunAction
{
public:
  sg4ActRunNt();
  virtual ~sg4ActRunNt();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

private:
   sg4DataManager* mngSD;
};

#endif
