#define BLYNK_TEMPLATE_ID "TMPL3KRt-_Fs9"
#define BLYNK_TEMPLATE_NAME "Water management"
#define BLYNK_AUTH_TOKEN "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 22
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//int ledPin = 16; // Replace with the pin number you have connected your LED to
//int threshold = 34; // Threshold temperature in degrees Celsius

char auth[] = "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8";
char ssid[] = "Salil OnePlus"; // type your wifi name
char pass[] = "12345678"; // type your wifi password

BlynkTimer timer;
void sendSensor()
{
// Request temperature to all devices on the data line
sensors.requestTemperatures();
Serial.print("Celsius temperature: ");
//We can connect more than one IC on the same data wire. 0 refers to the first IC on the wire
Serial.print(sensors.getTempCByIndex(0));
//Serial.print(" - Fahrenheit temperature: ");
Serial.println(sensors.getTempFByIndex(0));
int tempC=sensors.getTempCByIndex(0);
//int tempF=sensors.getTempFByIndex(0);
delay(1000);
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V1, tempC);
//Blynk.virtualWrite(V2, tempF);
delay(200);
}
void setup()
{
//  pinMode(ledPin, OUTPUT);
Serial.begin(9600);
sensors.begin();
Blynk.begin(auth, ssid, pass);
timer.setInterval(100L, sendSensor);
//timer.setInterval(500L, blinkLedWidget);
}
void loop(){

Blynk.run();
timer.run();
}

