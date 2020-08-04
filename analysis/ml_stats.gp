set term post enhance color "Helvetica,26" lw 1.5
set out "|ps2pdf - ml_stats.pdf"

set title "Model C (AverageFatC train)"
set xlabel "> ml return"
set ylabel "Value"
set key outside top

block=0
plot [0:1.1][0:1.2] 'ml_stats.dat' u 1:7 every :::block::block w linespoints tit 'accuracy',\
                '' u 1:8 every :::block::block w linespoints tit 'precision',\
                '' u 1:9 every :::block::block w linespoints tit 'recall',\
                '' u 1:10 every :::block::block w linespoints tit 'F1'

set title "Model B (AverageFatB train)"
set xlabel "> ml return"
set ylabel "Value"
set key outside top
block=1
plot [0:1.1][0:1.2] 'ml_stats.dat' u 1:7 every :::block::block w linespoints tit 'accuracy',\
                '' u 1:8 every :::block::block w linespoints tit 'precision',\
                '' u 1:9 every :::block::block w linespoints tit 'recall',\
                '' u 1:10 every :::block::block w linespoints tit 'F1'
