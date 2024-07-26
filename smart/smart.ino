#define BLYNK_TEMPLATE_ID "TMPL33AG-e1m0"
#define BLYNK_TEMPLATE_NAME "SMART PARKING SYSTEM"
#define BLYNK_AUTH_TOKEN "z3iSRT-CgLZQmCe1LNifZKG9Kq-sDYrE"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <MFRC522.h>

#define SERVO_PIN 13      // Pin connected to the servo control wire
#define RFID_SS_PIN 5      // Pin connected to the RFID module's SDA/SS line
#define RFID_RST_PIN 14    // Pin connected to the RFID module's RST line

#define pirPin  4  // define the PIR sensor input pin
#define irPin1  33 // Replace wi-th the first IR sensor pin
#define irPin2  25 // Replace with the second IR sensor pin
#define irPin3  26 // Replace with the third IR sensor pin
#define irPin4  27 // Replace with the fourth IR sensor pin


int pirState = LOW;  // variable to store PIR sensor state
int val = 0;  // variable to store the PIR sensor value
unsigned long lastMotionTime = 1;  // variable to store the time of the last motion detection


char auth[] = "z3iSRT-CgLZQmCe1LNifZKG9Kq-sDYrE";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

Servo myServo;

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);  // Create an MFRC522 object

// Replace this with the UID of your authorized RFID card
byte authorizedCardUID[] = {0xC3, 0xF0, 0xCA, 0x0F};

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  myServo.attach(SERVO_PIN);  // Attach the servo to the specified pin
  pinMode(pirPin, INPUT); 
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);
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

 BLYNK_WRITE(V0) {
   int angle = param.asInt();  // Get the value from the Slider widget
   myServo.write(angle);
}

void loop(){
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

  val = digitalRead(pirPin);  // read PIR sensor value

  if (val == HIGH) {  // motion detected
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      myServo.write(140);  // rotate servo to 180 degrees (or any desired position)
      delay(15000);  // wait for 5 seconds
      myServo.write(0);  // rotate servo back to 0 degrees
      pirState = HIGH;  // update PIR sensor state
      lastMotionTime = millis();  // record the time of the last motion detection
    }
  } else {
    if (pirState == HIGH) {
      unsigned long elapsedTime = millis() - lastMotionTime;
      if (elapsedTime >= 1000) {  // if 30 seconds have passed since the last motion detection
        Serial.println("Motion ended. Returning to initial position.");
        myServo.write(0);  // rotate servo back to 0 degrees
        pirState = LOW;  // update PIR sensor state
      }
    }
  }
  {
   Blynk.run();

   int irValue1 = digitalRead(irPin1);
   int irValue2 = digitalRead(irPin2);
   int irValue3 = digitalRead(irPin3);
   int irValue4 = digitalRead(irPin4);

   Blynk.virtualWrite(V1, irValue1); // Use the virtual pin associated with the first Value Display widget
   Blynk.virtualWrite(V2, irValue2); // Use the virtual pin associated with the second Value Display widget
   Blynk.virtualWrite(V3, irValue3); // Use the virtual pin associated with the third Value Display widget
   Blynk.virtualWrite(V4, irValue4); // Use the virtual pin associated with the fourth Value Display widget
   
  

   delay(1000); // Adjust delay based on your requirements
 }

}
