/*
  Florida Polytechnic University
  IEEE - Computer Society
  Escape Room - Module 2
  Written by Ramiro Rojas, Aug 2025

  This is exactly what was uploaded to the Arduino UNO board.
  Due to the short amount of time spent working on this project,
  this code is not commented and needs cleaning up.
*/

#include <SPI.h>
#include <MFRC522.h>

#define LED1  A5
#define LED2  A4
#define LED3  A3
#define LED4  A2

// PIN Numbers : RESET + SDAs
#define RST_PIN         10
#define SS_1_PIN        6
#define SS_2_PIN        7
#define SS_3_PIN        8
#define SS_4_PIN        9

#define NR_OF_READERS   4

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN, SS_4_PIN};

byte leds[4] = {LED1, LED2, LED3, LED4};

String answers[4] = {"73DA402A", "33FDAF28", "B3CD026", "3D5A928"};
// String answers[5] = {"73DA402A", "33FDAF28", "B3CD026", "3D5A928", "D3D92128"};

MFRC522 rfid[NR_OF_READERS];
String CurrentCard[NR_OF_READERS] = {"", "", "", ""};
int CardTimeOut[NR_OF_READERS] = {50, 50, 50, 50};
String content[NR_OF_READERS] = {"", "", "", ""};

int state = 0;
int wins[4] = {false, false, false, false};

void setup() {
  Serial.begin(31250);
  while (!Serial);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  SPI.begin();

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    rfid[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    rfid[reader].PCD_DumpVersionToSerial();
    //rfid[reader].PCD_SetAntennaGain(rfid[reader].RxGain_max);
  }
}

void loop() {
  if(state == 0) {
    while (!Serial.available());
    int x = Serial.readString().toInt();
    // Serial.println(x);
    if(x == 0) {
      // digitalWrite(13, HIGH);
    } else if(x == 1) {
      // digitalWrite(13, LOW);
      state = 1;
    }
  } else if(state == 1) {
    checkReaders();
  } else if(state == 2) {
    ;
  }
}

void checkReaders() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if(state == 1) {
      if (rfid[reader].PICC_IsNewCardPresent()) {
        CardTimeOut[reader] = 0;
        if (rfid[reader].PICC_ReadCardSerial()) {
          getUID(reader);
          handleUID(reader);
          content[reader] = "";
        }
      }
      // Detects when the tag is removed
      if (CardTimeOut[reader] == 8) {
        onRemove(reader);
        // Serial.println("Remove was called");
      }
      CardTimeOut[reader]++;
      if(CardTimeOut[reader] > 100) {
        CardTimeOut[reader] = 100;
      }
      // Serial.println(CardTimeOut[reader]);
    }
  }
  // delay(5);
}

void getUID(int reader) {
  for (byte i = 0; i < rfid[reader].uid.size; i++) {
    content[reader].concat(String(rfid[reader].uid.uidByte[i], HEX));
  }
  content[reader].toUpperCase();
  // Serial.println(content[reader]);
}
void handleUID(int reader) {
  // [Called everytime]
  if (content[reader] != CurrentCard[reader]) {
    onFirst(reader);
  } else {
    // afterFirst();
  }
}

void onFirst(int reader) {
  CurrentCard[reader] = content[reader];
  Serial.print(reader+1);
  Serial.print(" ");
  Serial.println(content[reader]);
  // digitalWrite(leds[reader], HIGH);
  if(content[reader] == answers[reader]) {
    digitalWrite(leds[reader], HIGH);
    wins[reader] = true;
    checkWins();
  }
}

void onRemove(int reader) {
  CurrentCard[reader] = "";
  content[reader] = "";
  Serial.print(reader+1);
  Serial.println(" was removed");
  digitalWrite(leds[reader], LOW);
  wins[reader] = false;
}

void checkWins() {
  int count = 0;
  for(int i = 0; i < 4; i++) {
    if(wins[i] == true) {
      count++;
    }
  }
  if(count == 4) {
    state = 2;
    Serial.print(1);
  }
}