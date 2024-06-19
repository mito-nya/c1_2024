set terminal gif animate delay 10
set output "simulation.gif"

set xrange [0:2]
set yrange [0:2]

do for [i=0:999] {
    set title sprintf("Step %03d", i)
    plot sprintf("output_step_%03d.dat", i) using 1:2:(($3==1)?1:0) with points pointtype 7 pointsize 1 linecolor variable notitle
}
