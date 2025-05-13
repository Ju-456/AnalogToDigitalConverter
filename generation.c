#include "generation.h"

int *getWaveInfo()
{
    int *waveInfo = (int *)malloc(3 * sizeof(int));
    if (waveInfo == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    printf("Please enter the first amplitude (A) = ");
    scanf("%d", &waveInfo[0]);
    printf("Please enter the second amplitude (B) = ");
    scanf("%d", &waveInfo[1]);
    printf("Please enter the frequency = ");
    scanf("%d", &waveInfo[2]);
    return waveInfo;
}

void printWaveInfo(int *waveInfo)
{
    printf("Wave Info:\n");
    printf("Amplitude A: %d\n", waveInfo[0]);
    printf("Amplitude B: %d\n", waveInfo[1]);
    printf("Frequency: %d\n", waveInfo[2]);
}

void generateWave(int *waveInfo)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = 9.81;
    int i;
    double t;
    double pi = 3.14159265358979323846;
    FILE *file;
    char time[100];
    char ampl;

    file = fopen("wave.txt", "w+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < 100; i++)
    {
        t = (double)i / 100.0;
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, waveValue);
    }
    fclose(file);
}