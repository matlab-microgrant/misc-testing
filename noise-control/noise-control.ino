#include <Wire.h>//Include the Wire library to talk I2C
//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0.
#define MCP4725_ADDR 0x60
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
}

void loop() {
  // if 'set' switch is closed, begin experiment
  if (digitalRead(dip_pins[5]) == 1) {
    // executes differently depending on the experiment chosen
    execute_program(dip_setting);
  } else { //otherwise, see what the controls say
    // read other pins to get values
    for (int i = 0; i < 5; i++) {
      dip_vals[i] = digitalRead(dip_pins[i]);
    }
    for (int i = 0; i < 5; i++) {
      bitSet(dip_setting, i, dip_vals[5 - 1 - i]);
    }
    pot_val = analogRead(pot_pin);

  }


}

void execute_program(byte exp_select) {
  if (exp_select == 0) { //make uniform noise
    // tell tx arduino what to do for this experiment

    // begin experiment
    while (true) {
      // check to see if user has ended experiment, and break if so
      if (digitalRead(dip_pins[5]) == 0)
        break;

      // otherwise, do the experiment
      Wire.beginTransmission(MCP4725_ADDR);
      Wire.write(64);                     // cmd to update the DAC
      int toSend = random(4096);
      Wire.write(toSend >> 4);        // the 8 most significant bits...
      Wire.write((toSend & 15) << 4); // the 4 least significant bits...
      Wire.endTransmission();
      int sign_toSend = random(2);
      digitalWrite(sign_switch_pin, sign_toSend);
      delay(1);
    }

  } else if (exp_select == 1) { //make gaussian noise
    // tell tx arduino what to do for this experiment

    // define noise profile

    // begin experiment
  }
}
