set term post enhance color "Helvetica,26" lw 1.5
set out "|ps2pdf - ml_stats.pdf"

set title "Model B (AverageFatB train)"
set xlabel "> ml return"
set ylabel "Value"
set key outside top

plot [0:1.1][0:1.2] 'ml_stats.dat' u 1:7 every :::0::0 w linespoints tit 'accuracy',\
                '' u 1:8 every :::0::0 w linespoints tit 'precision',\
                '' u 1:9 every :::0::0 w linespoints tit 'recall',\
                '' u 1:10 every :::0::0 w linespoints tit 'F1'
