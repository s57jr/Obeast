#ifndef EXWARMUP_H
#define EXWARMUP_H
#include <string>
#include <iostream>

#include "exercisebase.h"


class ex_warmup : public exerciseBase
{
public:
	ex_warmup(std::string songname);
  ~ex_warmup();
  
  void playex();
  
private: 
  void exercise(player *music);
  
};

#endif // EXWARMUP_H
