#include "ex_pushup.h"


ex_pushup::ex_pushup(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello exPushup!" << std::endl;
}

ex_pushup::~ex_pushup()
{
  std::cout << "Goodbye exPushup!" << std::endl;
  
}

void ex_pushup::playex( )
{
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(60);
  musicplayer->play();
  sleep(1);
  exercise(musicplayer);
 // playSound("Negative/WhyDoIEvenBother",40);
 // sleep(6);
 // if(musicplayer->isPlaying() == 1){
     musicplayer->stop();
 // }
 sleep(1);
  delete musicplayer;
  
}

void ex_pushup::exercise(player *music){
   uint16_t data[45];
 //  int stepped;
   playSound("PushUp/BeginEasy", 60);
   playSound("Random/NOGOD",60);
   playSound("PushUp/Do10Pushups", 60);
   sleep(15);
   playSound("PushUp/TrainBiceps", 60);
   playSound("Jokes/500Pushups", 60);
   playSound("PushUp/DoAnother10", 60);
   sleep(5);
   playSound("Positive/GoodJob", 60);
   sleep(5);
   playSound("Random/TakeARest", 60);
   sleep(10);
   playSound("PushUp/DoAnother102", 60);
   sleep(15);
   playSound("PushUp/DoneEnoughPushups", 60);
   sleep(5);

}