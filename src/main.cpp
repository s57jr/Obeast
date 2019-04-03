#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unistd.h>
#include <thread>

#include "basicwarmup.h"
#include "exPushup.h"
#include "uart.h"
#include "player.h"
#include "workout.h"
#include "pressure.h"
#include "uart.h"


#include "time.h"

using namespace std;
/*
 compile using:

g++ -Iheaders/ -o output -pthread src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp src/player.cpp src/workout.cpp src/expushup.cpp -lvlc -lmpg123 -lm -Wall


*/

std::mutex mtx;
uint16_t DataArray[45];

int uart0_filestream;
void callthread() {
  std::cout << "uart0_filestream address " << & uart0_filestream << std::endl;
  pressure letsgo;
  letsgo.datathread(uart0_filestream);

}


int main(void)
{

  	int i = 1;
    
   
  	while (i!=5){
  	
  	enum states { standby=1, idle=2, workout_s=3, playback_s=4, stop=5};
  	states statemachine = standby;
  	
  	cout << "start switch" << endl;
  	switch(i)
  	{
      case standby:
  		cout << "STANDBY..." << endl;
  		//cout  << "which state do you want to go to?" << endl;
  		cin >> i;
  		break;
  		
      case idle: 
  				cout << "IDLE..." << endl;
  		cout  << "which state do you want to go to?" << endl;
  		cin >> i;
     
     
  		break;
      case workout_s: 
              
  			cout << "WORKOUT..." << endl;
        
  		  cout  << "which workout do you want to play?" << endl;
  		  string workoutname;
        cin >> workoutname;
        
        std::thread t1(callthread);
        t1.detach();
        
        workoutname = "workouts/" + workoutname + ".txt";
        workout tmpworkout (workoutname);

        tmpworkout.runworkout();
        
        mtx.lock();
        for (int i = 0; i < 40; i++) {
          std::cout << "position " << i << " gives value: " << DataArray[i] << std::endl;
        }
        mtx.unlock();
        
        t1.~thread();
        
        std::cout << "exercises completed" << std::endl;
    
         i=5;
          
  		break;
     
//  	case playback_s:
//  		cout << "PLAYBACK..." << endl;
//  		cout  << "which state do you want to go to?" << endl;
//  		cin >> i;
//  		break;
  	}
  	}
   
    std::cout << "Hello Obeast!" << std::endl;
   
    return 0;
}
