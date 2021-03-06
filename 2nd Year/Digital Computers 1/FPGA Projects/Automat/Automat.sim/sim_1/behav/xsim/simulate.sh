#!/bin/bash -f
# ****************************************************************************
# Vivado (TM) v2020.2 (64-bit)
#
# Filename    : simulate.sh
# Simulator   : Xilinx Vivado Simulator
# Description : Script for simulating the design by launching the simulator
#
# Generated by Vivado on Tue Jun 01 21:26:24 EEST 2021
# SW Build 3064766 on Wed Nov 18 09:12:47 MST 2020
#
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
#
# usage: simulate.sh
#
# ****************************************************************************
set -Eeuo pipefail
# simulate design
echo "xsim sim1_behav -key {Behavioral:sim_1:Functional:sim1} -tclbatch sim1.tcl -protoinst "protoinst_files/automat_V1.protoinst" -log simulate.log"
xsim sim1_behav -key {Behavioral:sim_1:Functional:sim1} -tclbatch sim1.tcl -protoinst "protoinst_files/automat_V1.protoinst" -log simulate.log

