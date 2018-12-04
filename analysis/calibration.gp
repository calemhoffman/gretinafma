set term post enhance color "Helvetica,22"
set out "|ps2pdf - cal.pdf"

set title ""
set ylabel "scale factor"
set xlabel "run number"

plot [50:300][1000:3000] 'fma_fits.dat' u 1:2 every 3::0 w points tit 'signal e1 1',\
                         '' u 1:2 every 3::1 w points tit 'signal e2 1',\
                         'fma_fits.dat' u 1:6 every 3::0 w points tit 'signal e1 2',\
                         '' u 1:6 every 3::1 w points tit 'signal e2 2',\
                         'fma_fits.dat' u 1:4 every 3::2 w points tit 'signal e3 1'

plot [50:300][0.5:1.5] 'fma_fits.dat' u 1:($2/$6) every 3::0 w points tit 'signal e1 1/2',\
                       '' u 1:($2/$6) every 3::1 w points tit 'signal e2 1/2'


f(x)=a*x+b
a=1
b=1.2

fit [50:300] f(x) 'fma_fits.dat' u 1:(750/($6-$2)) every 3::0 via a,b

plot [50:300][0:2] 'fma_fits.dat' u 1:(750/($6-$2)) every 3::0 w points tit 'signal e1',\
                   f(x) w lines tit ''



fit [50:300] f(x) 'fma_fits.dat' u 1:(250/($6-$2)) every 3::1 via a,b

plot [50:300][0:2] 'fma_fits.dat' u 1:(250/($6-$2)) every 3::1 w points tit 'signal e2',\
                   f(x) w lines tit ''


f1(x)=a1*x+b1
a1=-0.1
b1=2500
f2(x)=a2*x+b2
a2=-0.1
b2=3000

fit [50:180] f1(x) 'fma_fits.dat' u 1:4 every 3::2 via a1,b1
fit [190:300] f2(x) 'fma_fits.dat' u 1:4 every 3::2 via a2,b2

plot [50:300][2000:3000] 'fma_fits.dat' u 1:4 every 3::2 w points tit 'signal e3',\
                         f1(x) w lines tit '',\
                         f2(x) w lines tit ''

plot [50:300][0.5:2.5] 'fma_cal.dat' u 1:4 every 3::0 w points tit 'signal e1',\
                       'fma_cal.dat' u 1:4 every 3::1 w points tit 'signal e2'


plot [50:300][-400:400] 'fma_cal.dat' u 1:3 every 3::2 w points tit 'signal e3'
