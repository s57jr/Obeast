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
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(6);
  playSound("Nice");
  sleep(6);
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
  }
  delete musicplayer;
  
}