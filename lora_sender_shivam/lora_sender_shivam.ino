#include <LoRa.h>
#include <SPI.h>

#define ss 5
#define rst 14
#define dio0 2
#define flameSensorPin 21
#define smokeSensorPin 22
//#define buzzerPin 23

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");

  pinMode(flameSensorPin, INPUT);
  pinMode(smokeSensorPin, INPUT);
  //pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read the flame sensor and smoke sensor
  int flameValue = digitalRead(flameSensorPin);
  int smokeValue = digitalRead(smokeSensorPin);

  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);
  Serial.print("Smoke Sensor Value: ");
  Serial.println(smokeValue);

  // Activate buzzer if either flame or smoke is detected
/*  if (flameValue == LOW || smokeValue == LOW) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);  // Buzzer on for 500 milliseconds
    digitalWrite(buzzerPin, LOW);
  }*/

  // Send binary values to the receiver
  LoRa.beginPacket();
  LoRa.write(flameValue);
  LoRa.write(smokeValue);
  LoRa.endPacket();

  delay(1);
}
