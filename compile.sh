#!/bin/sh
g++ -Iheaders/ -o output src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp src/player.cpp src/workout.cpp -lvlc -lmpg123 -lm -lrt
