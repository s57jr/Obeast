#include <iostream>
#include <stdlib.h>
#include <string>
#include <mpg123.h>
#include <math.h> 
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>

/*
COMPILE WITH:

g++ mp3ToPCM.cpp -o wazaapp -lmpg123

*/


void read_directory(const std::string& name, std::vector<std::string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
} 




void PCMtoInt16(int16_t *dataBufL,int16_t *dataBufR, int samples, std::string filename ){

    std::ifstream is(filename);
    char ch;
    int inx = 0;
    int smp =0;
    while (is.get(ch) && inx < samples) {
        switch(smp%4){


            case 0: dataBufL[inx] = (int16_t)ch; smp++;break;

            case 1: dataBufL[inx] = ((((int16_t)ch)<<8)|(int16_t)dataBufL[inx]);smp++;break;

            case 2: dataBufR[inx] = (int16_t)ch;smp++;break;

            case 3: dataBufR[inx] = (int16_t)((((int16_t)ch)<<8)|(int16_t)dataBufR[inx]); smp++;inx++;break;

        }
    }
}

int decodeMp3(std::string filename,std::string outFilename)
{
    mpg123_handle *mh;
    //unsigned char *buffer;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;
    int bytesOut =0;
    int samples =0;
    


    int channels, encoding;
    long rate;

    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, filename.c_str());
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    int m_bits = mpg123_encsize(encoding);
    int m_rate = rate;
    int m_channels = channels;
    std::fstream  out;
    out.open(outFilename, std::ios::out | std::ios::in | std::ios::binary);

    /* decode and play */

    for (int totalBtyes = 0; mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK; )
    {
        char *data = new char[done + 1];
        for (int i = 0; i != done; i++)
        {
            out << (buffer[i]);
            bytesOut +=1;
        }
        totalBtyes += done;
    }


    std::cout << "Buffer size " << bytesOut << std::endl;
    std::cout << "Samples " << samples << std::endl;
    std::cout << "err " << err << std::endl;
    std::cout << "channels " << channels << std::endl;
    std::cout << "encoding " << encoding << std::endl;
    std::cout << "Rate " << rate << std::endl;
    std::cout << "m_bytes " << m_bits << std::endl;
    std::cout << "m_rate " << m_rate << std::endl;
    std::cout << "m_channels " << m_channels << std::endl;
    std::cout << "The size of buffer " << sizeof(buffer) << std::endl;

    out.close();
    free(buffer);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    
    


    return samples = bytesOut/(m_bits+m_channels);

}

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
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

int getFileSize(const std::string &fileName) //bytes
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

int main(void){

    std::vector<std::string> tracklist;

    int16_t *dataBufL;
    int16_t *dataBufR;
    
    int16_t val;
    
    std::vector<int> data;
    int samples;
    std::string filec;
    
    
    read_directory("music", tracklist);
     for (int i=0;i<tracklist.size();i++){
        if (tracklist[i].rfind(".", 0) == 0) {
          tracklist.erase(tracklist.begin()+i);
        }
    } 
  
    
    for (int i=0;i<tracklist.size();i++){
      findAndReplaceAll(tracklist[i],".mp3","");
      filec = "touch raw/" + tracklist[i]+".raw";
      system(filec.c_str());
      samples = decodeMp3("music/"+tracklist[i]+".mp3", filec);
   }
   
    int size = getFileSize("raw/BML.raw");
    
    std::cout << "size: " <<size << std::endl;
   
	  dataBufL = (int16_t*)malloc(size/2 * sizeof(int16_t));
    dataBufR = (int16_t*)malloc(size/2 * sizeof(int16_t));
    PCMtoInt16(dataBufL,dataBufR,size/2, "raw/BML.raw" );
    free(dataBufL);
    free(dataBufR);
  
   

  return 0;
}