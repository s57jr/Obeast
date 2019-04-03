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

struct product {
    int hour;
    int minute;
    std::string name;
    } ;

product parseworkouts(std::string filename)
{
    
    
    std::string line,line2;
	  ifstream file;
    std::string filelocation = "workout/" + filename + ".txt";
	  file.open(filename);
	  if (file.is_open()) {
 	  getline(file, timestamp);
    line2 = line;
    file.close();
    }
    
    line.erase(0,6); 	
    line.erase(3,5);
    line2.erase(0,9);
    product testworkout;
    workoutparse.hour = stoi(line);
    workoutparse.minute = stoi(line2);
    workoutparse.name = filelocation;
    return workoutparse
}



int main(void)
{
    std::vector<product> workouttimes;
    
    workouttime = parseworkouts(testworkout);
    workouttimes.push_back(testworkout);

  	int i = 1;
    
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    int hour_now = local_tm.tm_hour;
    int minute_now = local_tm.tm_min;
    std::string workouttorun;
    // if statements for certain time stamps
    
    
    

    
    
    
    
    
   
while (i!=5){
  	
enum states { standby=1, idle=2, workout_s=3, playback_s=4, stop=5};
states statemachine = standby;
  	
   
   
   
  	cout << "start switch" << endl;
  	switch(i)
  	{
      case standby:
  		std::cout << "STANDBY..." << endl;
  		//cout  << "which state do you want to go to?" << endl;
  		//cin >> i;
  		break;
  		
      case idle: 
      
      
      for ( int i = 0;i<workouttimes.length();i++){
      if (workouttimes[i].minute == minute_now && workouttimes[i].hour == hour_now)
      { i = 3;
      workouttorun = workouttimes[i].name;
      }
      }
      
      
       sleep(1);        
    
     
     
  		break;
      case workout_s: 
              
  			std::cout << "WORKOUT..." << endl;
        
  		  //std::cout  << "which workout do you want to play?" << std::endl;

        
        std::thread t1(callthread);
        t1.detach();
        
        
        workout tmpworkout (workouttorun);

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
