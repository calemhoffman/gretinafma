#!/bin/bash
cmd=../tools/num_to_letter

run=1; x=$($cmd $run); 


GammaE=2320
aligment=1.5

J1=4
J2=2


# counts measured under total projection.
#-------------------------------------------------------
(
cat<<EOF
 Gamma-ray energy = ${GammaE}
 Theta    Yexp    Yerr 
 ----------------------- 
75 34.2 10.2
95 36.9 6.8
115 31.9 5.4
135 31.3 5.8
155 25.0 7.3

EOF
) > ${GammaE}${x}.0

if [ -e "ad_input.txt" ]; then rm ad_input.txt; fi
if [ -e "fort.3" ]; then rm fort.3; fi
if [ -e "fort.4" ]; then rm fort.4; fi

#--------------------------------------( check detector Det. dimension )
(
	cat<<EOF
3.5,25,8.5        !detector dimension.
${GammaE}         !energy of gamma ray.
${GammaE}${x}.0   !the filename of the angular distribution.	
${aligment},0     !aligment, and feeding.
${J1}
${J2}
EOF
)>>ad_input.txt


xterm -fg black -bg white -fa  faceSize4 -e ../AD_code/ad &
