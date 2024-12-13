reset
set term gif animate optimize delay 2 size 840,480
set output '01.gif'
set style fill solid border lc rgb "black"

do for [time = 0:8596] {
    set multiplot layout 1,2
    set title sprintf("t=%06d", time*10)
    set xrange [0.5:6.5]    
    set yrange [0:30]
    set boxwidth 0.8 relative
    plot sprintf("./out/out_chip_%06d.data", time*10) using 1:2:xtic(1) with boxes lw 2 lc rgb "light-cyan" notitle

    set xrange [0.5:30.5]
    set yrange [0:0.2]
    set boxwidth 1. relative
    plot sprintf("./out/out_dist_%06d.data", time*10) using 1:2:xtic(1) with boxes lw 2 lc rgb "light-cyan" notitle
}

unset multiplot
set out
set terminal wxt enhanced