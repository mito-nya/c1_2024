reset

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'magnetic_field_lines_2.png'

set title "Magnetic Field Lines in XY Plane"
set xlabel "x"
set ylabel "y"

# special filename "++" のときは
# urange, vrange で描画範囲の設定
set urange [-5.5:5.5]
set vrange [-5.5:5.5]
set size ratio 1

# x 軸方向のサンプル数
set samples 12
# y 軸方向のサンプル数
set isosamples 12

# 表示範囲の設定
set xrange [-5.8:5.8]
set yrange [-5.8:5.8]
set xtics 1
set ytics 1
set grid

# ベクトルの長さ調整用
scaling = 0.1

# 定数
B0 = 1.0
L = 4.0

# 磁場
Bx(x, y) = -B0*(y/L)
By(x, y) = 1
B(x, y) = sqrt(Bx(x, y)**2+By(x, y)**2)

plot "++" using 1:2:(Bx($1,$2)):(By($1,$2)):(B($1,$2)) \
    w vec lc palette lw 2 filled head notitle