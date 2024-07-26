#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


#define BLYNK_TEMPLATE_ID "TMPL3kB0mNIWD"
#define BLYNK_TEMPLATE_NAME "agricuture robot"
#define BLYNK_AUTH_TOKEN "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg"

#define DHTPIN 2
#define DHTTYPE DHT11

char auth[] = "NFjUY5ww3RXf6Y3Y30mb8jXVoSp92WZg";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  Blynk.run();

  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V7, humidity);    // V5 is the virtual pin in the Blynk app for humidity
  Blynk.virtualWrite(V8, temperature); // V6 is the virtual pin in the Blynk app for temperature

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}