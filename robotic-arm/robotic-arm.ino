#include <WiFi.h>
#define BLYNK_PRINT Serial // Enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3FciRT16m"
#define BLYNK_TEMPLATE_NAME "robotic arm"
#define BLYNK_AUTH_TOKEN "BX6H_fjkzu5hboy1Eossq-dJJF0oqikt"
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h> 

//Motor PINs
#define Servo_pin1        12
#define Servo_pin2        13
#define Servo_pin3        14
#define Servo_pin4        27
#define Servo_pin5        26
#define Servo_pin6        25



char auth[] = "BX6H_fjkzu5hboy1Eossq-dJJF0oqikt"; //Enter your Blynk application auth token
char ssid[] = "Salil"; //Enter your WIFI name
char pass[] = "12345678"; //Enter your WIFI passowrd

Servo servo1; // Create a servo object
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
int angle = 0;
bool isRotating = false;
int cycleCount = 0;

 
// This function
//creates the timer object. It's part of Blynk library
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(Servo_pin1, OUTPUT);
  pinMode(Servo_pin2, OUTPUT);
  pinMode(Servo_pin3, OUTPUT);
  pinMode(Servo_pin4, OUTPUT);
  pinMode(Servo_pin5, OUTPUT);
  pinMode(Servo_pin6, OUTPUT);

  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  Blynk.begin(auth, ssid, pass);

  servo1.attach(Servo_pin1);
  servo2.attach(Servo_pin2);
  servo3.attach(Servo_pin3);
  servo4.attach(Servo_pin4);
  servo5.attach(Servo_pin5);
  servo6.attach(Servo_pin6);
  
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

BLYNK_WRITE(V4) {
  int value = param.asInt();
  Serial.println("Received value for servo5: " + String(value));
  servo5.write(value);
}

BLYNK_WRITE(V5) {
  int value = param.asInt();
  Serial.println("Received value for servo6: " + String(value));
  servo6.write(value);
}


void loop() { 
  Blynk.run();
}
