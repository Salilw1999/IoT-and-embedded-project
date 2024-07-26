#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL3j2M8HtRd"
#define BLYNK_TEMPLATE_NAME "floor cleaning robot"
#define BLYNK_AUTH_TOKEN "9I6VWINpRFbbbmzCWy2KWkGoqbZopXz6"

char auth[] = "9I6VWINpRFbbbmzCWy2KWkGoqbZopXz6";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

#define SERVO_PIN_1 2
#define SERVO_PIN_2 4
#define SERVO_PIN_3 16
#define SERVO_PIN_4 17

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

BLYNK_WRITE(V0) {
  servo1.write(param.asInt());
}

BLYNK_WRITE(V1) {
  servo2.write(param.asInt());
}

BLYNK_WRITE(V2) {
  servo3.write(param.asInt());
}

BLYNK_WRITE(V3) {
  servo4.write(param.asInt());
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);
}

void loop() {
  Blynk.run();
}
