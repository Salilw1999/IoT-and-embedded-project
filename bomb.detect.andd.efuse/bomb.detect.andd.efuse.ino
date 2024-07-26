#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#define BLYNK_PRINT Serial // Enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3FjWX7wZc"
#define BLYNK_TEMPLATE_NAME "Bomb Defuse Robot"
#define BLYNK_AUTH_TOKEN "ozX53MxxbBlp-F-icxdL8SGtyfqj9ttt"

#define Servo_pin1 12
#define Servo_pin2 13
#define Servo_pin3 14
#define Servo_pin4 27
#define gasSmokeSensorPin  15

char auth[] = "ozX53MxxbBlp-F-icxdL8SGtyfqj9ttt"; // Enter your Blynk application auth token
char ssid[] = "Shruti"; // Enter your WIFI name
char pass[] = "12345678"; // Enter your WIFI password

Servo servo1; // Create a servo object
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
   pinMode(gasSmokeSensorPin, INPUT);
  pinMode(Servo_pin1, OUTPUT);
  pinMode(Servo_pin2, OUTPUT);
  pinMode(Servo_pin3, OUTPUT);
  pinMode(Servo_pin4, OUTPUT);

  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Blynk.begin(auth, ssid, pass);

  servo1.attach(Servo_pin1);
  servo2.attach(Servo_pin2);
  servo3.attach(Servo_pin3);
  servo3.attach(Servo_pin4);
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  Serial.println("Received value for servo1: " + String(value));
  servo1.write(value);
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  Serial.println("Received value for servo2: " + String(value));
  servo2.write(value);
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  Serial.println("Received value for servo3: " + String(value));
  servo3.write(value);
}
  
BLYNK_WRITE(V3) {
  int value = param.asInt();
  Serial.println("Received value for servo4: " + String(value));
  servo4.write(value);
}

void loop() {
  Blynk.run();
  int gasSmokeValue = digitalRead(gasSmokeSensorPin);
  Blynk.virtualWrite(V4, gasSmokeValue);  // Update Blynk app with gas/smoke sensor reading

  if (gasSmokeValue == LOW) {
    Serial.println("Gas/smoke or flame detected!");
    Blynk.virtualWrite(V4, "Gas/Smoke or Flame Detected");  // Update Blynk app status
  // Turn on the buzzer
  } else {
    Serial.println("No gas/smoke or flame detected.");
    Blynk.virtualWrite(V4, "No Gas/Smoke or Flame Detected");  // Update Blynk app status
   // Turn off the buzzer
  }

  delay(100);  // Introduce a delay to avoid excessive updates

}
