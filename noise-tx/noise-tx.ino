#include <Wire.h>//Include the Wire library to talk I2C
int tx_pin = 13;
int x = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
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
