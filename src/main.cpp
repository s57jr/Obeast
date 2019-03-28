#include <iostream>
#include "basicwarmup.h"
#include "exPushup.h"
#include <string>
#include "UART.h"
#include <stdint.h>

/*
 compile using:

 g++ -Iheaders/ -o output src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp -lwiringPi
*/

using namespace std;

int main(void)
{

	//int a = 6;
	//string b = "hoi";
	//basicWarmUp warmupExercise2(a,b);
	//exPushup extrastrong();
	UART letsgo;
	vector<uint16_t> singlesensordata
	singlesensordata = letsgo.getsensordata();
	std::cout << "sensordata 0 = " << singlesensordata[0] << std::endl;
	std::cout << "sensordata 1 = " << singlesensordata[1] << std::endl;

    std::cout << "Hello Obeast!" << std::endl;
    return 0;
}
