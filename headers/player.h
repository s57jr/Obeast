#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <vlc/vlc.h>

class player
{
public:
    player(std::string filename);
	~player();

	void play();
	void stop();

private:
	
	const char *file;

    libvlc_instance_t *inst;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;

};

#endif // PLAYER_H