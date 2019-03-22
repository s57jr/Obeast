#include "workout.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

workout::workout()
	{
		name = "noname";
		cout << "created with name: " << name << endl;
	}

workout::workout(string nameget)
{
	name = nameget;
	cout << "created with name: " << name << endl;
}

string workout::getname()
{
 return name;
} 
