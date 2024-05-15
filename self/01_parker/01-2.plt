set terminal pngcairo size 1560, 1280 # ターミナルをpngに設定
set output "01-2.png" # graph.pngで出力
unset key
set ylabel 'V/c_{sc}'
set xlabel 'r/r_c'

set contour
set view 0,0,1,1
unset key
unset surface
set isosamples 400,400
set cntrparam levels incremental -0.4, 0.08, 0.4

array gamma_list[6] = [1.00001, 1.25, 1.4, 1.5, 1.6, 1.66667]

set multiplot layout 3,2

do for [i=1:6] {
    gamma = gamma_list[i]
    g(x,y) = y**(gamma+1.) - (4./x + (5-3*gamma)/(gamma-1))*y**(gamma-1.) + 2.*x**(2.-2.*gamma)/(gamma-1.)
    set table sprintf("0%d.data", i)
    splot [0.1:4][0.1:2] g(x,y)
    unset table
    set title sprintf("{/Symbol G}=%f", gamma)
    set title font"Arial,24"
    plot sprintf("0%d.data", i) u 1:2 w l lc 'black'
}

unset multiplot

set out
set terminal wxt enhanced
