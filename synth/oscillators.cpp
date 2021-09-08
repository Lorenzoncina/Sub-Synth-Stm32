//
// Created by lorenzo on 20/03/21.
//

#include "oscillators.h"


void SinusoidalOsc::process(){
    unsigned int freq;
    //while (true){
        freq = freqControll->read();
       // freq = linearMap(freq, 0, 4095, 0, 1000);
    //}

    phaseDelta = freq * 2 * M_PI / 44100.0;
    // Todo insert a knob for the gain if the oscullator
    auto &buffer = getBuffer();
    float *left = buffer.getWritePointer(0);
    float *right = buffer.getWritePointer(1);
    static float linearCount = 0.0;

    for (auto i = 0; i < getBufferSize(); i += 1) {
        left[i] = 0.8 * sineLUT(phase);
        right[i] = left[i];
        phase += phaseDelta;
        if (phase >= 2 * M_PI) phase -= 2 * M_PI;
    }
}


void SquareOsc::process() {
    auto &buffer = getBuffer();
    float *left = buffer.getWritePointer(0);
    float *right = buffer.getWritePointer(1);
    unsigned int freq = freqControll->read();
    phaseDelta = freq * 2 * M_PI / 44100.0;;

    for (auto i = 0; i < getBufferSize(); i += 1) {
        left[i] = squareLUT(phase);
        right[i] = left[i];
        phase += phaseDelta;
        if (phase >= 2 * M_PI) phase -= 2 * M_PI;
    }
}


void WhiteNoise::process() {
    auto &buffer = getBuffer();
    float *left = buffer.getWritePointer(0);
    float *right = buffer.getWritePointer(1);
    float randomSample = 0;
    for (auto i = 0; i < getBufferSize(); i += 1) {
        randomSample = (float) rand() / RAND_MAX;
        left[i] = randomSample;
        right[i] = randomSample;

    }
}
