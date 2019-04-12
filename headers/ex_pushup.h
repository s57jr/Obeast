#ifndef EX_PUSHUP_H
#define EX_PUSHUP_H
#include <string>
#include <iostream>

#include "exercisebase.h"


class ex_pushup : public exerciseBase
{
public:
	ex_pushup(std::string songname);
  ~ex_pushup();
  
  void playex();
  void exercise(player *music);
  
};

#endif // EX_PUSHUP_H
