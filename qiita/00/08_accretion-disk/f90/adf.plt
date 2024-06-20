reset
set term gif animate optimize delay 2 size 480,360
set output 'ad-f.gif'
unset key
set logscale xy
set xrange [0.001: 1.]
set yrange [1e-4: 1e4]
do for [i = 1:1000 ] {
    set multiplot layout 2,1
    plot sprintf("%05d.dat", i) u 1:2 w l
    plot sprintf("%05d.dat", i) u 1:3 w l
}

unset multiplot
set out
set terminal wxt enhanced
reset