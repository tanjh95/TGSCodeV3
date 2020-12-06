loop=45
val1=`echo "$loop" |awk '{printf("%g",50*cos(-1*$1*3.1415/180))}'`
val2=`echo "$loop" |awk '{printf("%g",50*sin(-1*$1*3.1415/180))}'`

echo "$val2"
