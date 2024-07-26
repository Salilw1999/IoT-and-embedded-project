#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>

// GPS Module Configuration
static const int GPS_RX_Pin = 1; // GPIO 4=D2(connect Tx of GPS) and GPIO 5=D1(connect Rx of GPS)
static const int GPS_TX_Pin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial mygps(GPS_RX_Pin, GPS_TX_Pin);

float latitude;
float longitude;
float velocity;
float sats;
String bearing;

// SOS Configuration
const int SOS_Pin = 2; // SOS switch pin
SoftwareSerial SIM800L(17, 16); // RX, TX pins
bool sosTriggered = false; // Flag to track if SOS has been triggered

// Ultrasonic Sensor Configuration
const int trigPin1 = 13;
const int echoPin1 = 12;

const int trigPin2 = 14;
const int echoPin2 = 27;

const int trigPin3 = 26;
const int echoPin3 = 25;

// Buzzer Configuration
const int buzzerPin = 4;

void setup() {
  Serial.begin(115200);
  mygps.begin(GPSBaud);
  SIM800L.begin(9600);
  pinMode(SOS_Pin, INPUT_PULLUP); // Set SOS pin as input with internal pull-up resistor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (digitalRead(SOS_Pin) == LOW && !sosTriggered) {
    while (mygps.available() > 0) {
      if (gps.encode(mygps.read())) {
        displayInfo();
        sendSOS();
        makeCall();
        sosTriggered = true;
      }
    }
  } else if (digitalRead(SOS_Pin) == HIGH) {
    sosTriggered = false;
  }

  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  int distance3 = getDistance(trigPin3, echoPin3);

  Serial.print("Distance 1: ");
  Serial.println(distance1);

  Serial.print("Distance 2: ");
  Serial.println(distance2);

  Serial.print("Distance 3: ");
  Serial.println(distance3);

  triggerBuzzer(distance1);
  triggerBuzzer(distance2);
  triggerBuzzer(distance3);
}

void displayInfo() {
  if (gps.location.isValid()) {
    sats = gps.satellites.value();
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    velocity = gps.speed.kmph();
    bearing = TinyGPSPlus::cardinal(gps.course.value());

    Serial.print("SATS: ");
    Serial.println(sats);
    Serial.print("LATITUDE: ");
    Serial.println(latitude, 6);
    Serial.print("LONGITUDE: ");
    Serial.println(longitude, 6);
    Serial.print("SPEED: ");
    Serial.print(velocity);
    Serial.println(" kmph");
    Serial.print("DIRECTION: ");
    Serial.println(bearing);
  }
}

void sendSOS() {
  SIM800L.println("AT+CMGF=1");
  delay(1000);

  while (SIM800L.available()) {
    Serial.write(SIM800L.read());
  }

  SIM800L.print("AT+CMGS=\"+919579798405\"\r");
  delay(1000);

  String googleMapsURL = "http://maps.google.com/maps?q=";
  googleMapsURL += String(latitude, 6);
  googleMapsURL += ",";
  googleMapsURL += String(longitude, 6);

  SIM800L.print("SOS triggered! Latitude: ");
  SIM800L.print(latitude, 6);
  SIM800L.print(", Longitude: ");
  SIM800L.print(longitude, 6);
  SIM800L.print(", Speed: ");
  SIM800L.print(velocity);
  SIM800L.print(" kmph, Direction: ");
  SIM800L.print(bearing);
  SIM800L.println(". Open in Google Maps: " + googleMapsURL);
  delay(1000);

  SIM800L.print((char)26);

  delay(1000);
}

void makeCall() {
  SIM800L.print("ATD+919579798405;\r\n");
  delay(30000);
  SIM800L.println("ATH");
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void triggerBuzzer(int distance) {
  if (distance >= 1 && distance <= 5) {
    delay(5);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 5 && distance <= 10) {
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 10 && distance <= 15) {
    delay(500);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 15 && distance <= 25) {
    delay(700);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 25 && distance <= 35) {
    delay(1000);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
}
