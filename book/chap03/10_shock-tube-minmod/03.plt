reset
set terminal pngcairo size 480, 480
set out "03.png"
unset key

set title "2nd order TVD (minmod + midpoint)"

set xlabel "x"
set ylabel "rho"
set xrange [-0.5:0.5]
plot "out.data" u 1:2 

set out
set terminal wxt enhanced
reset