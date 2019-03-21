// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() { 
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile("example.txt");

    while (std::getline(myfile, line)){
        ++number_of_lines;
		cout << "op lijn " << number_of_lines << " staat: " << line << '\n';
	}
	cout << "\n\n";
	cout << "Number of lines in text file: " << number_of_lines;
    return 0;
}