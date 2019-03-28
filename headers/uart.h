#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <iostream>

class UART
{
public:
    UART();
		
protected:
	vector<uint16_t> getSensorData();
	
};

#endif // UART_H
