#include "workout.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

workout::workout()
	{
		name = "noname";
	}

workout::workout(string nameget)
{
	string line;
	filename = nameget;
	ifstream file;
	file.open(filename);
	char output[100];
	if (file.is_open()) {
		getline(file, line);
		line.erase (0,6);
		name = line;
		
		getline(file, line);
		line.erase (0,10);
		duration = stod(line);
		
		getline(file, line);
		line.erase (0,6);
		type = line;
		
		getline(file, line);
		line.erase (0,14);
		maxHeartrate = stoi(line);
		
		getline(file, line);
		line.erase (0,14);
		minHeartrate = stoi(line);
		
		getline(file, line);
		line.erase (0,17);
		warmup_duration = stod(line);
		
		getline(file, line);
		line.erase (0,7);
		cout << line << endl << endl;
		cout << "line size is: " << line.size() <<endl;
			for(int i = 0,j=0; i<line.size(); i++)
			{
				if(line.at(i)==',' || line.at(i)=='\0'){
					songs.push_back(stoi(line.substr(j,i-j))); //pushing the sub string
					j=i+1;
				}
			}
	}
}

string workout::getname()
{
 return name;
} 

double workout::getduration()
{
	return duration;
}

int workout::getsong(int position)
{
	return songs[position];
}

