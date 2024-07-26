#define BLYNK_TEMPLATE_ID "TMPL3xg0VmnSy"
#define BLYNK_TEMPLATE_NAME "Health Monitoring system"
#define BLYNK_AUTH_TOKEN "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8"

#define BLYNK_PRINT Serial
#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

#define MAX30100 sensor  16 ;
#define BUZZER_PIN 14
#define DHTPIN 15          // The pin which is connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11 sensor type

int buzzerState = LOW;

char auth[] = "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8";             // You should get Auth Token in the Blynk App.
char ssid[] = "Salil OnePlus";                                     // Your WiFi credentials.
char pass[] = "12345678";

PulseOximeter pox;
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

BlynkTimer timer; 

BLYNK_WRITE(V5)
{   
  int pos = param.asInt(); // Get value as integer
  myservo.write(pos);
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin();
  pox.begin();
  dht.begin();
  myservo.attach(13); 
  Blynk.begin("I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8", "Salil OnePlus", "12345678");
}

void loop() {
  pox.update();

  if (pox.getHeartRate() && pox.getSpO2()) {
    Serial.print("Heart rate: ");
    Serial.print(pox.getHeartRate());
    Serial.print(" bpm / SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println(" %");

    Blynk.virtualWrite(V7, pox.getHeartRate());
    Blynk.virtualWrite(V8, pox.getSpO2());
  }

  if (pox.getHeartRate() > 90) {
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerState = HIGH;
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerState = LOW;
  }
 {
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Blynk.virtualWrite(V0, humidity);
  Blynk.virtualWrite(V1, temperature);
  delay(2000);
  }
  Blynk.run();
  timer.run();
}







