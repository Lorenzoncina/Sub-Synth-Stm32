//
// Created by lorenzo on 21/03/21.
//

#ifndef SUB_SYNTH_STM32_SYNTH_H
#define SUB_SYNTH_STM32_SYNTH_H
#include "drivers/stm32f407vg_discovery/audio.h"
#include "audio/audio_processor.h"
#include "audio/audio_math.h"
#include <math.h>
#include "oscillators.h"
#include "filters.h"
//#include "./main.cpp"


class Synth : public AudioProcessor{
public:
    Synth();

    void process() override;

private:

    WhiteNoise noise;
    //SinusoidalOsc osc;
    //SquareOsc osc;
    BiquadFilter* lpf;
};


#endif //SUB_SYNTH_STM32_SYNTH_H
