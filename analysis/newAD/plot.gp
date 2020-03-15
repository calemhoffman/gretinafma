set term post enhance color "Helvetica,26" lw 1.5
set out "|ps2pdf - plot.pdf"

set title
set xlabel "{/Symbol d}"
set ylabel "Reduced {/Symbol c}^2"
set log y
set key bottom left

set title 'current'
plot [-90:90][0.001:10] 'fort.3' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    '' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    '' u 1:2 every ::370::540 w lines tit 'J_{max}-2'

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

