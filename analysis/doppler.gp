set term post enhance color "Helvetica, 18"
set out "| ps2pdf - doppler.pdf"
set pointsize 2
set key spacing 1.2
set logscale y
set ylabel offset -1.5,0,0

set title "^{38}S Doppler Determination"
set xlabel "Angle [deg]"
set ylabel "Energy [keV]"

set border 3
set tics nomirror
unset grid

beta1 = 0.06
energy1 = 1292.0
f1(x) = energy1 * sqrt((1 - beta1*beta1))/(1 - beta1*cos(x/180.0*3.14))
beta2 = 0.06
energy2 = 1292.0
f2(x) = energy2 * sqrt((1 - beta2*beta2))/(1 - beta2*cos(x/180.0*3.14))

fit [60:180] f1(x) 'doppler.dat' u ($1):($2) via beta1,energy1
fit [60:180] f2(x) 'doppler.dat' u ($1):($3) via beta2,energy2


plot [60:180][1200:1600] 'doppler.dat' u 1:2 w points tit '1292 keV',\
                         '' u 1:3 w points tit '1534 keV',\
                         f1(x) w lines tit '',\
                         f2(x) w lines tit ''
