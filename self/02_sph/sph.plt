set terminal gif animate delay 10
set output "simulation.gif"

set xrange [0:1]
set yrange [0:1]

do for [i=0:99] {
    set title sprintf("Step %03d", i)
    plot sprintf("output_step_%03d.dat", i) with points pointtype 7 pointsize 1 notitle
}
