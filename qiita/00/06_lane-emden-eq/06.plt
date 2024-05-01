set terminal png #ターミナルをpngに設定
set output "06.png" #graph.pngで出力


set xrange [0:10]
set yrange [0:1]
plot "r0.data" u 1:2 with lines
replot "r1.data" u 1:2 with lines
replot "r2.data" u 1:2 with lines
replot "r3.data" u 1:2 with lines
replot "r4.data" u 1:2 with lines
replot "r5.data" u 1:2 with lines

set out
set terminal wxt enhanced