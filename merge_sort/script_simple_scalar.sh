#!/bin/bash

SIM_OUTORDER=/usr/ensta/pack/simplescalar-3v0d/simplesim-3.0/sim-outorder

PRG_SS="merge_sort.ss"
REDIR_OUT_SIMU="-redir:sim simu.out"
OPTIONS="-fetch:ifqsize 4 -decode:width 4 -issue:width 4 -issue:inorder true -commit:width 4 -ruu:size 16 -lsq:size 8 -res:memport 2"

$SIM_OUTORDER $OPTIONS $REDIR_OUT_SIMU $PRG_SS