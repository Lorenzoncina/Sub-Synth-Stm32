//
// Created by lorenzo on 18/05/21.
//

#ifndef SUB_SYNTH_STM32_VOLUME_H
#define SUB_SYNTH_STM32_VOLUME_H

#include "miosix.h"
#include "drivers/stm32f407vg_discovery/audio.h"
#include "audio/audio_processor.h"
#include "audio/audio_math.h"
#include <math.h>
#include "knob.h"

using namespace AudioMath;

class Volume : public AudioProcessor{
public:
    Volume();
    void process() override;
private:
    Knob *volumeControll;
    float currinLeft, currinRight;
};


#endif //SUB_SYNTH_STM32_VOLUME_H
