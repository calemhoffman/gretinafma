#!/bin/sh

if [ $# -ne 1 ] 
  then
   echo "Specify only the run number to sort"
  exit 1
fi

RUN=$1

echo "GEBSort started sorting run $RUN at `date`"

../GEBSort/GEBSort_nogeb -input disk ../../data/GEBMerged_run$RUN.gtd_000 -rootfile ../../data/root_data/run$RUN.root RECREATE -chat GEBSort.chat > ./LOG_FILES/GEBSort_run$RUN.log

echo "GEBSort DONE at `date`"

#exit


