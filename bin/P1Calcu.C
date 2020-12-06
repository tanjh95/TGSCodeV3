#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include "TRandom3.h"
///参数设置
///////几何参数
double MCPL=0.6;//mm
double ChanD=6;//um
double Wallthickness=2; //um
double ChanS=ChanD+Wallthickness;//um
double Angle=12.0;//deg
//材料参数
char str='B';
double moleRatio=0.1;
double abun=0.96;//mole浓度 丰度(若是掺钆则与丰度无关)


///
const double pi= 3.14159;
void NeutronSource(double *pos){ //对入射源位置抽样，边界为六边形，边长为孔径，输入孔间距，返回x，y值是个数组 
    double x=0,y=0;
  bool flag=1;
  do{
    double ag=2*pi*gRandom->Uniform(0,1);
    double r=ChanS*gRandom->Uniform(0,1);
    x=r*cos(ag);
    y=r*sin(ag);
    if(y<sqrt(3)*ChanS/2&&y>0){
        if (x<(ChanS-sqrt(3)*y/3)&&x>(sqrt(3)*y/3-ChanS)){//舍选法抽样
            flag=0;
          pos[0]=x;
          pos[1]=y;
        }
      }
      if(y<0&&y>-ChanS*sqrt(3)/2){
        if(x<(sqrt(3)*y/3+ChanS)&&x>(-ChanS-sqrt(3)*y/3)){
            flag=0;
          pos[0]=x;
          pos[1]=y;
        }
      }
    }while(flag);
    flag=1;
//return pos;
} 

int ThroughChannel(double x,double y,double xx,double yy){  //判断是否有穿过孔 输入入射源坐标，通道中心坐标 返回1或0
double Li=2*sqrt(ChanD*ChanD/4-(y-yy)*(y-yy));
double xmax=xx+MCPL*1000*tan(Angle*pi/180)/2+Li/2/cos(Angle*pi/180);
double xmin=xx-MCPL*1000*tan(Angle*pi/180)/2-Li/2/cos(Angle*pi/180);//um
double ymax=yy+ChanD/2;
double ymin=yy-ChanD/2;
//cout<<xmin<<"  "<<xmax<<endl;
int flag=0;//0为不相交 1为相交
if ((x-xmax)*(x-xmin)<0&&(y-ymax)*(y-ymin)<0){
    flag=1;
}
else{
  flag=0;
}
   return  flag;
}
double ThroughLength(double x,double y,double xx, double yy){ //若穿透，计算穿透长度  输入入射源坐标，通道中心坐标 返回长度值
//可能有问题，，主要是算法问题
    double length=0;
    double Li=2*sqrt(ChanD*ChanD/4-(y-yy)*(y-yy));
    double xmax=xx+MCPL*1000*tan(Angle*pi/180)/2+Li/2/cos(Angle*pi/180); 
    double xmin=xx-MCPL*1000*tan(Angle*pi/180)/2-Li/2/cos(Angle*pi/180);
    double xr1=xx+MCPL*1000*tan(Angle*pi/180)/2-Li/2/cos(Angle*pi/180);
    double xr2=xx-MCPL*1000*tan(Angle*pi/180)/2+Li/2/cos(Angle*pi/180);
   // cout<<(xr1+xmax)/2<<"  "<<(xr2+xmin)/2<<endl;
  //  cout<<"xmax="<<xmax<<" xmin="<<xmin<<" xr1="<<xr1<<" xr2="<<xr2<<" Li="<<Li<<endl;

   if (xr1>xr2){
     if (x>xr2&&x<xr1){
       length=Li/sin(Angle*pi/180);
        //cout<<"111"<<endl;
     }
     if(x>xr1&&x<xmax){
        length=(xmax-x)/tan(Angle*pi/180);
        //cout<<"222"<<endl;
     }
    if(x>xmin&&x<xr2){
        length=(x-xmin)/tan(Angle*pi/180);
      //  cout<<"333"<<endl;
    }
   }
   if(xr2>xr1){
      if(x>xr1&&x<xr2){
          length=MCPL*1000;
        //  cout<<"444"<<endl;
      }
      if(x>xr2&&x<xmax){
          length=(xmax-x)/tan(Angle*pi/180);
          //cout<<"555"<<endl;
      }
      if(x>xmin&&x<xr1){
          length=(x-xmin)/tan(Angle*pi/180);
          //cout<<"666"<<endl;
      }
   }
   return length;//um
    
    }
