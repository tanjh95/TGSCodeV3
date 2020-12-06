#include<stdio.h>
#include<iostream>

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

TCanvas* NG(TFile *fn,TFile *fg,TCanvas* c_1){
int rebin=10,BinNb=200,cut=20;
TH2F *h_1=(TH2F*)fn->Get("h5");
TH2F *h_2=(TH2F*)fg->Get("h5");//rebin后cut前
h_1->Rebin2D(rebin,rebin);
h_2->Rebin2D(rebin,rebin);
double count1=0,count2=0;
int BinNb2=BinNb/rebin;
TH2F *h_3=new TH2F("h_3"," ",BinNb2,-100,100,BinNb2,-100,100);
TH2F *h_4=new TH2F("h_4"," ",BinNb2,-100,100,BinNb2,-100,100);//经过cut后的hist
for (int i=0;i<BinNb2;i++){
	for(int j=0;j<BinNb2;j++){
	count1=h_1->GetBinContent(i,j)-cut;
	count2=h_2->GetBinContent(i,j)-cut;
	if (count1>0){
		h_3->SetBinContent(i,j,count1);
		}
	if(count2>0){
		h_4->SetBinContent(i,j,count2);
		}
	}
}
c_1->Divide(2,1);
c_1->cd(1);
h_3->DrawCopy("COLZ");
c_1->cd(2);
h_4->DrawCopy("COLZ");

return c_1;
}

TCanvas *Centrod(TFile *f_3,TCanvas *c_2){
TH2F*h_1=(TH2*)f_3->Get("h3");
TH2F*h_2=(TH2*)f_3->Get("h6");
TH1F*h_3=(TH1*)f_3->Get("h6_px");
TH1F*h_4=(TH1*)f_3->Get("h6_py");
int rebin=10,BinNb=200;
c_2->Divide(2,2);
h_1->Rebin2D(rebin,rebin);
h_2->Rebin2D(rebin,rebin);
h_3->Rebin(rebin);
h_4->Rebin(rebin);
c_2->cd(1);
h_1->GetXaxis()->SetTitle("PositionX/um");
h_1->GetYaxis()->SetTitle("PositionY/um");
h_1->GetXaxis()->CenterTitle();
h_1->GetYaxis()->CenterTitle();
h_1->DrawCopy("COLZ");
c_2->cd(2);
h_2->GetXaxis()->SetTitle("PositionX/um");
h_2->GetYaxis()->SetTitle("PositionY/um");
h_2->GetXaxis()->CenterTitle();
h_2->GetYaxis()->CenterTitle();
h_2->DrawCopy("COLZ");
c_2->cd(3);
h_3->GetXaxis()->SetTitle("PositionX/um");
h_3->GetYaxis()->SetTitle("Counts");
histgram_format(h_3);
h_3->DrawCopy();
c_2->cd(4);
h_4->GetXaxis()->SetTitle("PositionY/um");
h_4->GetYaxis()->SetTitle("Counts");
histgram_format(h_4);
h_4->DrawCopy();
return c_2;
}

TCanvas *Compare(TFile*f_3,TFile*f_4,TFile*f_5,TCanvas*c_3){
TH1F *h_1=(TH1*)f_3->Get("h6_px");
TH1F *h_2=(TH1*)f_4->Get("h6_px");
TH1F *h_3=(TH1*)f_5->Get("h6_px");
THStack *hs=new THStack("hs"," ");
double rms1=h_1->GetRMS();
double rms2=h_2->GetRMS();
double rms3=h_3->GetRMS();
h_1->SetLineColor(kRed);
h_1->SetLineWidth(2);
hs->Add(h_1);
h_2->SetLineColor(kBlue);
h_2->SetLineWidth(2);
hs->Add(h_2);
h_3->SetLineColor(kGreen);
h_3->SetLineWidth(3);
hs->Add(h_3);
c_3->Divide(2,1);
c_3->cd(1);
hs->Draw("nostack");
Stack_format(hs);
char str1[25],str2[25],str3[25];
sprintf(str1,"B2O3 RMS=%d",rms1);
sprintf(str2,"Gd2O3 RMS=%d",rms2);
sprintf(str3,"B2O3+Gd2O3 RMS=%d",rms3);
auto legend=new TLegend(0.6,0.8,0.85,0.6);
legend->AddEntry(h_1,str1);
legend->AddEntry(h_2,str2);
legend->AddEntry(h_3,str3);
legend->Draw();

c_3->cd(2);
TH1F *h_4=(TH1*)f_3->Get("h6_py");
TH1F *h_5=(TH1*)f_4->Get("h6_py");
TH1F *h_6=(TH1*)f_5->Get("h6_py");
THStack *hs2=new THStack("hs2"," ");
double rms11=h_4->GetRMS();
double rms22=h_5->GetRMS();
double rms33=h_6->GetRMS();
h_4->SetLineColor(kRed);
h_4->SetLineWidth(2);
hs2->Add(h_4);
h_5->SetLineColor(kBlue);
h_5->SetLineWidth(2);
hs2->Add(h_5);
h_6->SetLineColor(kGreen);
h_6->SetLineWidth(3);
hs2->Add(h_6);
hs2->Draw("nostack");
Stack_format(hs2);
auto legend2=new TLegend(0.6,0.8,0.85,0.6);
legend2->AddEntry(h_4,str1);
legend2->AddEntry(h_5,str2);
legend2->AddEntry(h_6,str3);
legend2->Draw();
return c_3;
}

int ProcessRoot2(){
string file1,file2,file3,file4,file5,file6;
file1="GdneutH2D.root";
file2="GdgamH2D.root";//BGd=25 gamma全甄别  B=22  Gd=24
TFile *f1=new TFile(file1.c_str());
TFile *f2=new TFile(file2.c_str());
TCanvas *c1=new TCanvas("c1"," ",200,10,1000,500);
//c1=NG(f1,f2,c1);//f1:中子数据 f2:gamma数据 c1:Canvas
//c1->SaveAs("BGd0.jpg");
f1->Close();
f2->Close();
file3="B6degResLar2.root";
TFile *f3=new TFile(file3.c_str());
TCanvas *c2=new TCanvas("c2"," ",200,10,1000,500);
c2=Centrod(f3,c2);
f3->Close();
file4="Gd6degResLar2.root";
file5="BGd6degResLar2.root";
TFile *f3=new TFile(file3.c_str());
TFile *f4=new TFile(file4.c_str());
TFile *f5=new TFile(file5.c_str());
TCanvas *c3=new TCanvas("c3"," ",200,10,1000,500);
//c3=Compare(f3,f4,f5,c3);
return 0;
}
