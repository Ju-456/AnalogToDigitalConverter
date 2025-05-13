#include "generation.h"

int main(int argc, char const *argv[])
{
    int *waveInfo; //{ A, B , f }
    waveInfo = getWaveInfo();
    // printWaveInfo(waveInfo);
    generateWave(waveInfo);
    return 0;
}
