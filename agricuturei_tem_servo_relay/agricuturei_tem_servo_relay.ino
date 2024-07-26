#define BLYNK_PRINT Serial // enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3Bwg-No7C"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <DHT.h>

#define Servo_pin1  D8
#define Servo_pin2  D7
#define Servo_pin3  D6
#define  relayPin   1  // Relay control pin
bool isRelayOn = false; // Flag to track relay status

#define DHTPIN      3          // Pin where the DHT11 sensor is connected
#define DHTTYPE     DHT11      // DHT11 sensor type

char auth[] = "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"; // replace with your own auth token
char ssid[] = "Salil OnePlus"; // replace with your own WiFi SSID
char pass[] = "12345678"; // replace with your own WiFi password

DHT dht(DHTPIN, DHTTYPE); 
Servo servo1; // create a servo object
Servo servo2;
Servo servo3;
int angle = 0;
bool isRotating = false;
int cycleCount = 0;
 

void setup()
{
  Serial.begin(9600);
  pinMode(Servo_pin1, OUTPUT); 
  pinMode(Servo_pin2, OUTPUT); 
  pinMode(Servo_pin3, OUTPUT);
  pinMode(relayPin, OUTPUT); // Set the relay pin as output
  digitalWrite(relayPin, LOW); // Turn off the relay initially
  
  dht.begin();
  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) // Wait for Wi-Fi connection
  Blynk.begin(auth, ssid, pass); // connect to Blynk server

  servo1.attach(Servo_pin1);
  servo2.attach(Servo_pin2);
  servo3.attach(Servo_pin3);
  delay(1000);
  
  // attach the servo signal pin to D2 pin of ESP8266
}

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

void loop()
{
  Blynk.run(); // run Blynk
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
  delay(2000);
}
