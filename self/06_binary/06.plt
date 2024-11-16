# plot_potential.gnu

# L1 点でのポテンシャル値を設定
phi_L1 = -2.944798

# 出力設定：PNG形式、サイズ800x800、フォントを'Sans'に変更
set terminal pngcairo size 800,800 enhanced font 'Sans,12'
set output 'equipotential_L1.png'

# 背景を白に設定
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb 'white' behind

# 軸やラベルを非表示
set size ratio -1
set xrange [-1:1]
set yrange [-1:1]
unset border
unset tics
unset xlabel
unset ylabel
unset key
unset title

# 等高線の設定
unset surface
set view map
set contour base
set cntrparam levels discrete phi_L1

# カラーバーを非表示
unset colorbox

# y=0 の直線を描画
set style line 1 lc rgb 'black' lw 1
set arrow from -1,0 to 1,0 nohead ls 1

# 質点の位置と質量を設定
x1 = -0.333333   # 恒星の位置（質量 M1）
x2 = 0.666667    # 惑星の位置（質量 M2）
M1 = 1           # 恒星の質量
M2 = 0.5         # 惑星の質量

# 質量に応じたポイントサイズを計算
ps1 = (M1 / (M1 + M2)) * 10    # 恒星のポイントサイズ
ps2 = (M2 / (M1 + M2)) * 10    # 惑星のポイントサイズ
ps_origin = 2               # 原点のポイントサイズ（固定）

# 質点を描画するためのラベル設定
# 恒星
set label 1 at x1,0 point pt 7 ps ps1 lc rgb 'black' front
# 惑星
set label 2 at x2,0 point pt 7 ps ps2 lc rgb 'black' front
# 原点
set label 3 at 0,0 point pt 7 ps ps_origin lc rgb 'black' front

# 等高線と質点のみを表示
splot 'potential_data.dat' using 1:2:3 with lines linecolor rgb 'black' linewidth 2 notitle
