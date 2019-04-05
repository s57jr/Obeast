#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <vlc/vlc.h>
#include <time.h>
#include <thread>
#include <unistd.h>

class player
{
public:
player(std::string filename);
	~player();

	void play();
	void stop();
  long  getTimeUs();
  float getPos();
  int isPlaying();
  void setVolume(int vol);

private:
  
	long  getMediaTime();
  long int  currentTimeUs();
  
  std::thread st;
  std::thread rt;
  struct timespec gettime_now;
	const char *file;
  long currentTime;
  long lastPlayTime = 0;
  long lastPlayTimeGlobal = 0;
  libvlc_instance_t *inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;

};

#endif // PLAYER_H