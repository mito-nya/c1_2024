reset
set terminal pngcairo size 1280, 840
set out "02-4slide.png"
unset key

set multiplot layout 2, 3 title "2nd order TVD (minmod + midpoint)"

set xlabel "x"
set ylabel "rho"
set xrange [-0.5:0.5]
plot "out.data" u 1:2 

set xlabel "x"
set ylabel "p"
set xrange [-0.5:0.5]
plot "out.data" u 1:3

set xlabel "x"
set ylabel "v"
set xrange [-0.5:0.5]
plot "out.data" u 1:4

set xlabel "x"
set ylabel "epsilon"
set xrange [-0.5:0.5]
plot "out.data" u 1:5 

set xlabel "x"
set ylabel "M"
set xrange [-0.5:0.5]
plot "out.data" u 1:6

set xlabel "x"
set ylabel "Entropy"
set xrange [-0.5:0.5]
plot "out.data" u 1:7 

unset multiplot
set out
set terminal wxt enhanced
reset