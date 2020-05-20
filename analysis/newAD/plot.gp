set term post enhance color "Helvetica,26" lw 1.5
set out "|ps2pdf - plot.pdf"

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
array ang[20]=[90,113,127,138,154]
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


set title 'current'
plot [-90:90][0.01:100] 'fort.3' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    '' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    '' u 1:2 every ::370::540 w lines tit 'J_{max}-2',\
                    '' u 1:2 every ::550::720 w lines lt 14 tit '0.1'

set title '779-keV ^{38}S'
plot [-90:90][0.08:8] 'g779.dat' u 1:2 every ::5::180 w lines tit '6->4',\
                    '' u 1:2 every ::185::360 w lines tit '5->4',\
                    '' u 1:2 every ::370::540 w lines tit '4->4'

set title '438-keV ^{38}S'
plot [-90:90][0.001:10] 'g438.dat' u 1:2 every ::5::180 w lines tit '6->4',\
                    '' u 1:2 every ::185::360 w lines tit '5->4',\
                    '' u 1:2 every ::370::540 w lines tit '4->4'

set title '384-keV ^{38}S'
plot [-90:90][0.2:20] 'g385.dat' u 1:2 every ::5::180 w lines lt 2 tit '4->3',\
                    '' u 1:2 every ::185::360 w lines lt 3 tit '3->3'

set title '1576-keV ^{38}S'
plot [-90:90][0.001:10] 'g1576.dat' u 1:2 every ::5::180 w lines tit '7->5',\
                    '' u 1:2 every ::185::360 w lines tit '6->5',\
                    '' u 1:2 every ::370::540 w lines tit '5->5'

set title '2320-keV ^{38}S'
plot [-90:90][0.01:10] 'g2320.dat' u 1:2 every ::5::180 w lines lt 2 tit '3->2',\
                    '' u 1:2 every ::185::360 w lines lt 3  tit '2->2'

set title '2668-keV ^{38}S'
plot [-90:90][0.001:10] 'g2668.dat' u 1:2 every ::5::180 w lines tit '8->6',\
                    '' u 1:2 every ::185::360 w lines tit '7->6',\
                    '' u 1:2 every ::370::540 w lines tit '6->6'

set title '850-keV ^{38}S'
plot [-90:90][0.01:100] 'g850.dat' u 1:2 every ::5::180 w lines tit '6->4',\
                    '' u 1:2 every ::185::360 w lines tit '5->4',\
                    '' u 1:2 every ::370::540 w lines tit '4->4'

set title '1535-keV ^{38}S'
plot [-90:90][0.1:100] 'g1535.dat' u 1:2 every ::5::180 w lines tit '4->2',\
                    '' u 1:2 every ::185::360 w lines tit '3->2',\
                    '' u 1:2 every ::370::540 w lines tit '2->2'

set title '1293-keV ^{38}S'
plot [-90:90][0.1:100] 'g1293.dat' u 1:2 every ::5::180 w lines tit '2->0',\
                    '' u 1:2 every ::185::360 w lines tit '1->0'
