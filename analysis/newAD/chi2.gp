set term post enhance color "Helvetica,20" lw 1.0
set out "|ps2pdf - chi2.pdf"
set lmargin 0
set tmargin 0
set bmargin 1
set rmargin 0
set title
set xlabel "{/Symbol d}"
set ylabel "Reduced {/Symbol c}^2"
set log y
set key bottom left
set key horizontal top
set ylabel ''
set xlabel ''
set xtic offset 0,0.5
############################################## 1
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
set arr 1 from -90,2e2 to -60,2e2 nohead lt 1
set arr 2 from -15,2e2 to 15,2e2 nohead lt 2
set arr 3 from 60,2e2 to 90,2e2 nohead lt 3
set arr 4 from 135,2e2 to 165,2e2 nohead lt 4
set arr 5 from 210,2e2 to 240,2e2 nohead lt 6
set label 100 "{/Symbol D}J=-2" at -57,2e2 left
set label 101 "{/Symbol D}J=-1" at 18,2e2 left
set label 102 "{/Symbol D}J=0" at 93,2e2 left
set label 103 "{/Symbol D}J=+1" at 168,2e2 left
set label 104 "{/Symbol D}J=+2" at 243,2e2 left

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
yhigh=100.0
set format y "  10^{%T}"
set ylabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set format x "%.0f"
set label 1 '1293-keV (5pt)' at -80,50
set label 11 'J_f=0^+' at 80,50 right
set xtics
set for [i=0:9] xtics (""i*30-90)
set ytics offset 0.75,0
plot [-90:90][ylow:yhigh] 'g1293_5pt.dat' u 1:2 every ::1::181 w lines lw 5 notit,\
'' u 1:2 every ::183::363 w lines lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1535-keV (5pt)' at -80,50
set label 11 'J_f=2^+' at 80,50 right
set ytics
set for [i=-2:9] ytics add (""10**i)
unset label 3
plot [-90:90][ylow:yhigh] 'g1535_5pt.dat' u 1:2 every ::1::181 w lines lw 5 notit,\
'' u 1:2 every ::183::363 w lines lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit,\
'' u 1:2 every ::547::727 w lines lw 0.5 lt 4 notit,\
'' u 1:2 every ::729::909 w lines lw 0.5 lt 6 notit
set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
set label 1 '850-keV (5pt)' at -80,50
set label 11 'J_f=4^+' at 80,50 right
set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.035 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g850_5pt.dat' u 1:2 every ::1::181 w lines lw 5 notit,\
'' u 1:2 every ::183::363 w lines  lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines  lw 0.5 notit,\
'' u 1:2 every ::547::727 w lines  lw 0.5 lt 4 notit,\
'' u 1:2 every ::729::909 w lines  lw 0.5 lt 6 notit
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '2668-keV (5pt)' at -80,50
set label 11 'J_f=6^+' at 80,50 right
unset label 3
set xtics -90,30,90
set ytics
set for [i=-2:9] ytics add (""10**i)
plot [-90:90][ylow:yhigh] 'g2668_5pt.dat' u 1:2 every ::1::181 w lines lw 5 notit,\
'' u 1:2 every ::183::363 w lines lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit,\
'' u 1:2 every ::547::727 w lines lw 0.5 lt 4 notit,\
'' u 1:2 every ::729::909 w lines lw 0.5 lt 6 notit

