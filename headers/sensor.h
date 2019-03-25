#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include "bluetooth.h"
#include "uart.h"

class sensor : public bluetooth, public UART
{
public:
    sensor();
};

#endif // SENSOR_H
