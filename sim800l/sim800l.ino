#include <SoftwareSerial.h>

// Create a SoftwareSerial object to communicate with the SIM800L module
SoftwareSerial SIM800L(17, 16); // RX, TX pins

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  // Set baud rate for SIM800L module
  SIM800L.begin(9600);

  delay(1000); // Wait for module to stabilize
}

void loop() {
  // Send AT command to check if module is responding
  SIM800L.println("AT");
  delay(1000);

  // Check for response from module
  while (SIM800L.available()) {
    Serial.write(SIM800L.read());
  }
  
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

  // Replace <MESSAGE_CONTENT> with the message you want to send
  SIM800L.print("hello");
  delay(1000);A

  // End the message with a Ctrl+Z character
  SIM800L.print((char)26);

  delay(1000);
}
