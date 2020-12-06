#include <fstream>
#include <stdio.h>
#include <iostream>
 

int draw3(){
TFile *f=new TFile("B1_8_0.root");
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
int sum =t1->GetEntries();
char PName[100];
double xPre=0,yPre=0,zPre=0;
int EventID=0,PreEventID=-1;
t1->SetBranchAddress("PName",PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("xPre",&xPre);
t1->SetBranchAddress("yPre",&yPre);
t1->SetBranchAddress("zPre",&zPre);
TCanvas *c1=new TCanvas("c1"," ",200,10,500,500);
TH2 *h1=new TH2F("h1"," ",100,-50,50,100,-50,50);
for (int i=0;i<sum;i++){
    t1->GetEntry(i);
    if(PName[0]=='n'&&EventID!=PreEventID){
        h1->Fill(xPre*1000,yPre*1000);
        PreEventID=EventID;

    }

}
c1->cd();
h1->DrawCopy();
f->Close();    
return 0;
}
