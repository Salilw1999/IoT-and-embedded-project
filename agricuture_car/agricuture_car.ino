#define BLYNK_TEMPLATE_ID "TMPL3q9sjY808"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
//Motor PINs
#define ENA               D0
#define IN1               D1
#define IN2               D2
#define IN3               D3
#define IN4               D4
#define ENB               D5
#define relay             D8
#define sensorPin         A0    //IR1 - D7
   
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;


int sensorState;
int lastState=0;


char auth[] = "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7"; //Enter your Blynk application auth token
char ssid[] = "Salil OnePlus"; //Enter your WIFI name
char pass[] = "12345678"; //Enter your WIFI passowrd

// This function creates the timer object. It's part of Blynk library
BlynkTimer timer;
 
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(relay,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  pinMode(sensorPin, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  right = param.asInt();
}
 
BLYNK_WRITE(V3) {
  left = param.asInt();
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

void loop() {
  Blynk.run();
   sensorState = analogRead(sensorPin);
Serial.println(sensorState);

if (sensorState > 1000 && lastState == 0) {
  Serial.println("needs water, send notification");
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState > 1000 && lastState == 1) {
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    Blynk.virtualWrite(V6, sensorState);
    if (sensorState < 30) {
    digitalWrite(relay, HIGH);   // turn on the relay
  } else if (sensorState > 50) {
    digitalWrite(relay, LOW);    // turn off the relay
  }
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
  timer.run();
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
