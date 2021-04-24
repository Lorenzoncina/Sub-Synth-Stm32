//
// Created by Federico Di Marzo on 25/02/2021.
//

#ifndef MIOSIX_AUDIO_DRIVER_KNOB_H
#define MIOSIX_AUDIO_DRIVER_KNOB_H

#include <miosix.h>
#include "string"

using namespace std;

class Knob {
public:
    //typedef Gpio<P,N>  knobPin;
    Knob(string port, int pin);
    unsigned int read();
private:

    string port;
    int pin;


};

#endif //MIOSIX_AUDIO_DRIVER_KNOB_H
