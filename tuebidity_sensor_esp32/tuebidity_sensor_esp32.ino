#define BLYNK_TEMPLATE_ID "TMPL3KRt-_Fs9"
#define BLYNK_TEMPLATE_NAME "Water management"
#define BLYNK_AUTH_TOKEN "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8"
//#define LED_PIN 15
//#define sensorPin  36
#define BLYNK_PRINT Serial
//#define turbidityLevel  100
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>

char auth[] = "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8";
char ssid[] = "Salil OnePlus"; // type your wifi name
char pass[] = "12345678"; // type your wifi password

const int sensorPin = 36; // analog pin connected to sensor
const int ledPin = 15;      // pin that the LED is attached to
const int threshold = 40;  // an arbitrary threshold level that's in the range of the analog input

//float calibration_value = 0.62; // calibration value for your sensor

int sensorValue = analogRead(sensorPin);
//float percentageValue = map(sensorValue, 0, 1023, 0, 100)

void setup() {
  Serial.begin(9600); // initialize serial communication
  pinMode(sensorPin, INPUT); // set sensor pin as input
  pinMode(ledPin, OUTPUT); // initialize the digital pin as an output
  Blynk.begin("LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm", "Salil OnePlus", "12345678"); // connect to Blynk server
}

void loop() {
  int turbidityValue = analogRead(sensorPin);
  // Convert the analog value to turbidity level (0-100)
  float turbidityLevel = map(turbidityValue, 0, 2000, 0, 100);
  
  // Print the turbidity level on the serial monitor
  Serial.print("Turbidity Level: ");
  Serial.print(turbidityLevel);
  Serial.println("%");
  Blynk.virtualWrite(V2, turbidityLevel);
   // send turbidity value to Blynk app sensorValue = analogRead(A0); // read the value from the sensor
 {
  // read the value of the potentiometer:
  int analogValue = analogRead(sensorPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // print the analog value:
  Serial.println(analogValue);
  delay(100);  // delay in between reads for stability
  }
}