unset multiplot
######################################## 2
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
set ytics 0.001,10,9e1
set arr 1 from -90,2e2 to -60,2e2 nohead lt 1
set arr 2 from -15,2e2 to 15,2e2 nohead lt 2
set arr 3 from 60,2e2 to 90,2e2 nohead lt 3
set arr 4 from 135,2e2 to 165,2e2 nohead lt 4
set arr 5 from 210,2e2 to 240,2e2 nohead lt 6
set label 100 "{/Symbol D}J=-2" at -57,2e2 left
set label 101 "{/Symbol D}J=-1" at 18,2e2 left
set label 102 "{/Symbol D}J=0" at 93,2e2 left
set label 103 "{/Symbol D}J=+1" at 168,2e2 left
set label 104 "{/Symbol D}J=+2" at 243,2e2 left

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
yhigh=100.0
set ytics
set format y "  10^{%T}"
set ylabel ""
set xlabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set format x "%.0f"
set label 1 '1609-keV (5pt)' at -80,50
set label 11 'J_f=4^+' at 80,50 right
set xtics
set for [i=-2:9] xtics (""i*30-90)
set ytics offset 0.75,0
unset label 2
plot [-90:90][ylow:yhigh] 'g1609_5pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1577-keV (5pt)' at -80,50
set label 11 'J_f=(5)' at 80,50 right
set ytics
set for [i=-2:5] ytics add (""10**i)
unset label 3
unset label 2
plot [-90:90][ylow:yhigh] 'g1577_5pt.dat' u 1:2 every ::1::181 w lines lw 5 notit,\
'' u 1:2 every ::183::363 w lines lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit
set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
set label 1 '1950-keV (3pt)' at -80,50
set label 11 'J_f=(7)' at 80,50 right
set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.035 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g1950_3pt.dat' u 1:($2*10.0) every ::1::181 w lines lw 5 notit,\
'' u 1:($2*10.0) every ::183::363 w lines  lw 0.5 notit,\
'' u 1:($2*10.0) every ::365::545 w lines  lw 0.5 notit
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1617-keV (5pt)' at -80,50
set label 11 'J_f=(8)' at 80,50 right
unset label 3
set xtics -90,30,90
set for [i=-2:9] ytics add (""10**i)
plot [-90:90][ylow:yhigh] 'g1617_5pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit

unset multiplot
################################################# 3
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
set ytics 0.001,10,9e1
set arr 1 from -90,2e2 to -60,2e2 nohead lt 1
set arr 2 from -15,2e2 to 15,2e2 nohead lt 2
set arr 3 from 60,2e2 to 90,2e2 nohead lt 3
set arr 4 from 135,2e2 to 165,2e2 nohead lt 4
set arr 5 from 210,2e2 to 240,2e2 nohead lt 6
set label 100 "{/Symbol D}J=-2" at -57,2e2 left
set label 101 "{/Symbol D}J=-1" at 18,2e2 left
set label 102 "{/Symbol D}J=0" at 93,2e2 left
set label 103 "{/Symbol D}J=+1" at 168,2e2 left
set label 104 "{/Symbol D}J=+2" at 243,2e2 left

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
yhigh=100.0
set ytics
set format y "  10^{%T}"
set ylabel ""
set xlabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set format x "%.0f"
set label 1 '2323-keV (5pt)' at -80,50
set label 11 'J_f=2^+' at 80,50 right
set xtics
set for [i=-2:9] xtics (""i*30-90)
set ytics offset 0.75,0
unset label 2
plot [-90:90][ylow:yhigh] 'g2320_5pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '384-keV (5pt)' at -80,50
set label 11 'J_f=3' at 80,50 right
set ytics
set for [i=-2:5] ytics add (""10**i)
unset label 3
unset label 2
plot [-90:90][ylow:yhigh] 'g383_5pt.dat' u 1:2 every ::1::181 w lines lt 2 lw 5 notit,\
'' u 1:2 every ::183::363 w lines lt 3 lw 0.5 notit
set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
set label 1 '830-keV (5pt)' at -80,50
set label 11 'J_f=4^+' at 80,50 right
set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.035 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g830_5pt.dat' u 1:($2*1.0) every ::1::181 w lines lw 0.5 lt 6 notit,\
'' u 1:($2*1.0) every ::183::363 w lines  lw 5 lt 4 notit,\
'' u 1:($2*1.0) every ::365::545 w lines  lw 5 lt 3 notit
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '780-keV (5pt)' at -80,50
set label 11 'J_f=(4)' at 80,50 right
unset label 3
set xtics -90,30,90
set for [i=-2:9] ytics add (""10**i)
plot [-90:90][ylow:yhigh] 'g780_5pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit

