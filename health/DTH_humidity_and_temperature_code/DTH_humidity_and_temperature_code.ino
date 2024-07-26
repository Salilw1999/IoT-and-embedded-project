#define BLYNK_TEMPLATE_ID "TMPL3xg0VmnSy"
#define BLYNK_TEMPLATE_NAME "Health Monitoring system"
#define BLYNK_AUTH_TOKEN "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "I96BPIKDWxInkvHFXtPe4zhbWcHkz1f8";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

#define DHTPIN 15          // The pin which is connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop()
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
  Blynk.run();
}
