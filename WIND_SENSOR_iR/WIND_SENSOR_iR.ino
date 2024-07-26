#define Sensor1 14  // Replace with the actual pin numbers
#define Sensor2 32
#define Sensor3 35
#define Sensor4 2
#define Sensor5 4
#define Sensor6 5
#define Sensor7 33
#define Sensor8 34   
#define Sensor9 15

unsigned long t1, t2;
float windSpeed;

void setup() {
  Serial.begin(9600);  // start serial for output

  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(Sensor5, INPUT);
  pinMode(Sensor6, INPUT);
  pinMode(Sensor7, INPUT);
  pinMode(Sensor8, INPUT);
  pinMode(Sensor9, INPUT);
}

void loop() {
  static bool state = true;
  static bool count = true;

  if (state == false) {
    if (count == false) {
      readSensor();
      if (digitalRead(Sensor9) == HIGH) {
        t2 = millis();
        float t = (t2 - t1) / 1000.0;
        windSpeed = (2 * 3.1416 * 0.0001 * 3600) / t;
        Serial.print("Wind Speed: ");
        Serial.print(windSpeed);
        Serial.println(" km/h");
        count = true;
      }
    } else {
      readSensor();
      if (digitalRead(Sensor9) == LOW) {
        t1 = millis();
        count = false;
      }
    }
  } else {
    readSensor();
    if (digitalRead(Sensor9) == HIGH) {
      state = false;
    }
    Serial.println("Wind Speed: 0 km/h");
  }

  // Introduce a delay of 1 second
  delay(.1);
}

void readSensor() {
  // Read sensor values if needed, adjust as per your actual sensors
}
