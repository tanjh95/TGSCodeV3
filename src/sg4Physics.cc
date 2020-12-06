#include "sg4Physics.hh"
//#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonElasticPhysics.hh"
//#include "G4EmDNAPhysics.hh"
//#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include <stdio.h>
using namespace std;

sg4Physics::sg4Physics() :G4VModularPhysicsList(){
	
//    RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
//	RegisterPhysics(new G4EmStandardPhysics());
//	RegisterPhysics(new G4EmDNAPhysics());
	RegisterPhysics(new G4EmLivermorePhysics());
	RegisterPhysics(new G4EmExtraPhysics());
//	RegisterPhysics(new G4EmPenelopePhysics());
	RegisterPhysics(new G4DecayPhysics() );
	RegisterPhysics(new G4RadioactiveDecayPhysics());// QGSP_BIC独家
	RegisterPhysics(new G4HadronElasticPhysicsHP() );
	RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());
	RegisterPhysics(new G4StoppingPhysics());
	RegisterPhysics(new G4IonElasticPhysics());//QGSP_BIC独家
	RegisterPhysics(new G4IonPhysics());
	SetVerboseLevel(0);

}

sg4Physics::~sg4Physics()
{

}
/*
void sg4Physics::ConstructParticle(){///这些函数在主函数中没有调用，程序中是否有哪里会自动调用吗?

cout<<"Flag1"<<endl;


}

void sg4Physics::ConstructProcess(){
cout<<"Flag2"<<endl;


}
*/
void sg4Physics::SetCuts()
{
SetCutsWithDefault();
}

