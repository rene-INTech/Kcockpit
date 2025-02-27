//
// Created by rene on 23/12/18.
//

#ifndef TEENSY_LED_H
#define TEENSY_LED_H

#include "Arduino.h"
#include "MAX7221.h"

struct address{
    unsigned int registre;
    unsigned int bit;
};


class LED {
private:
    MAX7221* host;
    address adr;

    byte toByte(int data);

public:
    LED(MAX7221* newHost, address newAdr);
    void on();
    void off();
};


#endif //TEENSY_LED_H
