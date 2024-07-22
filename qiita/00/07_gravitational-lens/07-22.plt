set terminal pngcairo #ターミナルをpngに設定
set output "07-22.png" #graph.pngで出力
unset key

set xrange [-10:10]
set yrange [-10:10]
set size sq

set parametric
plot [0:2*pi] 2*cos(t),2*sin(t) linecolor 'black', for [i=1:15] "r0.data" u 2*i-1:2*i with lines linecolor 'gray', for [i=16:29] "r0.data" u 2*i-1:2*i with lines linecolor 'orange'




set out
set terminal wxt enhanced