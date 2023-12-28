// Libraries
#include <HX711_ADC.h> // https://github.com/olkal/HX711_ADC
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c

// Constants
const int tareButton0Pin = 2;
const int tareButton1Pin = 3;

const int HX711_0_dout = 4; //mcu > HX711_0 dout pin
const int HX711_0_sck = 5; //mcu > HX711_0 sck pin
const int HX711_1_dout = 6; //mcu > HX711_1 dout pin
const int HX711_1_sck = 7; //mcu > HX711_1 sck pin

const int calVal0_eepromAdress = 0;
const int calVal1_eepromAdress = 4;

unsigned long startUpStabilizingTime = 2000;
bool startUpTare = true;

unsigned long t0 = 0;
unsigned long t1 = 0;

const int serialPrintInterval0 = 500; //increase value to slow down serial print activity
const int serialPrintInterval1 = 500; //increase value to slow down serial print activity

//int tareCountdown0;
//int tareCountdown1;
//const int tareCountdownThreshold = 500;

// Constructors
HX711_ADC LoadCell0(HX711_0_dout, HX711_0_sck);
HX711_ADC LoadCell1(HX711_1_dout, HX711_1_sck);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(57600);

  lcd.init();
  lcd.backlight();

  pinMode(tareButton0Pin, INPUT);
  pinMode(tareButton1Pin, INPUT);

  float calibrationValue0;
  float calibrationValue1;

  LoadCell0.begin();
  LoadCell1.begin();

  //EEPROM.begin(512);
  EEPROM.get(calVal0_eepromAdress, calibrationValue0);
  EEPROM.get(calVal1_eepromAdress, calibrationValue1);

  LoadCell0.start(startUpStabilizingTime, startUpTare);
  LoadCell1.start(startUpStabilizingTime, startUpTare);

  if (LoadCell0.getTareTimeoutFlag() || LoadCell1.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell0.setCalFactor(calibrationValue0);
    LoadCell1.setCalFactor(calibrationValue1);
    Serial.println("Startup is complete");
  }
}

void loop() {

  /*
    if (isButtonPressed(0))
    {
      LoadCell0.tareNoDelay();
      LCDPrintTare(0);
    }
    if (isButtonPressed(1))
    {
      LoadCell1.tareNoDelay();
      LCDPrintTare(1);
    }
  */

  static boolean newDataReady0 = 0;
  if (LoadCell0.update()) newDataReady0 = true;
  if (newDataReady0) {
    if (millis() > t0 + serialPrintInterval0) {
      float reading0 = LoadCell0.getData();
      LCDPrint(0, reading0);
      newDataReady0 = 0;
      t0 = millis();
    }
  }

  static boolean newDataReady1 = 0;
  if (LoadCell1.update()) newDataReady1 = true;
  if (newDataReady1) {
    if (millis() > t1 + serialPrintInterval1) {
      float reading1 = LoadCell1.getData();
      LCDPrint(1, reading1);
      newDataReady1 = 0;
      t1 = millis();
    }
  }

}
