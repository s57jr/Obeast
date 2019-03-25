#include <iostream>
#include "workout.h"
#include "song.h"
#include <string>
using namespace std;

int main()
{
 cout << "startup with workout1.txt as name\n";
 workout blaworkout("testworkout.txt");
 cout << "the duration of the created workout is: " << blaworkout.getduration() << endl;
 cout << "which position of song do you want to get from this workout?" << endl;
 int songchosen;
 	cin >> songchosen;
	songchosen--;
//cout << "song on position" << songchosen << "is: " << blaworkout.getsong(songchosen) << endl;
 
 //cout << "\n" << "now we get song name and bpm and duration of the song: " << blaworkout.getsong(songchosen) << endl;
 
 //cout << blaworkout.tracklist[songchosen].getname() << endl;
 cout << blaworkout.getsong(songchosen).getname() << endl;
//song song1("songs.txt",blaworkout.getsong(songchosen));
 //string songname = song1.getname();

 
 //cout << "song name is: " << songname;
 
 
 return 0;
 
 
 
 
} 