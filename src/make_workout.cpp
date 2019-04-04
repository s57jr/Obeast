// writing on a text file
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
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


int main () {
  string answer_create_workout = "yes";
  string answer;
  string linetext;
  
while (answer_create_workout == "yes"){
	
	cout << "welcome you are now making a workout program. \n";
	cout << "how would you name this workout program?\n";
	string name, txtname;
	cin >> name;
	txtname = "workouts/" + name + ".txt";
	ofstream myfile (txtname);
 
 std::cout << "how late do you want the reminder to be sent? type in format: HH:MM" << std::endl;
 std::string timetostart;
 cin >> timetostart;
 myfile << "time: " << timetostart <<"\n";
 
 
	myfile << "name: " << name <<"\n";
	cout << "wourkout created called:" << name << "\nnow we will get all data...\n\n";
	

	cout << "How long will the workout take in minutes?\n";
	double duration_total;
	cin >> duration_total;
	myfile << "duration: " << duration_total <<"\n";	
	
	cout << "What is the type of the workout?\n"; cin >> answer;
	myfile << "type: " << answer <<"\n";	
	
	int maxHeartrate;
	cout << "What is the max heartrate you can reach?\n"; 
	cin >> maxHeartrate;
	myfile << "maxHeartrate: " << maxHeartrate <<"\n";
	
	int minHeartrate=0;
	bool heartratetyped = false;
	while (heartratetyped == false){
	cout << "What is the min heartrate you can reach? This should be less than the maxHeartrate\n";	
	cin >> minHeartrate;
	if(minHeartrate<maxHeartrate && minHeartrate != 0) {
		heartratetyped = true;
	}
	}
	myfile << "minHeartrate: " << minHeartrate <<"\n";
	
	double duration_warmup=0;
	bool timetyped = false;
	while (timetyped == false){
	cout << "How long does the warming up take, needs to be shorter then the total time\n";
	cin >> duration_warmup;
	if(duration_warmup<duration_total && duration_warmup != 0) {
		timetyped = true;
	}
	}
	myfile << "warmup_duration: " << duration_warmup <<"\n";

	
	
	int number_of_songs=0;
	string song_answer;
	cout << "what songs do you want to play during the workout?\n";
	cout << "these songs can be chosen" << endl;


  std::vector<std::string> v;
    read_directory("music", v);
     for (int i=0;i<v.size();i++){
        if (v[i].rfind(".", 0) == 0) {
          v.erase(v.begin()+i);
        }
     }
       
    for (unsigned i=0; i<v.size(); ++i)
    std::cout << "[" << i << "]" << ": " << v[i] << std::endl;;   
 


	
	cout << "Type the number of the song and press enter, type no for no more songs...\n";
	myfile << "songs: ";
	while (song_answer != "no"){
	cin >> song_answer;
	if (song_answer != "no" && stoi(song_answer)<v.size()){
		myfile << song_answer << ",";
		number_of_songs++;
	}
	else {
		cout << "song number is incorrect, or you have decided to add no more songs.\n\n";
	}
	}
	cout << "\nyou have added " << number_of_songs << " songs.\n";
	myfile << endl;
	
	int number_of_ex = 0;
	string ex_answer;
	cout << "Type the exersize and press enter, type no for no more exersizes...\n";
	myfile << "exersize: ";
	while (ex_answer != "no"){
	cin >> ex_answer;
	if (ex_answer != "no"){
		myfile << ex_answer << ",";
		number_of_ex++;
	}
	else {
		cout << "song number is incorrect, or you have decided to add no more songs.\n\n";
	}
	}
	cout << "\nyou have added " << number_of_ex << " exersizes.\n";
	
		
	cout << "Would you like to create a new program? \n";
	cin >> answer_create_workout;
	
}

  return 0;
}

