set term post enhance color "Helvetica,22"
set out "|ps2pdf - cal.pdf"

set title ""
set ylabel "scale factor"
set xlabel "run number"
xmin=69
xmax=299

plot [xmin:xmax][1000:3000] 'fma_fits.dat' u 1:2 every 3::0 w points tit 'signal e1 1',\
                         '' u 1:2 every 3::1 w points tit 'signal e2 1',\
                         'fma_fits.dat' u 1:6 every 3::0 w points tit 'signal e1 2',\
                         '' u 1:6 every 3::1 w points tit 'signal e2 2',\
                         'fma_fits.dat' u 1:4 every 3::2 w points tit 'signal e3 1'

plot [xmin:xmax][0.5:1.5] 'fma_fits.dat' u 1:($2/$6) every 3::0 w points tit 'signal e1 1/2',\
                       '' u 1:($2/$6) every 3::1 w points tit 'signal e2 1/2'

exit

f(x)=a*x+b
a=1
b=1.2

fit [xmin:xmax] f(x) 'fma_fits.dat' u 1:(750/($6-$2)) every 3::0 via a,b

plot [xmin:xmax][0:2] 'fma_fits.dat' u 1:(750/($6-$2)) every 3::0 w points tit 'signal e1',\
                   f(x) w lines tit ''



fit [xmin:xmax] f(x) 'fma_fits.dat' u 1:(250/($6-$2)) every 3::1 via a,b

plot [xmin:xmax][0:2] 'fma_fits.dat' u 1:(250/($6-$2)) every 3::1 w points tit 'signal e2',\
                   f(x) w lines tit ''


f1(x)=a1*x+b1
a1=-0.1
b1=2500
f2(x)=a2*x+b2
a2=-0.1
b2=3000

fit [50:180] f1(x) 'fma_fits.dat' u 1:4 every 3::2 via a1,b1
fit [190:300] f2(x) 'fma_fits.dat' u 1:4 every 3::2 via a2,b2

plot [xmin:xmax][2000:3000] 'fma_fits.dat' u 1:4 every 3::2 w points tit 'signal e3',\
                         f1(x) w lines tit '',\
                         f2(x) w lines tit ''

plot [xmin:xmax][0.5:2.5] 'fma_cal.dat' u 1:4 every 3::0 w points tit 'signal e1',\
                       'fma_cal.dat' u 1:4 every 3::1 w points tit 'signal e2'


plot [xmin:xmax][-400:400] 'fma_cal.dat' u 1:3 every 3::2 w points tit 'signal e3'
