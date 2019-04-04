#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unistd.h>
#include <thread>
#include <fstream>

#include "exPushup.h"
#include "uart.h"
#include "player.h"
#include "workout.h"
#include "pressure.h"



#include "time.h"

#define THRSHLD 20000

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
    
    std::string filelocation = "workouts/" + filename + ".txt";
	  file.open(filelocation);
	  if (file.is_open()) {
 	  getline(file, line);
    line2 = line;
    file.close();
    }
    
    line.erase(8,3); 
    line.erase(0,6);
    line2.erase(0,9);
    product workoutparse;
    workoutparse.hour = stoi(line);
    workoutparse.minute = stoi(line2);
    workoutparse.name = filelocation;
    return workoutparse;
}


int readSensorData(uint16_t *data){  //returns average value
    int avg=0;
    mtx.lock();
    for (int i = 0; i < 40; i++) {
      std::cout << "position " << i << " gives value: " << DataArray[i] << std::endl;
      data[i] = DataArray[i];
      avg+=DataArray[i];
    }
    mtx.unlock();
    
    return avg/40;
}


int main(void)
{
    std::vector<product> workouttimes;
    product workouttime;
    workouttime = parseworkouts("testworkout");
    workouttimes.push_back(workouttime);
  	int i = 2;
    int hour_now;
    int minute_now;
    std::string workouttorun;
    uint16_t sensorData[45];
    player *playit;
    
    int notified =0;
    
    
    cout << "hourW: " << workouttime.hour << endl;
    cout << "minW: " << workouttime.minute << endl;
    
    std::thread t1(callthread);
    t1.detach();  //destroy if nothing happens
   
while (i!=5){
  	
enum states { standby=1, idle=2, workout_s=3, playback_s=4, stop=5};
states statemachine = standby;
  	
std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
time_t tt = std::chrono::system_clock::to_time_t(now);
tm local_tm = *localtime(&tt);
hour_now = local_tm.tm_hour;
minute_now = local_tm.tm_min;
   
   
  //	cout << "start switch" << endl;
  	switch(i)
  	{
      case standby:
  	//	std::cout << "STANDBY..." << endl;
  		//cout  << "which state do you want to go to?" << endl;
  		//cin >> i;
  		break;
  		
      case idle: 
             
       
      
      for ( int a = 0;a<workouttimes.size();a++){
        if (workouttimes[a].minute == minute_now && workouttimes[a].hour == hour_now)
        { 
          if(notified == 0){
            playit = new player("sounds/StartWorkout.mp3");
            playit->setVolume(20);
            playit->play();
            sleep(2);
            while(playit->isPlaying()){
              sleep(1);
            }
          
            delete playit;
            notified = 1;
          }
        
          int c= readSensorData(sensorData);
          std::cout << "Sensor data : " << c << std::endl;
          if(c > THRSHLD){
            i=3;
            workouttorun = workouttimes[a].name;
          }
        }
      }
      
      sleep(1);        

  		break;
      case workout_s: 
              
  			std::cout << "WORKOUT..." << endl;
        
  		  //std::cout  << "which workout do you want to play?" << std::endl;
        
        
        workout tmpworkout (workouttorun);

        tmpworkout.runworkout();
        
        readSensorData(sensorData);
        
        
        
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
    t1.~thread();
    std::cout << "Hello Obeast!" << std::endl;
   
    return 0;
}
