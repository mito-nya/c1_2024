set terminal pngcairo #ターミナルをpngに設定
set output "07-v2-42.png" #graph.pngで出力
unset key

set title "初期値をr～10000, 光路の幅をさらに狭く"

set xrange [-10:10]
set yrange [-10:10]
set size sq

set parametric
plot [0:2*pi] 2*cos(t),2*sin(t) linecolor 'black', for [i=1:3] "rv242.data" u 2*i-1:2*i with lines linecolor 'gray', for [i=4:7] "rv242.data" u 2*i-1:2*i with lines linecolor 'orange'

set out
set terminal wxt enhanced