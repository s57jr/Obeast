#include "ex_crunch.h"


ex_crunch::ex_crunch(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello ex_crunch!" << std::endl;
}

ex_crunch::~ex_crunch()
{
  std::cout << "Goodbye ex_crunch!" << std::endl;
  
}

void ex_crunch::playex( )
{
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(6);
  
  playSound("Crunches/IntroCrunches",40);
  sleep(6);
  
  
  
  
  
  
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
  }
  delete musicplayer;
  
}