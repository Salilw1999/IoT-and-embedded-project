#include <WiFi.h>

#define BLYNK_PRINT Serial // enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3ivw8jn1n"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "pMyxo1nkm2kmzqNaTb-JvKENWzJMSvq1"
#include <BlynkSimpleEsp32.h>


#define SOIL_MOISTURE_PIN 34 // Change this to the available analog pin
#define relayPin1 2 // Assuming you're using GPIO 2 for relay control on ESP32

int soilMoisturePercentage = 0; // Default soil moisture percentage

char auth[] = "pMyxo1nkm2kmzqNaTb-JvKENWzJMSvq1";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin1, OUTPUT);
}

void loop() {
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  if (soilMoistureValue != 0) {
    soilMoisturePercentage = map(soilMoistureValue, 4095, 0 , 0 , 100); // ESP32 ADC resolution is 12 bits (4096)
  }

  if (soilMoisturePercentage >= 1 && soilMoisturePercentage <= 50) {
    digitalWrite(relayPin1, LOW); // Relay ON
  } else {
    digitalWrite(relayPin1, HIGH); // Relay OFF
  }

  Serial.print("Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercentage);
  Serial.println("%");
  Blynk.virtualWrite(V1, soilMoisturePercentage);

  Blynk.run();
  delay(1000);
}
