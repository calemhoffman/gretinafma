set term post enhance color "Helvetica,16"
set out "|ps2pdf - gamScan.pdf"

set xlabel 'e3'
set ylabel 'e1'


set title '670 + 1823 + 2168 keV'

plot [0:3500][1:1e5] 'scan_fits_ar38.dat' u 8:2 w points notit,\
                    '' u 9:2 w points notit

set title '670 keV'
plot [0:3500][0:3500] 'scan_fits_ar38.dat' u 8:($2>1e2 ? $9:1/0) every :::0::0 w points notit,\
                      '' u 8:($2>5e2 ? $9:1/0) every :::0::0 w points notit,\
                      '' u 8:($2>1e3 ? $9:1/0) every :::0::0 w points notit,\
                      '' u 8:($2>5e3 ? $9:1/0) every :::0::0 w points notit,\
                      '' u 8:($2>1e4 ? $9:1/0) every :::0::0 w points notit
set title '1823 keV'

plot [0:3500][0:3500] 'scan_fits_ar38.dat' u 8:($2>1e2 ? $9:1/0) every :::1::1 w points notit,\
                      '' u 8:($2>5e2 ? $9:1/0) every :::1::1 w points notit,\
                      '' u 8:($2>1e3 ? $9:1/0) every :::1::1 w points notit,\
                      '' u 8:($2>5e3 ? $9:1/0) every :::1::1 w points notit,\
                      '' u 8:($2>1e4 ? $9:1/0) every :::1::1 w points notit

set title '2168 keV'

plot [0:3500][0:3500] 'scan_fits_ar38.dat' u 8:($2>1e2 ? $9:1/0) every :::2::2 w points notit,\
                      '' u 8:($2>5e2 ? $9:1/0) every :::2::2 w points notit,\
                      '' u 8:($2>1e3 ? $9:1/0) every :::2::2 w points notit,\
                      '' u 8:($2>5e3 ? $9:1/0) every :::2::2 w points notit,\
                      '' u 8:($2>1e4 ? $9:1/0) every :::2::2 w points notit



set title '292 + 1133 + 2044 keV'

plot [0:3500][1:1e5] 'scan_fits.dat' u 8:2 w points notit,\
                    '' u 9:2 w points notit

set title '292 keV'
plot [0:3500][0:3500] 'scan_fits.dat' u 8:($2>1e1 ? ($6 > 0 ? ($4<294 ? ($4>290 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit,\
                      '' u 8:($2>1e2 ? ($6 > 0 ? ($4<294 ? ($4>290 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit,\
                      '' u 8:($2>5e2 ? ($6 > 0 ? ($4<294 ? ($4>290 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit,\
                      '' u 8:($2>1e3 ? ($6 > 0 ? ($4<294 ? ($4>290 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit
set title '2044 keV'
plot [0:3500][0:3500] 'scan_fits.dat' u 8:($2>1e1 ? ($6 > 0 ? ($4<2046 ? ($4>2042 ? $9:1/0):1/0):1/0):1/0) every :::1::1 w points notit,\
                      '' u 8:($2>5e1 ? ($6 > 0 ? ($4<2046 ? ($4>2042 ? $9:1/0):1/0):1/0):1/0) every :::1::1 w points notit,\
                      '' u 8:($2>1e2 ? ($6 > 0 ? ($4<2046 ? ($4>2042 ? $9:1/0):1/0):1/0):1/0) every :::1::1 w points notit,\
                      '' u 8:($2>5e2 ? ($6 > 0 ? ($4<2046 ? ($4>2042 ? $9:1/0):1/0):1/0):1/0) every :::1::1 w points notit

set title '1133 keV'
plot [0:3500][0:3500] 'scan_fits.dat' u 8:($2>1e1 ? ($6 > 0 ? ($4<1137 ? ($4>1129 ? $9:1/0):1/0):1/0):1/0) every :::2::2 w points notit,\
                      '' u 8:($2>5e1 ? ($6 > 0 ? ($4<1137 ? ($4>1129 ? $9:1/0):1/0):1/0):1/0) every :::2::2 w points notit,\
                      '' u 8:($2>1e2 ? ($6 > 0 ? ($4<1137 ? ($4>1129 ? $9:1/0):1/0):1/0):1/0) every :::2::2 w points notit,\
                      '' u 8:($2>5e2 ? ($6 > 0 ? ($4<1137 ? ($4>1129 ? $9:1/0):1/0):1/0):1/0) every :::2::2 w points notit

set pointsize 1
set title '292+670 keV'
plot [0:3500][0:3500] 'scan_fits_ar38.dat' u ($8):($2>1e2 ? ($6 > 0 ? ($4<674 ? ($4>666 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit,\
                      'scan_fits.dat' u ($8):($2>1e1 ? ($6 > 0 ? ($4<294 ? ($4>290 ? $9:1/0):1/0):1/0):1/0) every :::0::0 w points notit


set title '1292 keV'
plot [0:3500][0:3500] 'scan_fits.dat' u 8:($2>0 ? ($6 > 0 ? ($4<1305 ? ($4>1280 ? $9:1/0):1/0):1/0):1/0) every :::3::3 w points notit
