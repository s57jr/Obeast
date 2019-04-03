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
  musicplayer->play();
  sleep(5);
  if(musicplayer->isPlaying() == 1){
     //musicplayer->stop();
  }
  delete musicplayer;
  
}