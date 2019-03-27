#include <iostream>
#include "basicwarmup.h"
#include "exPushup.h"
#include <string>

/*
 compile using:

 g++ -Iheaders/ -o output src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp 
*/

using namespace std;

int main(void)
{

	int a = 6;
	string b = "hoi";
	basicWarmUp warmupExercise2(a,b);
	exPushup extrastrong();
	

    cout << "Hello Obeast!" << endl;
    return 0;
}
