#include <FirebaseESP8266.h>  //https://github.com/mobizt/Firebase-ESP8266
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus
//#include <avr/interrupt.h>

//Install ArduinoJson Library
//Note: The latest JSON library might not work with the code. 
//So you may need to downgrade the library to version v5.13.5
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
#define FIREBASE_HOST "gps-tracker-4c6fd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "gbvoNE5kmeS21E9gPempJ9HJ5p4OjkK8VLCsYZOF"
#define WIFI_SSID "Salil OnePlus"
#define WIFI_PASSWORD "12345678"
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//GPS Module RX pin to NodeMCU D1
//GPS Module TX pin to NodeMCU D2
const int RXPin = 4;
const int TXPin = 5;
SoftwareSerial neo6m(RXPin, TXPin);
TinyGPSPlus gps;
//-----------------------------------------------------------------------------------


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void setup()
{

  Serial.begin(115200);

  neo6m.begin(9600);
  
  wifiConnect();

  Serial.println("Connecting Firebase.....");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase OK.");

}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void loop() {
  
  smartdelay_gps(1000);

  if(gps.location.isValid()) 
  {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    
    //-------------------------------------------------------------
    Send to Serial Monitor for Debugging
    Serial.print("LAT:  ");
    Serial.println(latitude);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude);
    //-------------------------------------------------------------
    
    //-------------------------------------------------------------
    if(Firebase.setFloat(firebaseData, "/GPS/f_latitude", latitude))
      {print_ok();}
    else
      {print_fail();}
    //-------------------------------------------------------------
    if(Firebase.setFloat(firebaseData, "/GPS/f_longitude", longitude))
      {print_ok();}
    else
      {print_fail();}
   //-------------------------------------------------------------
  }
  else
  {
    Serial.println("No valid GPS data found.");
  }
  
  delay(5000);
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
static void smartdelay_gps(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (neo6m.available())
      gps.encode(neo6m.read());
  } while (millis() - start < ms);
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void print_ok()
{
    Serial.println("------------------------------------");
    Serial.println("OK");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
void print_fail()
{
    Serial.println("------------------------------------");
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

void firebaseReconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}