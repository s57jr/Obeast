#ifndef EXERCISEBASE_H
#define EXERCISEBASE_H
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include "player.h"

class exerciseBase
{
public:
    
	exerciseBase();
  virtual void playex();
	
protected:

  player *musicplayer;
  std::vector<std::string> songname;
	
	
	
	
};

#endif // EXERCISEBASE_H
