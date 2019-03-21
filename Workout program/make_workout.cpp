// writing on a text file
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  string answer_create_workout = "yes";
  string answer;
  string linetext;

while (answer_create_workout == "yes"){
	
	cout << "welcome you are now making a workout program. \n";
	cout << "how would you name this workout program?\n";
	string name, txtname;
	getline (cin,name);
	txtname = name + ".txt";
	ofstream myfile (txtname);
	myfile << "name: " << name <<"\n";
	cout << "wourkout created called:" << name << "\nnow we will get all data...\n\n";
	

	cout << "How long will the workout take in minutes?\n";
	getline (cin,answer);
	myfile << "duration: " << answer <<"\n";	
	
	cout << "What is the type of the workout?\n";
	getline (cin,answer);
	myfile << "type: " << answer <<"\n";	
	
	cout << "What is the max heartrate you can reach?\n";
	getline (cin,answer);
	myfile << "maxHeartrate: " << answer <<"\n";
	
	cout << "What is the min heartrate you can reach?\n";
	getline (cin,answer);
	myfile << "minHeartrate: " << answer <<"\n";
	
	int number_of_songs=0;
	string song_answer;
	cout << "what songs do you want to play during the workout?\n";
	cout << "Type the number of the song and press enter, type no for no more songs...\n";
	myfile << "songs: ";
	while (song_answer != "no"){
	getline (cin,song_answer);
	if (song_answer != "no"){
		myfile << song_answer << ", ";
		number_of_songs++;
	}
	}
	cout << "\nyou have added " << number_of_songs << " songs.\n";
	
	
	
	
	cout << "Would you like to create a new program? \n";
	getline (cin,answer_create_workout);
}

  return 0;
}

