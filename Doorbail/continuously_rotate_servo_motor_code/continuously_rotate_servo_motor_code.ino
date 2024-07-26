#define BLYNK_PRINT Serial // enable Blynk debugging#define BLYNK_TEMPLATE_ID "TMPL3Bwg-No7C"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Servo_pin3  D8

Servo servo3;
int angle = 0;
bool isRotating = false;
int cycleCount = 0;


char auth[] = "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"; // replace with your own auth token
char ssid[] = "Salil OnePlus"; // replace with your own WiFi SSID
char pass[] = "12345678"; // replace with your own WiFi password

BLYNK_WRITE(V4) // V1 is the virtual pin number in Blynk app
{
  int value = param.asInt(); // Get the value from the Blynk app
  if (value == 1 && !isRotating) // Check if the value is equal to 1 and not already rotating
  {
    isRotating = true; // Set the flag to indicate that the motor is rotating
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
    }
  }
}

void setup()
{
   Serial.begin(9600);
  pinMode(Servo_pin3, OUTPUT);
  servo3.attach(Servo_pin3); // Attach the servo to pin 2 of the ESP8266 board
  WiFi.begin(ssid, pass); // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) // Wait for Wi-Fi connection
  {
    delay(1000);
  }
  Blynk.begin(auth, ssid, pass); // Initialize Blynk with your authentication token and Wi-Fi connection
}

void loop()
{
  Blynk.run(); // Run Blynk
}
