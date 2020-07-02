set term post enhance color "Helvetica,20" lw 1.0
set out "|ps2pdf - plot.pdf"
set lmargin 0
set tmargin 0
set bmargin 1
set rmargin 0
a0=1
#sigma/j=1.2
#a2=0.084691
#a4=-0.005278
#sigma/j=0.7
a2=0.230179
a4=-0.045619
l2(x)=a2*(3*x**2-1)/2
l4(x)=a4*(35*x**4-30*x**2+3)/8
ll(x)=a0*(1+l2(x)+l4(x))
array ang[20]=[90.0,113,127,138,154,119.0,149.0]
print "ll() = ",ll(cos(ang[1]/180.0*pi))
print "ll() = ",ll(cos(ang[2]/180.0*pi))
print "ll() = ",ll(cos(ang[3]/180.0*pi))
print "ll() = ",ll(cos(ang[4]/180.0*pi))
print "ll() = ",ll(cos(ang[5]/180.0*pi))


#plot [-1:1][0:2] ll(x) w lines tit 'full ll(x)'

set title
set xlabel "{/Symbol d}"
set ylabel "Reduced {/Symbol c}^2"
set log y
set key bottom left

#set xrange [-1:1]
#set yrange [-1:2]
#set xlabel "x"
#set ylabel "P_n (x)"
#plot 1 ti "n = 0",\
#x ti "n = 1",\

 # ti "n = 2",\
#  (5*x**3-3*x)/2 ti "n = 3",\
# ti "n = 4",\
#    (63*x**5-70*x**3+15*x)/8 ti "n = 5"
set key horizontal top
set ylabel ''
set xlabel ''
set xtic offset 0,0.5
set title 'current'
plot [-90:90][0.01:100] 'fort.3' u 1:2 every ::1::181 w lines tit '1',\
                    '' u 1:2 every ::183::363 w lines tit '2',\
                    '' u 1:2 every ::365::545 w lines tit '3',\
                    '' u 1:($2) every ::547::727 w lines lt 4 tit '4',\
                    '' u 1:($2) every ::729::909 w lines lt 6 tit '5',\
                    '' u 1:($2) every ::911::1091 w lines lt 8 tit '6'


############
set out "|ps2pdf - ad1.pdf"
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
set label 3 "{/Symbol c}^{2}/NDF" at -115,1 center rotate
set format x "%.0f"
set label 1 '1293-keV (5pt)' at -80,50
set label 11 'J_f=0^+' at 80,50 right

set xtics
set for [i=0:9] xtics (""i*30-90)
set ytics offset 0.75,0
plot [-90:90][ylow:yhigh] 'g1293_5pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i

set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1535-keV (5pt)' at -80,50
set label 11 'J_f=2^+' at 80,50 right

set ytics
#set for [i=1:5] ytics ("" 10^{i})
set ytics (""0.001,""0.01,""0.1,""1.0,""10,""100)
unset label 3
plot [-90:90][ylow:yhigh] 'g1535_5pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
set label 1 '850-keV (5pt)' at -80,50
set label 11 'J_f=4^+' at 80,50 right

set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,0.035 center
set label 3 "{/Symbol c}^{2}/NDF" at -115,1 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g850_5pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '2668-keV (5pt)' at -80,50
set label 11 'J_f=6^+' at 80,50 right

unset label 3
set xtics -90,30,90
set ytics (""0.001,""0.01,""0.1,""1.0,""10,""100)
plot [-90:90][ylow:yhigh] 'g2668_5pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

unset multiplot

############
set out "|ps2pdf - ad2.pdf"
set multiplot layout 2,2
set key bottom center
unset grid
set title ''
unset for [i=1:1000] label i
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
ylow=0.001
yhigh=100.0
set format y "  10^{%T}"
set ylabel ""
set label 3 "{/Symbol c}^{2}/NDF" at -115,1 center rotate
set format x "%.0f"
set label 1 '2365-keV (3pt)' at -80,50
set label 11 'J_f=2' at 80,50 right
set ytics 0.001,10
set xtics
set for [i=0:9] xtics (""i*30-90)
set ytics offset 0.75,0
plot [-90:90][ylow:yhigh] 'g2365_3pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit
unset for [i=0:1000] arr i
unset for [i=0:1000] label i

set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '830-keV (3pt)' at -80,50
set label 11 'J_f=4' at 80,50 right

set ytics
#set for [i=1:5] ytics ("" 10^{i})
set ytics (""0.001,""0.01,""0.1,""1.0,""10,""100)
unset label 3
plot [-90:90][ylow:yhigh] 'g830_3pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

set lmargin 1
set bmargin 0
set tmargin 0
set rmargin 0
set label 1 '780-keV (3pt)' at -80,50
set label 11 'J_f=(3)' at 80,50 right

set xtics -90,30,89
set ytics 0.001,10,9e1
set label 2 "{/Symbol d} [deg]" at 0,ylow-0.8*ylow center
set label 3 "{/Symbol c}^{2}/NDF" at -115,1 center rotate
set xlabel ''
plot [-90:90][ylow:yhigh] 'g780_3pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

