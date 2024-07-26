#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LoRa.h>
#include <SPI.h>

#define BLYNK_TEMPLATE_ID "TMPL30icM9MHB"
#define BLYNK_TEMPLATE_NAME "Forest Rescue System"
#define BLYNK_AUTH_TOKEN "AFdKMIEuZniYhGsJmnbqIvbMxqUnHrII"
#include <BlynkSimpleEsp32.h>

#define ss 5
#define rst 14
#define dio0 2
//#define flameSensorStatusPin V1
//#define smokeSensorStatusPin V2
#define buzzerPin 27

char auth[] = "AFdKMIEuZniYhGsJmnbqIvbMxqUnHrII";  // Replace with your Blynk auth token
char ssid[] = "prathamesh";
char pass[] = "12345678";

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

void setup() {
  Serial.begin(115200);
  delay(1000);

  Blynk.begin(auth, ssid, pass);
  LoRa.setPins(ss, rst, dio0);

  lcd.begin();
  lcd.clear();
  lcd.print("LoRa Receiver");

  pinMode(buzzerPin, OUTPUT);
  
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Blynk.run();

  // Check for LoRa packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read the binary values from the packet
    int flameStatus = LoRa.read();
    int smokeStatus = LoRa.read();

    // Display the sensor status in Blynk
    Blynk.virtualWrite(V1, flameStatus);
    Blynk.virtualWrite(V2, smokeStatus);

    // Activate buzzer if either flame or smoke is detected
    if (flameStatus == LOW || smokeStatus == LOW) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);  // Buzzer on for 500 milliseconds
      digitalWrite(buzzerPin, LOW);
    }

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flame: ");
    lcd.print(flameStatus == 1 ? "Not Detected" : "Detected");
    
    lcd.setCursor(0, 1);
    lcd.print("Smoke: ");
    lcd.print(smokeStatus == 1 ? "Not Detected" : "Detected");

    Serial.print("Flame Sensor Status: ");
    Serial.println(flameStatus);
    Serial.print("Smoke Sensor Status: ");
    Serial.println(smokeStatus);
  }

  delay(1);
}
