#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
//全二维图  2DHist()
////面源入射，归一到同一点
//位置:新Centroding
//伽马甄别:可以卡不同cut
string str="B";//设置文件名
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

void char2double(char* VolumePost,double*ch1){//char转double 获得channel中的信息
	string ss,ss2;
	stringstream ss3;
	ss=VolumePost;
	ss2=ss.substr(1);
	ss3<<ss2;
	ss3>>ch1[0]>>ch1[1]>>ch1[2];
//	cout<<ch[0]<<endl;
}
int char2int(char *VolumePre){
	string ss,ss2,temp;
	stringstream ss3;
	int NbChan=0;
	ss=VolumePre;
	ss2=ss.substr(1);
	ss3<<ss2;
	ss3>>temp>>NbChan;
	return NbChan;
}

void Hist2D(TTree *t1,string str3){
int sum =t1->GetEntries();
//string outfile=str+"H2D.root"
string filename2=str3+"_2.root";
cout<<"target file: "<<filename2<<endl;
TFile *fout=new TFile(filename2.c_str(),"RECREATE");
char PName[100],VolumePre[100],VolumePost[100],ProcessName[100];
int EventID=0,PreEventID=-1,PreEventIDp2=-1,PreEventIDp22=-1,PreEventIDp222=-1,TrackID=0,PreTrackID=-1,ParentID=0,flag=0,num1=0;
double posX=0,posY=0,xPost=0,yPost=0,length=0,EkPost=0,temp_a=0,temp_aa=0,temp_bb=0;
double xPre=0,yPre=0,xIni=0,yIni=0,channel_x=0,channel_y=0;
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
TH2 *h1=new TH2F("h1"," ",200,-100,100,200,-100,100);//电子终点二维图
TH2 *h2=new TH2F("h2"," ",200,-100,100,200,-100,100);//电子最后通道二维图 
TH2 *h3=new TH2F("h3"," ",200,-100,100,200,-100,100);//对每个Event 进行Centrod 
TH2 *h4=new TH2F("h4"," ",200,-100,100,200,-100,100);//电子终点二维图  归一
TH2 *h5=new TH2F("h5"," ",200,-100,100,200,-100,100);//电子最后通道二维图  归一
TH2 *h6=new TH2F("h6"," ",200,-100,100,200,-100,100);//对每个Event 进行Centrod  归一
TCanvas *c1=new TCanvas("c1"," ",200,10,1000,500);
TCanvas *c2=new TCanvas("c2"," ",200,10,500,500);
TCanvas *c3=new TCanvas("c3"," ",200,10,1000,1000);
c1->Divide(2,1);
c2->Divide(2,1);
c3->Divide(2,2);

t1->GetEntry(0);
int NbChan=char2int(VolumePre);
double (*channel)[3]=new double[NbChan][3];
//229取决于模拟时通道设置了多少，229需要大于等于设置的通道数
double ch[3]={0,0,0};
cout<<"NbChan="<<NbChan<<endl;
for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if(EventID!=PreEventID){
//////////////////////////////////////////////////////////	

		for(int k=0;k<NbChan;k++){//遍历229个channel
		int channelID=(int)channel[k][0];
			if(channelID!=0){
				channel_x=channel[k][1]-xIni;
				channel_y=channel[k][2]-yIni;
			
				for(int s=0;s<channelID;s++){////有问题！！！！
					//for(int s=0;s<100;s++){
					h2->Fill(channel[k][1],channel[k][2]);
					//h5->Fill(channel[k][1]-xIni,channel[k][2]-yIni);
					h5->Fill(channel_x,channel_y);
//					cout<<"k="<<k<<endl;
					}
				
				temp_a=channel[k][0]+temp_a;
				temp_aa=channel[k][0]*channel[k][1]+temp_aa;
				temp_bb=channel[k][0]*channel[k][2]+temp_bb;
			}
			
		
		}
		

		if (temp_a!=0){
		posX=temp_aa/temp_a;//-xIni;
		posY=temp_bb/temp_a;//-yIni;
//		cout<<"posX="<<posX<<" "<<"posY="<<posY<<" EventID="<<EventID<<endl;
		h3->Fill(posX,posY);
		h6->Fill(posX-xIni,posY-yIni);
		temp_a=0;
		temp_aa=0;
		temp_bb=0;
		}
		memset(channel,0,NbChan*3*sizeof(double));
		PreEventID=EventID;////////////////////
		xIni=xPre*1000;//每个Event初始位置  一个Event彻底结束，变量初始化完毕
		yIni=yPre*1000;////////////////////////
	}
	if(PreEventID==EventID){

	if(PName[0]=='e'||(PName[0]=='a'&&PName[1]=='l')||PName[0]=='L'){
		if(EkPost==0){
			posX=xPost*1000;
			posY=yPost*1000;	
			h1->Fill(posX,posY);
			h4->Fill(posX-xIni,posY-yIni);
		//	cout<<posX<<"  "<<posY<<endl;
			}//基体内电子终点,用于填充h1
		if(TrackID!=PreTrackID){//一个track只记录该track最后经过的channel中心坐标
			if(flag!=0){//判断该电子是否有进入通道，没有则舍弃
				int ch0=ch[0];
				channel[ch0][0]++;//counts
				channel[ch0][1]=ch[1];//x um
				channel[ch0][2]=ch[2];//y um
//				cout<<channel[ch[0]][0]<<" "<<channel[ch[0]][1]<<" "<<channel[ch[0]][2]<<endl;
				flag=0;
				}
			PreTrackID=TrackID;
			}
		if(TrackID==PreTrackID&&(VolumePre[0]=='m'&&VolumePost[0]=='c')){
			char2double(VolumePost,ch);//ch只存电子经过的最后一个channel
			flag=1;
			}

		}
	 
	}
}
c1->cd(1);
h1->DrawCopy("COLZ");
c1->cd(2);
h4->DrawCopy("COLZ");
c2->cd(1);
h2->GetXaxis()->SetTitle("PositionX/um");
h2->GetYaxis()->SetTitle("PositionY/um");
h2->GetXaxis()->CenterTitle();
h2->GetYaxis()->CenterTitle();
h2->DrawCopy("COLZ");
c2->cd(2);
h5->DrawCopy("COLZ");
c3->cd(1);
h3->GetXaxis()->SetTitle("PositionX/um");
h3->GetYaxis()->SetTitle("PositionY/um");
h3->GetXaxis()->CenterTitle();
h3->GetYaxis()->CenterTitle();
h3->DrawCopy("COLZ");
c3->cd(2);
h6->GetXaxis()->SetTitle("PositionX/um");
h6->GetYaxis()->SetTitle("PositionY/um");
h6->GetXaxis()->CenterTitle();
h6->GetYaxis()->CenterTitle();
h6->DrawCopy("COLZ");
c3->cd(3);
TH1 *h6x=h6->ProjectionX();
h6x->GetXaxis()->SetTitle("PositionX/um");
h6x->GetYaxis()->SetTitle("Counts");
histgram_format(h6x);
h6x->DrawCopy();
c3->cd(4);
TH1 *h6y=h6->ProjectionY();
h6y->GetXaxis()->SetTitle("PositionY/um");
h6y->GetYaxis()->SetTitle("Counts");
histgram_format(h6y);
h6y->DrawCopy();
//c1->SaveAs("BGd6c1.jpg");
//c2->SaveAs("BGd6c2.jpg");
//c3->SaveAs("BGd6c3.jpg");
fout->Write();
delete []channel;
delete c1;
delete c2;
delete c3;
delete h1,h2,h3,h4,h5,h6;
fout->Close();
}
int ProcessRoot1(){
string str2,str3;
stringstream ss;
str3="_2_0";
for(int k=0;k<5;k++){
	ss<<k+6;
	ss>>str2;
string filename=str+str2+str3+".root";
//TFile *f=new TFile(filename.c_str());
cout<<"Processing "<<filename<<endl;
TFile *f=new TFile(filename.c_str());
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
Hist2D(t1,str+str2+str3);
ss.clear();//
ss.str("");//重置sstream，缺一不可
f->Close();
}
return 0;
}
