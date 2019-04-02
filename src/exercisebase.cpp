#include "exercisebase.h"
#include <string>

exerciseBase::exerciseBase()
{
	std::cout << "Hello exerciseBase! " <<  std::endl;

	
}

virtual void exerciseBase::playex()
{
  
  musicplayer = new player(songname[0]);
  musicplayer.play();
  sleep(10);
  
}

