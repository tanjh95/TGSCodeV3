// nw.cc - 
// YushouSong, 宋玉收
// email : songyushou80@163.com
// Created On      : Thu Apr  7 10:33:24 2016
// Last Modified On: Sat Feb 25 11:19:02 2017
// Update Count    : 83
// 


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

//mandatory class - physics 
//#include "QGSP_BERT_HP.hh"
//#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "FTFP_BERT_HP.hh"
#include "sg4Physics.hh"
//#include "QBBC.hh"
//madatory class - Detector Construction
#include "sg4Detector.hh"

//#include "DetUrich.hh"
//User actions, not mandatory class
#include "sg4ActionInitialization.hh"
#include "sg4WorkerInitialization.hh"

//
#include "G4GenericBiasingPhysics.hh"

//UI 
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//assitance 
#include "G4Version.hh"
#include "Randomize.hh"//随机数这里产生

//common classes
#include "ysongMsg.hh"

//system heads
#include <ctime>// initialize random seed
using namespace std;

int main(int argc,char** argv)
{
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  if(ysongMsg::ReadValue<int>("EnableRandSeed", "input.txt")>0){
    G4int seconds = time(NULL);
    G4Random::setTheSeed(seconds); //G4Random for MT and Seq is set in Randomize.hh
  }

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  int nthreads=ysongMsg::ReadValue<int>("NumberOfThreads", "input.txt");
  runManager->SetNumberOfThreads(nthreads); 
  //runManager->SetUserInitialization(new sg4WorkerInitialization);
#else
  G4RunManager* runManager = new G4RunManager;
#endif
  // Set mandatory initialization classes  
  // Detector construction
  runManager->SetUserInitialization(new sg4Detector());
  //runManager->SetUserInitialization(new DetUrich());
  // Physics list
//  G4VModularPhysicsList* physicsList =new sg4Physics();
//  G4VModularPhysicsList* physicsList =new QGSP_BIC_HP();
  G4VModularPhysicsList* physicsList =new FTFP_BERT_HP();
  physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new sg4ActionInitialization());

  // Initialize G4 kernel
  //
  runManager->Initialize();

  //G4cout<<"%%%%%%%%%%%%% "<<G4endl;
#ifdef G4VIS_USE
  G4VisManager* visManager=0;
#endif
  G4UIExecutive* ui = 0;
  if ( argc==1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
   G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if ( ! ui ) { 
    G4String fileName = argv[1];
      if(fileName=="-l"){  // -l 无UI界面
#ifdef G4UI_USE_TCSH    
      G4UIsession* session= new G4UIterminal(new G4UItcsh);
      session->SessionStart();
         delete session;
#endif
	    }
      if(fileName == "vis.mac"){//可视化
#ifdef G4VIS_USE
      visManager = new G4VisExecutive;
     visManager->Initialize();
#endif   
    ui = new G4UIExecutive(argc, argv);
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+fileName);
    ui->SessionStart();
    delete ui;
	}
      if(fileName != "vis.mac"){//无可视化界面
	    // batch mode
	    G4String command = "/control/execute ";
	    UImanager->ApplyCommand(command+fileName);
	}
  }
  else {//交互界面
#ifdef G4VIS_USE
      visManager = new G4VisExecutive;
      visManager->Initialize();
      ui->SessionStart();
      delete ui;
#endif 
  }

#ifdef G4VIS_USE
  if(visManager!=0)
  delete visManager;
#endif
  
  delete runManager;
 return 0;

}
