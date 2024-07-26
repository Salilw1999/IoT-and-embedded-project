/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-cam-projects-ebook/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/


#include "esp_camera.h"
#include "SPI.h"
#include "driver/rtc_io.h"
#include "ESP32_MailClient.h"
#include <FS.h>
#include <SPIFFS.h>
//#include <WiFi.h>
//#include <BlynkSimpleEthernet.h>

#include <WiFi.h>
#define BLYNK_TEMPLATE_ID           "TMPL3mnVcyg1F"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "ONkfiOcHh5lx48vPY8ljoqSMy2QSiOLJ"

//#define BLYNK_TEMPLATE_ID "TMPLAuGIFQht"
//#define BLYNK_DEVICE_NAME "mailbell"
//#define BLYNK_AUTH_TOKEN "FXLxzDw68csS794XthCf_97XfeEvc_KN"
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define FILE_PHOTO "/photo.jpg"

char auth[] = "ONkfiOcHh5lx48vPY8ljoqSMy2QSiOLJ";

char ssid[] = "Pranav";
char pass[] = "123456789";

// REPLACE WITH YOUR NETWORK CREDENTIALS
//const char* ssid = "Pawar";
const char* password = "123456789";


void startCameraServer() {
  
}

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } 
  else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

// To send Emails using Gmail on port 465 (SSL), you need to create an app password: https://support.google.com/accounts/answer/185833
#define emailSenderAccount    "mailwine8@gmail.com"
#define emailSenderPassword   "gpbszmjlpndithvp"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32-CAM test Photo Captured"

//#define emailRecipient        "shantanup410@gmail.com"
#define emailRecipient2        "pranavshinde0004@gmail.com"
#define emailRecipient3        "mailwine8@gmail.com"
#define emailRecipient4        "salilwadke@gmail.com"

#define CAMERA_MODEL_AI_THINKER

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#else
#error "Camera model not selected"
#endif

// The Email Sending data object contains config and data to send
SMTPData smtpData;

// Photo File Name to save in SPIFFS
#define FILE_PHOTO "/photo.jpg"

//BlynkTimer timer;

/*
  #define BLYNK_TEMPLATE_ID "TMPLAuGIFQht"
  #define BLYNK_DEVICE_NAME "doorbell"
  #define BLYNK_AUTH_TOKEN "XrpghLDMcqXaRY0PgNT2ElhTChnZ2yTO"
*/

#define RELAY_1 12
#define RELAY_2 13
#define BELL_BUTTON 15
#define LED_FLASH 4

//char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "Pawar";
//char pass[] = "iampawar@41";

unsigned int number_of_pins = 4;
unsigned int V_pin[ 4] = { RELAY_1, RELAY_2, BELL_BUTTON, LED_FLASH };


BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite( RELAY_1, pinValue);
}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  digitalWrite( RELAY_2, pinValue);
}

/*
  BLYNK_READ(V2){
  Blynk.virtualWrite(V2, millis() / 1000);
  }
*/

BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  digitalWrite( LED_FLASH, pinValue);
}
/*
  BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  digitalWrite(7, pinValue);
  }


  BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  digitalWrite(7, pinValue);
  }
*/

BlynkTimer timer_lr;

void myTimerEvent() {

}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  Serial.begin(115200);
  Serial.println();


  for ( unsigned int __counter = 0; __counter < number_of_pins; __counter ++) {
    if ( __counter != 2) {
      pinMode( V_pin[__counter], OUTPUT);
    }
    else {
      pinMode( V_pin[__counter], INPUT);
    }
  }


  // Connect to Wi-Fi
  //Blynk.begin(auth);
  Blynk.begin(auth, ssid, pass);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
  else {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }

  // Print ESP32 Local IP Address
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());

  camera_config_t config;

  // Initialize camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }


  capturePhotoSaveSpiffs();
  sendPhoto();
  
    for (int i = 10; i > 0; i--) {
    delay(3000);
    }

  Serial.println("Starting camera server");
  startCameraServer();
  
  timer_lr.setInterval(100L, myTimerEvent);
}

void loop() {
  if ( digitalRead( BELL_BUTTON) == HIGH ) {
    Blynk.virtualWrite(V2, HIGH);

    capturePhotoSaveSpiffs();
    sendPhoto();

    startCameraServer(80);
  }
  Blynk.run();
  timer_lr.run();
}

// Check if photo capture was successful
bool checkPhoto( fs::FS &fs ) {
  File f_pic = fs.open( FILE_PHOTO );
  unsigned int pic_sz = f_pic.size();
  return ( pic_sz > 100 );
}

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveSpiffs( void ) {
  camera_fb_t * fb = NULL; // pointer
  bool ok = 0; // Boolean indicating if the picture has been taken correctly

  do {
    // Take a photo with the camera
    Serial.println("Taking a photo...");

    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    // Photo file name
    Serial.printf("Picture file name: %s\n", FILE_PHOTO);
    File file = SPIFFS.open(FILE_PHOTO, FILE_WRITE);

    // Insert the data in the photo file
    if (!file) {
      Serial.println("Failed to open file in writing mode");
    }
    else {
      file.write(fb->buf, fb->len); // payload (image), payload length
      Serial.print("The picture has been saved in ");
      Serial.print(FILE_PHOTO);
      Serial.print(" - Size: ");
      Serial.print(file.size());
      Serial.println(" bytes");
    }
    // Close the file
    file.close();
    esp_camera_fb_return(fb);

    // check if file has been correctly saved in SPIFFS
    ok = checkPhoto(SPIFFS);
  } while ( !ok );
}

void sendPhoto( void ) {
  // Preparing email
  Serial.println("Sending email...");
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

  // Set the sender name and Email
  smtpData.setSender("ESP32-CAM", emailSenderAccount);

  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");

  // Set the subject
  smtpData.setSubject(emailSubject);

  // Set the email message in HTML format
  //Serial.print("IP Address: http://");
  //Serial.println();
  
  String stringMessage = String("<h2>You have visitor</h2> at: http://" + IpAddress2String( WiFi.localIP()) );  // concatenating two strings
  //String stringOne = String(13);                        //
  smtpData.setMessage(stringMessage, true);
  // Set the email message in text format
  //smtpData.setMessage("Photo captured with ESP32-CAM and attached in this email.", false);

  // Add recipients, can add more than one recipient
  //smtpData.addRecipient(emailRecipient);
  smtpData.addRecipient(emailRecipient2);
  smtpData.addRecipient(emailRecipient3);
  smtpData.addRecipient(emailRecipient4);

  // Add attach files from SPIFFS
  smtpData.addAttachFile(FILE_PHOTO, "image/jpg");
  // Set the storage type to attach files in your email (SPIFFS)
  smtpData.setFileStorageType(MailClientStorageType::SPIFFS);

  smtpData.setSendCallback(sendCallback);

  // Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  // Clear all data from Email object to free memory
  smtpData.empty();
}

// Callback function to get the Email sending status
void sendCallback(SendStatus msg) {
  //Print the current status
  Serial.println(msg.info());
}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}
