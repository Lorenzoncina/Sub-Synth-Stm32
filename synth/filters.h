//
// Created by lorenzo on 20/03/21.
//

#ifndef SUB_SYNTH_STM32_FILTERS_H
#define SUB_SYNTH_STM32_FILTERS_H

#include "miosix.h"
#include "drivers/stm32f407vg_discovery/audio.h"
#include "audio/audio_processor.h"
#include "audio/audio_math.h"
#include <math.h>
#include "knob.h"


using namespace miosix;


/**
 * Biquadratic Filter implementation
 */
class BiquadFilter : public AudioProcessor{
public:

    enum FilterType{
        FIRST_ORDER_LOW_PASS_FILTER,
        FIRST_ORDER_HIGH_PASS_FILTER,
        SECOND_ORDER_LOW_PASS_FILTER,
        SECOND_ORDER_HIGH_PASS_FILTER
    };

    /**
     * Get an instance of a biquad filter
     * @param type of the filter: LPF,HPF
     */
    BiquadFilter(BiquadFilter::FilterType type);

    /**
     * Change type of the filter, between Low-pass and High-pass
     * @param type
     */
    void setFilterType(BiquadFilter::FilterType type);

    /**
     * Filter the audio buffer
     */
    void process() override;


private:

    FilterType type;

    void updateParameter( unsigned int cutOff, float resonance);

    float currinLeft, lastinLeft, lastin2Left;
    float currinRight, lastinRight, lastin2Right;
    float curroutLeft, lastoutLeft, lastout2Left;
    float curroutRight, lastoutRight, lastout2Right;
    float a0,a1,a2, b1,b2;

    Knob *cutOff;
    //Knob *resonance;
    //typedef Gpio<GPIOB_BASE,2> cutOff;

};




#endif //SUB_SYNTH_STM32_FILTERS_H
