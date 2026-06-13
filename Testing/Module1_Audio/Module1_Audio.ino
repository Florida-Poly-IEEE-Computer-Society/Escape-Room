#include <OneButton.h>
#include <DFRobot_DF1201S.h>

OneButton startButton = OneButton(23, true, true);
OneButton completeButton = OneButton(22, true, true);

#define DF1201SSerial Serial2
DFRobot_DF1201S player;

char state = 0;

void setup() {
  Serial.begin(9600);
  DF1201SSerial.begin(115200, SERIAL_8N1, 16, 17);
  while (!player.begin(DF1201SSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }

  startButton.attachClick(onStart);
  completeButton.attachClick(onComplete);

  player.switchFunction(player.MUSIC);
  player.setPlayMode(player.SINGLE);
  player.setVol(8);
  Serial.println("Started");
}

void loop() {
  startButton.tick();
  completeButton.tick();
}

void onStart() {
  Serial.println("Started module");
  player.playFileNum(1);
}

void onComplete() {
  Serial.println("Completed module");
  player.playFileNum(1);
}
