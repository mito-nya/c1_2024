reset
set terminal pngcairo
set out "01.png"

set xlabel "p"
set ylabel "P(p)"
# plot "out_08.data" linecolor '#9400d3', "out_08_2.data" w l linecolor '#9400d3' title "L=8", \
# "out_16.data" linecolor '#008044', "out_16_2.data" w l linecolor '#008044' title "L=16", \
# "out_32.data" linecolor '#0080ff', "out_32_2.data" w l linecolor '#0080ff' title "L=32"

# plot "out_08_2.data" w lp title "L=8", \
# "out_16_2.data" w lp title "L=16", \
# "out_32_2.data" w lp title "L=32"

filter(x,y)=int(x/y)*y
plot "out_08_2.data" u (filter($1,0.01)):2 w l smooth unique title "L=8", \
"out_16_2.data" u (filter($1,0.01)):2 w l smooth unique title "L=16", \
"out_32_2.data" u (filter($1,0.01)):2 w l smooth unique title "L=32"

set out
set terminal wxt enhanced
reset