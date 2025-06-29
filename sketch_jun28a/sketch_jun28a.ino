const int sensorPin = 32; // DO pin
const int bitDuration = 100; // ms per bit sampling interval
const unsigned long timeoutDuration = 300; // ms to detect end of transmission

String binaryString = "";
unsigned long lastSampleTime = 0;
unsigned long lastChangeTime = 0;
bool lastBit = false;
bool firstRead = true;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  Serial.println("Receiver ready, waiting for signal...");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSampleTime >= bitDuration) {
    lastSampleTime = currentTime;

    bool currentBit = digitalRead(sensorPin);

    if (firstRead) {
      lastBit = currentBit;
      lastChangeTime = currentTime;
      firstRead = false;
    }

    // Detect bit changes or stable bit continuation
    if (currentBit != lastBit) {
      // Bit changed - new bit
      binaryString += currentBit ? '1' : '0';
      lastChangeTime = currentTime;
      lastBit = currentBit;
    } else {
      // Bit same as last time
      // Check if timeout occurred (end of transmission)
      if (binaryString.length() > 0 && (currentTime - lastChangeTime > timeoutDuration)) {
        // End of transmission detected
        long receivedNum = strtol(binaryString.c_str(), NULL, 2);
        Serial.print("Received number: ");
        Serial.println(receivedNum);

        // Reset for next transmission
        binaryString = "";
        firstRead = true;
      }
    }
  }
}
