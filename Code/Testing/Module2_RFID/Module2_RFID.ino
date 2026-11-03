#include <SPI.h>
#include <MFRC522.h>

const char RFID_SS = 10, RFID_RST = 11;

MFRC522 rfid(RFID_SS, RFID_RST);
String CurrentCard = "";
int CardTimeOut = 50;
String content = "";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.printLn("Setup Complete");
}

void loop() {
  if(rfid.PICC_IsNewCardPresent()) {
    CardTimeOut = 0;
    if(rfid.PICC_ReadCardSerial()) {
      for(byte i = 0; i < rfid.uid.size; i++) {
        content.concat(String(rfid.uid.uidByte[i], HEX));
      }
      content.toUpperCase();

      if(content != CurrentCard) {
        CurrentCard = content;
        onFirst();
      } else {
        // afterFirst();
      }

      content = "";
    }
  }

if(CardTimeOut == 8) {
  onRemove();
}
CardTimeOut++;
if(CardTimeOut > 100) {
  CardTimeOut = 100;
}
}

void onFirst() {
  Serial.println(content);
}

void onRemove() {
  CurrentCard = "";
  content = "";
  Serial.println("Card was removed");
}

