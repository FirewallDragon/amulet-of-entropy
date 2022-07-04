#ifndef BUTTON_H
#define BUTTON_H

/*
=======================================================================================
    Define a simple Button object. The main job here is to debounce the button.
    See: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
=======================================================================================
*/

#include <string>
#include <Wire.h>

#include "utils.h"

using namespace std;

// Button IO pins
const int B1_pin = 5;
const int B2_pin = 6;
const int B3_pin = 7;
const int B4_pin = 8;

const bool NOT_PRESSED = LOW;
const bool PRESSED = HIGH;


class Button
{
public:
    Button(int pin, const string & bname)
    : _pin(pin), _name(bname)
    {
        pinMode(_pin, INPUT_PULLUP);
    }

    const char * name() const { return _name.c_str(); }
    bool read_button();

private:
    int _pin;
    const string _name;

    bool _state = NOT_PRESSED;
    bool _previous_reading = NOT_PRESSED;
    unsigned long _last_reading_change = 0;
    unsigned long _debounce_delay_millis = 50;
};

#endif