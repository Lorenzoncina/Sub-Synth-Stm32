//
// Created by lorenzo on 18/05/21.
//

#include "volume.h"

Volume::Volume() {
    volumeControll = new Knob("A",3);
}

void Volume::process() {
    auto &buffer = getBuffer();
    float *leftChannel = buffer.getWritePointer(0);
    float *rightChannel = buffer.getWritePointer(1);

    unsigned int volume;
    float vol;
    //while(true) {
        volume = volumeControll->read();

        vol = linearMap(volume, 0.0, 4095.0, 0.0, 1.0);
    //}
    for(int i=0; i< buffer.getBufferLength();i++) {
        currinLeft = leftChannel[i];
        currinRight = rightChannel[i];

        leftChannel[i] = currinLeft * vol;
        rightChannel[i] =  currinRight *  vol;
    }


    }
