#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <iostream>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>			//Used for UART
#include <vector>


class UART
{
public:
    UART();
    ~UART();
		

	std::vector<uint16_t> getSensorData(int uart0_filestream);
	
private:
int state; 
//int uart0_filestream;
std::vector<uint16_t> errorvector;
bool sreceived;
 
};

#endif // UART_H