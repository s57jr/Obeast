#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>
#include <vector>
#include "song.h"
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
	vector<int> songs;
	 vector<song> tracklist;
	
	
	
 public:
	workout(string nameget);
	workout();

	
	
 //functions
 string getname();
 double getduration();
 song getsong(int position);
 
};

#endif