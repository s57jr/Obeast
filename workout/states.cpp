#include <iostream>
//#include "workout.h"
//#include "song.h"
#include <string>
using namespace std;

int main(void)
{
	int i = 1;
	while (i!=5){
	
	enum states { standby=1, idle=2, workout=3, playback=4, stop=5};
	states statemachine = standby;
	
	//while(statemachine != stop) {
	cout << "start switch" << endl;
	switch(i)
	{
    case standby:
		cout << "STANDBY..." << endl;
		cout  << "which state do you want to go to?" << endl;
		cin >> i;
		break;
		
    case idle: 
				cout << "IDLE..." << endl;
		cout  << "which state do you want to go to?" << endl;
		cin >> i;
		break;
    case workout: 
			cout << "WORKOUT..." << endl;
		cout  << "which state do you want to go to?" << endl;
		cin >> i;
		break;
	case playback:
			cout << "PLAYBACK..." << endl;
		cout  << "which state do you want to go to?" << endl;
		cin >> i;
		break;
	}
	}
	
 return 0;
} 
