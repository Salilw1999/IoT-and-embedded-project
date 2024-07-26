const int buzzerPin = 15; // Replace 2 with the actual digital pin number where the buzzer is connected

void setup() {
  pinMode(buzzerPin, INPUT); // Set the buzzer pin as INPUT
  Serial.begin(9600); // Initialize Serial communication for debugging
}

void loop() {
  int buzzerState = digitalRead(buzzerPin); // Read the state of the buzzer pin (HIGH or LOW)

  if (buzzerState == HIGH) {
    Serial.println("Buzzer is ringing!");
  } else {
    Serial.println("Buzzer is not ringing.");
  }

  delay(1000); // Wait for a second before checking again
}
