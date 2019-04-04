#include "exercisebase.h"
#include <string>

exerciseBase::exerciseBase(std::string songname)
{
  song = songname;
 // proces = new DSP;
 // samples = proces -> decodeMp3(song, "decoded.raw");
 // dataBufL = (int16_t*)malloc(samples * sizeof(int16_t));
 // dataBufR = (int16_t*)malloc(samples * sizeof(int16_t));
 // proces -> PCMtoInt16(dataBufL,dataBufR,samples, "decoded.raw");
	std::cout << "Hello exerciseBase! " <<  std::endl;
}

exerciseBase::~exerciseBase()
{

 // delete proces;

}

void exerciseBase::playSound(std::string feedbackname)
{
  std::string feedbacklocation = "music/" + feedbackname + ".mp3";
  feedbackplayer = new player(feedbacklocation);
  feedbackplayer->setVolume(20);
  feedbackplayer->play();
  sleep(2);
  while(feedbackplayer->isPlaying()){
  sleep(1);
  }
  delete feedbackplayer;
}


int exerciseBase::readSensorData(uint16_t *data){  //returns average value
    int avg;
    mtx.lock();
    for (int i = 0; i < 40; i++) {
      std::cout << "position " << i << " gives value: " << DataArray[i] << std::endl;
      data[i] = DataArray[i];
      avg+=data[i];
    }
    mtx.unlock();
    
    return avg/40;
}
