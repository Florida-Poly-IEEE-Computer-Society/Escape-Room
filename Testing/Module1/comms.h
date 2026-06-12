// SENDER VARIABLES
uint8_t receiverAddress[] = {0x88, 0x57, 0x21, 0xAC, 0xCA, 0x68};
esp_now_peer_info_t peerInfo;

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
  esp_now_send(receiverAddress, (uint8_t*)&commandToSend, sizeof(commandToSend));
}