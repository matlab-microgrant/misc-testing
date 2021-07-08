/*
 * Project:  Mathworks Lab-in-a-box project 2021
 * Author:   P.Taylor (V1), B. O'Connell (V2)
 * Lab:      Signal/Noise - Transmitting Arduino
 * Version:  2
 * Date:     2021-07-07
 * 
 * This code is to be loaded onto the transmition Arduino - Redboard 1. 
 * 
 * 
 * 
 * This is a slave reciever of the master slave pair. 
 * It responds to a new value of x is sent to it from the Noise Arduino to determine what 
 * the transmission rate should be. 
 * the 
 * 
 * For reference:
 * https://www.arduino.cc/en/Reference/Wire
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
 * 
 * 
 * 
 */

#include <Wire.h>//Include the Wire library to talk I2C, communication protocol

int tx_pin = 13;
int x = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(9); //tx address is 9, arbitrary 
  Wire.onReceive(receiveEvent);
  // onRecieve registers a function to be called when a slave device receives a transmission from a master.
  pinMode(tx_pin, OUTPUT);
  Serial.begin(9600);
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from I2C
  Serial.println(x);
}

void end_program() { //if you get zero, end program, right now its turn LED off
  digitalWrite(tx_pin, LOW);
}

void loop() {
  if (x == 0) {
    end_program();
    //signal profile of each experiment
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
