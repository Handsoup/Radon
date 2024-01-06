//Alarm.h

#ifndef ALARM_H
#define ALARM_H

#include <iostream>
#include <vector>
#include <cmath>

const double PI = 3.14159265358979323846;
const int SAMPLE_RATE = 44100; // Sample rate (samples per second)

inline void GenerateTone(int frequency, int duration) {
    int numSamples = SAMPLE_RATE * duration;
    double* buffer = new double[numSamples];

    // Generate PCM waveform for the tone
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = 0.5 * sin(2 * PI * frequency * i / SAMPLE_RATE);
    }

    // Play the generated PCM waveform
    for (int i = 0; i < numSamples; ++i) {
        std::cout << (char)(buffer[i] * 127 + 128);
    }

    delete[] buffer;
}

#endif // ALARM_H

