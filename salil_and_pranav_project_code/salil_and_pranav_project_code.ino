#define BLYNK_PRINT Serial // enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3Bwg-No7C"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h> 
#include <DHT.h>

//Motor PINs
#define ENA               D0
#define IN1               D1
#define IN2               D2
#define IN3               D3
#define IN4               D4
#define ENB               D5
#define Servo_pin1        D6
#define Servo_pin2        D7
#define Servo_pin3        D8
#define  relayPin          1  // Relay control pin
bool isRelayOn = false; // Flag to track relay status
#define DHTPIN            3          // Pin where the DHT11 sensor is connected
#define DHTTYPE           DHT11

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;

char auth[] = "pMyxo1nkm2kmzqNaTb-JvKENWzJMSvq1"; //Enter your Blynk application auth token
char ssid[] = "Salil OnePlus"; //Enter your WIFI name
char pass[] = "12345678"; //Enter your WIFI passowrd


DHT dht(DHTPIN, DHTTYPE); 
Servo servo1; // create a servo object
Servo servo2;
Servo servo3;
int angle = 0;
bool isRotating = false;
int cycleCount = 0;
 
// This function
//creates the timer object. It's part of Blynk library
BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
   pinMode(Servo_pin1, OUTPUT); 
  pinMode(Servo_pin2, OUTPUT); 
  pinMode(Servo_pin3, OUTPUT);
  pinMode(relayPin, OUTPUT); // Set the relay pin as output
  digitalWrite(relayPin, LOW); // Turn off the relay initially
  
  dht.begin();
  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  Blynk.begin(auth, ssid, pass);
  
  servo1.attach(Servo_pin1); // 15 means D8 pin of ESP8266
  servo2.attach(Servo_pin2);
  servo3.attach(Servo_pin3);
  timer.setInterval(1000L);
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

BLYNK_WRITE(V4) // V1 is the virtual pin number in Blynk app
{
  int value = param.asInt(); // Get the value from the Blynk app
  if (value == 1 && !isRotating) // Check if the value is equal to 1 and not already rotating
  {
    isRotating = true; // Set the flag to indicate that the motor is rotating
    digitalWrite(relayPin, LOW); // Turn on the relay
    for (int cycle = 0; cycle < 2; cycle++) // Run the cycle for 2 times
    {
      for (angle = 0; angle < 180; angle++) // Rotate the servo from 0 to 180 degrees
      {
        servo3.write(angle);
        delay(0.5); // Wait for 15 milliseconds
      }
      for (angle = 180; angle > 0; angle--) // Rotate the servo from 180 to 0 degrees
      {
        servo3.write(angle);
        delay(0.5); // Wait for 15 milliseconds
      }
    }
    isRotating = false; // Reset the flag to indicate that the motor is not rotating anymore
    cycleCount = 0; // Reset the cycle count
    servo3.write(0); // Stop the motor
    digitalWrite(relayPin, HIGH); // Turn off the relay
    isRelayOn = false; // Reset the flag to indicate that the relay is off
  }
  else if (value == 0) // Stop the motor if the value is equal to 0
  {
    if (isRotating && cycleCount < 2) // Check if the motor is rotating and the cycle is not completed
    {
      cycleCount++; // Increment the cycle count
    }
    else // Stop the motor if the cycle is completed
    {
      servo3.write(0);
      isRotating = false; // Reset the flag to indicate that the motor is not rotating anymore
      cycleCount = 0; // Reset the cycle count
      if (isRelayOn) // Turn off the relay if it is on
      {
        digitalWrite(relayPin, LOW);
        isRelayOn = false;
      }
    }
  }
}

BLYNK_WRITE(V5) 
{
servo1.write(param.asInt());
}

BLYNK_WRITE(V6) 
{
servo2.write(param.asInt());
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
  float temperature = dht.readTemperature();  // Read temperature value from DHT11 sensor
  float humidity = dht.readHumidity();        // Read humidity value from DHT11 sensor
  if (!isnan(temperature)) {                  // Check if temperature value is valid
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C");
    Serial.println();
    Blynk.virtualWrite(V7, temperature);      // Send temperature value to the Blynk app
  }
  if (!isnan(humidity)) {                     // Check if humidity value is valid
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");
    Serial.println();
    Blynk.virtualWrite(V8, humidity);         // Send humidity value to the Blynk app
  }

  
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
