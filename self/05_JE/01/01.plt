set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'combined_curve.png'

set xlabel 'X'
set ylabel 'Y'
set title 'Combined Polar Curves'
set grid
set size ratio -1

set xrange [-2:2]
set yrange [-2:2]

plot 'curve1.dat' using 1:2 with lines linewidth 2 linecolor 'blue' notitle, \
     'curve2.dat' using 1:2 with lines linewidth 2 linecolor 'red' notitle