double EffectLength(double x,double y){ ////有效长度计算输入中子MCP厚度，在空中穿行长度。
//构建通道19个  通道数目可能不够，要再加一倍--61个 20 21 20
double SourceX[41]={0};
double SourceY[3]={0};
for (int i=0;i<41;i++){
  SourceX[i]=-ChanS*10+i*ChanS/2;
  //cout<<SourceX[i]<<" x "<<endl;
}
SourceY[0]=sqrt(3)/2*ChanS;
SourceY[1]=0;
SourceY[2]=-sqrt(3)/2*ChanS;
double ChanPos[61][2]={0};
for (int j=0;j<61;j++){
  if(j<20){
    ChanPos[j][0]=SourceX[j*2+1];
    ChanPos[j][1]=SourceY[0];//第一行
      }
  if(j>=20&&j<41){
    ChanPos[j][0]=SourceX[(j-20)*2];
    ChanPos[j][1]=SourceY[1];//第二行
  }
  if(j>=41&&j<61){
    ChanPos[j][0]=SourceX[(j-41)*2+1];
    ChanPos[j][1]=SourceY[2];//第三行
  }
}
//TH2F *h2=new TH2F(" "," ",200,-100,100,400,-200,200);
///判断入射粒子与19个通道是否有交集，有的话计算有效路径
double Length=0,SumLength=0;
for(int k=0;k<61;k++){
  //for(int k=9;k<10;k++){
  //h2->Fill(ChanPos[k][0],ChanPos[k][1]);
if (ThroughChannel(x,y,ChanPos[k][0],ChanPos[k][1])){
    Length=ThroughLength(x,y,ChanPos[k][0],ChanPos[k][1]);//um
   // cout<<Length<<"=Length"<<endl;
 //   cout<<"121"<<endl;
}
else{
    Length=0;
  //  cout<<"122"<<endl;
}
//cout<<Length<<" =length"<<endl;
  SumLength=Length+SumLength;
}
//h2->Draw();
double FinalLength=MCPL*1000-SumLength;
return FinalLength/10000.0; //cm
}



////////确定N
//全局
double BCrossSection=3.95e-21;//纯硼10 // 3.84e-21  --3.96e-21
double GdCrossSection=4.6e-20;//天然钆
double Mole2Mass(double MoleRatio,double abun,char str){ //摩尔占比到质量占比 返回质量占比  //B或Gd
  double MPbO=(207+16);
	double MBiO=(209+16*3);
	double MNaO=23*2+16*3;
	double MCsO=133*2+16;
	double MBaO=137+16;
	double MTiO=204+16*2;//TiO2的摩尔质量
	double MAlO=27*2+16*3;//Al2O3的摩尔质量
	double MSiO=28+16*2;//SiO2的摩尔质量
	double B11O=70,B10O=68;//B11和B10氧化物的摩尔质量
	double MBO=B11O*(1-abun)+B10O*abun;//指定富集度下B2O3的摩尔质量
	double MGdO=16*3+2*(152*0.002+154*0.0218+155*0.148+156*0.2047+157*0.1565+158*0.2484+160*0.2186);
    double MassRatio=0;
    if(str=='B'){
         MassRatio=MBO*MoleRatio/(MBO*MoleRatio+(MPbO*0.5+MBiO*0.5)*0.175+(MNaO*0.33+MCsO*0.33+MBaO*0.34)*0.065+MTiO*0.03+MAlO*0.015+MSiO*(0.715-MoleRatio));
   //      cout<<"B"<<endl;
      // cout<<MassRatio<<endl;
        }
    if (str=='G'){
         MassRatio=MGdO*MoleRatio/(MGdO*MoleRatio+MSiO*(0.68-MoleRatio)+MPbO*0.1025+MBiO*0.1025+MNaO*0.023+MCsO*0.023+MBaO*0.024+MTiO*0.03+MAlO*0.015);
   //      cout<<"Gd"<<endl;
         }
    return MassRatio;
}
double MassInVolume(double MassRatio,double density){ //质量占比到单位体积质量数，输入质量占比、密度，返回单位体积质量数
    double MassVolume=0;
    MassVolume=MassRatio*density;
    return MassVolume;
}
double atomsInVolume(double MassVolume ,double moleMass){ //单位体积质量数到单位体积原子数,输入单位体积质量，摩尔质量，返回单位体积原子数
        double atomInVolume=0;
        atomInVolume=MassVolume/moleMass*6.02e23*2;//*2是B或Gd原子的个数
      // cout<<MassVolume<<"==MassVolume"<<endl;
    return atomInVolume;
}
////确定截面

