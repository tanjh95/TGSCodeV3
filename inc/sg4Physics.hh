#ifndef sg4Physis_h
#define sg4Physis_h 

#include "G4VModularPhysicsList.hh"

class sg4Physics : public G4VModularPhysicsList
{
		public:
		sg4Physics();
		virtual	~sg4Physics();
		//virtual void ConstructParticle();//基类有此函数了，继承过来的还要写吗?
//		virtual void ConstructProcess();
		virtual void SetCuts();

};

#endif 
