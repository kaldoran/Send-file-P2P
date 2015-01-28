#!/bin/bash
# NICOLAS R
# 27 Janvier 2015

echo -e "\nClient : \n";
(cd ./Client && make $1);

echo -e "\nServer : \n";
(cd ./Server && make $1);

if ( [ "$1" != "clean" ] ); then 
	if ( [ -e "./Server/BIN/Server" ] && [ -e "./Client/BIN/Client" ] ); then
		./Server/BIN/Server
		./Client/BIN/Client
	else 
		echo "Can't launch the Bittorrent program, please re-run 'run.sh' or 'run.sh all'";
	fi;
fi;