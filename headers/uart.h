#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <iostream>
#include <vector>

class UART
{
public:
    UART();
		
 
    std::vector<uint16_t> getSensorData();
	
};

#endif // UART_H
