reset
set terminal pngcairo size 840, 420
set out "01.png"

set multiplot layout 1, 2

set title "t=0.40"
set xlabel "x"
set ylabel "u"
set xrange [-0.5:0.5]
set yrange [-1.05:1.05]
plot "out_1st_40.data" w lp title "1次精度", \
"out_heun_40.data" w lp title "2次精度", \
"out_as_40.data" w l title "厳密解"

set title "t=0.55"
set xlabel "x"
set ylabel "u"
set xrange [-0.5:0.5]
set yrange [-1.05:1.05]
plot "out_1st_55.data" w lp title "1次精度", \
"out_heun_55.data" w lp title "2次精度", \
"out_as_55.data" w l title "厳密解"

unset multiplot
set out
set terminal wxt enhanced
reset