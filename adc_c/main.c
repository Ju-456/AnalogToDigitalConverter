#include "generation.h"

int main(int argc, char const *argv[])
{
    int *waveInfo; //{ A , B , f }
    waveInfo = getWaveInfo();
    // printWaveInfo(waveInfo);
    generateWave(waveInfo);
    float bestSampling = bestSamplingRate(waveInfo);

    printf("Best sampling rate: %f\n", bestSampling);
    generateSamplingWave(waveInfo, bestSampling);
    generateQuantizedWave(waveInfo, bestSampling);
    generateQuantizedWaveBinary(waveInfo, bestSampling);
    return 0;
}