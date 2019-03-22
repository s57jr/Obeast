#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>
using namespace std;


class song
{
//variables
 private:
	string songname;
	int bpm;
	string duration;
	vector<string> songvector;
	
 public:
	song(string nameget, int numberofsong);
	song();
 
 //functions
 string getname();
 
 
};

#endif