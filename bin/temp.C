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
	h->SetLineWidth(2);
	h->SetLineColor(kBlue);
	h->SetLineStyle(1);
}


int temp(){
	TFile *f=new TFile("test_t0.root");
	TTree *t1=(TTree*)f->Get("t");
	int sum =t1->GetEntries();
	char PName[100],ProcessName[100];
	int EventID=0,PreEventID=-1,TrackID=0,PreTrackID=-1;
	double EkPre=0.;
	t1->SetBranchAddress("ProcessName",ProcessName);
	t1->SetBranchAddress("PName",PName);
	t1->SetBranchAddress("EventID",&EventID);
	t1->SetBranchAddress("EkPre",&EkPre);
	t1->SetBranchAddress("TrackID",&TrackID);
	TH1 *h2=new TH1F("h2"," ",500,0,250);
	TCanvas *c2=new TCanvas("c2"," ",200,10,700,500);

	for(int i=0;i<sum;i++){
	t1->GetEntry(i);
	if (PName[0]=='e'&&ProcessName[0]=='n'){
		if (EventID!=PreEventID||TrackID!=PreTrackID){
		//		if(EkPre>0.001){
			h2->Fill(EkPre*1000);
	//		cout<<"EkPre= "<<EkPre*1000<<endl;
			PreEventID=EventID;
			PreTrackID=TrackID;
		//		}
		}
	}

	}

c2->cd(1);
c2->SetFrameLineWidth(2);
h2->GetXaxis()->SetTitle("Ek /keV");
h2->GetYaxis()->SetTitle("Counts");
istgram_format(h2);
h2->DrawCopy();


 cout<<"sum= "<<sum<<endl;
 f->Close();

return 0;
}
