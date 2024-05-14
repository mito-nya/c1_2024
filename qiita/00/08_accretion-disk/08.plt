set term gif animate optimize delay 2 size 480,360
set output '08-ex.gif'

do for [i = 1:100 ] {
    set multiplot layout 2,1
    set yrange [0:1]
    plot "r1.data" u 1:i+1 w l title "areal density"
    plot "r2.data" u 1:i+1 w l title "angular momentum"
    }

unset multiplot
set out
set terminal wxt enhanced