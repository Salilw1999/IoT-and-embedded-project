#define BLYNK_TEMPLATE_ID "TMPL3KRt-_Fs9"
#define BLYNK_TEMPLATE_NAME "Water management"
#define BLYNK_AUTH_TOKEN "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//const int potPin=A0;
const int potPin=36;
float ph;
float Value=0;
 
//String apiKey = "1S2U0Zglg9swb9ydOPrp5Ywa1_wFMDMK"; // Enter your Write API key from ThingSpeak

String AUTH = "g2WmQ0OzUrLRkzKd1A4ro-yEvzg6l3R8";
const char *ssid = "Salil OnePlus"; // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";
//const char* server = "api.thingspeak.com";// don't change this
//
//WiFiClient client;
//

void setup()
{
  // Debug console
  Serial.begin(9600);
   pinMode(potPin,INPUT);
   delay(100);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


//BLYNK_WRITE(V0) // V5 is the number of Virtual Pin  
//{
//  int potPin= param.asInt();
//}




 
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin();
//  pinMode(potPin,INPUT);
// delay(1000);
//
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(2000);
//    Serial.print(".");
//  }
//  // Print local IP address and start web server
//  Serial.println("");
//  Serial.println("WiFi connected.");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//  
//}
 
void loop() {
  // put your main code here, to run repeatedly:
//Value= analogRead(potPin);
Value= analogRead(potPin);
Serial.print(Value);
Serial.print(" | ");

float voltage=Value*(3.3/5095.0);
ph=(3.3*voltage);
Serial.println(ph);
Blynk.virtualWrite(V0,ph);
delay(200);
Blynk.run();
}
