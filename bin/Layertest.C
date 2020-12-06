#include <stdio.h>
#include <iostream>

void Btest(TTree *t1){
	FILE *fp;
	fp=fopen("BEdepData.txt","a");

int sum =t1->GetEntries();
char PName[10],ProcessName[20];
TH1 *h1=new TH1F("h1"," ",800,0,2000);//
//TH1 *h2=new TH1F("h2","gEdep",1000,0,1000);//gamma直射时候用
//TH1 *h2=new TH1F("h2","gEdep",100,0,20);//mcp整体沉积能量时候用
TH1 *h2=new TH1F("h2","gEdep",120,0,10);//Layer沉积能量时候用 .8mm->200,0,20 .6mm->120,0,10 
TH1 *h3=new TH1F("h3","N/gamma",100,0,100);//N gamma沉积能量比,没做出来
TCanvas *c1=new TCanvas("c1","Edep",50,10,900,500);
int EventID=0,TrackID=0,PreTrackID=-1,PreEventID=0,PreEventID2=0,PreEventIDp22=-1,PreEventIDp222=-1;
double num=0.0,num2=0.0,num3=0.0;//待用
double Edep=0.,nEdep=0.,gEdep=0.,nEdepTotal=0.,gEdepTotal=0.;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("Edep",&Edep);
t1->SetBranchAddress("TrackID",&TrackID);
for(int i=0;i<sum;i++){
t1->GetEntry(i);

//把nEdep和gEdep的计算放在一个Event判断里，方便读出nEdep和gEdep的比。但是现在与分别算相比差一点，已修正。
if(EventID!=PreEventID){
	if(nEdep>0){	
	h1->Fill(nEdep*1000);
	nEdepTotal+=nEdep;	
	nEdep=0;//防止在没有来a/Li的时候重复将之前的Fill
	}
	if(gEdep>0){	
	h2->Fill(gEdep*1000);
	gEdepTotal+=gEdep;
	gEdep=0;//防止在没来gamma时重复fill
	}
	if(PName[0]=='a'||PName[0]=='L'){
	nEdep=Edep;
	gEdep=0;
	}
	if (PName[0]=='g'||ProcessName[0]=='p'||ProcessName[0]=='c'||ProcessName[0]=='e'){ 
	gEdep=Edep;
	nEdep=0;
	}
	PreEventID=EventID;
}
else{
	if(PName[0]=='a'||PName[0]=='L'){
	nEdep+=Edep;
	}
	if (PName[0]=='g'||ProcessName[0]=='p'||ProcessName[0]=='c'||ProcessName[0]=='e'){ 
	gEdep+=Edep;
	}
}

/*
if(PName[0]=='L'||PName[0]=='a'){//中子信号沉积能量
	if(EventID!=PreEventID){//不同Event，填充上一个Event的Edep
		h1->Fill(nEdep*1000);
		PreEventID=EventID;
		nEdep=Edep;
		}	
	else{
		nEdep=nEdep+Edep;//同一个Event，累加Edep。
		}
	}
*/
/* gamma入射，测到的能量沉积准确
//if(PName[0]=='e'&&(ProcessName[0]=='p'||ProcessName[0]=='c')){//gamma信号沉积能量(包括光电子和康普顿电子),忽略了gamma的散射
	if(EventID!=PreEventID2){//||TrackID!=PreTrackID){//一个中子可能产生不止一个光子，一个光子可能产生不止一个电子
		h2->Fill(gEdep*1000);
		PreEventID2=EventID;
//		PreTrackID=TrackID;
		gEdep=Edep;
		}
	else { //在Event和Track都相等时表明是同一个粒子的不同步，这是Edep累加。
		gEdep+=Edep;
		}
//	}
       */
/*
	if (PName[0]=='g'||ProcessName[0]=='p'||ProcessName[0]=='c'||ProcessName[0]=='e'){//不能丢掉ProcessName=eIon,否则只记录了电子第一步产生的沉积。
																					//不能丢掉PName=gamma，否则gamma散射丢掉了

		if(EventID!=PreEventID2){
		if (gEdep>0){	h2->Fill(gEdep*1000);}
		PreEventID2=EventID;
		gEdep=Edep;
		}
		else{
		gEdep+=Edep;
		}

}
*/
}
num=nEdepTotal/gEdepTotal;
//cout<<"n/gamma"<<num<<endl;
//c1->Divide(2,1);
c1->cd();
//c1->SetLogx();
h1->GetXaxis()->SetTitle("E(keV)");
h1->GetYaxis()->SetTitle("counts");
h1->GetXaxis()->CenterTitle();
h1->GetYaxis()->CenterTitle();
h1->GetXaxis()->SetLabelSize(0.04);//轴上数字大小 0.05
h1->GetXaxis()->SetLabelFont(62);//轴上字体加粗
h1->GetXaxis()->SetTitleSize(0.04);//轴上标题大小
h1->GetXaxis()->SetTitleFont(62);//轴上标题加粗
h1->GetYaxis()->SetLabelSize(0.04);
h1->GetYaxis()->SetLabelFont(62);
h1->GetYaxis()->SetTitleSize(0.04);
h1->GetYaxis()->SetTitleFont(62);
h1->GetYaxis()->SetTitleOffset(1.1);
h1->SetLineWidth(2);
h2->SetLineWidth(2);
h2->SetLineColor(2);
/*
h1->Draw();
c1->cd(2);
h2->GetXaxis()->SetTitle("E(keV)");
h2->GetYaxis()->SetTitle("counts");
h2->GetXaxis()->CenterTitle();
h2->GetYaxis()->CenterTitle();
h2->GetXaxis()->SetLabelSize(0.04);//轴上数字大小 0.05
h2->GetXaxis()->SetLabelFont(62);//轴上字体加粗
h2->GetXaxis()->SetTitleSize(0.04);//轴上标题大小
h2->GetXaxis()->SetTitleFont(62);//轴上标题加粗
h2->GetYaxis()->SetLabelSize(0.04);
h2->GetYaxis()->SetLabelFont(62);
h2->GetYaxis()->SetTitleSize(0.04);
h2->GetYaxis()->SetTitleFont(62);
h2->GetYaxis()->SetTitleOffset(1.1);
*/
auto legend =new TLegend(0.2,0.7,0.4,0.5);
legend->SetLineWidth(0);
legend->AddEntry(h1,"Charged Edep","l");
legend->AddEntry(h2,"Gamma Edep","l");

h1->Draw();
h2->Draw("same");
//legend->Draw();
//c1->SaveAs("B420NGLog.png");
cout<<"n/gamma="<<num<<endl;
//fprintf(fp,"%f\t",num);
fclose(fp);
}

