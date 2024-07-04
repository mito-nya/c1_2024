reset
set terminal pngcairo size 1080, 640
set out "01.png"
unset key

set multiplot layout 1, 2

set title "C_A/C_S=sqrt(0.5)"
plot "out_aw_a.data" w l, \
"out_fw_a.data" w l, \
"out_sw_a.data" w l

set title "C_A/C_S=2"
plot "out_aw_c.data" w l, \
"out_fw_c.data" w l, \
"out_sw_c.data" w l

unset multiplot
set out
set terminal wxt enhanced
reset