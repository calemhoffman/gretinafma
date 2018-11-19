#!/bin/sh

echo "GEBSorting in parallel"
# For loop 5 times
count=0
for i in {200..209}
do
    ./gebsort_lcrc.sh $i & # Put a function in the background
    (( count++ ))
    if (( count = 2 )); then
        wait
    	count=0
    fi
done
wait 
echo "GEBSort all done"
