#include<stdio.h>
#include<iostream>
#include<fstream>


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
	h->SetLineWidth(4);
	h->SetLineColor(kBlue);
	h->SetLineStyle(1);
}
const double pi=3.141926;
double anglez(double pxPre,double pyPre,double pzPre){  //计算与z轴夹角，角度degree
	double angz;
	angz=acos(pzPre/sqrt(pxPre*pxPre+pyPre*pyPre+pzPre*pzPre))*180/pi;
	return angz;
}
double anglex(double pxPre,double pyPre,double pzPre){  //计算与z轴夹角，角度degree
	double angx;
	angx=acos(pxPre/sqrt(pxPre*pxPre+pyPre*pyPre+pzPre*pzPre))*180/pi;
	return angx;
}
double angley(double pxPre,double pyPre,double pzPre){  //计算与z轴夹角，角度degree
	double angy;
	angy=acos(pyPre/sqrt(pxPre*pxPre+pyPre*pyPre+pzPre*pzPre))*180/pi;
	return angy;
}

//能谱
void  nElectron(TTree* t1){ //内转换电子能谱
int sum =t1->GetEntries();
char PName[100],ProcessName[100];
int EventID=0,PreEventID=-1,TrackID=0,PreTrackID=-1;
double EkPre=0.;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("EkPre",&EkPre);
t1->SetBranchAddress("TrackID",&TrackID);
TH1 *h2=new TH1F("h2"," ",500,0,250);
//TCanvas *c2=new TCanvas("c2"," ",200,10,700,500);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if (PName[0]=='e'&&ProcessName[0]=='n'){
		if (EventID!=PreEventID||TrackID!=PreTrackID){
				if(EkPre>0.001){
				h2->Fill(EkPre*1000);
			PreEventID=EventID;
			PreTrackID=TrackID;
				}
		}
	}
}
//c2->cd(2);
//c2->SetFrameLineWidth(2);
h2->GetXaxis()->SetTitle("Ek /keV");
h2->GetYaxis()->SetTitle("Counts");
histgram_format(h2);
h2->DrawCopy();
//c2->SaveAs("jpg/Gd155ele.jpg");
}

void ICE(TTree *t1){ //每个中子产生多少内转换电子
int sum =t1->GetEntries();
char PName[100],ProcessName[100];
int EventID=0,PreEventID1=-1,PreEventID2=-1,TrackID=0,PreTrackID=-1;
int NbICE=0,NbReact=0,NbICEto=0,Nbn=0;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
TH1 *h1=new TH1F("h1"," ",20,0,20);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if(ProcessName[0]=='n'&&EventID!=PreEventID1){
	Nbn++;//发生反应中子数
	PreEventID1=EventID;
	}
	if (PName[0]=='e'&&ProcessName[0]=='n'){
		if(PreEventID2==EventID&&PreTrackID!=TrackID){
			NbICE++;
			PreTrackID=TrackID;
		}
		if (PreEventID2!=EventID){
			NbICEto+=NbICE;//发射的总的内转换电子数
			h1->Fill(NbICE);
//			cout<<NbICE<<endl;
			NbICE=1;
			NbReact++;//发射内转换电子的中子数
			PreEventID2=EventID;
		}
	}
}
cout<<"React N="<<Nbn<<" ICEn="<<NbReact<<" NbICE="<<NbICEto<<endl;
c1->cd();
h1->GetXaxis()->SetTitle("ICE/Neutron");
h1->GetYaxis()->SetTitle("Counts");
histgram_format(h1);
h1->DrawCopy();
c1->SaveAs("jpg/NumeleNeu.jpg");
}

void Gamma(TTree* t1){ //吸收中子产生gamma能谱
int sum = t1->GetEntries();
char PName[100],ProcessName[100];
int EventID=0,PreEventID,TrackID,PreTrackID;
double EkPre=0.;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("EkPre",&EkPre);
t1->SetBranchAddress("TrackID",&TrackID);
TH1F *h3=new TH1F("h3"," ",10000,0,9000);
TCanvas *c3=new TCanvas("c3"," ",200,10,700,500);

for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if (PName[0]=='g'&&ProcessName[0]=='n'){
		if (EventID!=PreEventID||TrackID!=PreTrackID){
			if(EkPre>0){
			h3->Fill(EkPre*1000);
			PreEventID=EventID;
			PreTrackID=TrackID;
			}
		}
	}
}
c3->cd();
h3->GetXaxis()->SetTitle("Ek /keV");
h3->GetYaxis()->SetTitle("Counts");
histgram_format(h3);
h3->DrawCopy();
c3->SaveAs("jpg/155GdGamma.jpg");

}

