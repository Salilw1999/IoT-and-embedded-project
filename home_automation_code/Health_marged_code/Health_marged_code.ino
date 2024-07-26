#define BLYNK_TEMPLATE_ID "TMPL3Yd9KkQCa"
#define BLYNK_TEMPLATE_NAME "Health Monitoring system"
#define BLYNK_AUTH_TOKEN "i-1hFK3893A3YvIaQvWB3oEhK7aqOnFh"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>
#include <Wire.h>
#include <PulseSensorPlayground.h> 
#include "MAX30100_PulseOximeter.h"
//#define REPORTING_PERIOD_MS     1000

char auth[] = "i-1hFK3893A3YvIaQvWB3oEhK7aqOnFh";
char ssid[] = "Edutech labs 5G";
char pass[] = "Edutech@1994";
 
#define DHTPIN D8 // D8, DHT
 #define DHTTYPE DHT11 // DHT 11
const int PulseWire = A0; 
PulseSensorPlayground pulseSensor;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
//int heartValue = 0;
//#define REPORTING_PERIOD_MS     3000
//SimpleTimer timer;

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
  ;
}


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V0, h);

}

Servo servo;

BLYNK_WRITE(V5)
{
  servo.write(param.asInt());
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth,ssid, pass);
 
 pinMode(D8, OUTPUT);
pinMode(D0, OUTPUT); 
pinMode(A0, OUTPUT); 
  servo.attach(D7); 
pulseSensor.analogInput(PulseWire); 
  dht.begin();
   
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
 Serial.print("Initializing Pulse Oximeter..");
 if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
    digitalWrite(1, HIGH);
  }

 pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);

  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);

  timer.setInterval(3000L, getSendData);

  }
 
void loop()
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  // Make sure to call update as fast as possible
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {


    // to android cell phone application
    Serial.print("BPM: ");
    Serial.print(pox.getHeartRate());
    //blue.println("\n");

    Serial.print("    SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.print("%");
    Serial.println("\n");

    Blynk.virtualWrite(V7, pox.getHeartRate() );
    Blynk.virtualWrite(V8, pox.getSpO2());

   /*int myBPM = pulseSensor.getBeatsPerMinute();      // Calculates BPM
   Serial.print(myBPM());
   Blynk.virtualWrite(V10, myBPM() ); 
    


    tsLastReport = millis();
*/
  }
  

Blynk.run();
timer.run();
 // Blynk.virtualWrite(V4, heartValue);
  //Wait for a bit to keep serial data from saturating
  delay(1);
 }

 void getSendData()
{


}
