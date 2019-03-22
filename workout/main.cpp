#include <iostream>
#include "workout.h"
#include <string>
using namespace std;

int main()
{
 cout << "startup\n";
 workout blaworkout("blaworkout");
 cout << "the name of the created workout is: " << blaworkout.getname() << endl;
 return 0;
} 
