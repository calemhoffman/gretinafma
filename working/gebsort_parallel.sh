#!/bin/sh
count=0
echo "GEBSorting in parallel"

sort_func(){
    sleep 1
    echo "Working File $1"
    ./gebsort_lcrc.sh $i &
    wait
    echo "Done with File $1"
}

# For loop
for i in {70..300}
do
    sort_func $i & #
    count=$((count+1))
    echo "Counter status: $count"
    if [ $count -eq 35 ]; then
	#echo "inside"
        wait
    	count=0
    fi
done
wait 
echo "GEBSort all done"
