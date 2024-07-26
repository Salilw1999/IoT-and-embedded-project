#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <MFRC522.h>

#define SERVO_PIN 13
#define RFID_SS_PIN 5
#define RFID_RST_PIN 14

#define pirPin 4
#define irPin1 33
#define irPin2 25
#define irPin3 26
#define irPin4 27

#define LCD_I2C_ADDR 0x27

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);

int pirState = LOW;
int val = 0;
unsigned long lastMotionTime = 0;

char auth[] = "z3iSRT-CgLZQmCe1LNifZKG9Kq-sDYrE";
char ssid[] = "Khushi";
char pass[] = "12345678";

Servo myServo;

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

byte authorizedCardUID[] = {0xC3, 0xF0, 0xCA, 0x0F};

int emptySlotCount = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  myServo.attach(SERVO_PIN);
  pinMode(pirPin, INPUT);
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);
  SPI.begin();
  rfid.PCD_Init();

  myServo.write(0);
  delay(1);

  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.print("SMART PARKING");
}

bool isAuthorized() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (memcmp(rfid.uid.uidByte, authorizedCardUID, rfid.uid.size) == 0) {
      Serial.println("Authorized access");
      lcd.clear();
      lcd.backlight();
      lcd.print("Authorized");
      lcd.setCursor(0, 1);
      lcd.backlight();
      lcd.print("Access Granted");
      delay(2000);
      lcd.clear();
      return true;
    } else {
      Serial.println("Unauthorized access");
      lcd.clear();
      lcd.backlight();
      lcd.print("Unauthorized");
      lcd.setCursor(0, 1);
      lcd.backlight();
      lcd.print("Access Denied");
      delay(2000);
      lcd.clear();
      return false;
    }
  }
  return false;
}

BLYNK_WRITE(V0) {
  int angle = param.asInt();
  myServo.write(angle);
}

void loop() {
  if (isAuthorized()) {
    for (int angle = 0; angle <= 140; angle++) {
      myServo.write(angle);
      delay(1500 / 900);
    }

    delay(10000);

    myServo.write(0);

    Serial.println("Gate Closed");
     lcd.clear();
      lcd.backlight();
      lcd.print("Gate Closed");

     delay(1);
  }

// Uncomment this section if you want to use the PIR sensor
  
  val = digitalRead(pirPin);

  if (val == HIGH) {
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      lcd.clear();
      lcd.backlight();
      lcd.print("Gate Opened");
      myServo.write(140);
      delay(10000);
      myServo.write(0);
      pirState = HIGH;
      lastMotionTime = millis();
    }
  } else {
    if (pirState == HIGH) {
      unsigned long elapsedTime = millis() - lastMotionTime;
      if (elapsedTime >= 1000) {
        Serial.println("Motion ended. Returning to initial position.");
        lcd.clear();
        lcd.backlight();
        lcd.print("Gate Closed");
        myServo.write(0);
        pirState = LOW;
      }
    }
  }
  

  Blynk.run();

  int irValue1 = digitalRead(irPin1);
  int irValue2 = digitalRead(irPin2);
  int irValue3 = digitalRead(irPin3);
  int irValue4 = digitalRead(irPin4);

  Blynk.virtualWrite(V1, irValue1);
  Blynk.virtualWrite(V2, irValue2);
  Blynk.virtualWrite(V3, irValue3);
  Blynk.virtualWrite(V4, irValue4);

/*  // Print data in the serial monitor
  Serial.print("IR Sensor 1: ");
  Serial.print(irValue1);
  Serial.print(" | IR Sensor 2: ");
  Serial.print(irValue2);
  Serial.print(" | IR Sensor 3: ");
  Serial.print(irValue3);
  Serial.print(" | IR Sensor 4: ");
  Serial.println(irValue4);
*/
  // Count empty slots
  emptySlotCount = (irValue1 == LOW) + (irValue2 == LOW) + (irValue3 == LOW) + (irValue4 == LOW);

  // Display empty slot count on LCD
  lcd.clear();
  lcd.backlight();
  lcd.print("Empty Slots: ");
  lcd.setCursor(0, 1);
  lcd.backlight();
  lcd.print(emptySlotCount);

  // Print empty slot count in the serial monitor
  Serial.print("Empty Slot Count: ");
  Serial.println(emptySlotCount);

  delay(1000);
}
