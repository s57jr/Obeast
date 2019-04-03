#include "uart.h"

UART::UART() {
  std::cout << "Hello UART!" << std::endl;
  errorvector.push_back(99);
  sreceived = false;

}

UART::~UART() {
  close(uart0_filestream);
}

int UART::init(int & uart0_filestream) {

  uart0_filestream = open("/dev/ttyS0", O_RDONLY | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode

  if (uart0_filestream == -1) {
    printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
    close(uart0_filestream);
  }

  tcgetattr(uart0_filestream, & options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; //<Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, & options);

  std::cout << "finished setting up" << std::endl;

  return 0;

}

int UART::getSensorData(int & uart0_filestream) {

  static int state = 1;

  uint16_t datavalue;
  uint8_t sensornumber;

  if (uart0_filestream != -1) {
    // Read up to 255 characters from the port if they are there
    unsigned char rx_buffer[1];
    int rx_length = read(uart0_filestream, (void * ) rx_buffer, 1); //Filestream, buffer to store in, number of bytes to read (max)

    if (rx_length < 0) {

      return -1;

    } else if (rx_length == 0) {
      return -1;
    } else {

      char serialdata = * rx_buffer;

      switch (state) {
      case 1:
        singlesensordata.clear();
        //s received from serialdata
        if (serialdata == 115) {
          sreceived = true;
          state = 2;
        }
        return -1; // and exits the switch
      case 2:
        if (serialdata == 116) {
          state = 3;
        } else if (serialdata == 115) {
          state = 2;
        } else state = 1;
        return -1;
      case 3:
        sensornumber = serialdata;
        singlesensordata.clear();
        singlesensordata.push_back(sensornumber);
        state = 4;
        return -1;
      case 4:
        datavalue = (serialdata << 8) | 0x0000;
        state = 5;
        return -1;
      case 5:
        uint16_t newdatavalue = datavalue | serialdata;
        singlesensordata.push_back(newdatavalue);

        //  std::cout << "serialdata is = " << serialdata << " length is: " << singlesensordata.size() << std::endl;
        //  std::cout << "singlesensor data: " << singlesensordata[0] << "  " << singlesensordata[1] << std::endl;
        //	std::cout << "case 5: " << singlesensordata[1] << std::endl;   
        state = 1;
        return 0;
      }
    }
  } else {
    return -1;
  }
}