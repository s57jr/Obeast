#include "dsp.h"

DSP::DSP()
{
    std::cout << "Hello DSP! " << std::endl;
}



void DSP::PCMtoInt16(int16_t *dataBufL,int16_t *dataBufR, int samples, std::string filename ){



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

int DSP::decodeMp3(std::string filename,std::string outFilename)
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


    return samples = bytesOut/4;

}

double DSP::getChunkEnergy(int16_t *dataL, int16_t *dataR, int st,int end){
    double energy =0;
    for(int i=0;i+st<end;i++){
        energy+=(pow(dataL[st+i],2)+pow(dataR[st+i],2));
    }
    return energy;
}

double DSP::blocksAvg(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){

    double average =0;
    int blkSize = (end-st)/blocks;
    for(int i=0;i<blocks;i++){
        average+=(getChunkEnergy(dataL,dataR,st+(i*blkSize),st+(i*blkSize)+blkSize)/(float)blocks);
    }

    return average;

}

double DSP::blocksVar(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){

    double average = blocksAvg(dataL,dataR,st,end, blocks);

    double variance =0;
    int blkSize = (end-st)/blocks;
    for(int i=0;i<blocks;i++){
        variance+=(pow(average-getChunkEnergy(dataL,dataR,st+(i*blkSize),st+(i*blkSize)+blkSize),2)/(float)blocks);
    }
    return variance;
}

double DSP::getC(int16_t *dataL, int16_t *dataR, int st,int end, int blocks){
    return (-0.0000015*blocksVar(dataL,dataR,st,end,blocks)+1.5142857);
}

double DSP::getBeat(int16_t *dataL, int16_t *dataR,int st, int end, int sr){  //here blocks are averaged blocks


    int blocks = 30;
    double average;
    double C;
    int sp;
    int ep;
    float bps =0;
    int beats=0;
    int beatUp =0;

    for(int k=0;k<floor((end-st)/sr);k++){

        beats+=1;  //numberr of seconds

        sp = st+(k*sr);
        ep = sp+sr;

        average = blocksAvg(dataL,dataL,sp,ep, blocks);
        C = getC(dataL,dataR,sp,ep,blocks);

        int blkSize = floor((ep-sp)/blocks);
        for(int i=0;i<blocks;i++){
            if(getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize) > average){
                if(beatUp == 0){
                    beatUp=1;
                    bps+=1;
                //	printf("Chunk energy: %lf  C*Average: %lf OVER\n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
                }

            }else{
                beatUp=0;
            }
            //printf("Chunk energy: %lf  C*Average: %lf \n",getChunkEnergy(dataL,dataR,sp+(i*blkSize),sp+(i*blkSize)+blkSize),average);
        }

    }

    bps/=(float)beats;

    return bps;
}
