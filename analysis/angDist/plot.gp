set term post enhance color "Helvetica,18"
set out "|ps2pdf - plot.pdf"
set palette defined ( 0 '#8C510A',\
    	    	      1 '#BF812D',\
		      2 '#DFC27D',\
		      3 '#F6E8C3',\
		      4 '#C7EAE5',\
		      5 '#80CDC1',\
		      6 '#35978F',\
		      7 '#01665E' )
                   # palette
set palette maxcolors 8
#show palette gradient
delta(x) = tan(x/180.0*3.14)
fa(x) = 1.0/(1.0 +  delta(x)*delta(x))
fb(x) = (delta(x)*delta(x))/(1.0 + delta(x)*delta(x))
print(delta(0))
set multiplot layout 2,1
set xlabel 'arctan(delta) [degrees]'
set ylabel 'ratio of L1/L2'
plot [-90:90] fa(x) w lines, fb(x) w lines
delta(x) = tan(x/180.0*3.14)
fa(x) = 1.0/(1.0 +  x*x)
fb(x) = (x*x)/(1.0 + x*x)
set xlabel 'delta'
plot [-2:2] fa(x) w lines, fb(x) w lines
unset multiplot


set pointsize 2
set obj rect from -0.39-0.18,-0.27 to -0.39+0.18,0.27
set title "^{38}S - 1609 keV sigma=1.5"
set xlabel "a2"
set ylabel "a4"
set key outside top
plot [-1:1][-0.5:0.5] '2_0.dat' u 3:(abs($1)==0 ? $4 : 1/0) every :::0::0 w points  tit '2->0',\
                    '4_2.dat' u 3:(abs($1)==0 ? $4 : 1/0) every :::0::0 w points tit '4->2',\
                    '6_4.dat' u 3:(abs($1)==0 ? $4 : 1/0) every :::0::0 w points tit '6->4',\
                    '8_6.dat' u 3:(abs($1)==0 ? $4 : 1/0) every :::0::0 w points tit '8->6'

plot [-1:1][-0.5:0.5] '3_2.dat' u 3:4:($1) every :::0::0 w points lc palette tit '3->2',\
                    '4_3.dat' u 3:4:($1) every :::0::0 w points lc palette tit '4->3',\
                    '5_4.dat' u 3:4:($1) every :::0::0 w points lc palette tit '5->4',\
                    '6_5.dat' u 3:4:($1) every :::0::0 w points lc palette tit '6->5'

plot [-1:1][-0.5:0.5] '2_2.dat' u 3:(abs($1)<180 ? $4 : 1/0):($1) every :::0::0 w points lc palette tit '2->2',\
                    '3_3.dat' u 3:4:($1) every :::0::0 w points lc palette tit '3->3',\
                    '4_4.dat' u 3:4:($1) every :::0::0 w points lc palette tit '4->4',\
                    '5_5.dat' u 3:4:($1) every :::0::0 w points lc palette tit '5->5'

plot [-1:1][-0.5:0.5] '4_4.dat' u 3:(abs($1)<30 ? $4 : 1/0):($1) every :::0::0 w points lc palette tit '4->4',\
                    '5_4.dat' u 3:(abs($1)<30 ? $4 : 1/0):($1) every :::0::0 w points lc palette tit '5->4'

set title "^{38}Cl - 171,292,638,755 keV"
set xlabel "a2"
set ylabel "a4"
set key outside top
plot [-0.55:0.55][-0.2:0.2] 'delta_8_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '8->6',\
                            'delta_7_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '7->6',\
                            'delta_6_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->6',\
                            'delta_6_5.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->5',\
                            'delta_4_5.dat' u 2:3:5 every :::0::0 w points lc palette tit '4->5',\
                            'delta_3_2.dat' u 2:3:5 every :::0::0 w points lc palette tit '3->2',\
                            'data.dat' u 2:4:3:5 every ::0:2:0:2 w xyerror lt 1 tit '171 data',\
                            'data.dat' u 2:4:3:5 every ::1:2:1:2 w xyerror lt 2 tit '292 data',\
                            'data.dat' u 2:4:3:5 every ::2:2:2:2 w xyerror lt 3 tit '638 data',\
                            'data.dat' u 2:4:3:5 every ::3:2:3:2 w xyerror lt 4 tit '755 data'

set title "^{38}Cl - 1190,2044 keV"
set xlabel "a2"
set ylabel "a4"
set key outside top
plot [-0.55:0.55][-0.1:0.35] 'delta_8_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '8->6',\
                            'delta_7_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '7->6',\
                            'delta_6_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->6',\
                            'delta_6_5.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->5',\
                            'delta_5_4.dat' u 2:3:5 every :::0::0 w points lc palette tit '5->4',\
                            'data.dat' u 2:4:3:5 every ::4:2:4:2 w xyerror lt 1 tit '1190 data',\
                            'data.dat' u 2:4:3:5 every ::5:2:5:2 w xyerror lt 2 tit '2044 data'

