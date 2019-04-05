#include "exercisebase.h"

exerciseBase::exerciseBase(std::string songname)
{
  song = songname;
//  process = new DSP();
  
  std::string beatFile = songname;
  
  findAndReplaceAll(beatFile, ".mp3", "Beat.raw");
  findAndReplaceAll(beatFile, "music", "raw");
  
  beatSize = getFileSize(beatFile);
    
  std::cout << "file: " <<beatFile << std::endl;
  
  beatArray = (uint8_t*)malloc(beatSize * sizeof(uint8_t));

  std::ifstream in;
  in.open(beatFile, std::ios::in | std::ios::binary);
  for (int j = 0;j < beatSize; j++)
  {
     in >> (beatArray[j]);
     //std::cout << beatArray[j] << std::endl;
  }
  in.close();
  
	std::cout << "Hello exerciseBase! " <<  std::endl;
}

exerciseBase::~exerciseBase()
{

  //delete process;
  free(beatArray);
//  free(dataBufR);
}

void exerciseBase::findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
 
	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

int exerciseBase::getFileSize(const std::string &fileName) //bytes
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}


void exerciseBase::playSound(std::string feedbackname, int volume)
{
  std::string feedbacklocation = "sounds/" + feedbackname + ".mp3";
  feedbackplayer = new player(feedbacklocation);
  feedbackplayer->setVolume(volume);
  feedbackplayer->play();
  sleep(2);
  while(feedbackplayer->isPlaying()){
  sleep(1);
  }
  delete feedbackplayer;
}


int exerciseBase::readSensorData(uint16_t *data){  //returns average value
    int avg;
    mtx.lock();
    for (int i = 0; i < 40; i++) {
      std::cout << "position " << i << " gives value: " << DataArray[i] << std::endl;
      data[i] = DataArray[i];
      avg+=data[i];
    }
    mtx.unlock();
    
    return avg/40;
}
