/////能量沉积2维图->分bin...
//一维hist存成root格式
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
string str="B6_";//设置文件名
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
	h->SetLineWidth(2);
//	h->SetLineColor(kBlue);
	h->SetLineStyle(1);
}

void Hist2D(TTree *t1,string str3){
int sum =t1->GetEntries();
//string outfile=str+"H2D.root"
string filename2=str3+"_3.root";
cout<<"target file: "<<filename2<<endl;
TFile *fout=new TFile(filename2.c_str(),"RECREATE");
char PName[100],VolumePre[100],VolumePost[100],ProcessName[100];
int EventID=0,PreEventID=-1,PreEventIDp2=-1,PreEventIDp22=-1,PreEventIDp222=-1,TrackID=0,PreTrackID=-1,ParentID=0,flag=0,num1=0;
int xbin=0,ybin=0;
double posX=0,posY=0,xPost=0,yPost=0,length=0,EkPost=0;
double maxBin=0,binContent=0,Edep=0,EdepPre=0,EdepNow=0;
double xPre=0,yPre=0,xIni=0,yIni=0,channel_x=0,channel_y=0;
double channel[229][3]={0};
//229取决于模拟时通道设置了多少，229需要大于等于设置的通道数
double ch[3]={0,0,0};
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("VolumePost",&VolumePost);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("EkPost",&EkPost);
t1->SetBranchAddress("xPost",&xPost);
t1->SetBranchAddress("yPost",&yPost);
t1->SetBranchAddress("xPre",&xPre);
t1->SetBranchAddress("yPre",&yPre);
t1->SetBranchAddress("Edep",&Edep);
int binsize=10;
TH1 *h1=new TH2F("h1"," ",200/binsize,-100,100,200/binsize,-100,100);//能量沉积二维图
TH1 *h2=new TH1F("h2"," ",300,0,3000);
TH1 *h3=new TH1F("h3"," ",300,0,3000);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if(EventID!=PreEventID){
		for(int j=0;j<200/binsize;j++){
			for(int k=0;k<200/binsize;k++){
				binContent=h1->GetBinContent(j+1,k+1);
				if(binContent>0&&maxBin<binContent){
					maxBin=binContent;
				}
			}
		}//寻找最大bin
		if(maxBin>0){
//			cout<<maxBin<<endl;
			if(flag==1) 	{h2->Fill(maxBin);}//n
			if(flag==2)  {h3->Fill(maxBin);}//gamma
//			cout<<flag<<endl;
			flag=0;	
		}
		h1->Reset();
		maxBin=0;//maxBin清零
		PreEventID=EventID;
		EdepPre=0;
		EdepNow=0;
		if(PName[0]=='n'&&ProcessName[0]=='#'){	flag=1;}
		if(PName[0]=='g'&&ProcessName[0]=='#'){ flag=2;}

	}//EventID!=
	if(EventID==PreEventID){
		if(PName[0]=='e'||PName[0]=='a'||PName[0]=='L'){
				xbin=(xPost*1000+100)/binsize+1;//um
				ybin=(yPost*1000+100)/binsize+1;//um
				EdepPre=h1->GetBinContent(xbin,ybin);
			 	EdepNow=EdepPre+Edep*1000;//单个event单个bin的Edep累加 //keV
//               cout<<"xbin="<<xbin<<" ybin="<<ybin<<" EdepNow="<<EdepNow<<endl;

				h1->SetBinContent(xbin,ybin,EdepNow);//fill
				}	
		
	}//EventID=
}//for
c1->cd();
c1->SetLogy();
histgram_format(h2);
h2->DrawCopy();
h3->SetLineColor(2);
h3->SetLineWidth(2);
h3->DrawCopy("same");
fout->Write();
fout->Close();
}

int NG4_2(){
string str2;
stringstream ss;
for(int i=0;i<6;i++){
		ss<<i+12;
		ss>>str2;
string filename=str+str2+".root";
TFile *f=new TFile(filename.c_str());
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
cout<<"Processing file:  "<<filename<<endl;
Hist2D(t1,str+str2);
ss.clear();
ss.str("");
f->Close();
}
return 0;
}
