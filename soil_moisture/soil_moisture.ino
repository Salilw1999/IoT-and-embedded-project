#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3SuEm97Sc"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "z17cl70ZzcRaOZG--NC4I2D25MW26sJw"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "z17cl70ZzcRaOZG--NC4I2D25MW26sJw"; // enter your authentication token here

char ssid[] = "Salil OnePlus"; // enter your WiFi SSID here
char pass[] = "12345678"; // enter your WiFi password here

int soilMoisturePin = 4; // enter the pin that the soil moisture sensor is connected to here

//int soilMoisturePin = ;
int soilMoistureValue = 0;

void setup()
{
  pinMode(soilMoisturePin, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  soilMoistureValue = analogRead(soilMoisturePin);
  Blynk.virtualWrite(V0, soilMoistureValue);
  delay(1000);
}
