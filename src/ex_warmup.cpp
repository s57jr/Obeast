#include "ex_warmup.h"


ex_warmup::ex_warmup(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello ex_warmup!" << std::endl;
}

ex_warmup::~ex_warmup()
{
  std::cout << "Goodbye ex_warmup!" << std::endl;
  
}

void ex_warmup::playex( )
{
  float position;
  float positionbuf;
  int pos;
  int posbuf=0;
  long currTime;
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(1);
  while(musicplayer->isPlaying() == 1){
     currTime = musicplayer->getTimeUs();

     pos = (int)((float)currTime*0.0441);

     if(beatArray[pos] > 0 && posbuf != beatArray[pos]){
        std::cout << "Beat! " << std::endl;
     }
     posbuf = beatArray[pos];

  
  }
  
  
  
  
  //sleep(6);
  playSound("WarmUp/LetsDoWarmup", 40);
  sleep(6);
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
  }
  delete musicplayer;
  
}