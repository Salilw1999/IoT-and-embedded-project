#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL3fbmocD56"
#define BLYNK_TEMPLATE_NAME "home automation"
#define BLYNK_AUTH_TOKEN "54jLx4NCfW5sDr6I-N-LKbdPzr33GYyt"

char auth[] = "54jLx4NCfW5sDr6I-N-LKbdPzr33GYyt";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

int relayPin1 = 5; // Set the GPIO pin for the relay

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin1, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run(); // Run Blynk loop
}

  BLYNK_WRITE(V0) // Virtual pin 1 for Blynk switch
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

  