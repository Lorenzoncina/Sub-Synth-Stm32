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
typedef Gpio<GPIOB_BASE,2>  filterButton;

class Synth : public AudioProcessor{
public:
    Synth();

    void process() override;

    void setOsc(int oscChooserArg);

private:
    int oscType, filterType;
    int oscValue, oscOldValue, filterValue, filterOldValue;
    //Oscillators
    WhiteNoise noise;
    SinusoidalOsc sinOsc;
    SquareOsc sqrOsc;
    //filters
    BiquadFilter* lpf;
    BiquadFilter* hpf;
    BiquadFilter* lpf2;
    BiquadFilter* hpf2;
    //Volume controller
    Volume vol;
};


#endif //SUB_SYNTH_STM32_SYNTH_H
