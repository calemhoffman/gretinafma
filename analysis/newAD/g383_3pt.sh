#!/bin/bash
cmd=tools/num_to_letter

run=1; x=$($cmd $run);


GammaE=383
aligment=1.8

J1=5
J2=3

# counts measured under total projection.
#-------------------------------------------------------
(
cat<<EOF
 Gamma-ray energy = ${GammaE}
 Theta    Yexp    Yerr
 -----------------------
90.0 222 22
119.0 159 16
149.0 166 22

EOF
) > ${GammaE}${x}.0

if [ -e "ad_input.txt" ]; then rm ad_input.txt; fi
if [ -e "fort.3" ]; then rm fort.3; fi
if [ -e "fort.4" ]; then rm fort.4; fi

#--------------------------------------( check detector Det. dimension )
(
	cat<<EOF
5,25,10       !detector dimension.
${GammaE}         !energy of gamma ray.
${GammaE}${x}.0   !the filename of the angular distribution.
${aligment},0     !aligment, and feeding.
${J1}
${J2}
EOF
)>>ad_input.txt


xterm -fg black -bg white -fa  faceSize4 -e AD_code/ad &
