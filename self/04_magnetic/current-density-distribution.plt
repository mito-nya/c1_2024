set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'current_density_distribution.png'

set title "Current Density Distribution"
set xlabel "y"
set ylabel "J_z"

B0 = 1.0
L = 1.0
c = 3.0e8

J_z(y) = -c*B0/(4*pi*L)*(1-tanh(y/L)**2)

set xrange [-10:10]
set yrange [-3e7:1e7]
set samples 1000

plot J_z(x) with lines title "J_z(y)"