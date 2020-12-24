#!/usr/bin/env bash
ji=$1
jf=$2
li=${jf}
lf=${jf}
sigma=1.5
echo "${sigma}"

# for (( i = -179; i < 180; i++ )); do

./bin/angcor 3 ${ji} ${li} ${lf} ${jf} 0.0 ${sigma}
  #./bin/angcor 3 3 2 2 2 ${i} 0.5
  #echo "${ji} ${li} ${lf} ${jf} ${i} ${sigma}"
# done
