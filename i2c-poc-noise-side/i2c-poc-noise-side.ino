// Include the required Wire library for I2C
#include <Wire.h>
int LED = 13;
int x = 0;
void setup() {
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Master
  Wire.begin(1);
}
void loop() {
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(x);              // sends x
  Wire.endTransmission();    // stop transmitting
  x++; // Increment x
  if (x > 5) x = 0; // `reset x once it gets 6
  if (x == 3) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(300);
  } else {
    delay(500);
  }

}
