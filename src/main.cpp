#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unistd.h>

#include "basicwarmup.h"
#include "exPushup.h"
#include "uart.h"
#include "player.h"
#include "workout.h"

#include "time.h"
/*
 compile using:

 g++ -Iheaders/ -o output src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp src/player.cpp src/workout.cpp -lvlc -lmpg123 -lm
*/

using namespace std;


int main(void)
{
    player sup("BM.mp3");
    
    sup.play();
    for(int i = 0;i<100;i++){
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    }
    sleep(2);
    for(int i = 0;i<100;i++){
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    cout << "Time now: " << sup.getTime() << endl;
    }
    cout << "Time 2: " << sup.getTime() << endl;
    sleep(30);
    cout << "Time 30: " << sup.getTime() << endl;
    
    cout << "startup with workout1.txt as name\n";
    workout blaworkout("workout.txt");
    cout << "the duration of the created workout is: " << blaworkout.getduration() << endl;


    std::cout << "Hello Obeast!" << std::endl;
    return 0;
}
