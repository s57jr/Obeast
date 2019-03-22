#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>
#include <vector>
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
	
	
 public:
	workout(string nameget);
	workout();
 
 //functions
 string getname();
 double getduration();
 int getsong(int position);
 
};

#endif