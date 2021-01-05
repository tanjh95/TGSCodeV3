#!/bin/bash

##控制MCP的厚度，孔径间距，倾角
tgshome=/home/tan/g4work/sg410mt/TGSCodeV4
bin=/home/tan/g4work/sg410mt/TGSCodeV4/bin
src=/home/tan/g4work/sg410mt/TGSCodeV4/src
inc=/home/tan/g4work/sg410mt/TGSCodeV4/inc
ChangePosition(){ ## barrel move，接收参数1 横向移动 参数2 纵向移动 单位mm
cd $src
sed -i "59c   	par.xBarrel=$1*mm;//changed by sh" sg4Detector.cc  
sed -i "69c		par.yBarrel=$2*mm;//changed by sh" sg4Detector.cc
}

ChangeRotation(){  ##更改倾角 degree
cd $src
sed -i "63c   par.Degree=$1;//changed by sh" sg4Detector.cc
}

ChangeSourcePos(){  ## 2 parameters x=$1 z=$2 *mm
cd $tgshome
sed -i "42c xInitPrimary $1 #changed by sh"  input.txt
sed -i "43c yInitPrimary $2 #changed by sh"  input.txt
sed -i "44c zInitPrimary $3 #changed by sh"  input.txt
./angleCal  $1 $2 $3 ##argc argv读取，换算后输出两个数存入文件angledata.temp
RotY=($(awk '{print $1}' angledata.temp)) ##第一行旋转角度
Theta=($(awk '{print $2}' angledata.temp)) ##第二行发散角度
#echo "Rot="$RotY "Theta="$Theta 
echo $Theta ##发散角 
ChangeSourceRot $RotY $Theta $RotX
}

ChangeSourceRot(){ ##e
cd $tgshome
sed -i "53c DirectRotY $1 #changed by sh" input.txt
sed -i "57c RangeThetaPri $2 #changed by sh" input.txt
sed -i "52c DirectRotX $3 #changed by sh" input.txt

}

ApplyRunTr(){ ## 接收参数:1.横移 2.纵移 3.旋转
cd $tgshome
sed -i "47c xRangePrimary -3 #changed by sh" input.txt
#sed -i "57c RangeThetaPri 0 #changed by sh" input.txt
sed -i "52c DirectRotX  0  #changed by sh" input.txt
sed -i "53c DirectRotY  0  #changed by sh" input.txt
sed -i "54c DirectRotZ  0  #changed by sh" input.txt
. build.sh
if [ $? != 0 ]
then
echo "build error"
echo "script exit"
else
echo "Run Start"
./TGS run.mac  && hadd ~/g4data/"Tr"$1"_"$2"_"$3".root"  test_t*.root # Transmision
echo "Tr"$1"_"$2"_"$3".root"

fi
}

ApplyRunEm(){ ## 接收参数:1.横移 2.纵移 3.旋转 4.voxel nub which have source
cd $tgshome
sed -i "47c xRangePrimary 0 #changed by sh" input.txt
#sed -i "57c RangeThetaPri 180 #changed by sh" input.txt
. build.sh
if [ $? != 0 ]
then
echo "build error"
echo "script exit"
else
echo "Run Start"
./TGS run.mac && hadd ~/g4data/"Em"$1"_"$2"_"$3"_"$4".root"  test_t*.root
echo "Em"$1"_"$2"_"$3"_"$4".root"

fi
}

###主程序开始
###############各体素中心y坐标
echo "输入模式 1:transmission 2:emmision"
read modNb
case $modNb in
##Transmission
1)
 cd  $tgshome
 sed -i "42c xInitPrimary 0  #changed by sh" input.txt
 sed -i "43c yInitPrimary 0 #changed by sh"  input.txt
 sed -i "44c zInitPrimary -100  #changed by sh" input.txt

 for loop2 in 50 #0 -50 #横移
  do 
   for loop in  0 #45 90 135 #旋转
   do
	for loop3 in 50 #0 -50 #纵移
		do
  ChangePosition $loop2 $loop3
  ChangeRotation $loop
#ApplyRunTr $loop3 $loop2 $loop
  done
  done
	done
;;
2)
###Emmision
  for loop2 in -50 0  50  #横移
    do 
    for loop in  0 45 90 135   #旋转
      do
		for loop3 in 0 #-50 0 50 #纵移
			do
	Y1=`echo "$loop3" |awk '{printf("%g",-50+$1)}'`
##第一层
	Y2=$loop3    ##第二层
	Y3=`echo "$loop3" |awk '{printf("%g",50+$1)}'` ##第三层

        ChangePosition  $loop2  $loop3
        ChangeRotation  $loop
###source1(1)
	X1=`echo "$loop $loop2" |awk '{printf("%g",-50*sqrt(2)*sin((45-$1)*3.1415926/180)+$2)}'` #first point
	Z1=`echo "$loop" |awk '{printf("%g",50*sqrt(2)*cos((45-$1)*3.1415926/180))}'`