set title "^{38}Cl - 2680,3142 keV"
set xlabel "a2"
set ylabel "a4"
set key outside top
plot [-0.55:0.55][-0.1:0.15] 'delta_8_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '8->6',\
                            'delta_7_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '7->6',\
                            'delta_6_6.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->6',\
                            'delta_6_5.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->5',\
                            'delta_5_5.dat' u 2:3:5 every :::0::0 w points lc palette tit '5->5',\
                            'data.dat' u 2:4:3:5 every ::6:2:6:2 w xyerror lt 1 tit '2680 data',\
                            'data.dat' u 2:4:3:5 every ::7:2:7:2 w xyerror lt 2 tit '3142 data'
#,\
#                            'data.dat' u 2:4:3:5 every ::2:2:2:2 w xyerror lt 3 tit '638 data',\
#                            'data.dat' u 2:4:3:5 every ::3:2:3:2 w xyerror lt 4 tit '755 data'



set title "Various Low-Lying"
set xlabel "a2"
set ylabel "a4"
set key outside top

plot [-0.6:0.6][-0.25:0.25] 'delta_4_2.dat' u 2:3:5 every :::0::0 w points lc palette tit '4->2',\
                            'delta_3_2.dat' u 2:3:5 every :::0::0 w points lc palette tit '3->2',\
                            'delta_2_2.dat' u 2:3:5 every :::0::0 w points lc palette tit '2->2',\
                            'delta_1_2.dat' u 2:3:5 every :::0::0 w points lc palette tit '1->2',\
                            'data.dat' u 2:4:3:5 every ::3:1:3:1 w xyerror lt 1 tit '2668',\
                            'data.dat' u 2:4:3:5 every ::4:1:4:1 w xyerror lt 2 tit '2322',\
                            'data.dat' u 2:4:3:5 every ::5:1:5:1 w xyerror lt 3 tit '1576',\
                            'data.dat' u 2:4:3:5 every ::6:1:6:1 w xyerror lt 4 tit '384',\
                            'data.dat' u 2:4:3:5 every ::7:1:7:1 w xyerror lt 11 tit '438',\
                            'data.dat' u 2:4:3:5 every ::8:1:8:1 w xyerror lt 12 tit '779',\
                            'data.dat' u 2:4:3:5 every ::9:1:9:1 w xyerror lt 13 tit '1018',\
                            'data.dat' u 2:4:3:5 every ::10:1:10:1 w xyerror lt 14 tit '1067',\
                            'data.dat' u 2:4:3:5 every ::11:1:11:1 w xyerror lt 21 tit '1456',\
                            'data.dat' u 2:4:3:5 every ::12:1:12:1 w xyerror lt 22 tit '1951'


plot [-0.6:0.6][-0.25:0.25] 'delta_6_4.dat' u 2:3:5 every :::0::0 w points lc palette tit '6->4',\
                            'delta_5_4.dat' u 2:3:5 every :::0::0 w points lc palette tit '5->4',\
                            'delta_4_4.dat' u 2:3:5 every :::0::0 w points lc palette tit '4->4',\
                            'delta_3_4.dat' u 2:3:5 every :::0::0 w points lc palette tit '3->4',\
                            'data.dat' u 2:4:3:5 every ::3:1:3:1 w xyerror lt 1 tit '2668',\
                            'data.dat' u 2:4:3:5 every ::4:1:4:1 w xyerror lt 2 tit '2322',\
                            'data.dat' u 2:4:3:5 every ::5:1:5:1 w xyerror lt 3 tit '1576',\
                            'data.dat' u 2:4:3:5 every ::6:1:6:1 w xyerror lt 4 tit '384',\
                            'data.dat' u 2:4:3:5 every ::7:1:7:1 w xyerror lt 11 tit '438',\
                            'data.dat' u 2:4:3:5 every ::8:1:8:1 w xyerror lt 12 tit '779',\
                            'data.dat' u 2:4:3:5 every ::9:1:9:1 w xyerror lt 13 tit '1018',\
                            'data.dat' u 2:4:3:5 every ::10:1:10:1 w xyerror lt 14 tit '1067',\
                            'data.dat' u 2:4:3:5 every ::11:1:11:1 w xyerror lt 21 tit '1456',\
                            'data.dat' u 2:4:3:5 every ::12:1:12:1 w xyerror lt 22 tit '1951'
