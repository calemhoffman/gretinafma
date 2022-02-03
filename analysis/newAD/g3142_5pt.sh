#!/bin/bash
cmd=/Users/calemhoffman/Research/anl/gretinafma/git/gretinafma/analysis/newAD/tools/num_to_letter


run=1; x=$($cmd $run);


GammaE=3142
aligment=1.5

J1=7
J2=5


# counts measured under total projection.
#-------------------------------------------------------
(
cat<<EOF
 Gamma-ray energy = ${GammaE}
 Theta    Yexp    Yerr
 -----------------------
 90.000000 3342.980 66.615
 113.000000 3581.554 72.939
 127.000000 3938.061 82.277
 138.000000 4310.567 114.376
 154.000000 4884.455 96.741


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


xterm -fg black -bg white -fa  faceSize4 -e /Users/calemhoffman/Research/anl/gretinafma/git/gretinafma/analysis/newAD/AD_code/ad