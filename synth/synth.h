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
#include "volume.h"
//#include "./main.cpp"

typedef Gpio<GPIOA_BASE,5>  oscButton;

class Synth : public AudioProcessor{
public:
    Synth();

    void process() override;

private:
    int oscChooser;
    //WhiteNoise noise;
    SinusoidalOsc sinOsc;
    SquareOsc sqrOsc;
    BiquadFilter* lpf;
    Volume vol;
};


#endif //SUB_SYNTH_STM32_SYNTH_H
