/************************************************************************************
* My Channel:https://www.youtube.com/c/ImpulseTech/featured Visit for More Project Videos
*
* *********************************************************************************
* Preferences--> Aditional boards Manager URLs :
* For ESP32:
* https://dl.espressif.com/dl/package_esp32_index.json
* https://blynk.cloud/external/api/logEvent?token=YourAuthToken&code=hello for loging the events
using rest API
* You can send only 100 events per devices per day
When the limit is reached you'll see the notification on the UI in the Device Timeline section
The maximum description length for the event is 300 chars
* *********************************************************************************/
#define BLYNK_TEMPLATE_ID "TMPLE8b_ltNC"
#define BLYNK_DEVICE_NAME "DS18B20 Temperature sensor"
#define BLYNK_AUTH_TOKEN "Ann6QdNGdrkIHC1_LxdR-_bNmlx7QS6Q"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "impulsetech"; // type your wifi name
char pass[] = "impulse567"; // type your wifi password
BlynkTimer timer;
void sendSensor()
{
// Request temperature to all devices on the data line
sensors.requestTemperatures();

Serial.print("Celsius temperature: ");
//We can connect more than one IC on the same data wire. 0 refers to the first IC on the wire
Serial.print(sensors.getTempCByIndex(0));
Serial.print(" - Fahrenheit temperature: ");
Serial.println(sensors.getTempFByIndex(0));
int tempC=sensors.getTempCByIndex(0);
int tempF=sensors.getTempFByIndex(0);
delay(1000);

// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V0, tempC);
Blynk.virtualWrite(V1, tempF);
delay(500);
}
void setup()
{
Serial.begin(9600);
sensors.begin();
Blynk.begin(auth, ssid, pass);
timer.setInterval(100L, sendSensor);
}
void loop()
{
Blynk.run();
timer.run();
}
