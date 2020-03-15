set term post enhance color "Helvetica,26" lw 1.5
set out "|ps2pdf - plot.pdf"

set title
set xlabel "{/Symbol d}"
set ylabel "{/Symbol c}^2"
set log y
set key bottom left

set title 'g1293'

plot [-90:90][0.01:10] 's38_g1293.out' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    's38_g1293.out' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    's38_g1293.out' u 1:2 every ::370::540 w lines tit 'J_{max}-2',\
                    's38_g1293.out' u 1:2 every ::555::720 w lines tit 'J_{max}-3',\
                    's38_g1293.out' u 1:2 every ::740::1090 w lines tit 'J_{max}-4'

set title 'g1535'
plot [-90:90][0.01:10] 's38_g1535.out' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    's38_g1535.out' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    's38_g1535.out' u 1:2 every ::370::540 w lines tit 'J_{max}-2',\
                    's38_g1535.out' u 1:2 every ::555::720 w lines tit 'J_{max}-3',\
                    's38_g1535.out' u 1:2 every ::740::1090 w lines tit 'J_{max}-4'

set title 'g849'

plot [-90:90][0.01:10] 's38_g849.out' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    's38_g849.out' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    's38_g849.out' u 1:2 every ::370::540 w lines tit 'J_{max}-2',\
                    's38_g849.out' u 1:2 every ::555::720 w lines tit 'J_{max}-3',\
                    's38_g849.out' u 1:2 every ::740::1090 w lines tit 'J_{max}-4'

set title 'g2320'


plot [-90:90][0.01:10] 's38_g2320.out' u 1:2 every ::5::180 w lines tit 'J_{max}',\
                    's38_g2320.out' u 1:2 every ::185::360 w lines tit 'J_{max}-1',\
                    's38_g2320.out' u 1:2 every ::370::540 w lines tit 'J_{max}-2',\
                    's38_g2320.out' u 1:2 every ::555::720 w lines tit 'J_{max}-3',\
                    's38_g2320.out' u 1:2 every ::740::1090 w lines tit 'J_{max}-4'
