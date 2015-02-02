#!/bin/bash
# NICOLAS R
# 27 Janvier 2015

trap control_c SIGINT
PID=0;
control_c() {
    echo -e "\nBye Bye";
    kill -9 $PID;
    exit $?;
}

echo -e "\nClient : \n";
(cd ./Collector && make $1);

echo -e "\nBoss : \n";
(cd ./Boss && make $1);

if ( [ "$1" != "clean" ] ); then 
    if ( [ -e "./Boss/BIN/Server" ] && [ -e "./Collector/BIN/Client" ] ); then
        ./Boss/BIN/Server &
        PID=$!;

    else 
        echo "Can't launch the Bittorrent program, please re-run 'run.sh' or 'run.sh all'";
    fi;
fi;

while :; do
    echo -n ".";
    sleep 5;
done;