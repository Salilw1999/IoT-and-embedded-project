#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial // enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3ivw8jn1n"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "pMyxo1nkm2kmzqNaTb-JvKENWzJMSvq1"
#include <BlynkSimpleEsp8266.h>

#define SOIL_MOISTURE_PIN A0
#define RELAY_PIN D7

int soilMoisturePercentage = 0; // Default soil moisture percentage

char auth[] = "pMyxo1nkm2kmzqNaTb-JvKENWzJMSvq1";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  if (soilMoistureValue != 0) {
    soilMoisturePercentage = map(soilMoistureValue, 1023, 0 , 0 , 100);
  }

  if (soilMoisturePercentage >= 7 && soilMoisturePercentage <= 24) {
    digitalWrite(RELAY_PIN, LOW); // Relay ON
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Relay OFF
  }

  Serial.print("Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercentage);
  Serial.println("%");
  Blynk.virtualWrite(V1, soilMoisturePercentage);

  Blynk.run();
  delay(1000);
}
