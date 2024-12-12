reset
unset multiplot
set terminal pngcairo size 720, 640
set out "02.png"
set multiplot layout 2,1
set style fill solid border lc rgb "black"

set title sprintf("t=%d", 85960)
set xrange [0.5:6.5]    
set yrange [0:30]
set boxwidth 0.8 relative
plot "./out/out_chip_085960.data" using 1:2:xtic(1) with boxes lw 2 lc rgb "light-cyan" notitle

set xrange [0.5:30.5]
set yrange [0:0.2]
set boxwidth 1. relative
plot "./out/out_dist_085960.data" using 1:2:xtic(1) with boxes lw 2 lc rgb "light-cyan" notitle

unset multiplot
set out
set terminal wxt enhanced