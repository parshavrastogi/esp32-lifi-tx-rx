const int ledPin = 27;

String binaryCode = "";
bool shouldBlink = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Enter any positive number:");
}

void loop() {
  // Read number from Serial
  if (Serial.available() > 0) {
    long num = Serial.parseInt();
    if (num >= 0) {
      binaryCode = String(num, BIN);
      shouldBlink = true;
      Serial.print("Binary: ");
      Serial.println(binaryCode);
    } else {
      Serial.println("Please enter a positive number.");
    }
  }

  // Blink LED with binary code
  if (shouldBlink) {
    int bitCount = binaryCode.length();

    // Minimum 100 ms per bit (50ms ON + 50ms OFF)
    int delayPerBit = 100;  
    int onTime = delayPerBit / 2;  
    int offTime = delayPerBit - onTime;

    Serial.print("Blinking at ");
    Serial.print(delayPerBit);
    Serial.println(" ms per bit.");

    for (int i = 0; i < bitCount; i++) {
      if (binaryCode[i] == '1') {
        digitalWrite(ledPin, HIGH);
        delay(onTime);
        digitalWrite(ledPin, LOW);
        delay(offTime);
      } else {
        // For '0' bits: keep LED OFF for full delay (no flash)
        digitalWrite(ledPin, LOW);
        delay(delayPerBit);
      }
    }

    shouldBlink = false; // done blinking
  }
}
