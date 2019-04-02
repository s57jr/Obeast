#include <iostream>
#include "workout.h"
#include <string>
using namespace std;


int main(void)
{
  
  //run thread here
  
  
  
  
  
	int i = 1;
	while (i!=5){
	
	enum states { standby=1, idle=2, workout=3, playback=4, stop=5};
	states statemachine = standby;
	
	cout << "start switch" << endl;
	switch(i)
	{
    case standby:
		cout << "STANDBY..." << endl;
		//cout  << "which state do you want to go to?" << endl;
		cin >> i;
		break;
		
    case idle: 
				cout << "IDLE..." << endl;
		cout  << "which state do you want to go to?" << endl;
		cin >> i;
   
   
		break;
    case workout: 
			cout << "WORKOUT..." << endl;
      
      
      
		  cout  << "which workout do you want to play?" << endl;
		  string workoutname;
      cin >> workoutname;
      
      workoutname = "workouts/" + workoutname + ".txt";
      
      workout tmpworkout(workoutname);
      tmpworkout.runworkout();
      
      std::cout << "exercises completed" << std::endl;
  
       i=2;
        
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
