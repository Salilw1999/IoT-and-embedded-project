#define BLYNK_TEMPLATE_ID "TMPL3kB0mNIWD"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h> 
#include <DHT.h>

//Threshold values (in percentage)
#define MOISTURE_THRESHOLD_ON 10
#define MOISTURE_THRESHOLD_OFF  50

char auth[] = "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";



Servo servo1; 


//Motor PINs
#define ENA 16
#define IN1 5
#define IN2 4
#define IN3 0
#define IN4 2
#define ENB 14
   
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
  
void setup() {
Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(Servo_pin, OUTPUT); // Initialise digital pin 2 as an output pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 

Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
servo1.attach(Servo_pin); // 15 means D8 pin of ESP8266
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
 
void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}

BLYNK_WRITE(V5) // Executes when the value of virtual pin 0 changes
 {
  if(param.asInt() == 1)
     {
    // execute this code if the switch widget is now ON
    digitalWrite(RELAY_PIN,HIGH);  // Set digital pin 2 HIGH
    }
 else
    {
    // execute this code if the switch widget is now OFF
    digitalWrite(RELAY_PIN,LOW);  // Set digital pin 2 LOW 
    }
 }

BLYNK_WRITE(V8) 
{
servo1.write(param.asInt());
}

 void loop() {
  // Read the moisture level from the sensor and convert it to a percentage value
  int sensorValue = analogRead(SENSOR_PIN);
  float moistureLevel = map(sensorValue, 1023, 350, 0, 100);

  // Update the Blynk app with the current moisture level
  Blynk.virtualWrite(V6, moistureLevel);

  // If the moisture level is below the threshold, turn on the relay
  if (moistureLevel < 10) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on relay
  }
  // If the moisture level is above the threshold, turn off the relay
  if (moistureLevel > 50) {
    digitalWrite(RELAY_PIN, LOW); // Turn off relay
  }

 Blynk.run();
 delay(1000);
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
