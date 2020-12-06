#include<stdio.h>
#include<iostream>
//Processing rootFile from  ProcessRoot1
//Output RMS to txt
string str="BGdnat8_2_6_";//设置文件名
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

void RmsRes(TFile *f1){
double RmsX=0,RmsY=0;
bool SF=1;
FILE *fp;
FILE *fp2;
if(SF){
fp=fopen("RMSX.txt","a");
fp2=fopen("RMSY.txt","a");
}

int rebin=2;
TH1F*h_1=(TH1F*)f1->Get("h6_px");
TH1F*h_2=(TH1F*)f1->Get("h6_py");
h_1->Rebin(rebin);
h_2->Rebin(rebin);
RmsX=h_1->GetRMS();
RmsY=h_2->GetRMS();
cout<<"RmsX="<<RmsX<<endl;
cout<<"RmsY="<<RmsY<<endl;
if(SF){
fprintf(fp,"%f\n",RmsX);
fprintf(fp2,"%f\n",RmsY);
fclose(fp);
fclose(fp2);
	}
}


int ProcessRoot3(){
string str2;
stringstream ss;
for (int k=0;k<5;k++){
	ss<<k+3;
	ss>>str2;
	string filename=str+str2+"_2.root";
	TFile *f=new TFile(filename.c_str());
	cout<<"processing "<<filename<<endl;
	RmsRes(f);
	ss.clear();
	ss.str("");
	f->Close();
}


return 0;
}
