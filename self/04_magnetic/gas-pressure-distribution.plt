set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'gas_pressure_distribution.png'

set title "Gas Pressure Distribution"
set xlabel "y"
set ylabel "P_{gas}"

B0 = 1.0
L = 1.0

P_gas(y) = (B0**2 / (8 * pi)) * (tanh(y / L)**2 - 1)

set xrange [-10:10]
set yrange [-0.06:0.02]
set samples 1000

plot [-10:10] P_gas(x) with lines title "P_{gas}(y)"
