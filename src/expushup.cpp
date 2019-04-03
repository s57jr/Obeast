#include "exPushup.h"
#include <string>

exPushup::exPushup(std::string songname)
{

    songs.push_back(songname);
    std::cout << "Hello exPushup!" << std::endl;
}

exPushup::~exPushup()
{
  std::cout << "Goodbye exPushup!" << std::endl;
  
}

void exPushup::playex( )
{
  
  musicplayer = new player(songs[0]);
  musicplayer->setVolume(20);
  musicplayer->play();
  sleep(6);
  if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
     sleep(1);
  }
  delete musicplayer;
  
}