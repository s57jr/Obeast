#include "uart.h"

UART::UART()
{
    std::cout << "Hello UART!" << std::endl;
    state = 1;
    
 //   int uart0_filestream = -1;
	  errorvector.push_back(99);
    sreceived = false;
    
  //	uart0_filestream = open("/dev/ttyS0", O_RDONLY | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
  //	if (uart0_filestream == -1)
  //	{
  //		//ERROR - CAN'T OPEN SERIAL PORT
  //		  printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
   //     close(uart0_filestream);
  //	}
   
  
   
   std::cout << "finished setting up" << std::endl;
    
    }
    
UART::~UART()  
    {
    //close(uart0_filestream);
    }
  


std::vector<uint16_t> UART::getSensorData(int uart0_filestream)
{

std::vector<uint16_t> singlesensordata;
singlesensordata.clear();
uint16_t datavalue;
uint8_t sensornumber;

   //std::cout << "before the if";
if (uart0_filestream != -1)
    //std::cout << ".. and now after..";

		{
			// Read up to 255 characters from the port if they are there
			unsigned char rx_buffer[1];
			int rx_length = read(uart0_filestream, (void*)rx_buffer, 1);		//Filestream, buffer to store in, number of bytes to read (max)
			//int rx_length = read(uart0_filestream, rx_buffer, 1);
      
      //std::cout << rx_buffer << " - ";
      //std::cout << rx_length << " ";
      //std::cout << "na de read function";
      if (rx_length < 0)
			{
        //close(uart0_filestream);
				//std::cout << "rx_length is smaller than 0" << std::endl;
        return errorvector;
				
				//An error occured (will occur if there are no bytes)
			}
			else if (rx_length == 0)
			{
        //close(uart0_filestream);
				//std::cout << "no data waiting rx_length == 0" << std::endl;
        return errorvector;
				
				//No data waiting
			}
			else {
      std::cout << "character received..." << rx_buffer << std::endl;
				//Bytes received
				//rx_buffer[rx_length] = '\0';
				//printf("%i bytes read : %s\n", rx_length, rx_buffer);
				char serialdata = *rx_buffer;
       
				switch(state) 
				{
					case 1 : 
						//s received from serialdata
						if (serialdata==115){
					            sreceived = true;                     
						std::cout<<"case 1 : " << serialdata <<  std::endl;	
						state=2;
						}
						return errorvector;       // and exits the switch
					case 2 :
						if (serialdata==116){
							state=3;
						}
						else if (serialdata==115){
						state=2;
						}
						else state=1;
						std::cout<<"case 2: " << serialdata << std::endl;
						return errorvector;
					case 3 :
						sensornumber=serialdata;
						singlesensordata.push_back(sensornumber);
						std::cout << "case 3: " << singlesensordata[0] << std::endl;
						state=4;
						return errorvector;
					case 4 :
						datavalue = (serialdata<<8);
						std::cout << "case 4: " << datavalue << std::endl;
						state=5;
						return errorvector;
					case 5 :
						datavalue = datavalue | serialdata;
						singlesensordata.push_back(datavalue);
						std::cout << "case 5: " << singlesensordata[1] << std::endl;
            state=1;
						return singlesensordata;
				}
			}
	}
}

