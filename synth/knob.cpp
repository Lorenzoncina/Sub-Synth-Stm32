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
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // clock for GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // clock for ADC1
    // GPIOA1 configuration
    if(port == "A") {
        GPIOA->MODER |= (ANALOG_MODE << (2 * pin)); // analog mode
        GPIOA->AFR[0] |= (6 << (4 * pin)); // alternate function ADC123_IN1
    }else if(port =="B")
    {
        GPIOB->MODER |= (ANALOG_MODE << (2 * pin)); // analog mode
        GPIOB->AFR[0] |= (6 << (4 * pin)); // alternate function ADC123_IN1
    }else if(port =="C") {

        GPIOC->MODER |= (ANALOG_MODE << (2 * pin)); // analog mode
        GPIOC->AFR[0] |= (6 << (4 * pin)); // alternate function ADC123_IN1
    }

    // ADC1 configuration
    ADC1->CR1 |= ADC_CR1_SCAN; // scan mode
    ADC1->CR2 |= ADC_CR2_ADON; // enable ADC1
    ADC1->SQR3 |= (1 << 0); // single conversion from channel 1

}

unsigned int Knob::read() {
    ADC1->CR2 |= ADC_CR2_SWSTART; // starts the conversion
    while (!ADC1->SR & ADC_SR_EOC); // waits untill the end of conversion
    return ADC1->DR; // value from DAC1
}