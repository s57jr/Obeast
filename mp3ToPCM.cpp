// vlc --demux=rawaud --rawaud-channels 2  --volume=10000 --rawaud-samplerate 41000 play.raw

//  g++ mp3ToPCM.cpp -o wazaapp -lmpg123

#include <iostream>
#include <string>
#include <mpg123.h>
#include <math.h> 
#include <fstream>
#include "AudioFile/AudioFile.h"

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

double getBeat(int16_t *dataL, int16_t *dataR,int st, int end, int sr){  //here blocks are averaged blocks
	
	
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
				printf("Chunk energy: %lf  C*Average: %lf OVER\n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
			}
			printf("Chunk energy: %lf  C*Average: %lf \n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
		}
		
	}
	
	bps/=(float)beats;
	
	return bps;
}


int decodeMp3(string filename)
{
    mpg123_handle *mh;
    //unsigned char *buffer;
    unsigned char *buffer;
    int16_t *dataBufL;
    int16_t *dataBufR;
    size_t buffer_size;
    size_t done;
    int err;
	int inx = 0;
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
	fstream  out;
    out.open("play.raw", ios::out | ios::in | ios::binary);
	
    /* decode and play */
	
    for (int totalBtyes = 0; mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK; ) 
    {
        char *data = new char[done + 1];
        for (int i = 0; i != done; i++)
        {
			out << (buffer[i]);
        }
        bytesOut +=done;
        totalBtyes += done;
    }
	
	
	samples = bytesOut/4;
	
	dataBufL = (int16_t*)malloc(samples * sizeof(int16_t));
	dataBufR = (int16_t*)malloc(samples * sizeof(int16_t));
	out.close();
	
	std::ifstream is("play.raw"); 
	char ch;
	inx = 0;
	int smp =0;
	while (is.get(ch)) {
		switch(smp%4){
		 
			case 0: dataBufL[inx] = (int16_t)ch; smp++;break;
			
			case 1: dataBufL[inx] = ((((int16_t)ch)<<8)|(int16_t)dataBufL[inx]);smp++;break;
			
			case 2: dataBufR[inx] = (int16_t)ch;smp++;break;
			
			case 3: dataBufR[inx] = (int16_t)((((int16_t)ch)<<8)|(int16_t)dataBufR[inx]); smp++;inx++;break;
			
		}
	}
	
	printf("Samples : %d \n", inx);
	printf("Beat : %lf bps \n", getBeat(dataBufL, dataBufR,44800, 490000, 44100));
	
	
	
    //out << buffer[i];

    cout << "Buffer size " << buffer_size << endl;
    cout << "Done " << done << endl;
    cout << "err " << err << endl;
    cout << "channels " << channels << endl;
    cout << "encoding " << encoding << endl;
    cout << "Rate " << rate << endl;
    cout << "m_bits " << m_bits << endl;
    cout << "m_rate " << m_rate << endl;
    cout << "m_channels " << m_channels << endl;
    cout << "The size of buffer " << sizeof(buffer) << endl;
    /* clean up */
    free(buffer);
	free(dataBufL);
	free(dataBufR);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    return bytesOut;
}


int main(void){
	
	decodeMp3("BM.mp3");
 
    system("vlc --demux=rawaud --rawaud-channels 2 --volume=10000 --intf dummy --rawaud-samplerate 41000 play.raw");	
	
	return 0;
}
