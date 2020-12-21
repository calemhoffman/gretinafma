set term post enhance color font "Helvetica,20" lw 0.5 fontscale 1.0 #landscape
#reset
#load 'gnuplot12'
set out "|ps2pdf - mltrain.pdf"
unset title
set tmargin at screen 0
set tmargin 0
set lmargin 2.5
set rmargin 0.5
set ylabel offset 2.0
set xtic offset 0,0.3
set ytic offset 0.65,0
set mxtics 5
set key top right
set key spacing 1.5
set xlabel
unset grid
set ylabel offset 1.6
set format x "%.0f"
set bmargin 0
set ylabel "Counts / 1 keV"
set xtics 0,500
set ytics 0,5000
set mxtics 5
set mytics 1
set xlabel "Energy [keV]"
set format y "%.0f"
xlow=100
xhigh=3200
yhigh=28000
#set log y
set label 1 at xhigh-(xhigh-xlow)*(0.1),(yhigh-yhigh*0.15)\
"^{38}S" font "Helvetica,18" tc rgb color_4 left
set label 2 at xhigh-(xhigh-xlow)*(0.1),(yhigh-yhigh*0.3)\
"^{38}Cl" font "Helvetica,18" tc rgb color_2 left
set label 3 at xhigh-(xhigh-xlow)*(0.1),(yhigh-yhigh*0.45)\
"^{33}P" font "Helvetica,18" tc rgb color_7 left
set label 4 at xhigh-(xhigh-xlow)*(0.1),(yhigh-yhigh*0.6)\
"^{181}Ta" font "Helvetica,18" tc rgb color_8 left
set tics front
set multiplot layout 3,1
set arr 1 from 350,0 to 350,yhigh nohead lt 12 lc rgb color_8
set label 10 at 370,(yhigh-yhigh*0.15) "x3" font "Helvetica,18"\
left front

plot [xlow:xhigh][0:yhigh] 'hgt.ascii' u ($1>10 ? $1 : 1/0):\
($1<350 ? $2 : $2*3.0)\
w fillsteps fs solid 1.0 noborder lt 9 notit,\
'' u ($1>10 ? $1 : 1/0):($1<350 ? $2 : $2*3.0)\
w steps lw 0.5 lt -1 notit,\
'hgts38.ascii' u ($1>10 ? $1 : 1/0):\
($1<350 ? $2 : $2*3.0)\
w fillsteps fs solid 1.0 noborder lt 4 notit,\
'' u ($1>10 ? $1 : 1/0):($1<350 ? $2 : $2*3.0)\
w steps lw 0.5 lt -1 notit,\
'hgtcl38.ascii' u ($1>10 ? $1 : 1/0):\
($1<350 ? $2 : $2*3.0)\
w fillsteps fs solid 1.0 noborder lt 2 notit,\
'' u ($1>10 ? $1 : 1/0):($1<350 ? $2 : $2*3.0)\
w steps lw 0.5 lt -1 notit,\
'hgtp33.ascii' u ($1>10 ? $1 : 1/0):\
($1<350 ? $2 : $2*3.0)\
w fillsteps fs solid 1.0 noborder lt 7 notit,\
'' u ($1>10 ? $1 : 1/0):($1<350 ? $2 : $2*3.0)\
w steps lw 0.5 lt -1 notit,\
'hgtta.ascii' u ($1<150 ? $1 : 1/0):\
($1>150 ? $2 : $2)\
w fillsteps fs solid 1.0 noborder lt 8 notit,\
'' u ($1<150 ? $1 : 1/0):($1>150 ? $2 : $2)\
w steps lw 0.5 lt -1 notit,\
'hgtta.ascii' u ($1>150 ? $1 : 1/0):\
($1<150 ? $2 : $2)\
w fillsteps fs solid 1.0 noborder lt 2 notit,\
'' u ($1>150 ? $1 : 1/0):($1<150 ? $2 : $2)\
w steps lw 0.5 lt -1 notit

unset multiplot
