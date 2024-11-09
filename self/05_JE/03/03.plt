set terminal pngcairo size 1200, 1000 enhanced font 'Arial,14'
set output 'all_combinations_polar.png'

# マルチプロットの設定
set multiplot layout 2,2 rowsfirst

# 共通の設定
set size ratio -1
set xlabel 'X'
set ylabel 'Y'
set xrange [-6:6]
set yrange [-6:6]
set grid

# 左上のプロット（組み合わせ①）
# set title "①"
unset key
plot 'curve1_1.dat' using 1:2 lc 'blue', \
     'curve1_2.dat' using 1:2 lc 'red'

# 右上のプロット（組み合わせ②）
# set title "②"
unset key
plot 'curve2_1.dat' using 1:2 lc 'blue', \
     'curve2_2.dat' using 1:2 lc 'red'

# 左下のプロット（組み合わせ③）
# set title "③"
unset key
plot 'curve3_1.dat' using 1:2 lc 'blue', \
     'curve3_2.dat' using 1:2 lc 'red'

# 右下のプロット（組み合わせ④）
# set title "④"
unset key
plot 'curve4_1.dat' using 1:2 lc 'blue', \
     'curve4_2.dat' using 1:2 lc 'red'

unset multiplot
