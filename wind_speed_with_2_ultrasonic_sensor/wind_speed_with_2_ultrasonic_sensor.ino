#define trigPin1  33
#define echoPin1  32
#define trigPin2  26
#define echoPin2  25

long duration1, duration2;
int distanceBetweenSensors = 10; // Distance between the two sensors in centimeters

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Measure distance for Sensor 1
  duration1 = measureDistance(trigPin1, echoPin1);

  // Measure distance for Sensor 2
  duration2 = measureDistance(trigPin2, echoPin2);

  // Calculate time taken for sound wave to travel between sensors
  // This will be affected by wind speed
  long timeDifference = duration2 - duration1;

  // Convert time difference to wind speed based on the distance between sensors
  float speedOfSound = 343.0; // Speed of sound in m/s at 20 degrees Celsius (adjust if needed)
  float distanceInMeters = distanceBetweenSensors / 100.0; // Convert distance to meters
  float windSpeed = (distanceInMeters / timeDifference) * speedOfSound;

  // Print wind speed
  Serial.print("Wind Speed: ");
  Serial.print(windSpeed);
  Serial.println(" m/s");

  delay(1000);
}

long measureDistance(int trigPin, int echoPin) {
  // Measure the distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}
