reset
set terminal pngcairo size 1080, 640
set out "01.png"
unset key

set palette model HSV functions gray,1,0.7
unset colorbox

PI = 3.14159265

set multiplot layout 2, 3

set xrange [0.:2.*PI]
set title "c=-1, nu=0.8"
plot for [i=0:10] sprintf("out_minus_08_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

set xrange [0.:2.*PI]
set title "c=-1, nu=1.0"
plot for [i=0:10] sprintf("out_minus_10_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

set xrange [0.:2.*PI]
set title "c=-1, nu=1.2"
plot for [i=0:10] sprintf("out_minus_12_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

set xrange [0.:2.*PI]
set title "c=+1, nu=0.8"
plot for [i=0:10] sprintf("out_plus_08_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

set xrange [0.:2.*PI]
set title "c=+1, nu=1.0"
plot for [i=0:10] sprintf("out_plus_10_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

set xrange [0.:2.*PI]
set title "c=+1, nu=1.2"
plot for [i=0:10] sprintf("out_plus_12_%04d.data", i*100) w l lc palette frac (150.+130.*i/9.)/360. 

unset multiplot
set out
set terminal wxt enhanced
reset