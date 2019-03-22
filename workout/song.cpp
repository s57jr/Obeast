#include "song.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

song::song()
	{
		songname = "noname";
	}

song::song(string nameget,int numberofsong)
{

	string line;
	ifstream file;
	file.open(nameget);
	if (file.is_open()) {

	for(int i = 0; i < numberofsong-1; ++i){
       std::getline(file, line);
	}

	
		getline(file, line);

		
			for(int i = 0,j=0; i<line.size(); i++)
			{
				if(line.at(i)==';' || line.at(i)=='\0'){

					songvector.push_back(line.substr(j,i-j)); //pushing the sub string
					j=i+1;
				}
			}
	}
	
	songname = songvector[0];
	bpm = stoi(songvector[1]);
	duration = songvector[2];
}


string song::getname()
{
	return songname;
}