set term post enhance color "Helvetica,16"
set out "|ps2pdf - s38Scan.pdf"
set pointsize 2

set title "A=38 Z selection"
set xlabel "Row"
set ylabel "Counts [norm to Row 1]"
plot [-0.5:2.5][0:15] for [i=1:3] 's38_scan.dat' using (i-1):(column(i*2)/$4) every :::0::0 with points pt 21 lc 1 notit,\
                     for [i=1:3] 's38_scan.dat' using (i-1):(column(i*2)/$4) every :::1::1 with points pt 22 lc 2 notit,\
                     for [i=1:3] 's38_scan.dat' using (i-1):(column(i*2)/$4) every :::2::2 with points pt 23 lc 3 notit


set title "A/Q selection"
set xlabel "Column"
set ylabel "Counts [norm to Row 1]"
plot [-0.5:2.5][0:0.35] for [i=4:6] 's38_scan.dat' using (i-4):(column(i*2)/$4) every :::0::0 with points pt 21 lc 1 notit,\
                        for [i=4:6] 's38_scan.dat' using (i-4):(column(i*2)/$4) every :::1::1 with points pt 22 lc 2 notit,\
                        for [i=4:6] 's38_scan.dat' using (i-4):(column(i*2)/$4) every :::2::2 with points pt 23 lc 3 notit
