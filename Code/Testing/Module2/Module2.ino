#include <esp_now.h>
#include <WiFi.h>
#include <OneButton.h>

OneButton button = OneButton(23, true, true);

char state = 0;

#include "comms.h"

void setup() {
  Serial.begin(115200);
  button.attachClick(onButtonClick);
  setUpESP();
  setUpSenderESP();
  setUpReceiverESP();
}

void loop() {
  if(state == 0) {
    //
  } else if(state == 1) {
    button.tick();
  } else if(state == 2) {
    Serial.println("IDLE");
    delay(3000);
  }
}

void onButtonClick() {
  sendDataESP(6);
  state = 2;
}
