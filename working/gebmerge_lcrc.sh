#!/bin/sh

if [ $# -ne 1 ] 
  then
   echo "Specify only the run number to sort"
  exit 1
fi

RUN=$1

echo "GEBMerge started at `date`"

../GEBSort/GEBMerge GEBMerge.chat /lcrc/project/HELIOS/gretinafma/merged_data/GEBMerged_run$RUN.gtd /lcrc/project/HELIOS/gretinafma/data/Run00$RUN/Global.dat  2> LOG_FILES/GEBMerge_run$RUN.log

echo "GEBMerge DONE at `date`"

exit


