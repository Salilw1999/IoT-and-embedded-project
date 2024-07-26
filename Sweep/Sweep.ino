
#define BLYNK_TEMPLATE_ID "TMPL3q9sjY808"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

const char* ssid = "Salil OnePlus";
const char* password = "12345678";
const char* auth = "rfpYDx3MfF48x2kWXP4oz8dS8SfKARU7";

Servo servo;
int servoPosition = 0;
int servoDirection = 1; // 1 for forward, -1 for backward

BLYNK_WRITE(V7) // Virtual Pin V1 handler
{
  int pinValue = param.asInt(); // get the pin value from Blynk app
  if (pinValue == 1) { // rotate the servo motor if the pin value is 1
    servoDirection = 1; // set the direction to forward
    servo.attach(16); // attach servo to pin D1
  }
  else { // turn off the servo motor if the pin value is not 1
    servo.detach(); // detach the servo from the pin
  }
}

void setup()
{
  Blynk.begin(auth, ssid, password);
}

void loop()
{
  if (servoDirection == 1) { // rotate the servo motor in the forward direction
    servoPosition += 1;
    if (servoPosition > 180) { // switch direction at the end of the range
      servoDirection = -1;
    }
  }
  else { // rotate the servo motor in the backward direction
    servoPosition -= 1;
    if (servoPosition < 0) { // switch direction at the end of the range
      servoDirection = 1;
    }
  }
  servo.write(servoPosition); // set the servo position
  delay(15); // wait for the servo to reach the position
  Blynk.run(); // run the Blynk app
}
