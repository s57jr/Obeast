 
#include "workout.h"

using namespace std;

workout::workout()
	{
		name = "noname";
	}

workout::workout(string nameget)
{
	parse(nameget);
}

string workout::getname()
{
 return name;
} 

double workout::getduration()
{
	return duration;
}

//song workout::getsong(int position)
//{
//	return tracklist[position];
//}

void workout::parse(string filename)
{
	string line;
	ifstream file;
	file.open(filename);
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
//		cout << line << endl << endl;
//		cout << "line size is: " << line.size() <<endl;
//			for(int i = 0,j=0; i<line.size(); i++)
//			{
//				if(line.at(i)==',' || line.at(i)=='\0'){
//					song songinvector("songs.txt",stoi(line.substr(j,i-j)));
//					tracklist.push_back(songinvector);
//					j=i+1;s
//				}
//			}
			
		getline(file, line);
		line.erase (0,10);
	//	cout << line << endl << endl;
//		cout << "line size is: " << line.size() <<endl;
			for(int i = 0,j=0; i<line.size(); i++)
			{
				if(line.at(i)==',' || line.at(i)=='\0'){
					exerciselist.push_back(stoi(line.substr(j,i-j)));
					j=i+1;
				}
			}
	}
}