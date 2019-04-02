#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <chrono>


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
  //  vector<song> tracklist;
	vector<string> exerciselist;
	
//functions
	void parse (string filename);
	
	
 public:
 
 //constructors
	workout(string nameget);
	workout();
  
 int runworkout();
 int runexercise(string exersisename);
 //functions
 string getname();
 double getduration();
// song getsong(int position);
 
 
 
};

#endif 
