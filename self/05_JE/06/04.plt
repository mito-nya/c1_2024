set terminal pngcairo size 1200, 1000 enhanced font 'Arial,14'
set output 'all_combinations_polar.png'

# マルチプロットの設定
set multiplot layout 2,2 rowsfirst

# 共通の設定
set size ratio -1
set xrange [-5:5]
set yrange [-5:5]
unset grid        # グリッド線を消去
unset border      # 枠線を消去
unset xtics       # x軸の目盛りを消去
unset ytics       # y軸の目盛りを消去
unset xlabel      # x軸のラベルを消去
unset ylabel      # y軸のラベルを消去
unset key         # 凡例（レジェンド）を消去
unset colorbox    # カラーボックスを消去（必要な場合）


# 左上のプロット（組み合わせ①）
# set title "1"
unset key
plot 'curve1_1.dat' using 1:2 lc 'blue', \
     'curve1_2.dat' using 1:2 lc 'red'

# 右上のプロット（組み合わせ②）
# set title "2"
unset key
plot 'curve1_1.dat' using 1:2 lc 'red', \
     'curve1_2.dat' using 1:2 lc 'blue'

# 左下のプロット（組み合わせ③）
# set title "3"
unset key
plot 'curve3_1.dat' using 1:2 lc 'blue', \
     'curve3_2.dat' using 1:2 lc 'red'

# 右下のプロット（組み合わせ④）
# set title "4"
unset key
plot 'curve3_1.dat' using 1:2 lc 'red', \
     'curve3_2.dat' using 1:2 lc 'blue'

unset multiplot
