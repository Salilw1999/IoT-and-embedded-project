#include <ESP32Servo.h>
#include <Wire.h>
#include <MFRC522.h>

#define SERVO_PIN 13      // Pin connected to the servo control wire
#define RFID_SS_PIN 5      // Pin connected to the RFID module's SDA/SS line
#define RFID_RST_PIN 14    // Pin connected to the RFID module's RST line

Servo myServo;            // Create a Servo object

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);  // Create an MFRC522 object

// Replace this with the UID of your authorized RFID card
byte authorizedCardUID[] = {0xC3, 0xF0, 0xCA, 0x0F};

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);  // Attach the servo to the specified pin
  SPI.begin();               // Initialize SPI communication for RFID module
  rfid.PCD_Init();           // Initialize RFID module

  // Move the servo to 0 degrees at startup
  myServo.write(0);
  delay(1000);
}

bool isAuthorized() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Compare the card UID with the authorized UID
    if (memcmp(rfid.uid.uidByte, authorizedCardUID, rfid.uid.size) == 0) {
      Serial.println("Authorized access");
      return true;
    } else {
      Serial.println("Unauthorized access");
      return false;
    }
  }
  return false;
}

void loop() {
  if (isAuthorized()) {
    // Rotate the servo to 90 degrees over 15 seconds
    for (int angle = 0; angle <= 140; angle++) {
      myServo.write(angle);
      delay(1500 / 900);  // 15 seconds divided by 90 steps
    }

    delay(15000);  // Wait for 2 seconds

    // Return the servo to 0 degrees
    myServo.write(0);

    // Print a message
    Serial.println("Servo movement complete");

    // Wait for a moment before checking for another RFID card
    delay(1000);
  }
}