###source2(N2)
	X2=`echo "$loop $loop2" |awk '{printf("%g",50*sin(1*$1*3.1415926/180)+$2)}'`
	Z2=`echo "$loop" |awk '{printf("%g",50*cos(1*$1*3.1415926/180))}'`
##soruce3
	X3=`echo "$loop $loop2" |awk '{printf("%g",50*sqrt(2)*cos((45-$1)*3.1415926/180)+$2)}'` #first point
	Z3=`echo "$loop" |awk '{printf("%g",50*sqrt(2)*cos((45+$1)*3.1415926/180))}'`
###source1(4)
	X4=`echo "$loop $loop2" |awk '{printf("%g",-50*cos($1*3.1415926/180)+$2)}'` #first point
	Z4=`echo "$loop" |awk '{printf("%g",50*sin($1*3.1415926/180))}'`
###source1(5)
	X5=`echo "$loop2" |awk '{printf("%g",$1)}'` #first point
	Z5=`echo "$loop" |awk '{printf("%g",0)}'`
###source1(6)
	X6=`echo "$loop $loop2" |awk '{printf("%g",50*cos($1*3.1415926/180)+$2)}'` #first point
	Z6=`echo "$loop" |awk '{printf("%g",-50*sin($1*3.1415926/180))}'`
##soruce7
	X7=`echo "$loop $loop2" |awk '{printf("%g",-50*sqrt(2)*cos((45-$1)*3.1415926/180)+$2)}'` #first point
	Z7=`echo "$loop" |awk '{printf("%g",-50*sqrt(2)*cos((45+$1)*3.1415926/180))}'`
###source8
	X8=`echo "$loop $loop2" |awk '{printf("%g",-50*sin(1*$1*3.1415926/180)+$2)}'`
	Z8=`echo "$loop" |awk '{printf("%g",-50*cos(1*$1*3.1415926/180))}'`
###source9
	X9=`echo "$loop $loop2" |awk '{printf("%g",50*sqrt(2)*sin((45-$1)*3.1415926/180)+$2)}'` #first point
	Z9=`echo "$loop" |awk '{printf("%g",-50*sqrt(2)*cos((45-$1)*3.1415926/180))}'`


ChangeSourcePos $X8 $Y2 $Z8  ##示例是 体素
#ApplyRunEm  $loop2  $loop  $loop3  17
        done 
	done
  done
;;
3)

###Efficiency


    for loop in 45 #0  45  90 135  ##旋转角
      do
	for loop2 in 0  #-50  0 50  ## 横移
	 do
	for loop3 in -50 #0 50  ##纵向移动
		do
        ChangePosition $loop2 $loop3
        ChangeRotation  $loop
	Y1=`echo "$loop3" |awk '{printf("%g",-50+$1)}'`
##第一层
	Y2=$loop3    ##第二层
	Y3=`echo "$loop3" |awk '{printf("%g",50+$1)}'` ##第三层

###source1(1)
	X1=`echo "$loop $loop2" |awk '{printf("%g",-50*sqrt(2)*sin((45-$1)*3.1415926/180)+$2)}'` #first point
	Z1=`echo "$loop" |awk '{printf("%g",50*sqrt(2)*cos((45-$1)*3.1415926/180))}'`
	ChangeSourcePos $X1 $Y1 $Z1

#  ApplyRunEm  $loop2  $loop3 $loop 1 
###source2(N2)
	X2=`echo "$loop $loop2" |awk '{printf("%g",50*sin(1*$1*3.1415926/180)+$2)}'`
	Z2=`echo "$loop" |awk '{printf("%g",50*cos(1*$1*3.1415926/180))}'`
	ChangeSourcePos $X2 $Y1 $Z2

#  ApplyRunEm  $loop2  $loop3 $loop 2 

##soruce3
	X3=`echo "$loop $loop2" |awk '{printf("%g",50*sqrt(2)*cos((45-$1)*3.1415926/180)+$2)}'` #first point
	Z3=`echo "$loop" |awk '{printf("%g",50*sqrt(2)*cos((45+$1)*3.1415926/180))}'`
	ChangeSourcePos $X3 $Y1 $Z3
#  ApplyRunEm  $loop2  $loop3 $loop 3

###source1(4)
	X4=`echo "$loop $loop2" |awk '{printf("%g",-50*cos($1*3.1415926/180)+$2)}'` #first point
	Z4=`echo "$loop" |awk '{printf("%g",50*sin($1*3.1415926/180))}'`
	ChangeSourcePos $X4 $Y1 $Z4
#  ApplyRunEm  $loop2  $loop3 $loop 4 

###source1(5)
	X5=`echo "$loop2" |awk '{printf("%g",$1)}'` #first point
	Z5=`echo "$loop" |awk '{printf("%g",0)}'`
	ChangeSourcePos $X5 $Y1 $Z5
#  ApplyRunEm  $loop2  $loop3 $loop 5 

