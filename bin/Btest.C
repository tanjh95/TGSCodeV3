#include <stdio.h>
#include <iostream>
#include <fstream>

//B MCP Test List
//int Btest() //main 
//double Effp1()
//double Effp2()
//int counts()
//void Li spectrum()
//void alpha spectrum()
//void gamma spectrum()
//void photon electron spectrum()
//void ion electron spectrum()
//
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
double angletheta(double pxPre,double pyPre,double pzPre){
	double r=sqrt(pxPre*pxPre+pyPre*pyPre+pzPre*pzPre);
	double theta=0;
	theta=(acos(pzPre/r)*180/pi);
	return pzPre/r*90; 
}
double anglephi(double pxPre,double pyPre,double pzPre){
	double  phi=0;
	if (pxPre>0){
	phi=atan(pyPre/pxPre)*180/pi;
	}
	if(pxPre<0&&pyPre>0){
	phi=atan(pyPre/pxPre)*180/pi+180;
	}
	if(pxPre<0&&pyPre<0){
		phi=atan(pyPre/pxPre)*180/pi-180;
	}
	return phi;

}
void histgram_format(TH1* h){
	h->GetXaxis()->CenterTitle();
	h->GetYaxis()->CenterTitle();
	h->GetXaxis()->SetTitleFont(62);
	h->GetYaxis()->SetTitleFont(62);
	h->GetXaxis()->SetTitleSize(0.04);
	h->GetYaxis()->SetTitleSize(0.04);
	h->GetXaxis()->SetTitleOffset(1.0);
	h->GetYaxis()->SetTitleOffset(1.0);
	h->GetXaxis()->SetLabelFont(62);
	h->GetYaxis()->SetLabelFont(62);
	h->GetXaxis()->SetLabelSize(0.04);
	h->GetYaxis()->SetLabelSize(0.04);
	h->SetLineWidth(2);
//	h->SetLineColor(kBlue);
	h->SetLineStyle(1);
}


void ParSpe(TTree *t1){//粒子出射通道时的能量分布 由初始能谱改过来的
int sum= t1->GetEntries();
char PName[100],ProcessName[100],VolumePre[100],VolumePost[100];
int EventID=0,TrackID=0,PreEventID=-1,PreEventID2=-2,PreEventID3=-3,PreEventID4=-1,PreTrackID4=-2;
double num=0.,EkPre=0.,EkPost=0;
t1->SetBranchAddress("PName",PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("EkPre",&EkPre);
t1->SetBranchAddress("EkPost",&EkPost);
t1->SetBranchAddress("ProcessName",ProcessName);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("VolumePost",&VolumePost);

TH1 *h1=new TH1F("h1"," ",1000,0,2000);
TH1 *h2=new TH1F("h2"," ",1000,0,2000);
TH1 *h3=new TH1F("h3"," ",1000,0,2000);
TH1 *h4=new TH1F("h4"," ",1000,0,1000);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
TCanvas *c2=new TCanvas("c2"," ",200,10,700,500);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
		switch(PName[0])
		{
				case'L':
						{

						if(EventID!=PreEventID)
							{
								if(VolumePre[0]=='m'&&VolumePost[0]=='c'){
								h1->Fill(EkPost*1000);//keV
								PreEventID=EventID;
								}
							}
						break;
						}
				case'a':
						{
						if(EventID!=PreEventID2)
							{
								if(VolumePre[0]=='m'&&VolumePost[0]=='c'){
								h2->Fill(EkPost*1000);
								PreEventID2=EventID;
									}
							}

						break;
						}
				case'g':
						{
						if(EventID!=PreEventID3&&ProcessName[0]=='n')
							{
								h3->Fill(EkPre*1000);
								PreEventID3=EventID;
							}
						break;
						}
			break;
		}//switch
	if(PName[0]=='e'&&ProcessName[0]=='i'&&ProcessName[1]=='o'){//电离电子能谱
		if(VolumePre[0]=='m'&&VolumePost[0]=='c'&&(EventID!=PreEventID4||TrackID!=PreTrackID4))
		{
			h4->Fill(EkPost*1000*1000);//ev
			PreEventID4=EventID;
			PreTrackID4=TrackID;
		}
	}
	}	//for
c1->cd();
h1->GetXaxis()->SetTitle("Ek/keV");
h1->GetYaxis()->SetTitle("Counts");
histgram_format(h1);
histgram_format(h2);
histgram_format(h3);
h1->SetLineColor(kBlue);
h2->SetLineColor(kRed);
h3->SetLineColor(kBlack);
h1->DrawCopy();
h2->DrawCopy("same");
auto legend =new TLegend(0.7,0.75,0.85,0.65);
legend->SetLineWidth(0);
legend->AddEntry(h1,"Li");
legend->AddEntry(h2,"Alpha");
legend->AddEntry(h3,"gamma");
legend->Draw();
c2->cd();
h4->GetXaxis()->SetTitle("Ek/eV");
h4->GetYaxis()->SetTitle("Counts");
histgram_format(h4);
h4->SetLineColor(kBlue);
h4->DrawCopy();
//h3->DrawCopy("same");
c1->SaveAs("BSpe.jpg");
}//void

