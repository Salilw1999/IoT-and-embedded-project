#include <NewPing.h>

#define TRIG_PIN D1
#define ECHO_PIN D2

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate
}

void loop() {
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  unsigned int distance = sonar.ping_cm(); // Send ping, get distance in centimeters.
  
  if (distance == 0) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  // You can add conditions here based on the distance measured, for example:
  if (distance < 50) {
    // Do something if the object is closer than 50cm
    // For instance, turn on an LED or take any specific action
  }
}
