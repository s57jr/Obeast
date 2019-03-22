#include <iostream>
#include "workout.h"
#include <string>
using namespace std;

int main()
{
 cout << "startup with workout1.txt as name\n";
 workout blaworkout("testworkout.txt");
 cout << "the duration of the created workout is: " << blaworkout.getduration() << endl;
 cout << "song on position 3 is: " << blaworkout.getsong(3) << endl;
 return 0;
} 
