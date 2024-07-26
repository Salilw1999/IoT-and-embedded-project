#include <SoftwareSerial.h>

SoftwareSerial mySerial(17, 16); // RX, TX pins for ESP8266 to communicate with A9G

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(1000);

  Serial.println("Initializing A9G module...");
  delay(2000);

  sendATCommand("AT", "OK");

  // Disable echo
  sendATCommand("ATE0", "OK");

  // Set SMS mode to text
  sendATCommand("AT+CMGF=1", "OK");
}

void loop() {
  Serial.println("Calling family member...");

  // Replace "FamilyPhoneNumber" with the actual phone number of your family member
  if (callPhoneNumber("+917620287909")) {
    Serial.println("Call initiated successfully.");
  } else {
    Serial.println("Failed to initiate call. Please check your connections and try again.");
  }

  delay(5000); // Wait for 5 seconds before making another call
}

void sendATCommand(String command, String expectedResponse) {
  mySerial.println(command);
  delay(500);
  waitForResponse(expectedResponse);
}

boolean callPhoneNumber(String phoneNumber) {
  String callCommand = "ATD" + phoneNumber + ";";
  mySerial.println(callCommand);
  delay(1000); // Wait for the call to be initiated

  // Check if the call is successfully initiated
  return waitForResponse("OK");
}

boolean waitForResponse(String expectedResponse) {
  String response = "";
  long timeout = millis() + 5000; // 5 seconds timeout

  while (millis() < timeout) {
    if (mySerial.available()) {
      char c = mySerial.read();
      response += c;

      if (response.endsWith(expectedResponse)) {
        return true; // Expected response received
      }
    }
  }

  Serial.println("Timeout waiting for response: " + expectedResponse);
  return false; // Return false if the expected response is not received within the timeout
}
