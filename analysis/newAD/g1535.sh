#!/bin/bash
cmd=tools/num_to_letter

run=1; x=$($cmd $run);


GammaE=1535
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
 75.000000 130.686 17.792
 95.000000 151.790 12.792
 115.000000 169.050 11.562
 135.000000 190.489 12.582
 155.000000 215.176 18.024

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
