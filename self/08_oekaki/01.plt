reset

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'fig1.png'

# set title "電場のベクトル場"
set xlabel "x"
set ylabel "y"

# special filename "++" のときは
# urange, vrange で描画範囲の設定
set urange [0:pi]

# 表示範囲の設定
set xrange [-1.7:1.1]
set yrange [-0.4:1.4]
set grid
set size ratio -1

# パラメータ設定
N = 36
set samples N

# ベクトルの長さ調整用
scaling = 0.05

# 電場
E(theta) = (sin(theta/2.)**3-cos(theta/2)**3)/(cos(theta/2)**2*sin(theta/2)**2)
Ex(theta) = E(theta)*cos(theta)
Ey(theta) = E(theta)*sin(theta)

plot "++" using (cos($1)):(sin($1)):(Ex($1)*scaling):(Ey($1)*scaling):(abs(E($1))*scaling) \
    w vec lc palette lw 2 filled head notitle