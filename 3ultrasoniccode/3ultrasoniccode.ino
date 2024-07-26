#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL3frwfWQY7"
#define BLYNK_TEMPLATE_NAME "smart belt for blind person"
#define BLYNK_AUTH_TOKEN "1uhHUo7QY44XClMHZZpXwIsoCPdxLvgW"

char auth[] = "1uhHUo7QY44XClMHZZpXwIsoCPdxLvgW";  // You'll get this from the Blynk app
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

#define trigPin1 13
#define echoPin1 12
#define trigPin2 14
#define echoPin2 27
#define trigPin3 26
#define echoPin3 25

long duration1, duration2, duration3;
int distance1, distance2, distance3;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void measureDistance(int trigPin, int echoPin, long &duration, int &distance) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void sendDistanceToBlynk(int pin, int distance) {
  Blynk.virtualWrite(pin, distance);
}

void loop() {
  Blynk.run();
  measureDistance(trigPin1, echoPin1, duration1, distance1);
  measureDistance(trigPin2, echoPin2, duration2, distance2);
  measureDistance(trigPin3, echoPin3, duration3, distance3);
  
  sendDistanceToBlynk(V0, distance1);  // Use the appropriate virtual pin for each sensor
  sendDistanceToBlynk(V1, distance2);
  sendDistanceToBlynk(V2, distance3);

  delay(1000);
}
