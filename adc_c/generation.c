#include "generation.h"

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
    printf("Please enter the 1rst frequency = ");
    scanf("%d", &waveInfo[2]);
    printf("Please enter the 2nd frequency = ");
    scanf("%d", &waveInfo[3]);
    return waveInfo;
}

void printWaveInfo(int *waveInfo)
{
    printf("Wave Info:\n");
    printf("Amplitude A: %d\n", waveInfo[0]);
    printf("Amplitude B: %d\n", waveInfo[1]);
    printf("1rst Frequency: %d\n", waveInfo[2]);
    printf("2nd Frequency: %d\n", waveInfo[3]);
}

void generateWave(int *waveInfo)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

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

    for (float i = 0; i < 5; i += 0.01)
    {
        t = (double)i / 100.0;
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, waveValue);
    }
    fclose(file);
}

float bestSamplingRate()
{
    FILE *fichier = fopen("wave.txt", "r"); // Ouvre le fichier en lecture

    if (fichier == NULL)
    {
        perror("Error opening file!\n");
        return 1;
    }

    double time, amplitude;
    double amplitude_max = -1;
    double maxTime = 0;

    while (fscanf(fichier, "%lf %lf", &time, &amplitude) == 2)
    {
        if (amplitude > amplitude_max)
        {
            amplitude_max = amplitude;
            maxTime = time;
        }
    }

    fclose(fichier);

    printf("Amplitude max : %.6f at t = %.6f secondes\n", amplitude_max, maxTime);
    return 1 / (float)amplitude_max;
}

void generateSamplingWave(int *waveInfo, float sampling)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double t;
    double pi = 3.14159265358979323846;
    FILE *file;
    char time[100];
    char ampl;

    file = fopen("wave_sampled.txt", "w+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (float i = 0; i < 5; i += sampling)
    {
        t = (double)i / 100.0;
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, waveValue);
    }
    fclose(file);
}

void generateQuantizedWave(int *waveInfo, float sampling)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double t;
    double pi = 3.14159265358979323846;
    FILE *file;

    file = fopen("wave_quantized.txt", "w+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (float i = 0; i < 5; i += sampling)
    {
        t = (double)i / 100.0;
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        fprintf(file, "%lf %lf\n", t, round(waveValue));
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

void generateQuantizedWaveBinary(int *waveInfo, float sampling)
{
    int A = waveInfo[0];
    int B = waveInfo[1];
    int f = waveInfo[2];
    int g = waveInfo[3];

    double t;
    double pi = 3.14159265358979323846;
    FILE *binaryFile;
    FILE *quantizedFile;

    binaryFile = fopen("wave_binary.txt", "w+");
    quantizedFile = fopen("wave_quantized_binary.txt", "w+");
    if (binaryFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    if (quantizedFile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (float i = 0; i < 5; i += sampling)
    {
        t = (double)i / 100.0;
        double waveValue = A * sin(2 * pi * f * t) + B * cos(2 * pi * g * t);
        char binary[17];
        int_to_binary((int)round(waveValue), 16, binary);
        fprintf(quantizedFile, "%lf %s\n", t, binary);
        fprintf(binaryFile, "%s", binary);
    }
    fclose(binaryFile);
    fclose(quantizedFile);
}