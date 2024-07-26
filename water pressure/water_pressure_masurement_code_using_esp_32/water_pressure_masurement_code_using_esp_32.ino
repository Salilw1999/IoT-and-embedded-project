#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL3VRlW_pf4"
#define BLYNK_TEMPLATE_NAME "water pressure"
#define BLYNK_AUTH_TOKEN "McKgQyW-2SZ4CHj-Mi8GggyzhIKoBD2W"

char auth[] = "McKgQyW-2SZ4CHj-Mi8GggyzhIKoBD2W"; // Replace with your Blynk auth token
char ssid[] = "Salil OnePlus"; // Replace with your Wi-Fi network SSID
char pass[] = "12345678"; // Replace with your Wi-Fi network password

const int pressurePin = 36; // GPIO pin connected to the pressure sensor

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pressurePin, INPUT);
}

void loop()
{
  Blynk.run();
  float pressure = readPressure(); // Call a function to read the pressure from the sensor
  Blynk.virtualWrite(V0, pressure); // Send the pressure value to virtual pin V1 in the Blynk app
  delay(1000); // Adjust the delay based on your requirements
}

float readPressure()
{
  // Code to read the pressure sensor and convert the raw value to pressure
  int rawValue = analogRead(pressurePin);
  float pressure = map(rawValue, 0, 4095, 0, 100); // Example mapping from raw value to pressure (adjust as needed)
  return pressure;
}
