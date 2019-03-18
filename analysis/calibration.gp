set term post enhance color "Helvetica,22"
set out "|ps2pdf - cal.pdf"

set title ""
set ylabel "scale factor"
set xlabel "run number"
xmin = 0
xmax = 350
set title 'xpos offset'

plot [xmin:xmax][0:400] 'fma_xcal.dat' u 1:2 w points tit 'x-offset'


set title 'slope'
plot [xmin:xmax][0.5:2.5] 'fma_ecal.dat' u 1:4 every 3::0 w points tit 'signal e1',\
                          'fma_ecal.dat' u 1:4 every 3::1 w points tit 'signal e2'

set title "offset"
plot [xmin:xmax][-100:2500] 'fma_ecal.dat' u 1:5 every 3::0 w points tit 'signal e1',\
                           'fma_ecal.dat' u 1:5 every 3::1 w points tit 'signal e2'


set title "Xoffset"
plot [xmin:xmax][-100:2500] 'fma_ecal.dat' u 1:3 every 3::0 w points tit 'signal e1',\
                           'fma_ecal.dat' u 1:3 every 3::1 w points tit 'signal e2',\
                           'fma_ecal.dat' u 1:3 every 3::2 w points tit 'signal e3'


set title "Xoffset-offset"
plot [xmin:xmax][-150:200] 'fma_ecal.dat' u 1:($5-$3) every 3::0 w points tit 'signal e1',\
                           'fma_ecal.dat' u 1:($5-$3) every 3::1 w points tit 'signal e2',\
                           'fma_ecal.dat' u 1:3 every 3::2 w points tit 'signal e3'
