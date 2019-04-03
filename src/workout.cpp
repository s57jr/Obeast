 
#include "workout.h"

using namespace std;

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
					exerciselist.push_back(line.substr(j,i-j));
					j=i+1;
				}
			}
	}
}


int workout::runworkout()
{

auto time_start = std::chrono::steady_clock::now();
bool exersisesfinished = false;
int exercisescounter = 0;
  while(exersisesfinished == false)
  {
     auto time_end = std::chrono::steady_clock::now();
     int timerunning = std::chrono::duration_cast<chrono::seconds>(time_end-time_start).count();
     
     std::cout << "Timerning: " << timerunning << std::endl;
     std::cout << "Duration: " << duration << std::endl;
     
     if (timerunning > (60*duration))
     { exersisesfinished = true; }
     
     //write code for determining which song is played
     
     runexercise(exerciselist[exercisescounter]);
     std::cout << "Exercise list size: " << exerciselist.size() << std::endl;
     
     if (exercisescounter < exerciselist.size()-1 )
     {
     exercisescounter++;
     }
     else
     {
     exercisescounter = 0;
     
     }
  }
  std::cout << "all exersizes completed" << std::endl;

  return 1;
}

int workout::runexercise(string exersisename)
{

tmpex = new exPushup("music/BM.mp3");

tmpex->playex();

delete tmpex;  
 return 0;
}
