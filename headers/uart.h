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
		
int getSensorData(int &uart0_filestream);
int init(int &uart0_filestream);


protected:
  std::vector<uint16_t> singlesensordata;
  
private:
  int uart0_filestream;
  std::vector<uint16_t> errorvector;
  bool sreceived;
  struct termios options;




};

#endif // UART_H