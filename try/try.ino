#include <Ultrasonic.h>

Ultrasonic sensor1(D1, D2);  // Trigger pin, Echo pin for Sensor 1
Ultrasonic sensor2(D3, D4);  // Trigger pin, Echo pin for Sensor 2

unsigned long previousMillis = 0;
const long interval = 1000;  // Measurement interval in milliseconds

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int distance1 = sensor1.read();
    int distance2 = sensor2.read();

    if (distance1 != 0 && distance2 != 0) {
      float speed = (float)(abs(distance2 - distance1) / 100.0) / (float)(interval / 1000.0);  // Convert to m/s
      Serial.print("Wind Speed: ");
      Serial.print(speed, 2);  // Print with two decimal places
      Serial.println(" m/s");
    }
  }
}
