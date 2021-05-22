
#include "miosix.h"
#include "drivers/stm32f407vg_discovery/audio.h"
#include "audio/audio_processor.h"
#include "audio/audio_buffer.hpp"
#include "audio/audio_math.h"
#include "midi/midi.h"
#include "tests/midi_test_data.h"
#include <functional>
#include <algorithm>
#include <math.h>
#include <cstdint>
#include "synth/oscillators.h"
#include "synth/synth.h"
#include "synth/knob.h"



using namespace miosix;
using namespace std;
using namespace AudioMath;

typedef Gpio<GPIOA_BASE,5>  oscButton;

int oscType = 0;
Synth synth;

/*
void *buttonThread(void *arg){
    oscButton::mode(Mode::INPUT);
    int value, oldValue = 0;
    while(true){
        value = oscButton::value();
        //every rising edge change the osc type
        if(value != oldValue && value == 1){
            oscType += 1;
            if(oscType > 2)
                oscType = 0;
            synth.setOsc(oscType);
        }
        oldValue = value;
    }
}
*/
int main() {

    // initializing the audio driver
    AudioDriver &audioDriver = AudioDriver::getInstance();
    audioDriver.getBuffer();
    //AudioProcessorTestOld audioProcessorTestOld;
    //AudioProcessorTest audioProcessorTestNew;
    //SinusoidalOsc sinOsc;

    audioDriver.init(SampleRate::_44100Hz);
    audioDriver.setAudioProcessable(synth);

    //start the processing
    audioDriver.start();

    //Thread button

    //pthread_t t;
    //pthread_create(&t ,NULL, buttonThread, NULL);

    while (true){

    }

}
