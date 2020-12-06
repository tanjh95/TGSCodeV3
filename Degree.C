#include<stdio.h>
#include<iostream>
#include<math.h>
#include<fstream>

double rmcp=0.25;
double d=0.0,degree=0.0;

const double pi=3.1415;
int Degree()
{
ofstream outfile("degree.txt");
for (int i=0;i<10;i++)
 {
d=d+2;
degree=atan(rmcp/d)*180/pi;//unit must be degree;2mm per movement;
 outfile<<d<<"*mm\t"<<degree<<"*degree\t"<<100*d<<"*mm"<<endl;
 }
return 0;
}
