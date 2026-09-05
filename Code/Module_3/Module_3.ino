/*
  Florida Polytechnic University
  IEEE - Computer Society
  Escape Room - Module 3
  Written by Ramiro Rojas, August 2026
*/

#include <esp_random.h>
#include <OneButton.h>
// #include <DFRobot_DF1201S.h>
// #include <SoftwareSerial.h>

// DFPlayerPro variables
// SoftwareSerial softSerial(2, 3);  //RX, TX
// DFRobot_DF1201S player;

// Button variables
OneButton button1(32, true, true);  // Only this pin has an internal pull-up resistor
OneButton button2(35, true, false);
OneButton button3(34, true, false);
OneButton button4(39, true, false);
OneButton button5(36, true, false);
const char bigButton = 13;

// LED variables
const char buttonLEDs[5] = {14, 27, 26, 25, 33};
const char leds[6] = {4, 18, 19, 21, 22, 23};

// Simon game variables
char currentIndex = 0;
char tempIndex = 0;
signed char state = -1;
signed char solution[6] = {-1, -1, -1, -1, -1, -1};

// Timer variables
long timerLength = long(4+26) * long(1000);
long startTime = 0;

void setup() {
  // setupPlayer();
  Serial.begin(115200);
  for(char i = 0; i < 5; i++) {
    pinMode(buttonLEDs[i], OUTPUT);
    pinMode(leds[i], OUTPUT);
  }
  pinMode(leds[5], OUTPUT);

  // WAIT FOR ESPNOW SIGNAL FROM MODULE 2
  // while(state == -1) {
  //   while (!Serial.available());
  //   int x = Serial.readString().toInt();
  //   // Serial.println(x);
  //   if(x == 0) {
  //     // digitalWrite(13, HIGH);
  //   } else if(x == 1) {
  //     digitalWrite(13, LOW);
  //     state = 0;
  //     // state = 2;
  //     // theWin();
  //   }
  // }

  // generateGame();

  // Serial.print("Started");
  // delay(1000);
  // state = 2;
  // theWin();

  state = 0;
}

void loop() {
  if(state == 0) {
    generateGame();
    displaySolution();
    state = 1;
  } else if(state == 1) {
    // handleInput();
  } else if(state == 2) {
    // Ending
  }
  // if(state == 0) {
  //   // printState();
  //   displayCurrentTurn();
  // } else if(state == 1) {
  //   handleInput();
  // } else if(state == 2) {
  //   resetLEDs();
  //   for(int i = -1; i < 6; i++) {
  //     if(i >= 0) {
  //       digitalWrite(leds[i], HIGH);
  //     }
  //     // if(checkTimer() == true) {
  //     //   state = 4;
  //     //   timerFinished();
  //     //   Serial.print(2);
  //     //   break;
  //     // }
  //     if(digitalRead(bigButton) == LOW) {
  //       state = 4;
  //       bigButtonPressed();
  //       Serial.print(3);
  //       break;
  //     }
  //     delay(100);
  //   }
  //   if(checkTimer() == true) {
  //     state = 4;
  //     timerFinished();
  //     Serial.print(2);
  //     // break;
  //   }
  // } else if(state == 3) {
  //   Serial.println("You lost");
  //   blinkWrong();
  // }
}

// Generate a new solution
void generateGame() {
  randomSeed(esp_random());
  for(int i = 0; i < 6; i++) {
    solution[i] = random(0, 5);
    Serial.print(solution[i]);
  }
  Serial.println();
}

// void printState() {
//   Serial.println();
//   Serial.print("Index: ");
//   Serial.println(index);
//   Serial.print("TempIndex: ");
//   Serial.println(tempIndex);
//   Serial.println();
// }

void displaySolution() {
  for(int i = 0; i < sizeof(solution); i++) {
    blinkButtonLED(solution[i]);
    if(i < sizeof(solution)-1) {
      delay(350);
    }
  }
  // state = 1;
}

// void handleInput() {
//   char customKey = customKeypad.getKey();
//   if(customKey == '0') {
//     // Serial.println("LED 1");
//     guess(0);
//   } else if(customKey == '1') {
//     // Serial.println("LED 2");
//     guess(1);
//   } else if(customKey == '2') {
//     // Serial.println("LED 3");
//     guess(2);
//   } else if(customKey == '3') {
//     // Serial.println("LED 4");
//     guess(3);
//   }
// }

// void guess(int turnIndex) {
//   blinkButtonLED(turnIndex);
//   if(turnIndex == solution[tempIndex]) {
//     // Serial.println("Yuh huh");
//     if(index == 5 && tempIndex == index) {
//       state = 2;
//       theWin();
//       return;
//     }
//   } else {
//     // Serial.println("Nuh uh");
//     state = 3;
//     return;
//   }
//   tempIndex++;
//   if(tempIndex > index) {
//     state = 0;
//     index++;
//     digitalWrite(leds[index-1], HIGH);
//     tempIndex = 0;
//     delay(1000);
//   }
// }

void blinkButtonLED(int index) {
  digitalWrite(buttonLEDs[index], HIGH);
  delay(200);
  digitalWrite(buttonLEDs[index], LOW);
}

// void resetLEDs() {
//   for(int i = 0; i < 6; i++) {
//     digitalWrite(leds[i], LOW);
//   }
// }

// void blinkWrong() {
//   resetLEDs();
//   delay(300);
//   for(int i = 0; i < 3; i++) {
//     digitalWrite(leds[0], HIGH);
//     digitalWrite(leds[1], HIGH);
//     delay(300);
//     resetLEDs();
//     delay(300);
//   }
//   index = 0;
//   tempIndex = 0;
//   state = 0;
//   generateGame();
//   delay(800);
// }

// void theWin() {
//   pinMode(bigButton, INPUT_PULLUP);
//   digitalWrite(leds[5], HIGH);
//   // Serial.println("You Won");
//   Serial.print(1);
//   // player.playFileNum(1);
//   delay(500);
//   startTimer();
// }

// void bigButtonPressed() {
//   resetLEDs();
//   Serial.println("UPLOAD INTERRUPTED");
// }

// void startTimer() {
//   startTime = long(millis());
//   // Serial.print("Started timer at: ");
//   // Serial.println(startTime);
// }

// bool checkTimer() {
//   long current = long(millis());
//   // Serial.println(timerLength);
//   // Serial.println(current);
//   // Serial.println(current - startTime);
//   // Serial.println();
//   if(current - startTime >= timerLength) {
//     return true;
//   } else {
//     return false;
//   }
//   // return false;
// }

// void timerFinished() {
//   resetLEDs();
//   // Serial.println("You did nothing");
// }



// void setupPlayer() {
//   softSerial.begin(115200);
//   while(!player.begin(softSerial)) {
//     Serial.println("Init failed, please check the wire connection!");
//     delay(1000);
//   }
//   player.setVol(3);
//   player.switchFunction(player.MUSIC);
//   player.setPlayMode(player.SINGLE);
//   // player.setPrompt(false);
//   player.setPrompt(true);
//   // player.pause();
//   // delay(1500);
// }