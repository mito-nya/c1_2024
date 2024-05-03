set term gif animate optimize delay 0.2 size 480,360
set output 'movie7.gif'

set xrange [-10:10]
set yrange [-10:10]

do for [i = 1:19 ] {
   plot "r1.data" u 2*i-1:2*i
   }

set out
set terminal wxt enhanced