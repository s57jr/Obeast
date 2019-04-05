#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <mpg123.h>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <math.h> 


#include "uart.h"
#include "player.h"
#include "workout.h"
#include "pressure.h"

#include "time.h"


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

