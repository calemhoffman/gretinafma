#!/bin/sh

if [ $# -ne 1 ] 
  then
   echo "Specify only the run number to sort"
  exit 1
fi

RUN=$1

echo "sorting run $RUN"
./gebmerge_local.sh $RUN 
./gebsort_local.sh $RUN

#exit
