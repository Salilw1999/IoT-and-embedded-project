#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLB91fxasr"
#define BLYNK_TEMPLATE_NAME "relay Module 2"
#define BLYNK_AUTH_TOKEN "yu0RDMzK4Gty1-B7XHsU7qPKfv1F5y_C"

char auth[] = "yu0RDMzK4Gty1-B7XHsU7qPKfv1F5y_C";
char ssid[] = "SamsungA30";
char pass[] = "aditya@21";

int relayPin6 = 4; // Set the GPIO pin for the relay
int relayPin7 = 0;
int relayPin8 = 14;
int relayPin9 = 12;
int relayPin10 = 13;
int relayPin11 = 15;

void setup()
{
  Serial.begin(9600);
 // pinMode(PirPin, INPUT);
  
  pinMode(relayPin6, OUTPUT);
  pinMode(relayPin7, OUTPUT);
  pinMode(relayPin8, OUTPUT);
  pinMode(relayPin9, OUTPUT);
  pinMode(relayPin10, OUTPUT);
  pinMode(relayPin11, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run(); // Run Blynk loop
}

  BLYNK_WRITE(V6) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin6, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin6, LOW); // Turn off the relay
  } 
}
  BLYNK_WRITE(V7) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin7, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin7, LOW); // Turn off the relay
  } 
}

BLYNK_WRITE(V8) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin8, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin8, LOW); // Turn off the relay
  } 
}
BLYNK_WRITE(V9) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin9, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin9, LOW); // Turn off the relay
  } 
}
BLYNK_WRITE(V10) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin10, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin10, LOW); // Turn off the relay
  } 
}
BLYNK_WRITE(V11) // Virtual pin 1 for Blynk switch
{
  int value = param.asInt();

  if (value == 1) // If the switch is turned on
  {
    digitalWrite(relayPin11, HIGH); // Turn on the relay
  }
  else // If the switch is turned off
  {
    digitalWrite(relayPin11, LOW); // Turn off the relay
  } 
}
