 
#include "workout.h"




using namespace std;

void read_directory(const std::string& name, std::vector<std::string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
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
		
	
  //get the songs of the location /music and put them in tracklist
  	getline(file, line);
		line.erase (0,7);
     
    std::vector<std::string> v;
    read_directory("music", v);
     for (int i=0;i<v.size();i++){
        if (v[i].rfind(".", 0) == 0) {
          v.erase(v.begin()+i);
        }
     } 
     
			for(int i = 0,j=0; i<line.size(); i++)
			{
				if(line.at(i)==',' || line.at(i)=='\0'){
					std::string songinvector = v[stoi(line.substr(j,i-j))];
          tracklist.push_back(songinvector);
					j=i+1;
				}
			}
      
// get the exercises and put them in exerciselist, just strings.
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
int exercisescounter, songcounter = 0;
  while(exersisesfinished == false)
  {
      std::cout << "Wasup1 " << std::endl;
     auto time_end = std::chrono::steady_clock::now();
     int timerunning = std::chrono::duration_cast<chrono::seconds>(time_end-time_start).count();
     
     std::cout << "timerunning: " << timerunning << std::endl;
     std::cout << "Duration: " << duration << std::endl;
     
     if (timerunning > (60*duration))
     { exersisesfinished = true; }
     
     //write code for determining which song is played
     std::cout << "Songcounter: " << songcounter << std::endl;
     std::cout << "exercisescounter: " << exercisescounter << std::endl;
     
     runexercise(exerciselist[exercisescounter], tracklist[songcounter]);
     std::cout << "Exercise list size: " << exerciselist.size() << std::endl;
     
     if (exercisescounter < exerciselist.size()-1 )
     { exercisescounter++; }
     else 
     { exercisescounter = 0; }
     
     if (songcounter < tracklist.size()-1 )
     { songcounter++; }
     else 
     { songcounter = 0; }
     
     
     
  }
  std::cout << "all exersizes completed" << std::endl;

  return 1;
}

int workout::runexercise(string exersisename, string songname)
{
std::string songlocation = "music/" + songname;

std::cout << songlocation << std::endl;
tmpex = new exPushup(songlocation);

tmpex->playex();

delete tmpex;  
 return 0;
}
