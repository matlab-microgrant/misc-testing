/*
 * Project:  Mathworks Lab-in-a-box project 2021
 * Author:   P.Taylor (V1), B. O'Connell (V2)
 * Lab:      Signal/Noise - Noise Arduino
 * Version:  2
 * Date:     2021-07-07
 * 
 * This code is to be loaded onto the Noise Arduino - The Arduino Mini. 
 * 
 * 
 * 
 * This is a master reciever of the master slave pair. 
 * It sends a value to the slave reciever through i2c. That value is based on the dip-pins selected
 * 
 * 
 * For reference:
 * https://www.arduino.cc/en/Reference/Wire
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
 * 
 * 
 * 
 */

#include <Wire.h>//Include the Wire library to talk I2C
//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0.
#define MCP4725_ADDR 0x60 //name of DAC, 96
//For devices with A0 pulled HIGH, use 0x61

// DIP control pins
int dip_pins[6] = {2, 3, 4, 5, 6, 7};
// pin that controls sign of output
int sign_switch_pin = 9;

bool dip_vals[6] = {0, 0, 0, 0, 0, 0};
byte dip_setting = 0;

int pot_pin = 23; // A0
int pot_val = 0;
void setup() {
  // put your setup code here, to run once:
  // DIP control pins
  for (int i = 0; i < 6; i++) {
    pinMode(dip_pins[i], INPUT_PULLUP);
  }
  // for sign switch
  pinMode(sign_switch_pin, OUTPUT);

  // setup i2c for ard-ard comms
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  // if 'set' switch is closed, begin experiment
  if (digitalRead(dip_pins[5]) == LOW) {
    digitalWrite(13, HIGH); //when experiment on, have light on
    execute_program(dip_setting); //what does this program do
  } else { //otherwise, see what the controls say, should not change experiment mid experiment by changing the dip switches
    // read other pins to get values when experiemnt is not on so when experiement is on the data is already available
    for (int i = 0; i < 5; i++) {
      dip_vals[i] = !digitalRead(dip_pins[i]); //reads dip swtich values
    }
    for (int i = 0; i < 5; i++) {
      bitWrite(dip_setting, i, dip_vals[5 - 1 - i]); //Taking values from dip val and turning it into a bit- dip setting
    }
    pot_val = analogRead(pot_pin);
    Serial.println(dip_setting);
  }

  delay(5);
}

void execute_program(byte exp_select) {//what does this program do, how do you manipulate this value
  //
  // tell tx arduino what experiment is happening
  Wire.beginTransmission(9); // transmit to arduino with address 9 (tx ard)
  Wire.write(exp_select);
  Wire.endTransmission();

  // different protocol for each experiment, if switch 5 was up, then this would be the loop that would run
  if (exp_select == 1) { //make uniform noise

    // begin experiment
    while (true) {
      // check to see if user has ended experiment (right most switch low), and break if so
      if (digitalRead(dip_pins[5]) == HIGH) {
        digitalWrite(13, LOW);
        // tell tx arduino what experiment is over
        Wire.beginTransmission(9);
        Wire.write(0);
        Wire.endTransmission();
        break;
      }


      // otherwise, do the experiment, more explanation necessary
      Wire.beginTransmission(MCP4725_ADDR); //initiate communication
      Wire.write(64);                     // cmd to update the DAC, the next thing the DAC recieves is 12 bit
      int toSend = random(4096);      //whole 12 bit range, get random number
      // Have to send 12 bits separately because only 8 bits at a time,
      Wire.write(toSend >> 4);        //The 8 most significant bits...
      Wire.write((toSend & 15) << 4); // the 4 least significant bits...
      Wire.endTransmission();
      //Stimulates positive or negative noise
      int sign_toSend = random(2); //0 or 1, add or subtract
      digitalWrite(sign_switch_pin, sign_toSend); //sends through pin 9, needs resistor 
      delay(1);
    }

  } else if (exp_select == 13) { //make gaussian noise, here showing code works
    // begin experiment
    while (true) {
      // check to see if user has ended experiment, and break if so
      if (digitalRead(dip_pins[5]) == HIGH) {
        digitalWrite(13, LOW);
        // tell tx arduino what experiment is over
        Wire.beginTransmission(9);
        Wire.write(0);
        Wire.endTransmission();
        break;
      }


      // otherwise, do the experiment, same function as above
      Wire.beginTransmission(MCP4725_ADDR);
      Wire.write(64);                     // cmd to update the DAC
      int toSend = random(4096);
      pot_val = analogRead(A0);       //Read potentometer to change noise volume
      Serial.println(pot_val);
      toSend = toSend/(pot_val/100);  //Changes the noise volume, all left no noise, all right high noise
      Wire.write(toSend >> 4);        // the 8 most significant bits...
      Wire.write((toSend & 15) << 4); // the 4 least significant bits...
      Wire.endTransmission();
      int sign_toSend = random(2);
      digitalWrite(sign_switch_pin, sign_toSend);
      delay(1);
    }
  }
}
