#include "ex_warmup.h"


ex_warmup::ex_warmup(std::string songname): exerciseBase(songname)
{

    std::cout << "Hello ex_warmup!" << std::endl;
}

ex_warmup::~ex_warmup()
{
  std::cout << "Goodbye ex_warmup!" << std::endl;
  
}

void ex_warmup::playex( )
{
  float position;
  float positionbuf;
  int pos;
  int posbuf=0;
  long currTime;
  musicplayer = new player(exerciseBase::song);
  musicplayer->setVolume(60);
  musicplayer->play();
  sleep(1);
  
  exercise(musicplayer);
  
  //while(musicplayer->isPlaying() == 1 ){
  //   currTime = musicplayer->getTimeUs();

 //    pos = (int)(static_cast<double>(currTime)*0.0441);
   //  std::cout << "Beat size: " << beatSize << "Pos: " << pos << std::endl;
 //    if(beatArray[pos] > 0 && posbuf==0){
    
//       if(beatArray[pos] == 3){
          std::cout << "Low! " << std::endl;
//       }else if(beatArray[pos] == 4){
//          std::cout << "Mid! " << std::endl;
//       }else if(beatArray[pos] == 5){
//          std::cout << "High! " << std::endl;
//       }else if(beatArray[pos] == 7){
//          std::cout << "Low & Mid! " << std::endl;
//       }else if(beatArray[pos] == 8){
//          std::cout << "Low & High! " << std::endl;
//       }else if(beatArray[pos] == 9){
//          std::cout << "Mid & High! " << std::endl;
//       }else if(beatArray[pos] == 12){
//          std::cout << "Mid & High! " << std::endl;
//       }
    
    
   //  }
  //   posbuf = beatArray[pos];
  
 // }
  
  
  //sleep(6);
  
 // sleep(6);
//  if(musicplayer->isPlaying() == 1){
  musicplayer->stop();
sleep(1);
  delete musicplayer;
  
}

void ex_warmup::exercise(player *music){
   uint16_t data[45];
 //  int stepped;
   playSound("WarmUp/LetsDoWarmup", 60);
   playSound("WarmUp/StepRightFoot", 60);
   playSound("WarmUp/StepLeftFoot", 60);
   playSound("WarmUp/JumpOnBeat", 60);
   sleep(20);
   playSound("WarmUp/AlternateFeet", 60);
   sleep(15);
   playSound("WarmUp/WarmedUpYet", 60);
   sleep(5);
   playSound("WarmUp/10Pushups", 60);
   sleep(15);
   playSound("WarmUp/StepRightFoot", 60);
   while(readSensorData(data) < 20000){
      
     sleep(1);
     std::cout << "wait step" << std::endl;
   }
   
}