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
  //  libvlc_media_release(m);
}

player::~player(){
	libvlc_media_release(m);
	libvlc_release(inst);
	libvlc_media_player_release(mp);
}

void player::play(){
	libvlc_media_player_play(mp);
}

void player::stop(){
	libvlc_media_player_stop(mp);
}