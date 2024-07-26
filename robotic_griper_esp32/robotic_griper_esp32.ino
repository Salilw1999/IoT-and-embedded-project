#define BLYNK_PRINT Serial // enable Blynk debugging
#define BLYNK_TEMPLATE_ID "TMPL3n2LEL7Mi"
#define BLYNK_TEMPLATE_NAME "BoreWell Rescue Project"
#define BLYNK_AUTH_TOKEN "SH4Meh-PGBtoHVekRmx7Ks6rQw1H8akw"
#include <BlynkSimpleEsp32.h>

char auth[] = "SH4Meh-PGBtoHVekRmx7Ks6rQw1H8akw";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

#define openPin 33  // GPIO pin connected to gripper open control pin
#define closePin 32  // GPIO pin connected to gripper close control pin
#define trigPin  26
#define echoPin  25
#define buzzerPin 33

long duration;
int distance;
int buzzerIntensity; 

BLYNK_WRITE(V0) {
  int gripperControl = param.asInt(); // Get value from the button (0 or 1)
  if (gripperControl == 1) {
    ledcWrite(0, 255);  // Open the gripper (adjust duty cycle as needed)
    ledcWrite(1, 0);
  } else {
    ledcWrite(0, 0);
    ledcWrite(1, 255);  // Close the gripper (adjust duty cycle as needed)
  }
}

void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

  // Configure LEDC timer and channels
    ledcSetup(0, 5000, 8);  // Timer 0, 5000 Hz, 8-bit resolution
    ledcSetup(1, 5000, 8);  // Timer 1, 5000 Hz, 8-bit resolution

  // Attach the LEDC channels to the GPIO pins
    ledcAttachPin(openPin, 0);
    ledcAttachPin(closePin, 1);
}

void loop() {
  Blynk.run();
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound is 34 microseconds per centimeter (2 * distance)
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send the distance value to a Blynk virtual pin
  Blynk.virtualWrite(V7, distance);
// Map the distance to buzzer intensity
  buzzerIntensity = map(distance, 0, 100, 255, 0);  // Adjust the range as needed

  // Set the buzzer intensity
    digitalWrite(buzzerPin, buzzerIntensity);
  delay(1000);
}