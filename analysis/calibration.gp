set term post enhance color "Helvetica,22"
set out "|ps2pdf - cal.pdf"

set title ""
set ylabel "scale factor"
set xlabel "run number"

plot [50:300][0.5:1.5] 'fma_cal.dat' u 1:3 every 3::0 w points tit 'signal e1',\
                      'fma_cal.dat' u 1:3 every 3::1 w points tit 'signal e2',\
                      'fma_cal.dat' u 1:3 every 3::2 w points tit 'signal e3'
