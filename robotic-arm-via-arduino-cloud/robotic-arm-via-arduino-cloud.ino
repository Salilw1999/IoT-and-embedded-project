#include <WiFi.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3FciRT16m"
#define BLYNK_TEMPLATE_NAME "robotic arm"
#define BLYNK_AUTH_TOKEN "BX6H_fjkzu5hboy1Eossq-dJJF0oqikt"
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Motor PINs
#define Servo_pin1 12
#define Servo_pin2 13
#define Servo_pin3 14
#define Servo_pin4 27
#define Servo_pin5 26
#define Servo_pin6 25

char auth[] = "BX6H_fjkzu5hboy1Eossq-dJJF0oqikt"; // Enter your Blynk auth token
char ssid[] = "Salil OnePlus"; // Enter your Wi-Fi name
char pass[] = "12345678"; // Enter your Wi-Fi password

Servo servo1; // SG90 Servos
Servo servo2;
Servo servo3;

Servo servo4; // MG995-360 Servos
Servo servo5;
Servo servo6;

// Timer for MG995-360 motor rotation (to simulate positional control)
int mg995_rotation_duration = 0;  // Store rotation duration for MG995-360 motors

void setup() {
  Serial.begin(115200);

  // Attach SG90 servos to their respective pins
  servo1.attach(Servo_pin1);
  servo2.attach(Servo_pin2);
  servo3.attach(Servo_pin3);

  // Attach MG995-360 servos to their respective pins
  servo4.attach(Servo_pin4);
  servo5.attach(Servo_pin5);
  servo6.attach(Servo_pin6);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Blynk.begin(auth, ssid, pass);
}

// Control SG90 (V0 to V2 for sliders in Blynk)
BLYNK_WRITE(V0) {
  int value = param.asInt();  // Get value from Blynk slider
  if (value >= 0 && value <= 180) {
    Serial.println("Servo 1 angle: " + String(value));
    servo1.write(value);  // Rotate to specified angle
  }
}

BLYNK_WRITE(V1) {
  int value = param.asInt();  // Get value from Blynk slider
  if (value >= 0 && value <= 180) {
    Serial.println("Servo 2 angle: " + String(value));
    servo2.write(value);  // Rotate to specified angle
  }
}

BLYNK_WRITE(V2) {
  int value = param.asInt();  // Get value from Blynk slider
  if (value >= 0 && value <= 180) {
    Serial.println("Servo 3 angle: " + String(value));
    servo3.write(value);  // Rotate to specified angle
  }
}

// Control MG995-360 to simulate positional control
BLYNK_WRITE(V3) {
  int value = param.asInt();  // Get value from Blynk slider
  mg995_rotation_duration = map(value, 0, 360, 0, 2000);  // Map angle to duration (up to 2 seconds)
  Serial.println("Servo 4 rotates for " + String(mg995_rotation_duration) + "ms");
  rotateMG995Servo(servo4, mg995_rotation_duration);
}

BLYNK_WRITE(V4) {
  int value = param.asInt();  // Get value from Blynk slider
  mg995_rotation_duration = map(value, 0, 180, 0, 2000);  // Map angle to duration (up to 2 seconds)
  Serial.println("Servo 5 rotates for " + String(mg995_rotation_duration) + "ms");
  rotateMG995Servo(servo5, mg995_rotation_duration);
}

BLYNK_WRITE(V5) {
  int value = param.asInt();  // Get value from Blynk slider
  mg995_rotation_duration = map(value, 0, 180, 0, 2000);  // Map angle to duration (up to 2 seconds)
  Serial.println("Servo 6 rotates for " + String(mg995_rotation_duration) + "ms");
  rotateMG995Servo(servo6, mg995_rotation_duration);
}

// Function to simulate positional control for MG995-360
void rotateMG995Servo(Servo &servo, int duration) {
  servo.write(90);  // Start rotating (you can adjust 90 for rotation direction)
  delay(duration);  // Rotate for the calculated duration
  servo.write(90);  // Stop the motor (sending neutral signal)
}

void loop() {
  Blynk.run();
}
