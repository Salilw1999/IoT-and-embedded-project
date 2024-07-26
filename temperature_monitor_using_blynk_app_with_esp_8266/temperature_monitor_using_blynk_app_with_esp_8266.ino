#define BLYNK_PRINT Serial // enable Blynk debugging#define BLYNK_TEMPLATE_ID "TMPL3Bwg-No7C"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 10          // Pin where the DHT11 sensor is connected
#define DHTTYPE DHT11      // DHT11 sensor type

char auth[] = "MLfecHdqYcTeYG2DgIAxWILMQrmhwhoo"; // replace with your own auth token
char ssid[] = "Salil OnePlus"; // replace with your own WiFi SSID
char pass[] = "12345678"; // replace with your own WiFi password

DHT dht(DHTPIN, DHTTYPE);         // Initialize the DHT11 sensor

void setup()
{
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  float temperature = dht.readTemperature();  // Read temperature value from DHT11 sensor
  float humidity = dht.readHumidity();        // Read humidity value from DHT11 sensor
  if (!isnan(temperature)) {                  // Check if temperature value is valid
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C");
    Serial.println();
    Blynk.virtualWrite(V7, temperature);      // Send temperature value to the Blynk app
  }
  if (!isnan(humidity)) {                     // Check if humidity value is valid
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");
    Serial.println();
    Blynk.virtualWrite(V8, humidity);         // Send humidity value to the Blynk app
  }
  delay(2000);                                // Wait for 2 seconds before reading again
}
