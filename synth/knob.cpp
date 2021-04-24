//
// Created by mailf on 25/02/2021.
//

#include "knob.h"
#include <miosix.h>

#define ANALOG_MODE 3

using namespace std;
using namespace miosix;


Knob::Knob(string port, int pin){
    // Enabling clock
    this->port = port;
    this->pin = pin;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // clock for ADC1
    // GPIOA1 configuration
    if(port == "A") {
        // TODO check if it's aproblem write two time on this register
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // clock for GPIOA
        GPIOA->MODER |= (ANALOG_MODE << (2*pin)); // analog mode
        GPIOA->AFR[0] |= (6 << (4 * pin)); // alternate function ADC123_IN1


    }else if(port =="B")
    {
        RCC->AHB1ENR |= (1<<1);
        GPIOB->MODER |= (ANALOG_MODE << (2 * pin)); // analog mode
        GPIOB->AFR[0] |= (6 << (4 * pin)); // alternate function ADC123_IN1
    }

    // ADC1 configuration
    //ADC1->CR1 |= ADC_CR1_SCAN; // scan mode
    ADC1->CR2 |= ADC_CR2_ADON; // enable ADC1
    //ADC1->CR2 |= (1<<10);
    //ADC1->SQR1 = 0; //number of conversion = number of knob

}

unsigned int Knob::read() {

    ADC1->SQR3 = 0;
    ADC1->SR = 0;
    if(pin == 1 ) {
        ADC1->SQR3 = (1 << 0); // single conversion from channel 1
    }
    else if(pin == 3) {
        ADC1->SQR3 = (1 << 0) | (1 << 1); // single conversion from channel 3
    } else if(pin == 2) {
        ADC1->SQR3 = (1 << 1); // single conversion from channel 3
    }

    ADC1->CR2 |= ADC_CR2_SWSTART; // starts the single conversion
    while (!ADC1->SR & (1<<1)); // waits until the end of conversion
    return ADC1->DR; // value from DAC1
}



/**
Knob::Knob(string port, int pin) {
    string portLetter= "GPIO"+port+"_BASE";
    typedef Gpio<portLetter,pin> knob;
}

int Knob::read() {
    return knob::value();
   **/
