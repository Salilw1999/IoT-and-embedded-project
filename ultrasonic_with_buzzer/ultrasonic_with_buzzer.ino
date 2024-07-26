// Define the pins for the ultrasonic sensors
const int trigPin1 = 13;
const int echoPin1 = 12;

const int trigPin2 = 14;  // Adjust pin numbers as needed
const int echoPin2 = 27;

const int trigPin3 = 26;   // Adjust pin numbers as needed
const int echoPin3 = 25;

// Define the pin for the buzzer
const int buzzerPin = 4;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the ultrasonic sensor pins as OUTPUT and INPUT
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Set the buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Function to get distance for each sensor
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);
  int distance3 = getDistance(trigPin3, echoPin3);

  // Print the distances to the serial monitor
  Serial.print("Distance 1: ");
  Serial.println(distance1);

  Serial.print("Distance 2: ");
  Serial.println(distance2);

  Serial.print("Distance 3: ");
  Serial.println(distance3);

  // Check the distance range and trigger the buzzer with the appropriate delay
  triggerBuzzer(distance1);
  triggerBuzzer(distance2);
  triggerBuzzer(distance3);
}

// Function to get distance from an ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo duration and calculate distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

// Function to trigger the buzzer based on distance
void triggerBuzzer(int distance) {
  if (distance >= 1 && distance <= 5) {
    delay(5); // 1-second delay
    digitalWrite(buzzerPin, HIGH);
    delay(100);  // Buzzer ON time
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 5 && distance <= 10) {
    delay(100); // 3-second delay
    digitalWrite(buzzerPin, HIGH);
    delay(100);  // Buzzer ON time
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 10 && distance <= 20) {
    // Add more distance ranges and corresponding delay times
    // For example, for the range 20 to 30, use a 2-second delay
    delay(500);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 30 && distance <= 35) {
    // For the range 30 to 40, use a 4-second delay
    delay(700);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  } else if (distance > 35 && distance <= 50) {
    // For the range 40 to 50, use a 6-second delay
    delay(1000);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  // Add more distance ranges and corresponding delay times as needed
}
