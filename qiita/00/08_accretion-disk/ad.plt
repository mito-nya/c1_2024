reset
set term gif animate optimize delay 2 size 480,360
set output 'ad-1.gif'
set logscale xy
set xrange [0.001: 1.]
set yrange [0.01: 3.]
do for [i = 1:100 ] {
    set multiplot layout 2,1
    plot "r1.data" u 1:10*i+1 w l title "areal density"
    plot "r2.data" u 1:10*i+1 w l title "angular momentum"
    }

unset multiplot
set out
set terminal wxt enhanced
reset