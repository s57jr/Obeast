// writing on a text file
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ofstream myfile ("example.txt");
  string answer = "yes";
  string linetext;
  
  if (myfile.is_open())
  {
	while (answer == "yes"){
			
		std::cout << "What do you want to type on the line?";
		std::getline (std::cin,linetext);  
		myfile << linetext <<"\n\n";
			
		std::cout << "do you want to add another line? ";
		std::getline (std::cin,answer);  
	}
	myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}
