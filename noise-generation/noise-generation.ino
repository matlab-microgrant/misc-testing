//First attempt at making noise
//Connect to DAC and generate random values
#include <Wire.h>//Include the Wire library to talk I2C

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0.
#define MCP4725_ADDR 0x60
//For devices with A0 pulled HIGH, use 0x61

//Sinewave Tables were generated using this calculator:
//http://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml

void setup()
{
  Wire.begin();

  // Set A2 and A3 as Outputs to make them our GND and Vcc, GND?, Vcc?
  //which will power the MCP4725
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(A2, LOW);//Set A2 as GND
  digitalWrite(A3, HIGH);//Set A3 as Vcc
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                     // cmd to update the DAC
  int toSend = random(4096);// why random?
  Wire.write(toSend >> 4);        // the 8 most significant bits...
  Wire.write((toSend & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
  int flipper = random(2); //flipper?
  if (flipper == 1) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(1);
}
