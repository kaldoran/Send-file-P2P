#!/bin/bash
# NICOLAS R
# 22 Mars 2015

# This script start from 1 to $1 collector

if [ ! -n "$1" ]; then 
    echo -e "Start from 1 to N collector\nTo start N collector use : ./flood_boss.sh N\nWith N > 1";
else 
    for i in $(seq 1 $1); do
        ../Collector/BIN/Collector moveFile.bat.ndex $(( 42777 + $i )) sharing &
    done;

fi