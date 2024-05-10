reset
set terminal pngcairo
set out "08-2.png"
unset key

set palette model HSV functions gray,1,1
unset colorbox

set multiplot layout 2,1
set yrange [0:0.6]
plot for [i=0:9] "r1.data" u 1:1*i+2 w l lc palette frac (150.+130.*i/9.)/360.
set yrange [0:0.6]
plot for [i=0:9] "r2.data" u 1:1*i+2 w l lc palette frac (150.+130.*i/9.)/360.

unset multiplot
set out
set terminal wxt enhanced