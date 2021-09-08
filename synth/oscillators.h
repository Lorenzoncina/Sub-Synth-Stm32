//
// Created by lorenzo on 20/03/21.
//

#ifndef SUB_SYNTH_STM32_OSCILLATORS_H
#define SUB_SYNTH_STM32_OSCILLATORS_H

#include "drivers/stm32f407vg_discovery/audio.h"
#include "audio/audio_processor.h"
#include "audio/audio_math.h"
#include <math.h>
#include "knob.h"
#include <cstdlib>
#include <time.h>

using namespace miosix;
using namespace std;
using namespace AudioMath;

/**
 * Sinusoidal Oscillator
 */
//typedef Gpio<GPIOA_BASE,0> knob;
class SinusoidalOsc : public AudioProcessor {
public:

    SinusoidalOsc(): sineLUT([](float x) { return std::sin(x); }, 0, 2 * M_PI,
                             AudioMath::LookupTableEdges::PERIODIC) {
        freqControll = new Knob("A",1);
        //knob::mode(Mode::INPUT_ANALOG);

    };

    void process() override;

private:
    AudioMath::LookupTable<128> sineLUT;
    float phase = 0;
    float phaseDelta = 440 * 2 * M_PI / 44100.0;
    Knob *freqControll;

};


/**
 * Triangular oscillator
 */

class SquareOsc : public AudioProcessor{
public:

   SquareOsc(): squareLUT([](float x) { if(x< M_PI) return 1; else return 0; }, 0, 2 * M_PI,
                               AudioMath::LookupTableEdges::PERIODIC){
        freqControll = new Knob("A",1);
    };

    void process() override;

private:
    float phase = 0;
    float phaseDelta;
    AudioMath::LookupTable<128> squareLUT;
    Knob *freqControll;

};


/**
 * White noise generator
 */

class WhiteNoise : public AudioProcessor {
public:
    //WhiteNoise();

    void process() override;
};


#endif //SUB_SYNTH_STM32_OSCILLATORS_H
