vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work xil_defaultlib -64 -incr \
"../../../bd/ceas_figure/ip/ceas_figure_pOR_0_0/sim/ceas_figure_pOR_0_0.v" \
"../../../bd/ceas_figure/ip/ceas_figure_pAND_0_0/sim/ceas_figure_pAND_0_0.v" \
"../../../bd/ceas_figure/ip/ceas_figure_bin2bcd_0_1/sim/ceas_figure_bin2bcd_0_1.v" \
"../../../bd/ceas_figure/ip/ceas_figure_bin2bcd_1_1/sim/ceas_figure_bin2bcd_1_1.v" \
"../../../bd/ceas_figure/ip/ceas_figure_numarator_59_0_1/sim/ceas_figure_numarator_59_0_1.v" \
"../../../bd/ceas_figure/ip/ceas_figure_numarator_59_1_1/sim/ceas_figure_numarator_59_1_1.v" \
"../../../bd/ceas_figure/sim/ceas_figure.v" \


vlog -work xil_defaultlib \
"glbl.v"

