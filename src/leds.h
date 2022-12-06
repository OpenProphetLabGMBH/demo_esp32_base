/**
 * @brief
 *
 */

#include <Arduino.h>

const int booleanLEDPin = 25;
const int analogLEDPin = 33;

void setupLEDs(){
    pinMode(booleanLEDPin, OUTPUT);
    pinMode(analogLEDPin, OUTPUT);
}

void updateLEDs(){
    digitalWrite(booleanLEDPin, ledState);
    analogWrite(analogLEDPin, ledBrightness);
}
