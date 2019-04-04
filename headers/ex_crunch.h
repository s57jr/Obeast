#ifndef EXCRUNCH_H
#define EXCRUNCH_H
#include <string>
#include <iostream>

#include "exercisebase.h"


class ex_crunch : public exerciseBase
{
public:
	ex_crunch(std::string songname);
  ~ex_crunch();
  
  void playex();
  
};

#endif // EXCRUNCH_H
