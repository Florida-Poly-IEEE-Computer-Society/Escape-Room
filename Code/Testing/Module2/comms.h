// SENDER VARIABLES
uint8_t receiverAddress[] = {0xB4, 0xE6, 0x2D, 0xDE, 0x29, 0xDD};
esp_now_peer_info_t peerInfo;

// RECEIVER VARIABLES
int receivedCommand;

void setUpESP() {
  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
}



void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\rLast Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setUpSenderESP() {
  // Register for Send CB to get status of transmitted packet
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  // Register peer
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if(esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void sendDataESP(int commandToSend) {
  // Send message via ESP-NOW
  esp_now_send(receiverAddress, (uint8_t *)&commandToSend, sizeof(commandToSend));
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