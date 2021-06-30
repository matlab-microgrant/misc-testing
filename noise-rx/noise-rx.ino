
int i = 0;
bool sendingData = false;
bool lightToggle = false;
int sampleDelay = 0;
String message = "";

// ------------ Put sensor-specific declarations here ----------

// -------------------------------------------------------------

// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // ---------- Put sensor-sepcific setup here -------------------
  
  // -------------------------------------------------------------
}

// The loop routine runs over and over again forever:
void loop() {
  // Write the sinewave points, followed by the terminator "Carriage Return" and "Linefeed".
  if (Serial.available() > 0) {
    message = Serial.readString();

    if (message == "begin sampling\n") {
      // start sending data sampled to the computer
      sendingData = true;

    } else if (message == "sample rate\n") {
      // prepare to recieve new sample rate and then update it after receiving
      while (!Serial.available() ) { }
      String newSampleRate = Serial.readString();
      float sampleRateHz = (newSampleRate.toFloat());
      float sampleDelaySecs= (1.0/sampleRateHz);
      sampleDelay = (int) (sampleDelaySecs*1000);
      //Serial.println(sampleDelay);
    }
  }
  while (sendingData) {
    // ------ put data collection below here ------
    int reading = analogRead(A0);
    
    // put data you want printed in the below line
    Serial.print(reading);
    // -------------------------------------------
    Serial.write(13);
    Serial.write(10);
    if (lightToggle == false) {
      digitalWrite(LED_BUILTIN, HIGH);
      lightToggle = true;
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      lightToggle = false;
    }
    i += 1;
    if (Serial.available() > 0) {
      message = Serial.readString();
      if (message == "end sampling\n") {
        sendingData = false;
        digitalWrite(LED_BUILTIN, LOW);
        i=0;
      }
    }
    delay(sampleDelay);
  }

}
// ------------------- put helper functions down here -----------------

// --------------------------------------------------------------------
