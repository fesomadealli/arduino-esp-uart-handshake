#define ESP_RX 2 // Connected to txPin 12 of Arduino
#define ESP_TX 4 // Connected to rxPin 11 of Arduino

void setup() {
  // put your setup code here, to run once
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, ESP_RX, ESP_TX);

  // Specifying pinModes
  pinMode(ESP_RX, INPUT);
  pinMode(ESP_TX, OUTPUT);
}

void loop() {
  // put your code here to run repeatedly
  // --------Creating Handshake
  Serial.println("Creating Handshake");
  String _datafromNano = Serial2.readStringUntil('\n'); // Read the handshake message from Arduino
  _datafromNano.trim();
  Serial.println(_datafromNano);
  delay(1000);

  if ( _datafromNano == "Nano Ready!") {
    Serial.println("Handshake Successful");

    // --- Give Nano a feedback
    String _msgtoNano = "Esp Cam Ready!";
    Serial2.println(_msgtoNano); // Send handshake confirmation back to Arduino
  } else {
    Serial.println("No Handshake");
  }
}
