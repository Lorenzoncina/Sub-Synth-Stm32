//
// Created by lorenzo on 21/03/21.
//

#include "synth.h"

Synth::Synth()/*: lpf(BiquadFilter::FilterType::HIGH_PASS_FILTER)*/ {
    lpf = new BiquadFilter( BiquadFilter::FilterType::FIRST_ORDER_LOW_PASS_FILTER);
    hpf = new BiquadFilter(BiquadFilter::FilterType::FIRST_ORDER_HIGH_PASS_FILTER);
    lpf2 = new BiquadFilter( BiquadFilter::FilterType::SECOND_ORDER_LOW_PASS_FILTER);
    hpf2 = new BiquadFilter(BiquadFilter::FilterType::FIRST_ORDER_HIGH_PASS_FILTER);
    oscButton::mode(Mode::INPUT);
    filterButton::mode(Mode::INPUT);
    oscType = 0;
    oscOldValue = 0;
    filterType=0;
    filterOldValue=0;
}

void Synth::process() {
    oscValue = oscButton::value();

    //Oscillator selection

    if(oscValue != oscOldValue && oscValue == 1){
        oscType += 1;
        if(oscType > 2)
            oscType = 0;
    }
    oscOldValue = oscValue;
    //selection of the oscillator
    if(oscType == 0){
        sinOsc.process();
    }else if(oscType == 1){
        sqrOsc.process();
    }else if(oscType == 2){
        noise.process();
    }

    //Filter selection
    filterValue = filterButton::value();
    if(filterValue != filterOldValue && filterValue == 1){
        filterType += 1;
        if(filterType > 3)
            filterType = 0;
    }
    oscOldValue = oscValue;
    if(filterType == 0) {
        lpf->process();
    }
    else if(filterType == 1){
        hpf->process();
    }else if(filterType == 2) {
        lpf2->process();
    }else if(filterType == 3) {
        hpf2->process();
    }

    vol.process();
}

void Synth::setOsc(int oscChooserArg) {
    //oscChooser = oscChooserArg;
}