#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

int val;
int tempPin = A0;
int fan=D3; 

float m = -0.6527; //Slope 
float b = 1.30; //Y-Intercept 
float R0 = 21.91; 
int mq3 = A0; 
double g;
int sensor = D4;
int sm=0;

#define Relay1            D1
#define Relay2            D2

#define WLAN_SSID       "Salil OnePlus"       // Your SSID
#define WLAN_PASS       "12345678"// Your password

/********* Adafruit.io Setup ***********/

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "wsalil"            // Username
#define AIO_KEY         "aio_wiUt159nnPtDOc11uInEzYFseYOQ"   // Auth Key

//WIFI CLIENT
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/relay1"); // Feeds name should be same everywhere
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay2");
//Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay3");

Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/AValue");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  Serial.println("WiFi");
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
//  pinMode(Relay3, OUTPUT);
  pinMode(mq3,INPUT);
  pinMode(fan,OUTPUT);
  pinMode(sensor,INPUT_PULLUP);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 
  mqtt.subscribe(&Light1);
//  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light2);
 
}

uint32_t x=0;
void loop() {
 temp();
  MQTT_connect();
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(Relay1, Light1_State);
      
    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(Relay2, Light2_State);
    }
    /*if (subscription == &Light3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light3.lastread);
      int Light3_State = atoi((char *)Light3.lastread);
      digitalWrite(Relay3, Light3_State);
    }
    */

  }
Serial.print(F("\nSending photocell val "));
 Serial.print(x);
  Serial.print("...");
 if(!digitalRead(sensor)&&(!sm))
 {
  sm=1;
   if (! photocell.publish(1)) 
   {
    Serial.println(F("Failed"));
  } else
  {
    Serial.println(F("OK!"));
  }
 }
   if(!digitalRead(sensor)&&(sm))
 {
   sm=0;
   if (! photocell.publish(0)) 
   {
    Serial.println(F("Failed"));
  } else 
  {
    Serial.println(F("OK!"));
  }
 }
delay(5000);
  
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}

void mq3read()
{
    float sensor_volt; //Define variable for sensor voltage 
  float RS_gas; //Define variable for sensor resistance  
  float ratio; //Define variable for ratio
 int sensorValue = analogRead(mq3); //Read analog values of sensor  
  sensor_volt = sensorValue*(5.0/1023.0); //Convert analog values to voltage 
  RS_gas = ((5.0*10.0)/sensor_volt)-10.0; //Get value of RS in a gas
  ratio = RS_gas/R0;  // Get ratio RS_gas/RS_air
  double ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale 
  g=ppm;
}

void temp()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
/* uncomment this to get temperature in farenhite
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
*/ 


if (cel>=50)
{
  Serial.print("high");
  pinMode(fan,OUTPUT);
  digitalWrite(fan,HIGH);
}
else
{
  Serial.print("low");
  digitalWrite(fan,LOW);
  
}
}