#include <fstream>
#include <stdio.h>
#include <iostream>

int draw(){
int s=11,bin=1;

double x[s];
double y1[s];
double y2[s];
double y3[s];

ifstream infile("Edepdata.txt");

for (int i=0;i<s;i++){
	x[i]=i+10;
}

for (int j=0;j<3*s;j++){
	if (j<s)	infile>>y1[j];
	if (j<2*s&&j>=s) infile>>y2[j-s];
	if (j<3*s&&j>=2*s) infile>>y3[j-2*s];

}
//cout<<y2[1]<<endl;

TGraph *h1=new TGraph(s,x,y1);
TGraph *h2=new TGraph(s,x,y2);
TGraph *h3=new TGraph(s,x,y3);
TCanvas *c1=new TCanvas("c1","Eff vs consistence",200,10,700,500);
c1->cd(1);
h1->GetXaxis()->SetTitle("Consistence(mole%)");
h1->GetYaxis()->SetTitle("Eff(%)");
h1->GetXaxis()->SetRangeUser(9,21);
h1->GetYaxis()->SetRangeUser(0,600);
h1->SetLineWidth(2);
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


h2->SetLineWidth(2);
h2->SetLineColor(2);
h3->SetLineWidth(2);
h3->SetLineColor(4);
h1->SetMarkerStyle(21);
h1->Draw("APL");
h2->SetMarkerStyle(20);
h2->SetMarkerColor(2);
h2->Draw("PL");
h3->SetMarkerColor(4);
h3->Draw("*L");

auto legend=new TLegend(0.6,0.3,0.9,0.1);//x1,y1,x2,y2坐标在图中的比例,
legend->SetLineWidth(0);
legend->AddEntry(h1,"0.4mm","lp");//TLegend::AddEntry()第三个参数：l（画出线的特征）；p（画出marker的特征）；f（填充满整个背景）；e（与l一起使用可以画出误差特征）
legend->AddEntry(h2,"0.6mm","lp");
legend->AddEntry(h3,"0.8mm","lp");
legend->Draw();



//c1->SaveAs("20enrich.png");




infile.close();
return 0;
}
