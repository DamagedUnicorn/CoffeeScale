// Abbreviations:
//    B: beans
//    L: liquid

// Libraries
#include <HX711_ADC.h> // https://github.com/olkal/HX711_ADC
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c


// Constants
const int tareButtonBPin = 1;
const int tareButtonLPin = 1;
const int loadCellSckPin = 1;
const int loadCellBDtPin = 1;
const int loadCellLDtPin = 1;

const int loadCellBCalFactor = 1;
const int loadCellLCalFactor = 1;

void setup() {
  pinMode(tareButtonBPin, INPUT_PULLUP);
  pinMode(tareButtonLPin, INPUT_PULLUP);
}

void loop() {

}
