set contour
set view 0,0,1,1
unset key
unset surface
set isosamples 400,400
g(x,y) = y**(gamma+1.)-(4./x+(5-3*gamma)/(gamma-1))*y**(gamma-1.)+2.*x**(2.-2.*gamma)/(gamma-1.)
gamma=1.5
set cntrparam levels incremental -0.4, 0.08, 0.4
set table "01.data"
splot [0:4][0:2] g(x,y)
unset table

set terminal pngcairo #ターミナルをpngに設定
set output "01.png" #graph.pngで出力
unset key

set ylabel 'V/c_{sc}'
set xlabel 'r/r_c'
set title '{/Symbol G}=1.5'
plot for [i=1:9] "01.data" u 1:2 w l lc 'black'

set out
set terminal wxt enhanced