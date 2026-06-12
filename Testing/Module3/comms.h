// RECEIVER VARIABLES
int receivedCommand;

void setUpESP() {
  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedCommand, incomingData, sizeof(receivedCommand));
  // Serial.print("Bytes received: ");
  // Serial.println(len);
  Serial.print("Command: ");
  Serial.println(receivedCommand);

  state = 1;
}

void setUpReceiverESP() {
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}