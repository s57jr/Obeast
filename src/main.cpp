#include <iostream>
#include "basicwarmup.h"
#include "exPushup.h"
#include <string>
#include "uart.h"
#include "player.h"
#include <stdint.h>
#include <vector>
#include <unistd.h>
/*
 compile using:

 g++ -Iheaders/ -o output src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp src/player.cpp -lwiringPi
*/

using namespace std;

int main(void)
{
    player sup("BM.mp3");
    
    sup.play();
    sleep(30);

    std::cout << "Hello Obeast!" << std::endl;
    return 0;
}
