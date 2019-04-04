#!/bin/sh
g++ -Iheaders/ -o output -pthread src/main.cpp src/pressure.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/player.cpp src/workout.cpp src/expushup.cpp -lvlc -lmpg123 -lm -Wall