//计算效率，输出信息: P1/P2/有效中子数/发生反应中子数/发生内转换中子数
void Eff(TTree *t1){ //p1计算
	bool SF=0;
	FILE *fp1,*fp2;
	if(SF){
	fp1=fopen("Gdp1data.txt","a");
	fp2=fopen("Gdp2data.txt","a");
	}
int sum = t1->GetEntries();
char PName[100],ProcessName[100],VolumePre[100],VolumePost[100];
int EventID=0,PreEventID=-1,PreEventIDp22=-1,PreEventIDp222=-1,TrackID=0,PreTrackID=-2,PreEventIDP2=-1;
double Nbe=0.,NbeChn=0.,NbEvent=0.,Nbin=0;
double num=0.;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("VolumePost",&VolumePost);
for (int i=0;i<sum;i++){
	t1->GetEntry(i);
//p1=Gd吸收中子产生电子/入射中子
	if(EventID!=PreEventIDp222){//入射到实体的中子数
	Nbin++;
	PreEventIDp222=EventID;
	}	
	if (ProcessName[0]=='n'&&EventID!=PreEventIDp22){//发生反应中子数
		NbEvent++;
		PreEventIDp22=EventID;
		}

	if (PName[0]=='e'&&ProcessName[0]=='n'){  //产生内转换电子的中子数。已查无误，内转换发射概率为0.698//这个发射概率许多文献都不统一，本数据与田阳博士论文一致
		if(EventID!=PreEventID){ //||TrackID!=PreTrackID){
		Nbe++;
		PreEventID=EventID;
		}
	}

	if(PName[0]=='e'){//||PName[0]=='g'){//产生p2信号的中子数
	if(VolumePre[0]=='m'&&VolumePost[0]=='c'){//&&ProcessName[0]=='n'){//MCP为SD时，计算发生反应且产物可以从MCP中穿透到channel中的中子数(每个event只取一个电子)
		if (EventID!=PreEventIDP2){
		NbeChn++;
		PreEventIDP2=EventID;
			}
		
		}
	}

}
double p1=NbEvent/100000.0;
double p2= NbeChn/100000.0;

//double pp1=NbEvent/Nbin;
double pp1=NbEvent/Nbin;

cout<<"NbIncident="<<Nbin<<endl;
cout<<"NbReaction="<<NbEvent<<endl;
cout<<"NbIe="<<Nbe<<endl;
cout<<"e into channel="<<NbeChn<<endl;
cout<<"p1="<<p1<<endl;
cout<<"p2="<<p2<<endl;
cout<<"P IC="<<Nbe/NbEvent<<endl;
if(SF){
	fprintf(fp1,"%f\t",p1);
	//fprintf(fp2,"%f\t",p2);
	fclose(fp1);
	fclose(fp2);
	}
}

//带电粒子角分布
void AngleDis(TTree *t1){ 
int sum =t1->GetEntries();
char PName[100],ProcessName[100],VolumePre[100],VolumePost[100];
int EventID=0,PreEventID=-1,PreEventIDp2=-1,PreEventIDp22=-1,PreEventIDp222=-1,TrackID=0,PreTrackID=-1,ParentID=0,flag=0;
double num=0.0,num2=0.0,xPost=0,yPost=0,zPost=0,pxPre=0,pyPre=0,pzPre=0,length=0,EkPost=0,angz=0;
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("VolumePost",&VolumePost);
t1->SetBranchAddress("EkPost",&EkPost);
t1->SetBranchAddress("xPost",&xPost);
t1->SetBranchAddress("yPost",&yPost);
t1->SetBranchAddress("zPost",&zPost);
t1->SetBranchAddress("pxPre",&pxPre);
t1->SetBranchAddress("pyPre",&pyPre);
t1->SetBranchAddress("pzPre",&pzPre);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
TCanvas *c2=new TCanvas("c2"," ",200,10,700,500);
TCanvas *c3=new TCanvas("c3"," ",200,10,700,500);
TH1 * h1=new TH1F("h1","X",180,0,180);
TH1 * h2=new TH1F("h2","Y",180,0,180);
TH1 * h3=new TH1F("h3","Z",180,0,180);
for (int i=0;i<sum;i++){
	t1->GetEntry(i);
	double angz=0,angx=0,angy=0;
	if(EventID!=PreEventID||TrackID!=PreTrackID){
	if(PName[0]=='a'&&PName[1]=='l'&&PName[2]=='p'){
	angz=anglez(pxPre,pyPre,pzPre);//degree
	angx=anglex(pxPre,pyPre,pzPre);
	angy=angley(pxPre,pyPre,pzPre);
	h1->Fill(angz);
	h2->Fill(angx);
	h3->Fill(angy);
	PreTrackID=TrackID;
	PreEventID=EventID;
	}
	}
}
c1->cd();
h1->GetXaxis()->SetTitle("Angle(deg)");
h1->GetYaxis()->SetTitle("Counts");
histgram_format(h1);
h1->DrawCopy();
c2->cd();
h2->GetXaxis()->SetTitle("Angle(deg)");
h2->GetYaxis()->SetTitle("Counts");
histgram_format(h2);
h2->DrawCopy();
c3->cd();
h3->GetXaxis()->SetTitle("Angle(deg)");
h3->GetYaxis()->SetTitle("Counts");
histgram_format(h3);
h3->DrawCopy();
}


//Gd的测试包括反应截面，电子能谱，电子产生概率
int TestGd(){
char str[50];
for (int i=0;i<12;i++){
sprintf(str,"Gd%d_5_8.root",i+1);
cout<<"processing "<<str<<endl;
TFile *f=new TFile(str);
TTree *t1=(TTree*)f->Get("t");
//Gamma(t1);
//nElectron(t1);
//Eff(t1);
AngleDis(t1);
//ICE(t1);
f->Close();
}
return 0;
}
///更改后的程序，，只有Eff函数稳定，nElectron时好时坏,
///关键点是DrawCopy,本来可以用的但是加了就不可以了.
//TestGd.C程序是本来可以用的，不知道为啥copy到这个文件夹就又不能用了