double Eff(TTree *t1){
bool SF=0;
FILE *fp;
FILE *fp2;
if(SF){
fp=fopen("BP1.txt","a");
fp2=fopen("BP2.txt","a");
}
int sum =t1->GetEntries();
char PName[100],ProcessName[100],VolumePre[100],VolumePost[100];
int EventID=0,PreEventID=-1,PreEventIDp2=-1,PreEventIDp22=-1,PreEventIDp222=-1,PreEventIDtest=-1,TrackID=0,PreTrackID=-1;
int PreEventIDt1=-1,PreEventIDt2=-1,PreEventIDt3=-1,PreEventIDt4=-1,PreTrackIDt1=-2,PreTrackIDt2=-2,PreTrackIDt3=-2,PreTrackIDt4=-2;
double num=0.0,num3=0.0,testNum=0,nbli=0,nbal=0,nbe=0,nbe2=0;
int flag1=0,flag2=0,flag3=0,flag4=0,NBALPHA=0,NBLI=0,NBEGa=0,NBEIo=0,NBALPHALI=0;
double PreEventIDu1=-1,PreEventIDu2=-1,PreEventIDu3=-1;
int NbEvent=0;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("VolumePost",&VolumePost);

for (int i=0;i<sum;i++){
	t1->GetEntry(i);
	if (PreEventID!=EventID)//打在实体上总中子数
	{
		NbEvent++;
		PreEventID=EventID;
	}

	if (PName[0]=='L'||PName[0]=='a'){//||PName[0]=='e'){//是否应该计算电子，发生反应的中子数
//		num++;
		if(EventID!=PreEventIDp2){
			num++;
//			cout<<"aaaa"<<endl;
			PreEventIDp2=EventID;
		}
	}
	if(PName[0]=='L'||PName[0]=='a'||PName[0]=='e'){
	if(VolumePre[0]=='m'&&VolumePost[0]=='c'){//穿透通道
	if (EventID!=PreEventIDp222){///p2总效率
		num3++;
		PreEventIDp222=EventID;
			}
	if(PName[0]=='L'&&PName[1]=='i'&&(EventID!=PreEventIDt1||TrackID!=PreTrackIDt1)){
			nbli++;///Li出射数目	
			PreEventIDt1=EventID;
			PreTrackIDt1=TrackID;
	}
	if(PName[0]=='a'&&PName[1]=='l'&&(EventID!=PreEventIDt2||TrackID!=PreTrackIDt2)){
			nbal++;///alpha出射数目	
			PreEventIDt2=EventID;
			PreTrackIDt2=TrackID;
	}
	if(PName[0]=='e'&&(ProcessName[0]=='p'||ProcessName[0]=='c')&&(EventID!=PreEventIDt3||TrackID!=PreTrackIDt3)){
			nbe++;///电子出射数目 gamma直接产生的次级电子及其次级电子
		PreEventIDt3=EventID;
		PreTrackIDt3=TrackID;	
	}
	if(PName[0]=='e'&&(ProcessName[0]=='i'&&ProcessName[1]=='o')&&(EventID!=PreEventIDt4||TrackID!=PreTrackIDt4)){
			nbe2++;///电子出射数目 gamma直接产生的次级电子及其次级电子
		PreEventIDt4=EventID;
		PreTrackIDt4=TrackID;	
	}
		}
	}
	if(EventID!=PreEventIDu1){
	if(flag1==1&&flag2==0){//alpha出来 Li没出
		NBALPHA++;	
	}
	if(flag1==0&&flag2==1){//Li出来 alpha没出
	NBLI++;
	}
	if(flag1==0&&flag2==0&&flag3==1&&flag4==0){//只有gamma电子出来
	NBEGa++;
	}
	if(flag1==0&&flag2==0&&flag3==0&&flag4==1){//只有电离电子出来
	NBEIo++;
	}


	if(flag1==1&&flag2==1){//alpha和Li一块出来
	NBALPHALI++;
	}
	
	PreEventIDu1=EventID;
	flag1=0,flag2=0,flag3=0,flag4=0;
	}
	if(EventID==PreEventIDu1){
		if(PName[0]=='a'&&PName[1]=='l'&&(VolumePre[0]=='m'&&VolumePost[0]=='c')){
		flag1=1;
		}
		if(PName[0]=='L'&&PName[1]=='i'&&(VolumePre[0]=='m'&&VolumePost[0]=='c')){
		flag2=1;	
		}
		if(PName[0]=='e'&&(ProcessName[0]=='p'||ProcessName[0]=='c')&&(VolumePre[0]=='m'&&VolumePost[0]=='c')){
		flag3=1;	
		}
		if(PName[0]=='e'&&(ProcessName[0]=='i'&&ProcessName[1]=='o')&&(VolumePre[0]=='m'&&VolumePost[0]=='c')){
		flag4=1;	
		}
	
	}

}

//////

	
double p1=num/10000.0;
double p222=num3/10000.0;
//using p2 data
/*
cout<<"NbOfEvent="<<NbEvent<<" P2 without gamma="<<p2<<endl;
cout<<"P2 with gamma="<<p22<<endl;
*/
//using p1 data
cout<<"total n="<<NbEvent<<" react n="<<num<<" into channel="<<num3<<endl;
cout<<"p1="<<p1<<endl;
cout<<"p2="<<p222<<endl;
cout<<"p111"<<NbEvent/100000.0<<endl;
cout<<"-------------------------"<<endl;
cout<<"alpha out="<<nbal<<" Li out="<<nbli<<" GamE out="<<nbe<<" IonE out"<<nbe2<<endl;
cout<<"-------------------------"<<endl;
cout<<"only Alpha="<<NBALPHA<<" only Li="<<NBLI<<" only GammaE="<<NBEGa<<" Only IonE="<<NBEIo<<" AlandLi="<<NBALPHALI<<endl;
//cout<<"testNum="<<testNum<<endl;
if(SF){
fprintf(fp,"%f\t",p1);
fprintf(fp2,"%f\t",p222);
fclose(fp);
fclose(fp2);
}

return 0;
}
void nGamma(TTree *t1){
int sum =t1->GetEntries();
char PName[100],ProcessName[100],VolumePre[100],VolumePost[100];
int EventID=0,PreEventID=-1,PreEventIDp2=-1,PreEventIDp22=-1,PreEventIDp222=-1,TrackID=0,PreTrackID=-1,ParentID=0,flag=0;
double num=0.0,num2=0.0,xPost=0,yPost=0,length=0,EkPost=0;
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("VolumePre",&VolumePre);
t1->SetBranchAddress("VolumePost",&VolumePost);
t1->SetBranchAddress("EkPost",&EkPost);
t1->SetBranchAddress("xPost",&xPost);
t1->SetBranchAddress("yPost",&yPost);
TH1 *h1=new TH1F("h1"," ",1000,0,2000);
TH1 *h2=new TH1F("h2"," ",1000,0,1000);
TCanvas *c1=new TCanvas("c1"," ",200,10,700,500);
for (int i=0;i<sum;i++){
	t1->GetEntry(i);
		if(EventID!=PreEventID){
				if(num2>0){
//						cout<<num2<<endl;
				switch(PName[0]){
					case'n':{
			 		h1->Fill(num2);
					break;
					}
					case'g':{
					h2->Fill(num2);
					break;
					}
				break;
				}//switchi 
				}
			PreEventID=EventID;
			num2=0;
		}
		if(EventID==PreEventID){
			if(PName[0]=='e'&&EkPost==0){    //&&((VolumePre[0]=='m'&&VolumePost[0]=='c')||(VolumePre[0]=='c'&&VolumePost[0]=='m'))
					length=sqrt((xPost*1000-6)*(xPost*1000-6)+(yPost*1000)*(yPost*1000));
					num2=12/length+num2;
				}
			}
	
	}//for
c1->cd();
h2 ->GetXaxis()->SetTitle("Nume");
h2 ->GetYaxis()->SetTitle("Counts");
histgram_format(h2 );
h2 ->SetLineColor(kBlue);
h2 ->DrawCopy();
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
t1->SetBranchAddress("ProcessName",&ProcessName);
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
TCanvas *c4=new TCanvas("c4"," ",200,10,700,500);
TCanvas *c5=new TCanvas("c5"," ",200,10,700,500);
TH1 * h1=new TH1F("h1"," ",180,0,180);
TH1 * h2=new TH1F("h2"," ",180,0,180);
TH1 * h3=new TH1F("h3"," ",180,0,180);
TH1 * h4=new TH1F("h4","phi",720,-360,360);
TH1 * h5=new TH1F("h5","theta",360,-180,180);
for (int i=0;i<sum;i++){
	t1->GetEntry(i);
	double angz=0,angx=0,angy=0,angtheta=0,angphi=0;
	if(PName[0]=='a'||ProcessName[0]=='n'){
	angz=anglez(pxPre,pyPre,pzPre);//degree
	angx=anglex(pxPre,pyPre,pzPre);
	angy=angley(pxPre,pyPre,pzPre);
	angphi=anglephi(pxPre,pyPre,pzPre);
	angtheta=angletheta(pxPre,pyPre,pzPre);
	h1->Fill(angz);
	h2->Fill(angx);
	h3->Fill(angy);
	h4->Fill(angphi);
	h5->Fill(angtheta);
	}
}
c1->cd();
histgram_format(h1);
h1->DrawCopy();
c2->cd();
histgram_format(h2);
h2->DrawCopy();
c3->cd();
histgram_format(h3);
h3->DrawCopy();
c4->cd();
h4 ->GetXaxis()->SetTitle("Angle(deg)");
h4 ->GetYaxis()->SetTitle("Counts");
histgram_format(h4);
h4->DrawCopy();
c5->cd();
h5 ->GetXaxis()->SetTitle("Angle(deg)");
h5 ->GetYaxis()->SetTitle("Counts");
histgram_format(h5);
h5->DrawCopy();
}


int Btest(){
char str[50];
for(int i=0;i<1;i++){
//sprintf(str1,"f%d",i);
//sprintf(str2,"t%d",i);
sprintf(str,"B0_0_0.root",i+1);

cout<<"Processing "<<str<<endl;
TFile *f=new TFile(str);
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
//Eff(t1);
AngleDis(t1);
//ParSpe(t1);
//nGamma(t1);
f->Close();
}
return 0;
}
