#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SS_PIN D4
#define RST_PIN D3
#define BUZZER_PIN D0
#define RELAY_PIN D8

#define BLYNK_TEMPLATE_ID "TMPLc2xQsiGt"
#define BLYNK_TEMPLATE_NAME "RFID sECURITY SYSTEM"
#define BLYNK_AUTH_TOKEN "HMwjAoWgO-Lw0EAnMbOxA010Bv2U22od"

char auth[] = "HMwjAoWgO-Lw0EAnMbOxA010Bv2U22od";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

MFRC522 mfrc522(SS_PIN, RST_PIN);
BlynkTimer timer;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfid = "";
    for (byte i = 0; i < 4; i++) {
      rfid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("RFID detected: " + rfid);
    if (rfid == "f731dbd7") {
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("Access granted");
      timer.setTimeout(3000, []() {
        digitalWrite(RELAY_PIN, HIGH);
      });
    } else {
      //digitalWrite(RELAY_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Access denied");
      timer.setTimeout(3000, []() {
        digitalWrite(BUZZER_PIN, LOW);
      });
    }
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
  BLYNK_WRITE(V0) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
  } 
}

/*
BLYNK_WRITE(V0) {
  if (param.asInt()) {
    digitalWrite(RELAY_PIN, HIGH);
    timer.setTimeout(1000, []() {
      digitalWrite(RELAY_PIN, LOW);
    });
  }
}*/