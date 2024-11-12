// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "6b09c228-dd27-4ee4-b28c-913ed747273f";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onServo1Change();
void onServo2Change();
void onServo3Change();

int servo1;
int servo2;
int servo3;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(servo1, READWRITE, ON_CHANGE, onServo1Change);
  ArduinoCloud.addProperty(servo2, READWRITE, ON_CHANGE, onServo2Change);
  ArduinoCloud.addProperty(servo3, READWRITE, ON_CHANGE, onServo3Change);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
