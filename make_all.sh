#!/bin/bash
# NICOLAS R
# 22 Mars 2015

echo -e "\nMake Collector : \n";
(cd ./Collector && make $1);

echo -e "\nMake Boss : \n";
(cd ./Boss && make $1);

echo -e "\nMake Generator : \n";
(cd ./Generator && make $1);