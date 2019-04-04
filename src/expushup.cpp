#include "exPushup.h"


exPushup::exPushup(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello exPushup!" << std::endl;
}

exPushup::~exPushup()
{
  std::cout << "Goodbye exPushup!" << std::endl;
  
}

void exPushup::playex( )
{
  
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(6);
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
  }
  delete musicplayer;
  
}