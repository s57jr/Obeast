#ifndef PRESSURE_H
#define PRESSURE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include "sensor.h"
#include <time.h>
#include <mutex>

extern std::mutex mtx;
extern uint16_t DataArray[45];


struct XX  {
	uint16_t nbr; 
	uint16_t value; 
	}; 

class pressure : public UART 
{
public:
    pressure();
    ~pressure();
    void datathread(int &uart0_filestream);
    
    
protected: 
	void getData(int &uart0_filestream); 

private: 

	struct XX singleSensor; 
	
};

#endif // PRESSURE_H