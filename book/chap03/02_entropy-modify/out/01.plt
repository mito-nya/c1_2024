reset
set terminal pngcairo size 720, 640
set out "01.png"
unset key

set multiplot layout 2, 2

set xlabel "x"
set ylabel "rho"
set xrange [-0.5:0.5]
plot "out.data" u 1:2 

set xlabel "x"
set ylabel "M"
set xrange [-0.5:0.5]
plot "out.data" u 1:3 

set xlabel "x"
set ylabel "Entropy"
set xrange [-0.5:0.5]
plot "out.data" u 1:4 

set xlabel "x"
set ylabel "v-Cs"
set xrange [-0.5:0.5]
plot "out.data" u 1:5 

unset multiplot
set out
set terminal wxt enhanced
reset