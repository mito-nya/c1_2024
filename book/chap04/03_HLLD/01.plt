reset
set terminal pngcairo size 840, 1080
set out "01.png"
unset key

set multiplot layout 3, 2 title "MHD"

set xlabel "x"
set ylabel "rho"
set xrange [-0.5:0.5]
plot "out.data" u 1:2 

set xlabel "x"
set ylabel "p"
set xrange [-0.5:0.5]
plot "out.data" u 1:3

set xlabel "x"
set ylabel "u"
set xrange [-0.5:0.5]
plot "out.data" u 1:4

set xlabel "x"
set ylabel "v"
set xrange [-0.5:0.5]
plot "out.data" u 1:5 

set xlabel "x"
set ylabel "By"
set xrange [-0.5:0.5]
plot "out.data" u 1:6

unset multiplot
set out
set terminal wxt enhanced
reset