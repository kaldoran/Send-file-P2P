#!/bin/bash
# NICOLAS R
# 27 Janvier 2015

(cd ./Client && make);
(cd ./Server && make);

./Server/BIN/Server
./Client/BIN/Client