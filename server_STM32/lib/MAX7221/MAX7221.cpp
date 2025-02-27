//
// Created by rene on 14/12/18.
//

#include "MAX7221.h"

MAX7221::MAX7221(uint8_t pinSelect, uint8_t position): selectPin(pinSelect), position(position) {
    pinMode(selectPin, OUTPUT_OPEN_DRAIN);
    memset(state, 0, sizeof(state));
    write(SCAN_LIMIT, 0x07);
    setIntensity(15);
    wake();
    flush();
}

void MAX7221::sleep() {
    write(SHUTDOWN, 0b0000);
}

void MAX7221::wake() {
    write(SHUTDOWN, 0b0001);
}

void MAX7221::test() {
    write(TEST, 0b0001);
    delay(1000);
    write(TEST, 0b0000);
}

void MAX7221::nbDigitsDisplayed(int nbdigit) {
    if(nbdigit>7 or nbdigit<1){return;}
    write(SCAN_LIMIT, (uint8_t)nbdigit);
}

void MAX7221::setDecodeMode(uint8_t mode) {
    write(DECODE, mode);
}

void MAX7221::setRegister(DigitsRegister digit, uint8_t data) {
    state[digit-1]=data;
}

uint8_t MAX7221::getRegister(DigitsRegister digit) {
    return state[digit-1];
}

void MAX7221::flushDigit(DigitsRegister digit) {
    digitalWrite(selectPin, LOW);
    //SPI.transfer((unsigned)digit);
    //SPI.transfer(state[digit-1]);
    SPI.transfer((unsigned)digit);
    SPI.transfer(state[digit-1]);
    static uint16_t zero = 0;
    for(int i = 0; i<position; ++i){
        SPI.transfer16(zero);
    }
    digitalWrite(selectPin, HIGH);
}

void MAX7221::flush() {
    for(auto digit:allRegisters){
        flushDigit(digit);
    }
}

void MAX7221::setIntensity(int newIntensity) {
    if(newIntensity>16 or newIntensity<1){return;}
    write(INTENSITY, (uint8_t)newIntensity);
}

void MAX7221::write(Register r, uint8_t data) {
    digitalWrite(selectPin, LOW);
    SPI.transfer((unsigned)r);
    SPI.transfer(data);
    static uint16_t zero = 0;
    for(int i = 0; i<position; ++i){
        SPI.transfer16(zero);
    }
    digitalWrite(selectPin, HIGH);
}
