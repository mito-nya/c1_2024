reset
set terminal pngcairo
set out "00.png"

set xlabel "x"
set ylabel "u"
set xrange [-0.5:0.5]
set yrange [-0.05:1.05]
plot "out_00.data" w l title "厳密解", \
"out_01.data" w lp title "1次精度", \
"out_02.data" w lp title "2次精度 (minmod)", \
"out_03.data" w lp title "2次精度 (superbee)"

set out
set terminal wxt enhanced
reset