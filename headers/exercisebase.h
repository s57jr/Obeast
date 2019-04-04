#ifndef EXERCISEBASE_H
#define EXERCISEBASE_H
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <mutex>

#include "player.h"
#include "dsp.h"

extern std::mutex mtx;
extern uint16_t DataArray[45];


class exerciseBase
{
public:
    
	exerciseBase(std::string songname);
  ~exerciseBase();
  virtual void playex() = 0;
	
protected:
  int readSensorData(uint16_t *data);
  int samples;
  player *musicplayer;
  player *feedbackplayer;
  DSP *proces;
  std::string song;
  int16_t *dataBufL;
  int16_t *dataBufR;
	
	
	
};

#endif // EXERCISEBASE_H
