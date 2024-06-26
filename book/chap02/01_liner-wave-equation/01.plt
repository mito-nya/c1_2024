reset
set terminal pngcairo size 720, 640
set out "01.png"
unset key

set multiplot layout 2, 2

set title 'FTBS, $\nu=0.8$'
set yrange [-0.2: 2]
plot "out_FTBS_08.data" w l linecolor 'black' lw 2, \
"out_FTBS_08.data" linecolor 'black', \
"as_08.data" w l linecolor 'black'

set title 'FTBS, $\nu=1.2$'
set yrange [-0.2: 2.7]
plot "out_FTBS_12.data" w l linecolor 'black' lw 2, \
"out_FTBS_12.data" linecolor 'black', \
"as_12.data" w l linecolor 'black'

set title 'FTFS, $\nu=0.8$'
set yrange [-25: 20]
plot "out_FTFS_08.data" w l linecolor 'black' lw 2, \
"out_FTFS_08.data" linecolor 'black', \
"as_08.data" w l linecolor 'black'

set title 'FTCS, $\nu=0.8$'
set yrange [-0.2: 2.2]
plot "out_FTCS_08.data" w l linecolor 'black' lw 2, \
"out_FTCS_08.data" linecolor 'black', \
"as_08.data" w l linecolor 'black'

unset multiplot
set out
set terminal wxt enhanced
reset