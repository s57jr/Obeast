// writing on a text file
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  string answer_create_workout = "yes";
  string answer = "yes";
  string linetext;

while (answer_create_workout == "yes"){
	cout << "welcome you are now making a workout program. \n";
	cout << "how would you name this workout program?\n";
	string name;
	std::getline (std::cin,name);
	name = name + ".txt";
	ofstream myfile ("example.txt");
	myfile << "name: " << name <<"\n";
	cout << "wourkout created called:" << name << "now we will get all data...";
  
}
  else cout << "Unable to open file";
  return 0;
}

