#define BLYNK_TEMPLATE_ID "TMPL3q9sjY808"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "Salil OnePlus";
const char* password = "12345678";
const char* auth = "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7";

int soilMoisturePin = A0;
int soilMoistureValue = 1024;

void setup()
{
  Serial.begin(115200);
  pinMode(soilMoisturePin, INPUT);
  Blynk.begin(auth, ssid, password);
}

void loop()
{
  soilMoistureValue = analogRead(soilMoisturePin);
  Blynk.virtualWrite(V6, soilMoistureValue);
   Blynk.run();
  delay(1000);
}
