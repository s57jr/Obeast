// writing on a text file
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main () {
  string answer_create_workout = "yes";
  string answer;
  string linetext;
  
while (answer_create_workout == "yes"){
	
	cout << "welcome you are now making a workout program. \n";
	cout << "how would you name this workout program?\n";
	string name, txtname;
	cin >> name;
	txtname = name + ".txt";
	ofstream myfile (txtname);
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
	
	string line;
	std::ifstream songfile("songs.txt");
	int totalnumberofsongs = 1;
    while (std::getline(songfile, line)){
        cout << totalnumberofsongs << ": " << line << '\n';
		totalnumberofsongs++;
	}
	cout << "\n\n";

	
	cout << "Type the number of the song and press enter, type no for no more songs...\n";
	myfile << "songs: ";
	while (song_answer != "no"){
	cin >> song_answer;
	if (song_answer != "no" && stoi(song_answer)<totalnumberofsongs){
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
	cout << "Type the number of the exersize and press enter, type no for no more exersizes...\n";
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

