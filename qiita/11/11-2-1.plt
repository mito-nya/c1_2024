set term gif animate optimize delay 2 size 480,360
set output 'movie-2-1.gif'

do for [i = 0:1000 ] {
   set yrange [0:1]
   plot "r21.data" u 1:i+2
   }

set out
set terminal wxt enhanced