#!/bin/bash
cmd=tools/num_to_letter

run=1; x=$($cmd $run);


GammaE=788
aligment=1.8

J1=2
J2=4

# counts measured under total projection.
#-------------------------------------------------------
(
cat<<EOF
 Gamma-ray energy = ${GammaE}
 Theta    Yexp    Yerr
 -----------------------
90.0 42   14
119.0 33  11
149.0 32  15

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
