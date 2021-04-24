//
// Created by lorenzo on 21/03/21.
//

#include "synth.h"

Synth::Synth()/*: lpf(BiquadFilter::FilterType::HIGH_PASS_FILTER)*/ {
    lpf = new BiquadFilter( BiquadFilter::FilterType::FIRST_ORDER_LOW_PASS_FILTER);
}

void Synth::process() {
    FastInterruptDisableLock lock;
    //osc.process();
    noise.process();
    lpf->process();
}