###source1(6)
	X6=`echo "$loop $loop2" |awk '{printf("%g",50*cos($1*3.1415926/180)+$2)}'` #first point
	Z6=`echo "$loop" |awk '{printf("%g",-50*sin($1*3.1415926/180))}'`
	ChangeSourcePos $X6 $Y1 $Z6
#  ApplyRunEm  $loop2  $loop3 $loop 6 

##soruce7
	X7=`echo "$loop $loop2" |awk '{printf("%g",-50*sqrt(2)*cos((45-$1)*3.1415926/180)+$2)}'` #first point
	Z7=`echo "$loop" |awk '{printf("%g",-50*sqrt(2)*cos((45+$1)*3.1415926/180))}'`
	ChangeSourcePos $X7 $Y1 $Z7
#  ApplyRunEm  $loop2  $loop3 $loop 7 


#     ApplyRunEm $loop2  $loop 7 # source point / angle degree/ measure point

###source8
	X8=`echo "$loop $loop2" |awk '{printf("%g",-50*sin(1*$1*3.1415926/180)+$2)}'`
	Z8=`echo "$loop" |awk '{printf("%g",-50*cos(1*$1*3.1415926/180))}'`
	ChangeSourcePos $X8 $Y1 $Z8
#  ApplyRunEm  $loop2  $loop3 $loop 8 


#    ApplyRunEm $loop2  $loop 8 # source point / angle degree/ measure point

###source9
	X9=`echo "$loop $loop2" |awk '{printf("%g",50*sqrt(2)*sin((45-$1)*3.1415926/180)+$2)}'` #first point
	Z9=`echo "$loop" |awk '{printf("%g",-50*sqrt(2)*cos((45-$1)*3.1415926/180))}'`
	ChangeSourcePos $X9 $Y1 $Z9
#  ApplyRunEm  $loop2  $loop3 $loop 9 

###source10
ChangeSourcePos $X1 $Y2 $Z1
#  ApplyRunEm  $loop2  $loop3 $loop 10

###source11
ChangeSourcePos $X2 $Y2 $Z2
#  ApplyRunEm  $loop2  $loop3 $loop 11

###source12
ChangeSourcePos $X3 $Y2 $Z3
#  ApplyRunEm  $loop2  $loop3 $loop 12 

###source13
ChangeSourcePos $X4 $Y2 $Z4
#  ApplyRunEm  $loop2  $loop3 $loop 13

###source14
ChangeSourcePos $X5 $Y2 $Z5
#  ApplyRunEm  $loop2  $loop3 $loop 14 

###source15
ChangeSourcePos $X6 $Y2 $Z6
#  ApplyRunEm  $loop2  $loop3 $loop 15

###source16
ChangeSourcePos $X7 $Y2 $Z7
#  ApplyRunEm  $loop2  $loop3 $loop 16

###source17
ChangeSourcePos $X8 $Y2 $Z8
#  ApplyRunEm  $loop2  $loop3 $loop 17 

###source18
ChangeSourcePos $X9 $Y2 $Z9
#  ApplyRunEm  $loop2  $loop3 $loop 18

###source19
ChangeSourcePos $X1 $Y3 $Z1
#  ApplyRunEm  $loop2  $loop3 $loop 19

###source20
ChangeSourcePos $X2 $Y3 $Z2
#  ApplyRunEm  $loop2  $loop3 $loop 20

###source21
ChangeSourcePos $X3 $Y3 $Z3
#  ApplyRunEm  $loop2  $loop3 $loop 21

###source22
ChangeSourcePos $X4 $Y3 $Z4
#  ApplyRunEm  $loop2  $loop3 $loop 22

###source23
ChangeSourcePos $X5 $Y3 $Z5
#  ApplyRunEm  $loop2  $loop3 $loop 23

###source24
ChangeSourcePos $X6 $Y3 $Z6
#  ApplyRunEm  $loop2  $loop3 $loop 24 

###source25
ChangeSourcePos $X7 $Y3 $Z7
#  ApplyRunEm  $loop2  $loop3 $loop 25 

###source26
ChangeSourcePos $X8 $Y3 $Z8
#  ApplyRunEm  $loop2  $loop3 $loop 26

###source27
ChangeSourcePos $X9 $Y3 $Z9
#  ApplyRunEm  $loop2  $loop3 $loop 27 

	done
	done
  done
;;
4)
        ChangePosition  0
        ChangeRotation  0
for loop in 0
do
	for loop2 in 0
	do
##########measure2
	X9=`echo "$loop $loop2" |awk '{printf("%g",50*sqrt(2)*sin((45-$1)*3.1415926/180)+$2)}'` #first point
	Z9=`echo "$loop" |awk '{printf("%g",-50*sqrt(2)*cos((45-$1)*3.1415926/180))}'`
	cd  $tgshome
	sed -i "42c xInitPrimary $X9  #changed by sh" input.txt
	sed -i "44c zInitPrimary $Z9  #changed by sh" input.txt




done
done
;;
esac
cd $bin