set lmargin 0
set bmargin 0
set tmargin 0
set rmargin 1
set label 1 '1609-keV (3pt)' at -80,50
set label 11 'J_f=4' at 80,50 right

unset label 3
set xtics -90,30,90
set ytics (""0.001,""0.01,""0.1,""1.0,""10,""100)
plot [-90:90][ylow:yhigh] 'g1609_3pt.dat' u 1:2 every ::1::181 w lines notit,\
'' u 1:2 every ::183::363 w lines notit,\
'' u 1:2 every ::365::545 w lines notit,\
'' u 1:2 every ::547::727 w lines lt 4 notit,\
'' u 1:2 every ::729::909 w lines lt 6 notit

unset multiplot

######
set out "|ps2pdf - plot2.pdf"


set multiplot layout 2,2
set key bottom center
set title ''

set label 1 '1609-keV (3pt)' at -80,0.6
plot [-90:90][0.1:100] 'g1609_3pt.dat' u 1:2 every ::1::181 w lines tit '6-4',\
'' u 1:2 every ::183::363 w lines tit '5->4',\
'' u 1:2 every ::365::545 w lines tit '4->4',\
'' u 1:2 every ::550::720 w lines lt 5 tit '3->4',\
'' u 1:($2/4.0) every ::729::1089 w lines lt 14 notit

set label 1 '830-keV (3pt)' at 20,0.1
plot [-90:90][0.001:10] 'g830_3pt.dat' u 1:2 every ::1::181 w lines tit '6-4',\
'' u 1:2 every ::183::363 w lines tit '5->4',\
'' u 1:2 every ::365::545 w lines tit '4->4',\
'' u 1:($2/4.0) every ::550::720 w lines lt 14 notit

set label 1 '780-keV (3pt)' at -80,0.1
plot [-90:90][0.001:10] 'g780_3pt.dat' u 1:2 every ::1::181 w lines tit '5->3',\
'' u 1:2 every ::183::363 w lines tit '4->3',\
'' u 1:2 every ::365::545 w lines tit '3->3',\
'' u 1:($2/4.0) every ::550::720 w lines lt 14 notit


set label 1 '2365-keV (3pt)' at -80,0.01
plot [-90:90][0.001:10] 'g2365_3pt.dat' u 1:2 every ::1::181 w lines tit '4->2',\
'' u 1:2 every ::183::363 w lines tit '3->2',\
'' u 1:2 every ::365::545 w lines tit '2->2',\
'' u 1:($2/4.0) every ::550::720 w lines lt 14 notit
unset multiplot


set multiplot layout 2,2
set label 1 '1950-keV (3pt)' at -80,0.1
plot [-90:90][0.001:10] 'g1950_3pt.dat' u 1:2 every ::1::181 w lines tit '9->7',\
                '' u 1:2 every ::183::363 w lines tit '8->7',\
                '' u 1:2 every ::365::545 w lines tit '7->7',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit

set label 1 '1577-keV (5pt)' at -80,40
plot [-90:90][0.1:100] 'g1577_5pt.dat' u 1:2 every ::1::181 w lines tit '7->5',\
                '' u 1:2 every ::183::363 w lines tit '6->5',\
                '' u 1:2 every ::365::545 w lines tit '5->5',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit

set label 1 '1617-keV (3pt)' at -80,0.1
plot [-90:90][0.001:10] 'g1617_3pt.dat' u 1:2 every ::1::181 w lines tit '10->8',\
                '' u 1:2 every ::183::363 w lines tit '9->8',\
                '' u 1:2 every ::365::545 w lines tit '8->8',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit
unset multiplot
set multiplot layout 2,2
set label 1 '559-keV (3pt)' at -80,0.1
plot [-90:90][0.001:10] 'g559_3pt.dat' u 1:2 every ::1::181 w lines tit '7->5',\
                '' u 1:2 every ::183::363 w lines tit '6->5',\
                '' u 1:2 every ::365::545 w lines tit '5->5',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit
unset multiplot

set multiplot layout 2,2
set key bottom left
set title ''
set label 1 '810-keV (2pt)' at -80,0.01
plot [-90:90][0.001:10] 'g810_2pt.dat' u 1:2 every ::1::181 w lines tit '4->2',\
                '' u 1:2 every ::183::363 w lines tit '3->2',\
                '' u 1:2 every ::365::545 w lines tit '2->2',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit

set key horizontal bottom
set label 1 '1512-keV (3pt)' at -80,0.01
plot [-90:90][0.001:10] 'g1512_3pt.dat' u 1:2 every ::1::181 w lines tit '4->2',\
                '' u 1:2 every ::183::363 w lines tit '3->2',\
                '' u 1:2 every ::365::545 w lines tit '2->2',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 notit

