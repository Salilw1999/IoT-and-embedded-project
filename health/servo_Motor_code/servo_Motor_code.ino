#define BLYNK_TEMPLATE_ID "TMPL3lA8GLbXE"
#define BLYNK_TEMPLATE_NAME "all in one agricuture"
#define BLYNK_AUTH_TOKEN "a4BbXSSWJKBfMpM8vVprv_yQBHqO2Gqv"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = "a4BbXSSWJKBfMpM8vVprv_yQBHqO2Gqv";
char ssid[] = "Salil OnePlus";
char pass[] = "12345678";

//#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;

BlynkTimer timer; 

BLYNK_WRITE(V6)
{   
 int pos = param.asInt(); // Get value as integer
  myservo.write(pos);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

 // timer.setInterval(1000L, dhtData); 
  myservo.attach(13); 
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
   // pos = map(pos,0,160,0,180);    
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(1);           // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees    
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(1);                           // waits 15ms for the servo to reach the position
  }
  Blynk.run();
  timer.run();
}
