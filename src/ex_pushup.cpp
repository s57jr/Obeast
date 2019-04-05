#include "ex_pushup.h"


ex_pushup::ex_pushup(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello exPushup!" << std::endl;
}

ex_pushup::~ex_pushup()
{
  std::cout << "Goodbye exPushup!" << std::endl;
  
}

void ex_pushup::playex( )
{
  
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(6);
  playSound("Negative/WhyDoIEvenBother",40);
  sleep(6);
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
  }
  delete musicplayer;
  
}