#include <iostream>
#include "basicwarmup.h"

/*
 compile using:

 g++ -Iheaders/ -o wazzaaappp src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp
 src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp
*/

using namespace std;

int main()
{

    basicWarmUp warmupEcercise;

    cout << "Hello Obeast!" << endl;
    return 0;
}
