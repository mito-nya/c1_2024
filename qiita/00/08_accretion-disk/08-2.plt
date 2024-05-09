reset
set terminal pngcairo
set out "08-2.png"
unset key

set multiplot layout 2,1
set yrange [0:3]
plot for [i=0:9] "r1.data" u 1:10*i+2 w l
set yrange [0:3]
plot for [i=0:9] "r2.data" u 1:10*i+2 w l

unset multiplot
set out
set terminal wxt enhanced