void Gdtest(TTree *t1){//局限性在于每个Event的第一个step不能是eIon
	FILE *fp;
	fp=fopen("GdEdepData.txt","a");

int sum =t1->GetEntries();
char PName[10],ProcessName[20];
TH1 *h1=new TH1F("h1","nEdep",400,0,250);//
//TH1 *h2=new TH1F("h2","gEdep",1000,0,1000);//
//TH1 *h2=new TH1F("h2","gEdep",100,0,20);//
TH1 *h2=new TH1F("h2","gEdep",4000,0,4000);//
TCanvas *c1=new TCanvas("c1","Edep",100,10,900,500);
int ParentID=0,EventID=0,TrackID=0,PreTrackIDn=-1,PreTrackIDg=-2,PreEventID=0,PreEventID2=0,PreEventIDp22=-1,PreEventIDp222=-1;
double num=0.0,ntotal=0.,gtotal=0.;
double Edep=0.,nEdep=0.,gEdep=0.;
t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("Edep",&Edep);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("ParentID",&ParentID);
for(int i=0;i<sum;i++){
t1->GetEntry(i);
	if(EventID!=PreEventID){//直方图填充
	if(nEdep>0){
	h1->Fill(nEdep*1000);//keV
	ntotal+=nEdep;
	nEdep=0;	//防止重复填充
	 }
	if(gEdep>0){
	h2->Fill(gEdep*1000); 
	gtotal+=gEdep;
	gEdep=0;
	}

	if (PName[0]=='e'&&ProcessName[0]=='n'){//n产生的e
		nEdep=Edep;//Edep初始化
		gEdep=0;
//		PreParentIDn=ParentID;//ParentID初始化
//		PreParentIDg=-2;		
		PreTrackIDn=TrackID;//TrackID初始化
		PreTrackIDg=-2;
	}	
	if(PName[0]=='g'||(PName[0]=='e'&&(ProcessName[0]=='p'||ProcessName[0]=='c'))){ ///gamma产生的e
		gEdep=Edep;
		nEdep=0;
//		PreParentIDn=-2;
//		PreParentIDg=ParentID;
		if(PName[0]=='e'){
		PreTrackIDn=-2;
		PreTrackIDg=TrackID;
		}
	}

	PreEventID=EventID;	//在EventID改变时没有对eIon考虑，因为eIon只能是次级粒子(本程序不考虑外部来的eIon)
}
else {
	
	if (PName[0]=='g'||(PName[0]=='e'&&(ProcessName[0]=='p'||ProcessName[0]=='c'))){//一个粒子是一个trackID,G4会把同一个粒子处理完再处理下一个粒子，因此trackID的粒子都连在一起
		gEdep+=Edep;
		if(PName[0]=='e'){//可能会产生eIon,初始化ParentID
//		PreParentIDg=ParentID;//目前没用到
		PreTrackIDg=TrackID;//
		}
	
	}

	if(PName[0]=='e'&&ProcessName[0]=='n'){//中子产生电子
		nEdep+=Edep;
//		PreParentIDn=ParentID;
		PreTrackIDn=TrackID;
	}

	if(PName[0]=='e'&&ProcessName[0]=='e'){//分辨eIon
	if(ParentID==PreTrackIDg){//由gamma产生的eIon
	gEdep+=Edep;
	}
	if(ParentID==PreTrackIDn){//由n产生的eIon
	nEdep+=Edep;
	}
	
	}


	}
}
//c1->Divide(2,1);
//c1->cd(1);
//c1->SetLogy();
h1->GetXaxis()->SetTitle("E(keV)");
h1->GetYaxis()->SetTitle("counts");
h1->GetXaxis()->CenterTitle();
h1->GetYaxis()->CenterTitle();
h1->GetXaxis()->SetLabelSize(0.04);//轴上数字大小 0.05
h1->GetXaxis()->SetLabelFont(62);//轴上字体加粗
h1->GetXaxis()->SetTitleSize(0.04);//轴上标题大小
h1->GetXaxis()->SetTitleFont(62);//轴上标题加粗
h1->GetYaxis()->SetLabelSize(0.04);
h1->GetYaxis()->SetLabelFont(62);
h1->GetYaxis()->SetTitleSize(0.04);
h1->GetYaxis()->SetTitleFont(62);
h1->GetYaxis()->SetTitleOffset(1.3);

/*
h1->Draw();
c1->cd(2);
h2->GetXaxis()->SetTitle("E(keV)");
h2->GetYaxis()->SetTitle("counts");
h2->GetXaxis()->CenterTitle();
h2->GetYaxis()->CenterTitle();
h2->Draw();
num2=ntotal/gtotal;
cout<<"n/gamma="<<num2<<endl;
//fprintf(fp,"%f\t",num2);
*/


}


int Layertest(){
TFile *f=new TFile("B6_10.root");
TTree *t1=new TTree("tree","tree disk");
t1=(TTree*)f->Get("t");

//Gdtest(t1);
Btest(t1);
//f->Close();
return 0;
}
