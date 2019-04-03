#include "player.h"

player::player(std::string filename)
{
    std::cout << "Hello player! " << std::endl;
	
	file = filename.c_str();
	
	inst = libvlc_new(0, NULL);
    // create a new item
    m = libvlc_media_new_path(inst, file);
    // create a media play playing environment
    mp = libvlc_media_player_new_from_media(m);
	
    // no need to keep the media now
    //libvlc_media_release(m);
    
}

player::~player(){
	libvlc_media_release(m);
	libvlc_release(inst);
	libvlc_media_player_release(mp);
  sleep(2);
  std::cout << "Goodbye player! " << std::endl;
}


void player::play(){
	libvlc_media_player_play(mp);
}

void player::stop(){
  libvlc_media_player_stop(mp);

}

int player::getMediaTime(){
	return libvlc_media_player_get_time(mp);
}

float  player::getPos(){
	return libvlc_media_player_get_position(mp);
}

int player::isPlaying(){
  if(	libvlc_media_player_is_playing(mp)){
    return true;
  }else{
    return false;
  }

}


void player::setVolume(int vol){
  libvlc_audio_set_volume(mp, vol);
}

int player::getTime(){
    currentTime = player::getMediaTime();
    
    std::cout << "Normal" << currentTime << std::endl;
    
    if (lastPlayTime == currentTime && lastPlayTime != 0){
        currentTime += player::currentTimeMillis() - lastPlayTimeGlobal;
    } else {
        lastPlayTime = currentTime;
        lastPlayTimeGlobal = player::currentTimeMillis();
    }
    

    return currentTime;    //to float
}

long player::currentTimeMillis()
{
  
	clock_gettime(CLOCK_REALTIME, &gettime_now);
	return gettime_now.tv_nsec/1000000;
}