set term post enhance color
set out "|ps2pdf - effic.pdf"
set pointsize 2
set title ""
set xlabel ""
set ylabel ""

###################################################

# eff(x) = exp( ( (A+B*log(x/100.0000)+C*log(x/100.0000)*log(x/100.0000))**(-G)\
 # + (D+E*log(x/1000.0000)+F*log(x/1000.0000)*log(x/1000.0000))**(-G) )**(-1.0/G) )
  eff(x) = exp( ( (A+B*log(x/100.0000))**(-G)\
  + (D+E*log(x/1000.0000)+F*log(x/1000.0000)*log(x/1000.0000))**(-G) )**(-1.0/G) )


A = 3.0
B = 0.56
C = 0.000000
D = 3.1
E = -0.60
F = 0.08
G = 7.9
fit eff(x) 'AddBack.sin' u ($2):($4/$8/$10) via A,B,D,E,F,G
# print eff(146)/10000/(1.0-0.13)
###################################################

plot [0:6000] 'AddBack.sin' u ($1<23 ? $2 : 1/0):($4/$8/$10) w points notit,\
'AddBack.sin' u ($1>22 ? $2 : 1/0):($4/$8/$10) w points notit,\
eff(x) w lines notit

#gamma ray energies, no particular order
array ge[100] = [383.7,438.4,558.9,759.7,779.8,\
788.3,809.6,822.0,830.2,850.1,\
886.6,1019.6,1066.9,1292.7,1457.0,\
1513.1,1534.5,1576.7,1609.3,1617.0,\
1625.4,1950.5,2057.3,2322.8,2364.8,\
2384.7,2577.8,2668.2,2804.0,2224.4,\
3520.0,3033.1] #32 total
nl=32
do for [i=1:nl] {
print sprintf("%.1f: %.2f",ge[i],eff(ge[i]))
}
