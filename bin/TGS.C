#include <stdio.h>
#include <iostream>
#include <fstream>

double GetNb(TTree *t1){
bool SF=1;
FILE *fp;
if(SF){
fp=fopen("Em2.txt","a");
}
int sum=t1->GetEntries();
char PName[100];
double EkPre=0;
int EventID=0,PreEventID=-1;
double NbEvent=0.0;
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("EkPre",&EkPre);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if((PreEventID!=EventID)&&(EkPre==0.662||EkPre==1.20)){
		NbEvent++;
		PreEventID=EventID;
	}	
}
cout<<NbEvent<<endl;
if(SF){
fprintf(fp,"%f\t",NbEvent);
fclose(fp);
}
return 0;
}

int TGS(){
char str[50];
for(int i=-1;i<2;i++){
sprintf(str,"Em%d_0_-50_1.root",i*50);
cout<<"Processing"<<str<<endl;
TFile *f=new TFile(str);
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
GetNb(t1);
f->Close();
}

return 0;
}
