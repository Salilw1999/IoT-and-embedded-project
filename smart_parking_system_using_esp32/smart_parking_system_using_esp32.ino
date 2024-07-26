#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
int servoPin = 13; // define the servo control pin
int pirPin = 15;  // define the PIR sensor input pin
int pirState = LOW;  // variable to store PIR sensor state
int val = 0;  // variable to store the PIR sensor value
unsigned long lastMotionTime = 0;  // variable to store the time of the last motion detection

void setup() {
  Serial.begin(115200);
  myservo.attach(servoPin);  // attaches the servo on pin 2 to the servo object
  pinMode(pirPin, INPUT);  // initialize PIR sensor pin as an input
}

void loop() {
  val = digitalRead(pirPin);  // read PIR sensor value

  if (val == HIGH) {  // motion detected
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      myservo.write(180);  // rotate servo to 180 degrees (or any desired position)
      delay(5000);  // wait for 5 seconds
      myservo.write(0);  // rotate servo back to 0 degrees
      pirState = HIGH;  // update PIR sensor state
      lastMotionTime = millis();  // record the time of the last motion detection
    }
  } else {
    if (pirState == HIGH) {
      unsigned long elapsedTime = millis() - lastMotionTime;
      if (elapsedTime >= 5000) {  // if 30 seconds have passed since the last motion detection
        Serial.println("Motion ended. Returning to initial position.");
        myservo.write(0);  // rotate servo back to 0 degrees
        pirState = LOW;  // update PIR sensor state
      }
    }
  }
}
