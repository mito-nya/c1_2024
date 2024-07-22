set terminal pngcairo #ターミナルをpngに設定
set output "07-22-v2.png" #graph.pngで出力
unset key

set xrange [-10:10]
set yrange [-10:10]
set size sq

set parametric
plot [0:2*pi] 2*cos(t),2*sin(t) linecolor 'black', "r0.data" with lines linecolor 'gray'

set out
set terminal wxt enhanced