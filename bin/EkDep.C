#include <iostream>
#include <stdio.h>
#include <fstream>
void GammaDep(TTree *t1){
		
int sum =t1->GetEntries();
char PName[50],ProcessName[50];
int EventID=0,PreEventIDg=-1,PreEventIDn=-1,PreEventID=-1,num=0;
double Edep=0.,EkPre=0.,gEdep=0.,nEdep=0.;
TCanvas *c1=new TCanvas("c1","Edep",100,10,1050,700);
//TH1 *h1=new TH1F("h1"," ",120,0,1000);//Gd
//TH1 *h2=new TH1F("h2"," ",120,0,1000);//Gd

TH1 *h1=new TH1F("h1","B",500,0,3000);//B
TH1 *h2=new TH1F("h2"," ",500,0,3000);//B

t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("Edep",&Edep);
t1->SetBranchAddress("EkPre",&EkPre);

//t1->SetBranchAddress("TrackID",&TrackID);
for(int i=0;i<sum;i++){
t1->GetEntry(i);
if(PName[0]=='n'&&ProcessName[0]=='#'&&Edep!=0){
num++;
}
/*
if (PreEventID!=EventID&&PName[0]=='g'){//入射能谱
	h2->Fill(EkPre*1000);
	PreEventID=EventID;

}
*/
/*	
	if (EventID!=PreEventIDg){//沉积能量

		if(PreEdepg>0){
		h1->Fill(PreEdepg*1000);//上一个粒子的沉积能量keV
		PreEdepg=0.;
					}

		if(PName[0]=='g'&&ProcessName[0]=='#'){
		PreEventIDg=EventID;
		PreEdepg=Edep;
				}
	}
	else
		{
		PreEdepg+=Edep;
		}
*/
	if(EventID!=PreEventID){
		if(nEdep>0){
			h1->Fill(nEdep*1000);
			nEdep=0;
			}
		if(gEdep>0){
			h2->Fill(gEdep*1000);
			gEdep=0;
			}
	if(PName[0]=='n'&&ProcessName[0]=='#'){
				nEdep=Edep;
				gEdep=0;
				PreEventIDn=EventID;
					}
	if(PName[0]=='g'&&ProcessName[0]=='#'){
			gEdep=Edep;
			nEdep=0;
			PreEventIDg=EventID;
	}
	PreEventID=EventID;
}
	else{
		if(EventID==PreEventIDn){
				if(PName[0]!='e'&&PName[0]!='g'){
				nEdep+=Edep	;
			}
		}
		if(EventID==PreEventIDg){
			gEdep+=Edep;
			}

		}
	}
//c1->Divide(2,1);
c1->cd();
c1->SetLogy();
//c1->SetLogx();
c1->SetFrameLineWidth(3);
h1->SetStats(kFALSE);
//h1->GetXaxis()->SetRangeUser(0,1000);//Gd
h1->GetXaxis()->SetRangeUser(0,3000);//B

h1->GetXaxis()->SetTitle("E(keV)");
h1->GetYaxis()->SetTitle("Counts");
h1->GetXaxis()->CenterTitle();
h1->GetYaxis()->CenterTitle();
h1->GetXaxis()->SetLabelSize(0.05);//轴上数字大小 0.05
h1->GetXaxis()->SetLabelFont(62);//轴上字体加粗
h1->GetXaxis()->SetTitleSize(0.05);//轴上标题大小
h1->GetXaxis()->SetTitleFont(62);//轴上标题加粗
h1->GetYaxis()->SetLabelSize(0.05);
h1->GetYaxis()->SetLabelFont(62);
h1->GetYaxis()->SetTitleSize(0.05);
h1->GetYaxis()->SetTitleFont(62);
h1->GetYaxis()->SetTitleOffset(1);
h1->SetLineWidth(4);
h1->SetLineColor(2);
h1->SetLineStyle(2);

h2->SetLineWidth(4);
h2->SetLineColor(4);
//h2->SetMarkerStyle(22);
//h2->SetMarkerSize(1.4);
//h2->SetFillColor(kRed);
//h2->SetFillStyle(3008);
//h2->SetLineStyle(2);
h1->Draw();
//c1->cd(2);
h2->Draw("same");

auto legend =new TLegend(0.5,0.85,0.7,0.65);//B&Gd

legend->SetLineWidth(0);
legend->AddEntry(h1,"Neutron");
legend->AddEntry(h2,"Gamma");
legend->Draw();
c1->SaveAs("Bng.jpg");
cout<<num<<"=n scatter"<<endl;
}


int EkDep(){
TFile *f=new TFile("BNG.root");
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");
//ParDep(t1);
GammaDep(t1);
//f->Close();

//f2->Close();
return 0;
}
