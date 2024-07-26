#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#define BLYNK_PRINT Serial // Enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3FjWX7wZc"
#define BLYNK_TEMPLATE_NAME "Bomb Defuse Robot"
#define BLYNK_AUTH_TOKEN "ozX53MxxbBlp-F-icxdL8SGtyfqj9ttt"
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

static const int GPS_RX_Pin = 1; // GPIO 4=D2(connect Tx of GPS) and GPIO 5=D1(connect Rx of GPS)
static const int GPS_TX_Pin = 3;
static const uint32_t GPSBaud = 9600;
static const int BUZZER_Pin = 2; // Buzzer input pin

TinyGPSPlus gps;
SoftwareSerial mygps(GPS_RX_Pin, GPS_TX_Pin);

float latitude;
float longitude;
float velocity;
float sats;
String bearing;

SoftwareSerial SIM800L(17, 16); // RX, TX pins

bool sosTriggered = false; // Flag to track if SOS has been triggered

#define Servo_pin1 12
#define Servo_pin2 13
#define Servo_pin3 14
#define Servo_pin4 27
#define gasSmokeSensorPin  15

//Motor PINs
#define ENA               23
#define IN1               22
#define IN2               21
#define IN3               19
#define IN4               18
#define ENB                5
#define Servo_pin1        12
#define Servo_pin2        13
#define Servo_pin3        14
#define Servo_pin4        27
#define gasSmokeSensorPin  15

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;


char auth[] = "ozX53MxxbBlp-F-icxdL8SGtyfqj9ttt"; // Enter your Blynk application auth token
char ssid[] = "shruti"; // Enter your WIFI name
char pass[] = "12345678"; // Enter your WIFI password

Servo servo1; // Create a servo object
Servo servo2;
Servo servo3;
Servo servo4;

int angle = 0;
bool isRotating = false;
int cycleCount = 0;

 
// This function
//creates the timer object. It's part of Blynk library
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  mygps.begin(GPSBaud);
  SIM800L.begin(9600);
  pinMode(BUZZER_Pin, INPUT); // Set buzzer pin as input
  pinMode(gasSmokeSensorPin, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
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
  servo4.attach(Servo_pin4);
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

BLYNK_WRITE(V5) {
  int value = param.asInt();
  Serial.println("Received value for servo1: " + String(value));
  servo1.write(value);
}

BLYNK_WRITE(V6) {
  int value = param.asInt();
  Serial.println("Received value for servo2: " + String(value));
  servo2.write(value);
}

BLYNK_WRITE(V7) {
  int value = param.asInt();
  Serial.println("Received value for servo3: " + String(value));
  servo3.write(value);
}
  
BLYNK_WRITE(V8) {
  int value = param.asInt();
  Serial.println("Received value for servo4: " + String(value));
  servo4.write(value);
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
  // Check for buzzer input indicating SOS
  if (digitalRead(BUZZER_Pin) == HIGH && !sosTriggered) { // Check if buzzer is ringing and not already triggered
    while (mygps.available() > 0) {
      if (gps.encode(mygps.read())) {
        displayInfo();
        sendSOS();
//        makeCall();
        sosTriggered = true; // Set flag to indicate SOS has been triggered
      }
    }
  }
  // Reset the flag if buzzer stops ringing
  else if (digitalRead(BUZZER_Pin) == LOW) {
    sosTriggered = false;
  }
   Blynk.run();
  int gasSmokeValue = digitalRead(gasSmokeSensorPin);
  Blynk.virtualWrite(V9, gasSmokeValue);  // Update Blynk app with gas/smoke sensor reading

  if (gasSmokeValue == LOW) {
    Serial.println("Gas/smoke or flame detected!");
    Blynk.virtualWrite(V4, "Gas/Smoke or Flame Detected");  // Update Blynk app status
  // Turn on the buzzer
  } else {
    Serial.println("No gas/smoke or flame detected.");
    Blynk.virtualWrite(V9, "No Gas/Smoke or Flame Detected");  // Update Blynk app status
   // Turn off the buzzer
  }
  timer.run();
  smartcar();
  delay(100);  // Introduce a delay to avoid excessive updates

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
  // Send AT command to set SMS mode
  SIM800L.println("AT+CMGF=1");
  delay(1000);

  // Check for response from module
  while (SIM800L.available()) {
    Serial.write(SIM800L.read());
  }

  // Replace <PHONE_NUMBER> with the recipient's phone number
  SIM800L.print("AT+CMGS=\"+917447408623\"\r");
  delay(1000);

  // Generate Google Maps URL
  String googleMapsURL = "http://maps.google.com/maps?q=";
  googleMapsURL += String(latitude, 6);
  googleMapsURL += ",";
  googleMapsURL += String(longitude, 6);

  // Send SOS message
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

  // End the message with a Ctrl+Z character
  SIM800L.print((char)26);

  delay(1000);
}

//void makeCall() {
  // Replace <PHONE_NUMBER> with the recipient's phone number
  //SIM800L.print("ATD+917620287909;\r\n");
 // delay(30000); // Give some time for the call to be answered (adjust as needed)
 // SIM800L.println("ATH"); // Hang up the call
//}
 
