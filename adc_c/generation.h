#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *getWaveInfo();
void generateWave(int *waveInfo);
void printWaveInfo(int *waveInfo);
float bestSamplingRate();
void generateSamplingWave(int *waveInfo, float sampling);
void generateQuantizedWave(int *waveInfo, float sampling);
void int_to_binary(int value, int bits, char *out);
void generateQuantizedWaveBinary(int *waveInfo, float sampling);
