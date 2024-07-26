#define BLYNK_TEMPLATE_ID "TMPL3LNwEE6jy"
#define BLYNK_TEMPLATE_NAME "Water management"
#define BLYNK_AUTH_TOKEN "ya3s7zlqra1wPDR65atd7oCrDFrA3wKj"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 22
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] = "ya3s7zlqra1wPDR65atd7oCrDFrA3wKj";
char ssid[] = "Salil Oneolus"; // type your wifi name
char pass[] = "12345678"; // type your wifi password

const int potPin=39;
float ph;
float Value=0;

const int sensorPin = 36; // analog pin connected to sensor
const int ledPin = 15;      // pin that the LED is attached to
const int threshold = 40;  // an arbitrary threshold level that's in the range of the analog input

int sensorValue = analogRead(sensorPin);

BlynkTimer timer;
void sendSensor()
{
// Request temperature to all devices on the data line
sensors.requestTemperatures();

Serial.print("Celsius temperature: ");
//We can connect more than one IC on the same data wire. 0 refers to the first IC on the wire
Serial.print(sensors.getTempCByIndex(0));
//Serial.print(" - Fahrenheit temperature: ");
//Serial.println(sensors.getTempFByIndex(0));
int tempC=sensors.getTempCByIndex(0);
//int tempF=sensors.getTempFByIndex(0);
delay(1000);

// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V1, tempC);
//Blynk.virtualWrite(V1, tempF);
delay(500);
}

void setup() {
  Serial.begin(9600); // initialize serial communication
  sensors.begin();
  pinMode(potPin,INPUT);
  pinMode(sensorPin, INPUT); // set sensor pin as input
  pinMode(ledPin, OUTPUT); // initialize the digital pin as an output
  Blynk.begin("LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm", "Salil OnePlus", "12345678"); // connect to Blynk server
  timer.setInterval(100L, sendSensor);
  delay(100);
}

void loop() 
{
  {
    // put your main code here, to run repeatedly:
  //Value= analogRead(potPin);
  Value= analogRead(potPin);
  Serial.print(Value);
  Serial.print(" | ");

  float voltage=Value*(3.3/5095.0);
  ph=(3.3*voltage);
  Serial.println(ph);
  Blynk.virtualWrite(V0,ph);
  delay(200);
  }

      // put your main code here, to run repeatedly:
  //Value= analogRead(potPin);
  Value= analogRead(potPin);
  Serial.print(Value);
  Serial.print(" | ");

  float voltage=Value*(3.3/5095.0);
  ph=(3.3*voltage);
  Serial.println(ph);
  Blynk.virtualWrite(V0,ph);
  delay(200);
  
    {
    int turbidityValue = analogRead(sensorPin);
    // Convert the analog value to turbidity level (0-100)
    float turbidityLevel = map(turbidityValue, 0, 2000, 0, 100);
    
    // Print the turbidity level on the serial monitor
    Serial.print("Turbidity Level: ");
    Serial.print(turbidityLevel);
    Serial.println("%");
    Blynk.virtualWrite(V2, turbidityLevel);
    // send turbidity value to Blynk app sensorValue = analogRead(A0); // read the value from the sensor
  {
    // read the value of the potentiometer:
    int analogValue = analogRead(sensorPin);

    // if the analog value is high enough, turn on the LED:
    if (analogValue > threshold) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    // print the analog value:
    Serial.println(analogValue);
    delay(100);  // delay in between reads for stability
    Blynk.run();
    timer.run();
    }
  }
}