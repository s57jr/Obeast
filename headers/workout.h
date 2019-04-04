#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>

#include "exPushup.h"


using namespace std;


class workout
{
//variables
 private:
	string filename;
	string name;
	string type;
	double duration;
	int maxHeartrate;
	int minHeartrate;
	double warmup_duration;
  vector<std::string> tracklist;
	vector<string> exerciselist;
	
//functions
	void parse (string filename);
	
 exPushup *tmpex;
	
 public:
 
 //constructors
	workout(string nameget);
	workout();
  
 int runworkout();
 int runexercise(string exercisename, string songname);
 //functions
 string getname();
 double getduration();
// song getsong(int position);
 
 
 
};

#endif 
