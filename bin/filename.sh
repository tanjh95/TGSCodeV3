#!/bin/bash

for name in `ls *.root`
do
name2=${name:0:7}
name5=${name:10:9}
name6=${name:9:1}
name3=${name2/B/B8_}
name4=${name3%_*}
mv $name $name2$name6$name5  
#mv $name $name4"_"$name5

done
