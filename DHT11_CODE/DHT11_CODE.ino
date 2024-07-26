#include <DHT.h>

#define DHTPIN 2    // Define the pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11   // Define the type of the DHT sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(2000);  // Delay for 2 seconds between readings

  float humidity = dht.readHumidity();     // Read humidity
  float temperature = dht.readTemperature();  // Read temperature in Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}