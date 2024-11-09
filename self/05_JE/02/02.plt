set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'curves_plot.png'

set xlabel 'X'
set ylabel 'Y'
set title 'Polar Curves Plot'
set grid
set size ratio -1

set xrange [-6:6]
set yrange [-6:6]

plot 'curve1_points.dat' using 1:2 with dots lc 'blue' title 'Curve 1', \
     'curve2_points.dat' using 1:2 with dots lc 'red' title 'Curve 2'
