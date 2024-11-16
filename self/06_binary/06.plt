# plot_potential.gnu

# L1 点でのポテンシャル値を読み込み
phi_L1 = -2.944798

set terminal pngcairo size 800,800 enhanced font 'Helvetica,12'
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

# PM3D を無効化して等高線のみを表示
# 等高線の色と線幅を splot コマンド内で指定
splot 'potential_data.dat' using 1:2:3 with lines linecolor rgb 'black' linewidth 2 notitle
