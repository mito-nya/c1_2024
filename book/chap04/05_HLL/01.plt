# Gnuplot script to plot orszag_tang_output.data with pm3d
set terminal pngcairo size 1024, 768 enhanced font 'Verdana,12'
set output 'orszag_tang_plot.png'

# Set labels
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Value'

# Set title
set title 'Orszag-Tang Vortex Solution'

# Set view (optional, can be adjusted for better perspective)
set view map

# Set color palette
set palette rgbformulae 33,13,10

# Enable color box on the right
set colorbox vertical

# Use pm3d mode
set pm3d at b

# Read the data from the file and plot
splot 'orszag_tang_output.data' using 1:2:3 with pm3d title 'Density'
