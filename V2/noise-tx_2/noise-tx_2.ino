/*
 * Project:  Mathworks Lab-in-a-box project 2021
 * Author:   P.Taylor (V1), B. O'Connell (V2)
 * Lab:      Signal/Noise - Transmitting Arduino
 * Version:  2
 * Date:     2021-07-07
 * 
 * This code is to be loaded onto the transmition Arduino. 
 * 
 * 
 * This is a template for lab communication with the various boards.
 * This version simplifies MATLAB commands to a single line and parses them
 * instead ofMATLAB sending a command, waiting, then sending a follow up. 
 * For variables like the Sample Rate, MATLAB should write "sample rate:45".
 * This script will recognize that start of the string and convert the portion
 * after the ':' to correct necessary variable. 
 * For actions, MATLAB just needs to write the command like "Datapoint" or "LiveSampling"
 * for the sensor hardware to begin that process and output it. See the examples below. 
 * 
 * For data collection from the sensor(s), that activity should be created in the
 * function dataPoint() and outputted in a comma seperated format as a string.
 * For collecting multiple datapoints, there are elements incorporated below that
 * utilize multiple calls for the dataPoint() command. That may not be sufficient for
 * your needs to you may need to add a sampling() or dataset() function to open a
 * data stream or collect a finite set of datapoints. Keep in mind the output buffer 
 * is limited to 64 bytes. 
 * 
 */

#include <Wire.h>//Include the Wire library to talk I2C

int tx_pin = 13;
int x = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  // onRecieve registers a function to be called when a slave device receives a transmission from a master.
  pinMode(tx_pin, OUTPUT);
  Serial.begin(9600);
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
  Serial.println(x);
}

void end_program() {
  digitalWrite(tx_pin, LOW);
}

void loop() {
  if (x == 0) {
    end_program();
  } else if (x == 1) {
    // quarter-second pulses
    digitalWrite(tx_pin, HIGH);
    delay(250);
    digitalWrite(tx_pin, LOW);
    delay(250);
  } else if (x == 13) {
    // eighth-second pulses
    digitalWrite(tx_pin, HIGH);
    delay(125);
    digitalWrite(tx_pin, LOW);
    delay(125);
  }

}
