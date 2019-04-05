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
g++ makeRaws.cpp -o wazaapp -lmpg123
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


using namespace std;


double getChunkEnergy(int16_t *dataL, int16_t *dataR, int st,int end){
	double energy =0;
	for(int i=0;i+st<end;i++){
		energy+=(pow(dataL[st+i],2)+pow(dataR[st+i],2));
	}
	return energy;
}

double blocksAvg(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){
	
	double average =0;
	int blkSize = (end-st)/blocks;
	for(int i=0;i<blocks;i++){
		average+=(getChunkEnergy(dataL,dataR,st+(i*blkSize),st+(i*blkSize)+blkSize)/(float)blocks);
	}
	
	return average;
	
}

double blocksVar(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){
	
	double average = blocksAvg(dataL,dataR,st,end, blocks);
	
	double variance =0;
	int blkSize = (end-st)/blocks;
	for(int i=0;i<blocks;i++){
		variance+=(pow(average-getChunkEnergy(dataL,dataR,st+(i*blkSize),st+(i*blkSize)+blkSize),2)/(float)blocks);
	}
	return variance;
}

double getC(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){
	return (-0.0000015*blocksVar(dataL,dataR,st,end,blocks)+1.5142857);
}

void fillOne(uint8_t *array, int st,int end){
    for(int i=st;i<end;i++){
      array[i] = 100;
    }
}

void fillZero(uint8_t *array, int st,int end){
    for(int i=st;i<end;i++){
      array[i] = 0;
    }
}

double getBeat(int16_t *dataL, int16_t *dataR,int st, int end, int sr, uint8_t *beatArr){  //here blocks are averaged blocks
	
	
	int blocks = 30;
	double average;
	double C;
	int sp;
	int ep;
	float bps =0;	
	int beats=0;
	
	for(int k=0;k<floor((end-st)/sr);k++){
		
		beats+=1;  //numberr of seconds
		
		sp = st+(k*sr);
		ep = sp+sr;
		
		average = blocksAvg(dataL,dataL,sp,ep, blocks);
		C = getC(dataL,dataR,sp,ep,blocks);
		
		int blkSize = (ep-sp)/blocks;
		for(int i=0;i<blocks;i++){
			if(getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize) > average){
				bps+=1;
        fillOne(beatArr,sp+(i*blkSize),sp+(i*blkSize)+blkSize);
			//	printf("Chunk energy: %lf  C*Average: %lf OVER\n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
			}else{
        fillZero(beatArr,sp+(i*blkSize),sp+(i*blkSize)+blkSize);
      }
		//	printf("Chunk energy: %lf  C*Average: %lf \n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
		}
		
	}
	
	bps/=(float)beats;
	
	return bps;
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
    
    


    return m_rate;

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
    std::vector<int> srs;

    int16_t *dataBufL;
    int16_t *dataBufR;
    uint8_t *beatArray;
    
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
  
    system("rm -f raw/{*,.*}");
    
     for (int i=0;i<tracklist.size();i++){
      findAndReplaceAll(tracklist[i],".mp3","");
      filec = "touch raw/" + tracklist[i]+".raw";
      system(filec.c_str());
      srs.push_back(decodeMp3("music/"+tracklist[i]+".mp3", "raw/" + tracklist[i]+".raw"));
}
   
   
   
    int size; 
    
    for (int i=0;i<tracklist.size();i++){
      filec = "raw/" + tracklist[i]+".raw";
      size = getFileSize(filec);
      std::cout << "size of "<< filec << " : " << size << std::endl;
      dataBufL  = (int16_t*)malloc(size/4 * sizeof(int16_t));
      dataBufR  = (int16_t*)malloc(size/4 * sizeof(int16_t));
      beatArray = (uint8_t*)malloc(size/4 * sizeof(uint8_t));
      PCMtoInt16(dataBufL,dataBufR,size/4, filec );
      printf("Beat : %lf bps \n", getBeat(dataBufL, dataBufR,0, size/4, srs[i],beatArray));
      
      filec = "touch raw/" + tracklist[i]+"Beat.raw";
      system(filec.c_str());
      
      std::fstream  out;
      out.open("raw/" + tracklist[i]+"Beat.raw", std::ios::out | std::ios::in | std::ios::binary);

      for (int j = 0;j < size/4; j++)
      {
         out << (beatArray[j]);
      }
      out.close();
      
      std::ifstream in;
      in.open("raw/" + tracklist[i]+"Beat.raw", std::ios::in | std::ios::binary);
      size = getFileSize("raw/" + tracklist[i]+"Beat.raw");
      for (int j = 0;j < size; j++)
      {
         in >> (beatArray[j]);
      }
      in.close();
      
      for (int j = 0;j < size; j++)
      {
         std::cout << "beat Arr: " << beatArray[j] << std::endl;
      }
      
      
      free(dataBufL);
      free(dataBufR);
      free(beatArray);
    }
    
    

  
   

  return 0;
}