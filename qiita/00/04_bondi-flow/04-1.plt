set terminal png #ターミナルをpngに設定
set output "04-1.png" #graph.pngで出力


set xrange [0:10]

set multiplot layout 2,1  #multiplotの開始、縦2横1自動配置

set yrange [1:3]
plot "r1.data" u 1:2 with lines
set yrange [0:1]
plot "r1.data" u 1:3 with lines
set yrange [1:3]
plot "r2.data" u 1:2 with lines
set yrange [0:1]
plot "r2.data" u 1:3 with lines
set yrange [1:3]
plot "r3.data" u 1:2 with lines
set yrange [0:1]
plot "r3.data" u 1:3 with lines
set yrange [1:3]
plot "r4.data" u 1:2 with lines
set yrange [0:1]
plot "r4.data" u 1:3 with lines
set yrange [1:3]
plot "r5.data" u 1:2 with lines
set yrange [0:1]
plot "r5.data" u 1:3 with lines

unset multiplot           #multiplotの終了

set out
set terminal wxt enhanced