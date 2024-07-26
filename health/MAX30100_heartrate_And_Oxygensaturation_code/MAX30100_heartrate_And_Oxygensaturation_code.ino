#define BLYNK_TEMPLATE_ID "TMPL3xg0VmnSy"
#define BLYNK_TEMPLATE_NAME "Health Monitoring system"
#define BLYNK_AUTH_TOKEN "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8"

#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define MAX30100 sensor  16 ;
#define BUZZER_PIN 14

int buzzerState = LOW;

char auth[] = "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8";             // You should get Auth Token in the Blynk App.
char ssid[] = "Salil OnePlus";                                     // Your WiFi credentials.
char pass[] = "12345678";

PulseOximeter pox;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin();
  pox.begin();
  Blynk.begin("I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8", "Salil OnePlus", "12345678");
}

void loop() {
  pox.update();

  if (pox.getHeartRate() && pox.getSpO2()) {
    Serial.print("Heart rate: ");
    Serial.print(pox.getHeartRate());
    Serial.print(" bpm / SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println(" %");

    Blynk.virtualWrite(V7, pox.getHeartRate());
    Blynk.virtualWrite(V8, pox.getSpO2());
  }

  if (pox.getHeartRate() > 90) {
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerState = HIGH;
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerState = LOW;
  }

  Blynk.run();
}