unset multiplot
#################################################
################################################# 3
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
set ytics 0.001,10,9e1
set arr 1 from -90,2e2 to -60,2e2 nohead lt 1
set arr 2 from -15,2e2 to 15,2e2 nohead lt 2
set arr 3 from 60,2e2 to 90,2e2 nohead lt 3
set arr 4 from 135,2e2 to 165,2e2 nohead lt 4
set arr 5 from 210,2e2 to 240,2e2 nohead lt 6
set label 100 "{/Symbol D}J=-2" at -57,2e2 left
set label 101 "{/Symbol D}J=-1" at 18,2e2 left
set label 102 "{/Symbol D}J=0" at 93,2e2 left
set label 103 "{/Symbol D}J=+1" at 168,2e2 left
set label 104 "{/Symbol D}J=+2" at 243,2e2 left

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
yhigh=100.0
set ytics
set format y "  10^{%T}"
set ylabel ""
set xlabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set format x "%.0f"
set label 1 '1020-keV (5pt)' at -80,50
set label 11 'J_f=(5)' at 80,50 right
set xtics
set for [i=-2:9] xtics (""i*30-90)
set ytics offset 0.75,0
unset label 2
plot [-90:90][ylow:yhigh] 'g1019_5pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1457-keV (5pt)' at -80,50
set label 11 'J_f=(4)' at 80,50 right
set ytics
set for [i=-2:5] ytics add (""10**i)
unset label 3
unset label 2
plot [-90:90][ylow:yhigh] 'g1456_5pt.dat' u 1:2 every ::1::181 w lines lt 1 lw 5 notit,\
'' u 1:2 every ::183::363 w lines lt 2 lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit
set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.01
set label 1 '559-keV (5pt)' at -80,50
set label 11 'J_f=(5)' at 80,50 right
set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.0025 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g559_5pt.dat' u 1:($2*1.0) every ::1::181 w lines lw 0.5 lt 1 notit,\
'' u 1:($2*1.0) every ::183::363 w lines  lw 5 lt 2 notit,\
'' u 1:($2*1.0) every ::365::545 w lines  lw 5 lt 3 notit
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '2804-keV (3pt)' at -80,50
set label 11 'J_f=(6)' at 80,50 right
unset label 3
set xtics -90,30,90
set for [i=-2:9] ytics add (""10**i)
plot [-90:90][ylow:yhigh] 'g2804_3pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit

unset multiplot
################################################# 3
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
set ytics 0.001,10,9e1
set arr 1 from -90,2e2 to -60,2e2 nohead lt 1
set arr 2 from -15,2e2 to 15,2e2 nohead lt 2
set arr 3 from 60,2e2 to 90,2e2 nohead lt 3
set arr 4 from 135,2e2 to 165,2e2 nohead lt 4
set arr 5 from 210,2e2 to 240,2e2 nohead lt 6
set label 100 "{/Symbol D}J=-2" at -57,2e2 left
set label 101 "{/Symbol D}J=-1" at 18,2e2 left
set label 102 "{/Symbol D}J=0" at 93,2e2 left
set label 103 "{/Symbol D}J=+1" at 168,2e2 left
set label 104 "{/Symbol D}J=+2" at 243,2e2 left

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
yhigh=100.0
set ytics
set format y "  10^{%T}"
set ylabel ""
set xlabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set format x "%.0f"
set label 1 '1512-keV (3pt)' at -80,50
set label 11 'J_f=2^+' at 80,50 right
set xtics
set for [i=-2:9] xtics (""i*30-90)
set ytics offset 0.75,0
unset label 2
plot [-90:90][ylow:yhigh] 'g1512_3pt.dat' u 1:2 every ::1::181 w lines lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lw 0.5 notit,\
'' u 1:2 every ::365::545 w lines lw 5 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i
set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '760-keV (5pt)' at -80,50
set label 11 'J_f=6^+' at 80,50 right
set ytics
set for [i=-2:5] ytics add (""10**i)
unset label 3
unset label 2
plot [-90:90][ylow:yhigh] 'g760_5pt.dat' u 1:2 every ::1::181 w lines lt 6 lw 0.5 notit,\
'' u 1:2 every ::183::363 w lines lt 4 lw 5 notit,\
'' u 1:2 every ::365::545 w lines lw 0.5 notit
set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
ylow=0.1
set label 1 '810-keV (3pt)' at -80,50
set label 11 'J_f=2^+' at 80,50 right
set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.0025 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,3 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g810_3pt.dat' u 1:($2*1.0) every ::1::181 w lines lw 0.5 lt 1 notit,\
'' u 1:($2*1.0) every ::183::363 w lines  lw 5 lt 2 notit,\
'' u 1:($2*1.0) every ::365::545 w lines  lw 0.5 lt 3 notit
unset multiplot
