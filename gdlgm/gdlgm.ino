#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>

static const int GPS_RX_Pin = 1; // GPIO 4=D2(connect Tx of GPS) and GPIO 5=D1(connect Rx of GPS)
static const int GPS_TX_Pin = 3;
static const uint32_t GPSBaud = 9600;
static const int BUZZER_Pin = 2; // Buzzer input pin

TinyGPSPlus gps;
SoftwareSerial mygps(GPS_RX_Pin, GPS_TX_Pin);

float latitude;
float longitude;
float velocity;
float sats;
String bearing;

SoftwareSerial SIM800L(17, 16); // RX, TX pins

bool sosTriggered = false; // Flag to track if SOS has been triggered

void setup() {
  Serial.begin(115200);
  mygps.begin(GPSBaud);
  SIM800L.begin(9600);
  pinMode(BUZZER_Pin, INPUT); // Set buzzer pin as input
  delay(1000);
}

void loop() {
  // Check for buzzer input indicating SOS
  if (digitalRead(BUZZER_Pin) == HIGH && !sosTriggered) { // Check if buzzer is ringing and not already triggered
    while (mygps.available() > 0) {
      if (gps.encode(mygps.read())) {
        displayInfo();
        sendSOS();
        makeCall();
        sosTriggered = true; // Set flag to indicate SOS has been triggered
      }
    }
  }
  // Reset the flag if buzzer stops ringing
  else if (digitalRead(BUZZER_Pin) == LOW) {
    sosTriggered = false;
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    sats = gps.satellites.value();
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    velocity = gps.speed.kmph();
    bearing = TinyGPSPlus::cardinal(gps.course.value());

    Serial.print("SATS: ");
    Serial.println(sats);
    Serial.print("LATITUDE: ");
    Serial.println(latitude, 6);
    Serial.print("LONGITUDE: ");
    Serial.println(longitude, 6);
    Serial.print("SPEED: ");
    Serial.print(velocity);
    Serial.println(" kmph");
    Serial.print("DIRECTION: ");
    Serial.println(bearing);
  }
}

void sendSOS() {
  // Send AT command to set SMS mode
  SIM800L.println("AT+CMGF=1");
  delay(1000);

  // Check for response from module
  while (SIM800L.available()) {
    Serial.write(SIM800L.read());
  }

  // Replace <PHONE_NUMBER> with the recipient's phone number
  SIM800L.print("AT+CMGS=\"+917620287909\"\r");
  delay(1000);

  // Generate Google Maps URL
  String googleMapsURL = "http://maps.google.com/maps?q=";
  googleMapsURL += String(latitude, 6);
  googleMapsURL += ",";
  googleMapsURL += String(longitude, 6);

  // Send SOS message
  SIM800L.print("SOS triggered! Latitude: ");
  SIM800L.print(latitude, 6);
  SIM800L.print(", Longitude: ");
  SIM800L.print(longitude, 6);
  SIM800L.print(", Speed: ");
  SIM800L.print(velocity);
  SIM800L.print(" kmph, Direction: ");
  SIM800L.print(bearing);
  SIM800L.println(". Open in Google Maps: " + googleMapsURL);
  delay(1000);

  // End the message with a Ctrl+Z character
  SIM800L.print((char)26);

  delay(1000);
}

void makeCall() {
  // Replace <PHONE_NUMBER> with the recipient's phone number
  SIM800L.print("ATD+917620287909;\r\n");
  delay(30000); // Give some time for the call to be answered (adjust as needed)
  SIM800L.println("ATH"); // Hang up the call
}
 
