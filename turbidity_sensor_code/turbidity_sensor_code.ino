#define BLYNK_TEMPLATE_ID "TMPL-eZ64sXm"
#define BLYNK_TEMPLATE_NAME "Water quality monitoring system"
#define BLYNK_AUTH_TOKEN "LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


//#define BLYNK_TEMPLATE_ID "TMPL-eZ64sXm"
//#define BLYNK_TEMPLATE_NAME "Water quality monitoring system"
//#define BLYNK_AUTH_TOKEN "LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm"

char auth[] = "LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm";
char ssid[] = "Salil OnePlus"; // type your wifi name
char pass[] = "12345678"; // type your wifi password


const int sensorPin = 4; // analog pin connected to sensor
const float VCC = 3.3; // ESP32 operating voltage
const float VOLTAGE_DIVIDER = 4.95; // voltage divider ratio
const float REFERENCE_VOLTAGE = 5.0; // ADC reference voltage
const float CALIBRATION_FACTOR = 6.4; // calibration factor for your sensor

void setup() {
  Serial.begin(9600); // initialize serial communication
  pinMode(sensorPin, INPUT); // set sensor pin as input
  Blynk.begin(LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm, Salil OnePlus, pa); // connect to Blynk server
}

void loop() {
  int sensorValue = analogRead(sensorPin); // read sensor value
  float voltage = sensorValue * (REFERENCE_VOLTAGE / 4095) * VOLTAGE_DIVIDER / 1000; // convert to voltage
  float turbidity = pow(1000, (voltage - CALIBRATION_FACTOR) / (-0.5)); // calculate turbidity
  Serial.print("Turbidity: ");
  Serial.print(turbidity);
  Serial.println(" NTU");
  Blynk.virtualWrite(V1, turbidity); // send turbidity value to Blynk app
  delay(1000); // wait for 1 second
}