double MacroCrossSection(double moleRatio, double abun , char str){ ////宏观截面计算

double B11O=70,B10O=68;//B11和B10氧化物的摩尔质量
double MBO=B11O*(1-abun)+B10O*abun;//指定富集度下B2O3的摩尔质量
double MGdO=16*3+2*(152*0.002+154*0.0218+155*0.148+156*0.2047+157*0.1565+158*0.2484+160*0.2186);
double MassRatio=0,MassVolume=0,atomVolume=0;
double MacroCrossSection=0;
if (str=='B'){
 MassRatio=Mole2Mass(moleRatio,abun,'B');
 MassVolume=MassInVolume(MassRatio,3.72);
 atomVolume=atomsInVolume(MassVolume,MBO);
 MacroCrossSection=atomVolume*abun*BCrossSection;
// cout<<"atomVolume="<<atomVolume*0.96<<endl;
 //cout<<"B"<<endl;
}
if(str=='G'){
 MassRatio=Mole2Mass(moleRatio,abun,'G');
 MassVolume=MassInVolume(MassRatio,4.29);
 atomVolume=atomsInVolume(MassVolume,MGdO);
 MacroCrossSection=atomVolume*GdCrossSection;
 //cout<<"Gd"<<endl;
}
//cout<<MassRatio<<" "<<MassVolume<<" "<<atomVolume<<endl;
return MacroCrossSection;
}



double EffiCalcu(double MacroCrossSection,double EffectLengthFinal){
    double Eff=0;
    Eff=1-exp(-MacroCrossSection*EffectLengthFinal);
    return Eff;
}

int P1Calcu(){
bool SF=1;
FILE *fp;
if(SF){
fp=fopen("P1th.txt","a");
}
double CrossSection=MacroCrossSection(moleRatio,abun,'B');//宏观截面
double Pos[2]={0};
double Eff=0,flag2=0,sumNb=0;
//TH2F *h2=new TH2F(" "," ",100,-50,50,100,-50,50);
for(int i=0;i<10000;i++){
//入射源测试
NeutronSource(Pos);
//cout<<Pos[0]<<" "<<Pos[1]<<endl;
//h2->Fill(Pos[0],Pos[1]);
//cout<<Pos[0]<<" "<<Pos[1]<<endl;
//double Length=EffectLength(0,0);//cm //中子入射位置
double Length=EffectLength(Pos[0],Pos[1]);//cm //中子入射位置
Eff=EffiCalcu(CrossSection,Length);//cm
//cout<<CrossSection<<"  "<<Length<<endl;
//cout<<Eff<<"=Eff"<<endl;
flag2=gRandom->Uniform(0,1);
if(flag2<Eff){sumNb++;}
}
//h2->Draw();
cout<<"Eff="<<sumNb/10000.0<<endl;
if(SF){
fprintf(fp,"%f\n",sumNb/10000.0);
fclose(fp);
}
//cout<<Length<<" length "<<endl;
return 0;
}

/*入射源测试
TH2F *h2=new TH2F(" "," ",100,-20,20,100,-20,20);
for(int i=0;i<10000;i++){
NeutronSource(Pos);
//cout<<Pos[0]<<" "<<Pos[1]<<endl;
h2->Fill(Pos[0],Pos[1]);
}
h2->Draw();
*/