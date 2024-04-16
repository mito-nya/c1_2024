set term gif animate optimize delay 2 size 480,360
set output 'movie-1-2.gif'

do for [i = 0:150 ] {
   plot "r12.data" u 1:i+2
   }

set out
set terminal wxt enhanced