#include "uart.h"
#include <vector>
#include <stdint.h>
#include <iostream>
#include <errno.h>
#include <wiringSerial.h>


UART::UART()
{
    std::cout << "Hello UART!" << std::endl;
}

UART::getSensorData();
{
  int fd ;

  if((fd=serialOpen("/dev/ttyS0",9600))<0){
    fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    return 1;
  }
int i=1;
int k=0;
std::vector<uint16_t> singlesensordata;
singlesensordata.clear();
uint16_t datavalue;
uint8_t sensornumber;
char serialdata;


  for (;;){
	serialdata=serialGetchar(fd);
	switch(i) {
 	case 1 : 
		//s received from serialdata
		if (serialdata==115){
		std::cout<<"case 1 : " << serialdata <<  std::endl;	
		i=2;
		}
		break;       // and exits the switch
	case 2 :
		if (serialdata==116){
			i=3;
		}
		else if (serialdata==115){
		i=2;
		}
		else i=1;
		std::cout<<"case 2: " << serialdata << std::endl;
		break;
	case 3 :
		sensornumber=serialdata;
		singlesensordata.push_back(sensornumber);
		std::cout << "case 3: " << singlesensordata[0] << std::endl;
		i=4;
		break;
	case 4 :
		datavalue = (serialdata<<8);
		std::cout << "case 4: " << datavalue << std::endl;
		i=5;
		break;
	case 5 :
		datavalue = datavalue | serialdata;
		singlesensordata.push_back(datavalue);
		std::cout << "case 5: " << singlesensordata[1] << std::endl;
		serialClose(fd);
 		return singlesensordata;
	}
  }
 

}

	
	
	
	

