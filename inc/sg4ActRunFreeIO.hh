// sg4ActRunFreeIO.hh - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Fri May 27 19:52:16 2016
// Last Modified On: Fri May 27 19:56:29 2016
// Update Count    : 7
// 


#ifndef sg4ActRunFreeIO_hh
#define sg4ActRunFreeIO_hh

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ios.hh"

#include <cstring>

#include "sg4DataFreeIO.hh"


class sg4ActRunFreeIO : public G4UserRunAction
{
public:
  sg4ActRunFreeIO();
  virtual ~sg4ActRunFreeIO();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

private:
   sg4DataFreeIO* pData;
};

#endif
