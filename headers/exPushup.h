#ifndef EXPUSHUP_H
#define EXPUSHUP_H
#include <string>
#include <iostream>
#include "exercisebase.h"

class exPushup : public exerciseBase
{
public:
	exPushup(std::string songname);
  ~exPushup();
  
  void playex();
  
private:
	std::vector<std::string> songs;
	


	
};

#endif // EXPUSHUP_H
