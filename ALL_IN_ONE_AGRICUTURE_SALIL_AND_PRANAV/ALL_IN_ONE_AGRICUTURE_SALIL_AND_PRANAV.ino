#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL3kB0mNIWD"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg"

//Motor PINs
#define ENA               D0
#define IN1               D1
#define IN2               D2
#define IN3               D3
#define IN4               D4
#define ENB               D5
#define relayPin1         D6 // Set the GPIO pin for the relay
#define relayPin2         D7 // Set the GPIO pin for the relay

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;

char auth[] = "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg"; //Enter your Blynk application auth token
char ssid[] = "Salil OnePlus"; //Enter your WIFI name
char pass[] = "12345678"; //Enter your WIFI passowrd

int angle = 0;
bool isRotating = false;
int cycleCount = 0;
 
// This function
//creates the timer object. It's part of Blynk library
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT); 
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  Blynk.begin(auth, ssid, pass);
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
 
//BLYNK_WRITE(V4) {
  //Speed = param.asInt();
//}

 BLYNK_WRITE(V4) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin1, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin1, LOW); // Turn off the relay
  } 
}
  BLYNK_WRITE(V5) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin2, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin2, LOW); // Turn off the relay
  } 
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
  timer.run();
  smartcar();
  delay(1000);
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
