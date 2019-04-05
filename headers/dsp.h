#ifndef DSP_H
#define DSP_H

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

class DSP
{
public:
    DSP();

    double getBeat(int16_t *dataL, int16_t *dataR,int st, int end, int sr);
    void PCMtoInt16(int16_t *dataBufL,int16_t *dataBufR, int samples, std::string filename );

private:
    double getChunkEnergy(int16_t *dataL, int16_t *dataR, int st,int end);
    double blocksAvg(int16_t *dataL, int16_t *dataR, int st,int end, int blocks);
    double blocksVar(int16_t *dataL, int16_t *dataR, int st,int end, int blocks);
    double getC(int16_t *dataL, int16_t *dataR, int st,int end, int blocks);


};

#endif // DSP_H
