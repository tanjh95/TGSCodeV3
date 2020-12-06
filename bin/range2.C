#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string>
double getRange(const double start[3],const double end[3],const double direction[3]){
 double range=0.,Cos=0.,length=0.,temp1=0.,temp2=0.,temp3=0.,motemp=1111,modir=1111;
 temp1=end[0]-start[0];
 temp2=end[1]-start[1];
 temp3=end[2]-start[2];
 double temp[3]={temp1,temp2,temp3};//位移向量
 length=sqrt(temp1*temp1+temp2*temp2+temp3*temp3)*1000;//um
 motemp=sqrt(temp[0]*temp[0]+temp[1]*temp[1]+temp[2]*temp[2]);//temp的模
 modir=sqrt(direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2]);
 Cos=(temp[0]*direction[0]+temp[1]*direction[1]+temp[2]*direction[2])/(modir*motemp);//向量点乘/向量模的积=向量夹角余弦值
	if(Cos>0){
 	range=length*Cos;//um
		}
	else{
	range=length*Cos*-1;
	}
//cout<<"length="<<length<<" Cos="<<Cos<<" motemp="<<motemp<<" modir="<<modir<<endl;
return range;
}


void processing(TTree *t1){
double rangeLi=0.,rangeal=0.,rangeE=0.;
double startLi[3]={0},endLi[3]={0},dirLi[3]={0},startal[3]={0},endal[3]={0},diral[3]={0},startE[3]={0},endE[3]={0},dirE[3]={0};
int sum = t1->GetEntries();
char PName[10],ProcessName[20];
double xPost=0.,yPost=0.,zPost=0.,xPre=0.,yPre=0.,zPre=0.,pxPre=0.,pyPre=0.,pzPre=0.;
int EventID=0,PreEventIDLi=-1,PreEventIDal=-1,PreEventIDE=-1,TrackID=0,PreTrackIDLi=-2,PreTrackIDal=-2,PreTrackIDE=-2;
int NbLi=0,Nbal=0,NbE=0;
TH1 *h1=new TH1F("h1"," ",2000,0,1100);//um
TH1 *h2=new TH1F("h2","rangeAlp",2000,0,1100);//um
TH1 *h3=new TH1F("h3"," ",2000,0,1100);
TCanvas *c1=new TCanvas("c1","range",100,10,1050,700);
//c1->Divide(2,1);

t1->SetBranchAddress("ProcessName",&ProcessName);
t1->SetBranchAddress("PName",&PName);
t1->SetBranchAddress("EventID",&EventID);
t1->SetBranchAddress("TrackID",&TrackID);
t1->SetBranchAddress("xPost",&xPost);
t1->SetBranchAddress("yPost",&yPost);
t1->SetBranchAddress("zPost",&zPost);
t1->SetBranchAddress("xPre",&xPre);
t1->SetBranchAddress("yPre",&yPre);
t1->SetBranchAddress("zPre",&zPre);
t1->SetBranchAddress("pxPre",&pxPre);
t1->SetBranchAddress("pyPre",&pyPre);
t1->SetBranchAddress("pzPre",&pzPre);
for(int i=0;i<sum;i++){
	t1->GetEntry(i);

	if(PName[0]=='a'&&PName[1]=='l'){
		if(EventID!=PreEventIDal||TrackID!=PreTrackIDal){
			rangeal=getRange(startal,endal,diral);
			if(rangeal>0){
				h2->Fill(rangeal);
					}
			startal[0]=xPre;
			startal[1]=yPre;
			startal[2]=zPre;
			diral[0]=pxPre;
			diral[1]=pyPre;
			diral[2]=pzPre;
			endal[0]=xPost;
			endal[1]=yPost;
			endal[2]=zPost;
			PreEventIDal=EventID;
			PreTrackIDal=TrackID;
			Nbal++;
//cout<<"al "<<rangeal<<endl;
		}
		else{//还是上一个al
			endal[0]=xPost;
			endal[1]=yPost;
			endal[2]=zPost;
		}

	}

	if(PName[0]=='L'){
		if(EventID!=PreEventIDLi||TrackID!=PreTrackIDLi){//出现下一个Li
			rangeLi=getRange(startLi,endLi,dirLi);
			if (rangeLi>0){ 
				h1->Fill(rangeLi);
							}
			startLi[0]=xPre;
			startLi[1]=yPre;
			startLi[2]=zPre;
			dirLi[0]=pxPre;
			dirLi[1]=pyPre;
			dirLi[2]=pzPre;
			endLi[0]=xPost;
			endLi[1]=yPost;
			endLi[2]=zPost;
			PreEventIDLi=EventID;
			PreTrackIDLi=TrackID;
			NbLi++;
//cout<<"Li "<<rangeLi<<endl;
		}
		else{//还是上一个Li
			endLi[0]=xPost;
			endLi[1]=yPost;
			endLi[2]=zPost;
		}
	}

if(PName[0]=='e'&&ProcessName[0]=='n'){
		if(EventID!=PreEventIDE||TrackID!=PreTrackIDE){
			rangeE=getRange(startE,endE,dirE);
			if(rangeE>0){
				h3->Fill(rangeE);
				}
			startE[0]=xPre;
			startE[1]=yPre;
			startE[2]=zPre;
			dirE[0]=pxPre;
			dirE[1]=pyPre;
			dirE[2]=pzPre;
			endE[0]=xPost;
			endE[1]=yPost;
			endE[2]=zPost;
			PreEventIDE=EventID;
			PreTrackIDE=TrackID;
			NbE++;		
//cout<<"rangeE= "<<rangeE<<endl;
			}
		else{
			endE[0]=xPost;
			endE[1]=yPost;
			endE[2]=zPost;
			}

			}

	}//for 循环结束
c1->SetLogy();
c1->SetLogx();

c1->SetFrameLineWidth(3);
//c1->SetRightMargin(0.15);
//c1->cd(1);
h1->SetStats(kFALSE);
h1->GetXaxis()->SetRangeUser(1,1100);
h1->GetXaxis()->SetTitle("Range(um)");
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
h1->GetYaxis()->SetTitleOffset(0.9);
h1->GetXaxis()->SetTitleOffset(1);
//h1->SetLineStyle(8);
//h1->SetFillColor(kBlue);//直方图填充颜色，默认白色
//h1->SetFillStyle(3001);//直方图填充图案
h1->SetLineStyle(2);//5挺好，
h1->SetLineWidth(4);
h1->SetLineColor(1);
h2->SetLineWidth(4);
//h2->SetLineStyle(2);
//h1->SetFillStyle(3005);
//h1->SetFillColor(kBlack);
h2->SetLineColor(2);
h3->SetLineWidth(3);
h3->SetLineColor(4);
h3->SetMarkerStyle(23);
h3->SetMarkerColor(4);
h3->SetMarkerSize(1);
//h2->SetMarkerStyle(28);
//h3->SetLineStyle(2);
h1->Draw();
//c1->cd(2);
h2->Draw("same");
h3->Draw("PL,same");
auto legend =new TLegend(0.65,0.8,0.85,0.6);
legend->SetLineWidth(0);
legend->AddEntry(h1,"Li Range");
legend->AddEntry(h2,"Alpha Range");
legend->AddEntry(h3,"e Range");
legend->Draw();
cout<<"Li="<<NbLi<<" al="<<Nbal<<" NbE="<<NbE<<endl;
c1->SaveAs("Ch.jpg");
}

int range2(){
TFile *f=new TFile("NochB.root");
TTree *t1=(TTree*)f->Get("t");
processing(t1);
//f->Close();
return 0;
}
