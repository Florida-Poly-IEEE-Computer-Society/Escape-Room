#include <esp_now.h>
#include <WiFi.h>
#include <OneButton.h>
#include "comms.h"

OneButton startButton = OneButton(23, true, true);
OneButton completeButton = OneButton(22, true, true);

char state = 0;

void setup() {
  Serial.begin(115200);
  startButton.attachClick(onStart);
  completeButton.attachClick(onComplete);
  setUpESP();
  setUpSenderESP();
  Serial.println("Started");
}

void loop() {
  if(state == 0) {
    startButton.tick();
  } else if(state == 1) {
    completeButton.tick();
  } else if(state == 2) {
    Serial.println("IDLE");
    delay(3000);
  }
}

void onStart() {
  Serial.println("Started module");
  state = 1;
}

void onComplete() {
  sendDataESP(5);
  state = 2;
}
