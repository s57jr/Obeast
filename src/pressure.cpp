#include "pressure.h"


pressure::pressure(): UART() {
  std::cout << "Hello pressure!" << std::endl;

}

pressure::~pressure() {}

void pressure::getData(int & uart0_filestream) {

  singleSensor.nbr = 99;
  int counter = 0;

  uint16_t tmp[45];
  std::fill(tmp, tmp + sizeof(tmp), 0);

  std::cout << "in the getData function" << std::endl;

  while (counter < 40) {

    if (UART::getSensorData(uart0_filestream) == -1) {

    } else {

      singleSensor.nbr = UART::singlesensordata[0];
      singleSensor.value = UART::singlesensordata[1];

      if (singleSensor.nbr == 99) {

      } else {
        //auto timestamp = std::chrono::system_clock::now(); 
        counter = singleSensor.nbr;
        //std::cout << "counter is " << counter << std::endl;

        //std::cout << "sensordata 0 = " << UART::singlesensordata[0] << std::endl;
        //std::cout << "sensordata 1 = " << UART::singlesensordata[1] << std::endl;

        tmp[singleSensor.nbr] = singleSensor.value; //, timestamp}; 
      }

      mtx.lock();
      for (int i = 0; i < 40; i++) {
        DataArray[i] = tmp[i];
      }

      mtx.unlock();

    }
  }
  return;
}

void pressure::datathread(int & uart0_filestream) {

  UART::init(uart0_filestream);

  while (1) {
    getData(uart0_filestream);
  }

  return;

}