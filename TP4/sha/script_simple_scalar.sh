#!/bin/bash

SIM_PROF=/usr/ensta/pack/simplescalar-3v0d/simplesim-3.0/sim-profile
SIM_OUTORDER=/usr/ensta/pack/simplescalar-3v0d/simplesim-3.0/sim-outorder

PRG_NAME="sha_driver"
INPUT_FILE="input_small.asc"
PRG_SS="$PRG_NAME.ss"

REDIR_PROF="-redir:sim ./output/$PRG_NAME-sim-prof.txt -redir:prog ./output/$PRG_NAME-out.txt"
REDIR_OUTORDER="-redir:sim ./output/$PRG_NAME-sim-outorder.txt -redir:prog ./output/$PRG_NAME-out.txt"

PROF_FLAGS="-brprof true -iclass true -segprof true"

A7_FLAGS="-issue:inorder true"

$SIM_PROF $PROF_FLAGS $REDIR_PROF $PRG_SS $INPUT_FILE

# $SIM_OUTORDER $A7_FLAGS $REDIR_OUTORDER $PRG_SS $INPUT_FILE


