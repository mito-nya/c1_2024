reset
set terminal pngcairo
set out "adf-cap.png"
unset key

set palette model HSV functions gray,1,0.7
unset colorbox

set logscale xy
set xrange [0.001: 1.]
set yrange [1e-4: 1e4]

# set multiplot layout 2,1
plot for [i=0:10] sprintf("%05d.dat", 10*i) u 1:2 w l lc palette frac (150.+130.*i/9.)/360.
# plot for [i=0:10] sprintf("%05d.dat", 10*i) u 1:3 w l lc palette frac (150.+130.*i/9.)/360.
# unset multiplot
set out
set terminal wxt enhanced