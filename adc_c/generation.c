#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100000
#define DUREE 1.5 

int *getWaveInfo()
{
    int *waveInfo = (int *)malloc(4 * sizeof(int));
    if (waveInfo == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    printf("Please enter the first amplitude (A) = ");
    scanf("%d", &waveInfo[0]);
    printf("Please enter the second amplitude (B) = ");
    scanf("%d", &waveInfo[1]);
    printf("Please enter the 1rst frequency (f) = ");
    scanf("%d", &waveInfo[2]);
    printf("Please enter the 2nd frequency (g) = ");
    scanf("%d", &waveInfo[3]);
    return waveInfo;
}

void generateWave(int *waveInfo)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double pi = 3.14159265358979323846;
    FILE *file = fopen("../adc_txt/wave.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    double dt = 0.0001;
    for (double t = 0; t < DUREE; t += dt)
    {
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, waveValue);
    }
    fclose(file);
}

float bestSamplingRate()
{
    FILE *file = fopen("../adc_txt/wave.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    double time[MAX_SIZE], amplitude[MAX_SIZE];
    int n = 0;

    while (fscanf(file, "%lf %lf", &time[n], &amplitude[n]) == 2 && n < MAX_SIZE)
    {
        n++;
    }
    fclose(file);

    if (n < 3)
    {
        printf("Not enough data points to estimate frequency.\n");
        return -1;
    }

    double lastPeakTime = 0;
    double periodSum = 0;
    int peakCount = 0;

    // Recherche pics locaux (maximum)
    for (int i = 1; i < n - 1; i++)
    {
        if (amplitude[i] > amplitude[i - 1] && amplitude[i] > amplitude[i + 1])
        {
            if (lastPeakTime > 0)
            {
                periodSum += (time[i] - lastPeakTime);
                peakCount++;
            }
            lastPeakTime = time[i];
        }
    }

    if (peakCount == 0)
    {
        printf("Not enough peaks to estimate frequency.\n");
        return -1;
    }

    double avgPeriod = periodSum / peakCount;
    double f_max = 1.0 / avgPeriod;

    double samplingRate = 1 / (2 * f_max); // fréquence d'échantillonnage minimale selon Nyquist

    printf("Estimated maximum frequency: %.3f Hz n", f_max);
    printf("Nyquist minimum sampling rate: %.3f Hz n", samplingRate);

    return (float)samplingRate;
}

void generateSamplingWave(int *waveInfo, float samplingInterval)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double pi = 3.14159265358979323846;
    FILE *file = fopen("../adc_txt/wave_sampled.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (double t = 0; t < DUREE; t += samplingInterval)
    {
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, waveValue);
    }
    fclose(file);
}

void generateQuantizedWave(int *waveInfo, float samplingInterval)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double pi = 3.14159265358979323846;
    FILE *file = fopen("../adc_txt/wave_quantized.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (double t = 0; t < DUREE; t += samplingInterval)
    {
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %d\n", t, (int)round(waveValue));
    }
    fclose(file);
}

void int_to_binary(int value, int bits, char *out)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        out[bits - 1 - i] = (value & (1 << i)) ? '1' : '0';
    }
    out[bits] = '\0';
}

void generateQuantizedWaveBinary(int *waveInfo, float samplingInterval)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double pi = 3.14159265358979323846;
    FILE *binaryFile = fopen("../adc_txt/wave_binary.txt", "w");
    FILE *quantizedFile = fopen("../adc_txt/wave_quantized_binary.txt", "w");
    if (binaryFile == NULL || quantizedFile == NULL)
    {
        printf("Error opening file!\n");
        if (binaryFile) fclose(binaryFile);
        if (quantizedFile) fclose(quantizedFile);
        return;
    }

    for (double t = 0; t < DUREE; t += samplingInterval)
    {
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        
        // Clamp to signed 16-bit range
        if (waveValue > 32767) waveValue = 32767;
        if (waveValue < -32768) waveValue = -32768;

        int signedVal = (int)round(waveValue);
        unsigned int unsignedVal = (unsigned int)(signedVal + 32768); // Shift to range [0, 65535]

        // Convert to 16-bit binary string
        char binary[17];
        int_to_binary(unsignedVal, 16, binary);

        // Write to files
        fprintf(quantizedFile, "%lf %s\n", t, binary);
        fprintf(binaryFile, "%s", binary);
    }

    fclose(binaryFile);
    fclose(quantizedFile);
}