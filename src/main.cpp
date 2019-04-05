#include "main.h"

#define THRSHLD 20000

using namespace std;
/*
 compile using:

g++ -Iheaders/ -o output -pthread src/main.cpp src/heartrate.cpp src/pressure.cpp src/sensor.cpp src/exercisebase.cpp src/uart.cpp src/dsp.cpp src/bluetooth.cpp src/basicwarmup.cpp src/player.cpp src/workout.cpp src/expushup.cpp -lvlc -lmpg123 -lm -Wall


*/



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
            playit = new player("sounds/Random/StartWorkout.mp3");
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
