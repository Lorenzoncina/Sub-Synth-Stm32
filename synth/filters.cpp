//
// Created by lorenzo on 20/03/21.
//

#include "filters.h"

BiquadFilter::BiquadFilter(BiquadFilter::FilterType type){
    this->type = type;
    //filter's conefficients inizialization
    if(type == BiquadFilter::FilterType::FIRST_ORDER_LOW_PASS_FILTER){
        this->a0 = 0.0;
        this->a1 = 0.0;
        this->a2 = 0.0;
        this->b1 = 0.0;
        this->b2 = 0.0;
    } else if(type == BiquadFilter::FilterType::FIRST_ORDER_HIGH_PASS_FILTER){
        this->a0 = 0.0;
        this->a1 = 0.0;
        this->a2 = 0.0;
        this->b1 = 0.0;
        this->b2 = 0.0;
    }
    else if(type == BiquadFilter::FilterType::SECOND_ORDER_LOW_PASS_FILTER){
        this->a0 = 0.0;
        this->a1 = 0.0;
        this->a2 = 0.0;
        this->b1 = 0.0;
        this->b2 = 0.0;
    }
    else if(type == BiquadFilter::FilterType::SECOND_ORDER_HIGH_PASS_FILTER){
        this->a0 = 0.0;
        this->a1 = 0.0;
        this->a2 = 0.0;
        this->b1 = 0.0;
        this->b2 = 0.0;
    }

    lastinLeft = 0;
    lastin2Left= 0;
    lastinRight= 0;
    lastin2Right=0;
    lastoutLeft= 0;
    lastout2Left=0;
    lastoutRight=0;
    lastout2Right=0;

    //cutOff = new Knob("A",3);
    resonance = new Knob("A", 2);
    //cutOff::mode(Mode::INPUT);

}

void BiquadFilter::process() {
    auto &buffer = getBuffer();
    float *leftChannel = buffer.getWritePointer(0);
    float *rightChannel = buffer.getWritePointer(1);

    unsigned int temp,cutOffFreq;
    float res;
    //for(int i= 0; i<2; i++) {
        cutOffFreq = cutOff->read();
        temp = resonance->read();
        res = temp / 200.0;
        //res = 0.1;
        //map res beetwen 0 and 20
    //}
    //int cutOffFreq = cutOff::value();

    this->updateParameter(cutOffFreq, res);

    for(int i=0; i< buffer.getBufferLength();i++){
       currinLeft = leftChannel[i];
       currinRight= rightChannel[i];

       //difference equation of the biquadratic filter
       curroutLeft =currinLeft * a0 + lastinLeft * a1 + lastin2Left * a2 - lastoutLeft * b1 - lastout2Left * b2;
       curroutRight=currinRight* a0 + lastinRight * a1 + lastin2Right * a2 - lastoutRight * b1 - lastout2Right * b2;

       leftChannel[i] = curroutLeft;
       rightChannel[i] = curroutRight;

       lastinLeft = currinLeft;
       lastout2Left = lastinLeft;
       lastoutLeft = curroutLeft;
       lastout2Left = lastoutLeft;

       lastinRight = currinRight;
       lastout2Right = lastinRight;
       lastoutRight = curroutRight;
       lastout2Right = lastoutRight;
    }

}

void BiquadFilter::setFilterType(BiquadFilter::FilterType type) {
    this-> type = type;
}

void BiquadFilter::updateParameter( unsigned int cutOff,  float resonance) {
    if(type == BiquadFilter::FilterType::FIRST_ORDER_LOW_PASS_FILTER) {
        //1st order LPF
        // TODO add the 2sd order LPF
        float fs = audioDriver.getSampleRate();
        float teta = (2 * M_PI * cutOff) / fs;
        float gamma = cos(teta) / (1 + sin(teta));
        a0 = (1 - gamma) / 2;
        a1 = (1 - gamma) / 2;
        a2 = 0.0;
        b1 = -gamma;
        b2 = 0.0;
    }
    else if(type == BiquadFilter::FilterType::FIRST_ORDER_HIGH_PASS_FILTER){
        //1st order HPF
        float fs = audioDriver.getSampleRate();
        float teta = (2 * M_PI * cutOff) / fs;
        float gamma = cos(teta) / (1 + sin(teta));
        a0 = (1 + gamma) / 2;
        a1 = -((1 + gamma) / 2);
        a2 = 0.0;
        b1 = -gamma;
        b2 = 0.0;
    } else if(type == BiquadFilter::FilterType::SECOND_ORDER_LOW_PASS_FILTER){
        float fs = audioDriver.getSampleRate();
        float Q = resonance; //quality factor
        float teta = (2 * M_PI * cutOff) / fs;
        float d = 1/Q;
        float beta = (0.5 *(1 -(d/2)* sin(teta))) /(1+(d/2)*sin(teta));
        float gamma = (0.5 + beta)*cos(teta);
        a0 = (0.5 + beta - gamma) / 2.0;
        a1 = 0.5 + beta - gamma;
        a2 = (0.5 + beta - gamma) / 2.0;
        b1 = -2 * gamma;
        b2 = 2 * beta;

    } else if(type == BiquadFilter::FilterType::SECOND_ORDER_HIGH_PASS_FILTER){
        float fs = audioDriver.getSampleRate();
        float Q = resonance; //quality factor
        float teta = (2 * M_PI * cutOff) / fs;
        float d = 1/Q;
        float beta = (0.5 *(1 -(d/2)* sin(teta))) /(1+(d/2)*sin(teta));
        float gamma = (0.5 + beta)*cos(teta);
        a0 = (0.5 + beta + gamma) / 2.0;
        a1 = -(0.5 + beta + gamma);
        a2 = (0.5 + beta + gamma) / 2.0;
        b1 = -2 * gamma;
        b2 = 2 * beta;
    }
}