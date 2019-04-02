#ifndef EXPUSHUP_H
#define EXPUSHUP_H
#include <string>
#include <iostream>
#include "exercisebase.h"

class exPushup : public exerciseBase
{
public:
	exPushup();
  ~exPushup();
  
private:
	std::vector<string> songs;
	


	
};

#endif // EXPUSHUP_H
