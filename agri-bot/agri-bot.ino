#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL30icM9MHB"
#define BLYNK_TEMPLATE_NAME "Forest Rescue System"
#define BLYNK_AUTH_TOKEN "AFdKMIEuZniYhGsJmnbqIvbMxqUnHrII"

const int gasSmokeSensorPin = 26;   // Digital pin for MQ-5 gas/smoke sensor
const int flameSensorPin = 27;      // Digital pin for flame sensor
const int buzzerPin = 13;           // Digital pin for the buzzer

char auth[] = "AFdKMIEuZniYhGsJmnbqIvbMxqUnHrII";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(gasSmokeSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  int gasSmokeValue = digitalRead(gasSmokeSensorPin);
  Blynk.virtualWrite(V1, gasSmokeValue);  // Update Blynk app with gas/smoke sensor reading

  int flameValue = digitalRead(flameSensorPin);
  Blynk.virtualWrite(V0, flameValue);  // Update Blynk app with flame sensor reading

  if (gasSmokeValue == LOW || flameValue == LOW) {
    Serial.println("Gas/smoke or flame detected!");
    Blynk.virtualWrite(V1, "Gas/Smoke or Flame Detected");  // Update Blynk app status
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  } else {
    Serial.println("No gas/smoke or flame detected.");
    Blynk.virtualWrite(V1, "No Gas/Smoke or Flame Detected");  // Update Blynk app status
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
  }

  delay(1000);  // Introduce a delay to avoid excessive updates
}
