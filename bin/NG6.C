#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
//处理中子/gamma的能量沉积， GetEdepHist()返回值为该文件内平均每个入射粒子能量沉积，并把能量沉积谱存为.root文件
string str="BGd6_0.3_";//设置文件名
void histgram_format(TH1* h){
	h->GetXaxis()->CenterTitle();
	h->GetYaxis()->CenterTitle();
	h->GetXaxis()->SetTitleFont(62);
	h->GetYaxis()->SetTitleFont(62);
	h->GetXaxis()->SetTitleSize(0.04);
	h->GetYaxis()->SetTitleSize(0.04);
	h->GetXaxis()->SetTitleOffset(1.0);
	h->GetYaxis()->SetTitleOffset(1.4);
	h->GetXaxis()->SetLabelFont(62);
	h->GetYaxis()->SetLabelFont(62);
	h->GetXaxis()->SetLabelSize(0.04);
	h->GetYaxis()->SetLabelSize(0.04);
	h->SetLineWidth(3);
//	h->SetLineColor(kBlue);
	h->SetLineStyle(1);
}
void Stack_format(THStack*hs){
hs->Draw("nostack");
hs->GetXaxis()->SetTitle("PositionX/um");
hs->GetYaxis()->SetTitle("Counts");
hs->GetXaxis()->CenterTitle();
hs->GetYaxis()->CenterTitle();
hs->GetXaxis()->SetTitleFont(62);
hs->GetYaxis()->SetTitleFont(62);
hs->GetXaxis()->SetTitleSize(0.04);
hs->GetYaxis()->SetTitleSize(0.04);
hs->GetXaxis()->SetTitleOffset(1.0);
hs->GetYaxis()->SetTitleOffset(1.2);
hs->GetXaxis()->SetLabelFont(62);
hs->GetYaxis()->SetLabelFont(62);
hs->GetXaxis()->SetLabelSize(0.04);
hs->GetYaxis()->SetLabelSize(0.04);
}

void  GetEdepHist(TTree *t1,string str2){
string filenameNG=str+"ng.root";
TFile *f=new TFile(filenameNG.c_str(),"UPDATE");
int sum=t1->GetEntries();
char PName[100],ProcessName[100];
string str3="h"+str2;
TH1 *h1=new TH1F(str3.c_str()," ",3000,0,3000);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
int EventID=0,PreEventID=-1,TrackID=0,PreTrackID=-1;
double Edep=0,EdepTotal=0;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("Edep",&Edep);
t1->SetBranchAddress("TrackID",&TrackID);
for (int i=0;i<sum;i++){
	t1->GetEntry(i);
	if(EventID!=PreEventID){
		if (EdepTotal!=0) {h1->Fill(EdepTotal*1000);} //keV
		EdepTotal=0;
		PreEventID=EventID;
	}
	if(EventID==PreEventID){
		EdepTotal=EdepTotal+Edep;
	}

}
c1->cd();
h1->DrawCopy();
delete c1;
f->Write();
f->Close();

}
double TreeProcess(TTree* t1){ //对于1个tree，计算Edep平均值
bool SF=1;
FILE *fp;
if(SF){
fp=fopen("gamRej1.txt","a");
}
double AvrEdep=0,TotalEdep=0,TotalEdepEvt=0,Edep=0,numEvt=0;
int EventID=0,PreEventID=-1;
char ProcessName[100],PName[100];
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("Edep",&Edep);
int sum=t1->GetEntries();
for(int i=0;i<sum;i++){
t1->GetEntry(i); 
if(EventID!=PreEventID&&ProcessName[0]!='#'){
	TotalEdep=TotalEdepEvt+TotalEdep;
	PreEventID=EventID;
	TotalEdepEvt=0;
	numEvt++;	
}
if(EventID==PreEventID){
	if(ProcessName[0]!='#'){
		TotalEdepEvt=TotalEdepEvt+Edep*1000;//keV
	}
}
}
AvrEdep=TotalEdep/numEvt;
if(SF){
fprintf(fp,"%f\n",AvrEdep);
fclose(fp);
}
return AvrEdep;
}
int NG6(){
string filenameN=str+".root";
//string filenameG=str+"g.root";
string filenameNG=str+"ng.root";
string str2;
stringstream ss;
for(int k=0;k<9;k++){
	ss<<k+1;
	ss>>str2;
	cout<<"str2="<<str2<<endl;
string filenameG=str+str2+"_g.root";
cout<<"Processing "<<filenameG<<endl;
//TFile *f1=new TFile(filenameN.c_str());
TFile *f2=new TFile(filenameG.c_str());
//TTree *t1=new TTree("tree","tree disk");
TTree *t2=new TTree("tree2","tre disk");
//t1=(TTree*)f1->Get("t");
t2=(TTree*)f2->Get("t");
//GetEdepHist(t1,"n");
//GetEdepHist(t2,"g");
double EdepPerN=0,EdepPerG=0;
//EdepPerN=TreeProcess(t1);
EdepPerG=TreeProcess(t2);
//f1->Close();
f2->Close();
cout<<EdepPerN<<" "<<EdepPerG<<endl;
ss.clear();//
ss.str("");//重置sstream，缺一不可
}
return 0;
}