set label 1 '1019-keV (3pt)' at -80,50
plot [-90:90][0.001:100] 'g1019_3pt.dat' u 1:2 every ::1::181 w lines tit '-2(7->5)',\
                '' u 1:2 every ::183::363 w lines tit '-1(6->5)',\
                '' u 1:2 every ::365::545 w lines tit '0(5->5)',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'

set label 1 '822-keV (2pt)' at-80,50
plot [-90:90][0.001:100] 'g822_2pt.dat' u 1:2 every ::1::181 w lines tit '-2(5->3)',\
                '' u 1:2 every ::183::363 w lines tit '-1(4->3)',\
                '' u 1:2 every ::365::545 w lines tit '0(3->3)',\
                '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'
unset multiplot

set multiplot layout 2,2

set label 1 '1456-keV (3pt)' at -80,5
plot [-90:90][0.01:10] 'g1456_3pt.dat' u 1:2 every ::1::181 w lines tit '-2(6->4)',\
                    '' u 1:2 every ::183::363 w lines tit '-1(5->4)',\
                    '' u 1:2 every ::365::545 w lines tit '0(4->4)',\
                    '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'

set label 1 '438-keV (3pt)' at -80,5
plot [-90:90][0.01:10] 'g438_3pt.dat' u 1:2 every ::1::181 w lines tit '-2(6->4)',\
                    '' u 1:2 every ::183::363 w lines tit '-1(5->4)',\
                    '' u 1:2 every ::365::545 w lines tit '0(4->4)',\
                    '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'


set label 1 '383-keV (3pt)' at -80,50
plot [-90:90][0.01:100] 'g383_3pt.dat' u 1:2 every ::1::181 w lines tit '-2(5->3)',\
                    '' u 1:2 every ::183::363 w lines tit '-1(4->3)',\
                    '' u 1:2 every ::365::545 w lines tit '0(3->3)',\
                    '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'

set label 1 '2322-keV (3pt)' at -80,50
plot [-90:90][0.01:100] 'g2320_3pt.dat' u 1:2 every ::1::181 w lines tit '4->2',\
                    '' u 1:2 every ::183::363 w lines tit '3->2',\
                    '' u 1:2 every ::365::545 w lines tit '2->2',\
                    '' u 1:($2/4.0) every ::550::720 w lines lt 14 tit '0.1'
unset multiplot
#
# set title '779-keV ^{38}S'
# plot [-90:90][0.08:8] 'g779.dat' u 1:2 every ::1::181 w lines tit '6->4',\
#                     '' u 1:2 every ::183::363 w lines tit '5->4',\
#                     '' u 1:2 every ::365::545 w lines tit '4->4'
#
# set title '438-keV ^{38}S'
# plot [-90:90][0.001:10] 'g438.dat' u 1:2 every ::1::181 w lines tit '6->4',\
#                     '' u 1:2 every ::183::363 w lines tit '5->4',\
#                     '' u 1:2 every ::365::545 w lines tit '4->4'
#
# set title '384-keV ^{38}S'
# plot [-90:90][0.2:20] 'g385.dat' u 1:2 every ::1::181 w lines lt 2 tit '4->3',\
#                     '' u 1:2 every ::183::363 w lines lt 3 tit '3->3'
#
# set title '1576-keV ^{38}S'
# plot [-90:90][0.001:10] 'g1576.dat' u 1:2 every ::1::181 w lines tit '7->5',\
#                     '' u 1:2 every ::183::363 w lines tit '6->5',\
#                     '' u 1:2 every ::365::545 w lines tit '5->5'
#
# set title '2320-keV ^{38}S'
# plot [-90:90][0.01:10] 'g2320.dat' u 1:2 every ::1::181 w lines lt 2 tit '3->2',\
#                     '' u 1:2 every ::183::363 w lines lt 3  tit '2->2'
#
# set title '2668-keV ^{38}S'
# plot [-90:90][0.001:10] 'g2668.dat' u 1:2 every ::1::181 w lines tit '8->6',\
#                     '' u 1:2 every ::183::363 w lines tit '7->6',\
#                     '' u 1:2 every ::365::545 w lines tit '6->6'
#
# set title '850-keV ^{38}S'
# plot [-90:90][0.01:100] 'g850.dat' u 1:2 every ::1::181 w lines tit '6->4',\
#                     '' u 1:2 every ::183::363 w lines tit '5->4',\
#                     '' u 1:2 every ::365::545 w lines tit '4->4'
#
# set title '1535-keV ^{38}S'
# plot [-90:90][0.1:100] 'g1535.dat' u 1:2 every ::1::181 w lines tit '4->2',\
#                     '' u 1:2 every ::183::363 w lines tit '3->2',\
#                     '' u 1:2 every ::365::545 w lines tit '2->2'
#
# set title '1293-keV ^{38}S'
# plot [-90:90][0.1:100] 'g1293.dat' u 1:2 every ::1::181 w lines tit '2->0',\
#                     '' u 1:2 every ::183::363 w lines tit '1->0'
