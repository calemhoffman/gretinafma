#set term post enhance color "Helvetica,18"
#set out "|ps2pdf - plot.pdf"

set title "sigma determination"
set xlabel "a2"
set ylabel "a4"

plot [-0.1:1.0][-0.5:0.5] 'sig_2_0.dat' u 2:3:6 every :::0::0 w points lc palette tit '2->0',\
                          'sig_4_2.dat' u 2:3:6 every :::0::0 w points lc palette tit '4->2',\
                          'sig_6_4.dat' u 2:3:6 every :::0::0 w points lc palette tit '6->4',\
                          'data.dat' u 2:4:3:5 every :::1::1 w xyerror tit 'data'

set xlabel 'sigma'
set ylabel 'a2'

set obj 1 rect from 0,2.84443e-01-3.15464e-02 to 3,2.84443e-01+3.15464e-02
set obj 1 fc rgb color_1
plot [-0.1:3.1][0.0:1.0] 'sig_2_0.dat' u 6:2 every :::0::0 w points tit '2->0'
#set obj 1 rect from 0,2.96394e-01-4.38496e-02 to 3,2.96394e-01+4.38496e-02
#set obj 1 fc rgb color_2
#plot [-0.1:3.1][0.0:1.0] 'sig_4_2.dat' u 6:2 every :::0::0 w points lt 2 tit '4->2'
#set obj 1 rect from 0,2.27977e-01-4.95302e-02  to 4,2.27977e-01+4.95302e-02
#set obj 1 fc rgb color_3
#plot [-0.1:4.1][0.0:1.0] 'sig_6_4.dat' u 6:2 every :::0::0 w points lt 3 tit '6->4'
