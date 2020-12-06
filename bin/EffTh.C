////注意：此程序只能计算无倾角的掺B和Gd的MCP的P1。在计算前要先计算好开度，与文献值对应好了在计算

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

double GetNbB(double a,double c,double d){ //当前条件下每立方厘米B10的量

double PbBiO=(207+16)*0.5+(209+16*3)*0.5;//PbO和BiO的平均摩尔质量
double NaCsBaO=(23*2+16*3)*0.33+(133*2+16)*0.33+(137+16)*0.34;//Na2O/Cs2O/BaO的平均摩尔质量
double TiO=204+16*2;//TiO2的摩尔质量
double AlO=27*2+16*3;//Al2O3的摩尔质量
double SiO=28+16*2;//SiO2的摩尔质量
double B11O=70,B10O=68;//B11和B10氧化物的摩尔质量
double BO=B11O*(1-a)+B10O*a;//指定富集度下B2O3的摩尔质量

double BMassRate=BO*c/(BO*c+PbBiO*0.175+NaCsBaO*0.065+TiO*0.03+AlO*0.015+SiO*(0.715-c));//B2O3的质量占比/(摩尔浓度*摩尔质量之比=质量之比)
double MassOfBO= d*BMassRate;//B2O3的质量 g
double MoleOfBO=MassOfBO/BO;//B2O3的摩尔数
double NbOfB=MoleOfBO*6.02E23*2*a;//乘2为B2O3有2个B，乘a为求B10的量。


return NbOfB;

}

double GetNbGd(double c,double d){ //当前条件下每立方厘米B10的量

double PbBiO=(207+16)*0.5+(209+16*3)*0.5;//PbO和BiO的平均摩尔质量
double NaCsBaO=(23*2+16*3)*0.33+(133*2+16)*0.33+(137+16)*0.34;//Na2O/Cs2O/BaO的平均摩尔质量
double TiO=204+16*2;//TiO2的摩尔质量
double AlO=27*2+16*3;//Al2O3的摩尔质量
double SiO=28+16*2;//SiO2的摩尔质量
double GdO=157*2+16*3;//Gd2O3的摩尔质量

double GdMassRate=GdO*c/(GdO*c+PbBiO*0.205+NaCsBaO*0.07+TiO*0.03+AlO*0.015+SiO*(0.68-c));//B2O3的质量占比/(摩尔浓度*摩尔质量之比=质量之比)
double MassOfGdO= d*GdMassRate;//B2O3的质量 g
double MoleOfGdO=MassOfGdO/GdO;//B2O3的摩尔数
double NbOfGd=MoleOfGdO*6.02E23*2;//乘2为B2O3有2个B，乘a为求B10的量。


return NbOfGd;

}

int EffTh(){
FILE *fp1=fopen("EffB20P1Th.txt","a");

for (int i=0;i<19;i++){
double concentration=0;
double abundence=0.20;//富集度
if (i<11){
	 concentration=0.03+0.005*i;//摩尔浓度
	cout<<" concentration="<<concentration<<endl;
}
else{
	concentration=0.02*i;
	cout<<" concentration="<<concentration<<endl;

}
double density=3.72;//MCP密度 g/cm3  B:3.72 Gd:4.29
double MCPL=0.06;//cm
double omegaB=3.84E-21;//B10截面 cm2
double NbOfB=GetNbB(abundence,concentration,density);
double OpenR=(250.*250.-4*4*1877.)/(250.*250.);//
double EffB=(1-exp(-MCPL*NbOfB*omegaB))*0.376;  //*OpenR=0.37638;
double omegaGd155=6.08E-20;
double omegaGd157=2.53929E-19;
//double NbOfGd=GetNbGd(concentration,density);
//double NbOfGd155=0.148*NbOfGd;//Gd155个数
//double NbOfGd157=0.1565*NbOfGd;//Gd157个数
//double NbOfGd155=0.*NbOfGd;//
//double NbOfGd157=1.0*NbOfGd;//纯Gd157
//double EffGd=(1-exp(-MCPL*(NbOfGd155*omegaGd155+NbOfGd157*omegaGd157)))*0.37638;//*OpenR;//Eff应乘MCP开度再乘内转换电子产生概率G4约0.69
//cout<<OpenR<<"=solid surface"<<endl;
cout<<EffB<<"= B "<<" Open Radio="<<OpenR<<endl;
fprintf(fp1,"%f\t",EffB);

}
fclose(fp1);
/*
///draw 理论与模拟P1结果
//实心MCP P1图像
double x[100],y[100];
TCanvas *c1=new TCanvas("c1","aa",200,10,600,400);
for (int i=0;i<100;i++){//浓度从0-20%取100个点
	x[i]=0.001*i;
	NbOfGd=GetNbGd(x[i],density);
	NbOfGd155=0.148*NbOfGd;
	NbOfGd157=0.1565*NbOfGd;
	y[i]=0.81*(1-exp(-MCPL*(NbOfGd155*omegaGd155+NbOfGd157*omegaGd157)));
//cout<<x[i]<<" "<<y[i]<<endl;

}
TGraph *g1=new TGraph (100,x,y);

double x2[5]={0.01,0.03,0.05,0.07,0.09};
double y2[5]={0.60562,0.79831,0.81432,0.8163,0.81675};
	TGraph *g2=new TGraph(5,x2,y2);
	c1->cd(1);
	g2->GetXaxis()->SetTitle("Consistence(mole%)");
	g2->GetYaxis()->SetTitle("Eff(100%)");
	g2->GetXaxis()->CenterTitle();
	g2->GetYaxis()->CenterTitle();
//h1->GetTitle()->SetTitleSize("0.04");//error 图标题怎么设置
//h1->GetTitle()->SetTitleFont(62);//error
	g2->GetXaxis()->SetLabelSize(0.04);//轴上数字大小 0.05
	g2->GetXaxis()->SetLabelFont(62);//轴上字体加粗
g2->GetXaxis()->SetTitleSize(0.04);//轴上标题大小
g2->GetXaxis()->SetTitleFont(62);//轴上标题加粗
g2->GetYaxis()->SetLabelSize(0.04);
g2->GetYaxis()->SetLabelFont(62);
g2->GetYaxis()->SetTitleSize(0.04);
g2->GetYaxis()->SetTitleFont(62);
g2->GetYaxis()->SetTitleOffset(1.1);

	g2->GetYaxis()->SetRangeUser(0,1);
	g2->SetMarkerStyle(21);
	g2->SetMarkerColor(2);
	g2->SetLineColor(2);
	g2->SetLineWidth(2);	

	auto legend=new TLegend(0.7,0.3,0.9,0.2);
	legend->SetLineWidth(0);
	legend->AddEntry(g1,"Theory","lp");
	legend->AddEntry(g2,"Simulation","lp");

	g2->Draw("ACP");
	g1->Draw("C*");
	legend->Draw();
	c1->SaveAs("GdP1.png");
*/
//	cout<<"Eff="<<EffGd<<" Effective radio="<<OpenR<<endl;
return 0;
}
