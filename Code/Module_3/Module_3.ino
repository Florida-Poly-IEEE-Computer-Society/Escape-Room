/*
  Florida Polytechnic University
  IEEE - Computer Society
  Escape Room - Module 3
  Written by Ramiro Rojas, August-September 2026
*/

#include <esp_random.h>
#include <OneButton.h>
#include <DFRobot_DF1201S.h>

// DFPlayerPro variables
#define DF1201SSerial Serial2
DFRobot_DF1201S player;

// Button variables
OneButton *buttons[5] = {
  new OneButton(32, true, true),  // Only this pin has an internal pull-up resistor
  new OneButton(35, true, false),
  new OneButton(34, true, false),
  new OneButton(39, true, false),
  new OneButton(36, true, false)
};
char chars[5] = {0, 1, 2, 3, 4};
const char bigButton = 13;

// LED variables
const char buttonLEDs[5] = {14, 27, 26, 25, 33};
const char leds[6] = {4, 18, 19, 21, 22, 23};

// Simon game variables
char mainIndex = 0;     // Round number
char currentIndex = 0;  // Current sequence index
signed char solution[6] = {-1, -1, -1, -1, -1, -1};
signed char state = 0;

// Timer variables
long timerLength = long(4+26) * long(1000);
long startTime = 0;

void setup() {
  Serial.begin(9600);
  setupPlayer();

  for(char i = 0; i < 5; i++) {
    buttons[i] -> attachPress(press, &chars[i]);
    buttons[i] -> attachClick(click, &chars[i]);
    buttons[i] -> attachLongPressStop(longPressStop, &chars[i]);
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

  Serial.println("Started");
  delay(1000);
  // state = 2;
  // theWin();
}

void loop() {
  if(state == 0) {
    generateGame();
    displaySolution();
    state = 1;
  } else if(state == 1) {
    for(char i = 0; i < 5; i++) {
      buttons[i] -> tick();
    }
  } else if(state == 2) {
    Serial.println("YOU WON");
    while(1);
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
  Serial.println("Start guessing");
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

void guess(char index) {
  // blinkButtonLED(turnIndex);
  if(index == solution[currentIndex]) {
    Serial.println("Yuh huh");
    currentIndex++;
    if(currentIndex > 5) {
      Serial.println("Next round!");
      digitalWrite(leds[mainIndex], HIGH);
      currentIndex = 0;
      mainIndex++;
      if(mainIndex > 5) {
        // WIN
        state = 2;
        return;
      } else {
        delay(1000);
        state = 0;
        return;
      }
    } else {
      return;
    }
  } else {
    Serial.println("Nuh uh");
    currentIndex = 0;
    delay(2000);
    displaySolution();
    return;
  }
}

void blinkButtonLED(int index) {
  digitalWrite(buttonLEDs[index], HIGH);
  player.playFileNum(index + 1);
  delay(200);
  digitalWrite(buttonLEDs[index], LOW);
  // player.pause();
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

void press(void* index) {
  char indexChar = *(char*)index;
  // Serial.print("Press ");
  // Serial.println((int)indexChar);
  digitalWrite(buttonLEDs[indexChar], HIGH);
  player.playFileNum(indexChar + 1);
}

void click(void* index) {
  char indexChar = *(char*)index;
  // Serial.print("Click ");
  // Serial.println((int)indexChar);
  digitalWrite(buttonLEDs[indexChar], LOW);
  // player.pause();
  guess(indexChar);
}

void longPressStop(void* index) {
  char indexChar = *(char*)index;
  // Serial.print("Long Press Stop ");
  // Serial.println((int)indexChar);
  digitalWrite(buttonLEDs[indexChar], LOW);
  // player.pause();
  guess(indexChar);
}

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



void setupPlayer() {
  DF1201SSerial.begin(115200, SERIAL_8N1, 16, 17);
  delay(50);
  while(!player.begin(DF1201SSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  player.setVol(10);
  player.switchFunction(player.MUSIC);
  player.setPlayMode(player.SINGLE);
  player.setPrompt(false);
  // player.setPrompt(true);
  // player.pause();
}