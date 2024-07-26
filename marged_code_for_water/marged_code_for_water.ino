#define BLYNK_TEMPLATE_ID "TMPL6jI2VmoW"
#define BLYNK_TEMPLATE_NAME "Water management system"
#define BLYNK_AUTH_TOKEN "F2D4-3zySbqKjuVPpePeiochRhySBqte"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 22
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] = "F2D4-3zySbqKjuVPpePeiochRhySBqte";
char ssid[] = "Salil OnePlus"; // type your wifi name
char pass[] = "12345678"; // type your wifi password

const int sensorPin = 36; // analog pin connected to sensor
int sensorValue = analogRead(sensorPin);
int ledPin1 = 16;
int ledPin2= 16; 
float percentageValue=0;

// Replace with the pin number you have connected your LED to
//float calibration_value = 0.62; // calibration value for your sensor
//int VIRTUAL_PIN1 = V1;
//int VIRTUAL_PIN2 = V2;

BlynkTimer timer;
//BlynkTimer timer;
WidgetLED led1(V15);
WidgetLED led2(V14);

void blinkLedWidget()
{
  if ((tempC >= 35)) {
    
         led1.on();
  }
  else{
         led1.off();
  }
    if(percentageValue < 20){
         led2.on();
    }
    else{
         led2.off();
    }
}

void setup()
{
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
Serial.begin(9600);
sensors.begin();
//Blynk.begin(auth, ssid, pass);
timer.setInterval(100L, sendSensor);
timer.setInterval(500L, blinkLedWidget);
pinMode(sensorPin, INPUT); // set sensor pin as input
Blynk.begin("LXzpdNkbT7j6ON5HsB8EbbmF3hMaG9pm", "Salil OnePlus", "12345678"); // connect to Blynk server
//Blynk.setProperty(VIRTUAL_PIN2, "refresh", "200");
}

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
// Please don
//'t send more that 10 values per second.
Blynk.virtualWrite(V1, tempC);
//Blynk.virtualWrite(V2, tempF);
delay(200);
}


void loop() {
  
  int sensorValue = analogRead(sensorPin); // read sensor value
  percentageValue = map(sensorValue, 0, 2000, 0, 100); // calculate turbidity // calculate turbidity
  Serial.print("Turbidity: ");
  Serial.print(percentageValue);
  Serial.println("%");
  Blynk.virtualWrite(V2, percentageValue); 
  
  
  sensors.requestTemperatures(); // Request temperature reading from DS18B20
  float temperature = sensors.getTempCByIndex(); // Get temperature in Celsius
  
  Blynk.virtualWrite(V4, sensors.getTempCByIndex(0)); // send temperature value to Blynk app

  //turbidityValue = analogRead(23);
  delay(1000);
// send turbidity value to Blynk app
  //delay(500); // wait for 1 second
  Blynk.run();
  timer.run();
  delay(200); // wait for 1 second
}
