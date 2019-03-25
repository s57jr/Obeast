#include <iostream>
#include <string>
#include <mpg123.h>
#include <math.h> 
#include <fstream>
#include "AudioFile/AudioFile.h"

using namespace std;

int decodeMp3(string filename)
{
    mpg123_handle *mh;
    //unsigned char *buffer;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

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
    out.open("play.raw", ios::out | ios::in );
	
    /* decode and play */
	int inx = 0;
	int bytesOut =0;
    for (int totalBtyes = 0; mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK; ) 
    {
        char *data = new char[done + 1];
        for (int i = 0; i != done; i++)
        {
          //  bufferOut[inx] = buffer[i];
			out << buffer[i];
			inx++;
        }
        bytesOut +=done;
        totalBtyes += done;
    }
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
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    return bytesOut;
}


int main(void){
	
	decodeMp3("conga.mp3");
 
	
	return 0;
}