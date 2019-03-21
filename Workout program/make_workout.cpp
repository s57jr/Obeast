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
	std::getline (std::cin,name);
	txtname = name + ".txt";
	ofstream myfile (txtname);
	myfile << "name: " << name <<"\n";
	cout << "wourkout created called:" << name << "now we will get all data...";
	
	cout << "Would you like to create a new program? \n";
	getline (cin,answer_create_workout);
	
	
  
}

  return 0;
}

