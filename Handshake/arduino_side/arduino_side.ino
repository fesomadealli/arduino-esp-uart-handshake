#include <SoftwareSerial.h>

#define rxPin 12 // Connect with ESP_TX (GPIO 2) on ESP32-CAM
#define txPin 11 // Connect with ESP_RX (GPIO 4) on ESP32-CAM

SoftwareSerial espSerial(rxPin, txPin); // Initialize the SoftwareSerial instance

void setup() {
  // put your code here to run once

  // Specifying pinModes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // Native Serial Port
  Serial.begin(9600);
  Serial.println("Native Serial Active");

  // Software Serial Port
  espSerial.begin(9600); // Use the same baud rate for SoftwareSerial
  Serial.println("Software Serial Active");
}

bool isHandshake() {
  if (espSerial.available()) {
    String _msgfromEsp = espSerial.readStringUntil('\n');
    _msgfromEsp.trim();
    Serial.println(_msgfromEsp);
    
    if ( _msgfromEsp == "Esp Cam Ready!") {
      return true;
    }
  }
  return false;
}

void loop() {
  // put your code here to run repeatedly
  // --------Creating Handshake
  String _datatoEsp = "Nano Ready!"; // the extra 1 for the terminal character
  Serial.println(_datatoEsp);
  espSerial.println(_datatoEsp); // Send handshake message to ESP32-CAM
  delay(1000);

  if (isHandshake()) {
    Serial.println("Handshake Successful");
    // Do whatever you need to do after the handshake is successful
  } else {
    Serial.println("No Handshake");
  }
}
