#!/bin/sh
# Our custom function
merge_func(){
  echo "Merging in parallel: at file $1"
 # sleep $1
  ./gebmerge_lcrc.sh $1
  echo "Done with file $1"
}
# For loop 5 times
#count=0
for i in {180..189}
do
	merge_func $i & # Put a function in the background
#	(( count++ ))
#	if (( count = 10 )); then
#	    wait
#	    count=0
#	fi
done
 
## Put all cust_func in the background and bash 
## would wait until those are completed 
## before displaying all done message
wait 
echo "All done"
