#!/bin/bash
cmd=/Users/calemhoffman/Research/anl/gretinafma/git/gretinafma/analysis/newAD/tools/num_to_letter


run=1; x=$($cmd $run);


GammaE=1190
aligment=2.1

J1=8
J2=6


# counts measured under total projection.
#-------------------------------------------------------
(
cat<<EOF
 Gamma-ray energy = ${GammaE}
 Theta    Yexp    Yerr
 -----------------------
90.000000 4169.592 89.318 1
113.000000 4819.835 96.849
127.000000 5393.381 110.585
138.000000 5836.010 146.749
154.000000 6345.529 119.605
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
