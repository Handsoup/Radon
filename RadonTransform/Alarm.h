//Alarm.h

#ifndef ALARM_H
#define ALARM_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>

inline void playSound(unsigned frequency, double duration) {
    const unsigned SAMPLE_RATE = 44100;
    const double TWO_PI = 6.28318;

    const unsigned NUM_SAMPLES = SAMPLE_RATE * duration;

    std::vector<sf::Int16> samples(NUM_SAMPLES);

    for (unsigned i = 0; i < NUM_SAMPLES; ++i) {
        double sample = std::sin(frequency * TWO_PI * i / SAMPLE_RATE);
        samples[i] = static_cast<sf::Int16>(sample * 32767);
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), NUM_SAMPLES, 1, SAMPLE_RATE);

    sf::Sound sound(buffer);
    sound.play();

    while (sound.getStatus() == sf::Sound::Playing) {
        // Wait until the sound finishes playing
    }
}

#endif // ALARM_H

