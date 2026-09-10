#include <OneButton.h>

OneButton *buttons[5] = {
  new OneButton(32, true, true),
  new OneButton(35, true, false),
  new OneButton(34, true, false),
  new OneButton(39, true, false),
  new OneButton(36, true, false)
};

char Bleds[5] = {14, 27, 26, 25, 33};
char leds[6] = {4, 18, 19, 21, 22, 23};
char chars[5] = {0, 1, 2, 3, 4};

void setup() {
  Serial.begin(115200);
  for(char i = 0; i < 5; i++) {
    buttons[i] -> attachPress(press, &chars[i]);
    buttons[i] -> attachClick(click, &chars[i]);
    // buttons[i] -> attachDoubleClick(doubleClick, &chars[i]);
    // buttons[i] -> attachMultiClick(multiClick, &chars[i]);
    // buttons[i] -> attachLongPressStart(longPressStart, &chars[i]);
    buttons[i] -> attachLongPressStop(longPressStop, &chars[i]);
    // buttons[i] -> attachDuringLongPress(duringLongPress, &chars[i]);
    // buttons[i] -> attachIdle(idle);
    pinMode(Bleds[i], OUTPUT);
    pinMode(leds[i], OUTPUT);
  }
  pinMode(leds[5], OUTPUT);
  Serial.println("Started");
}

void loop() {
  for(char i = 0; i < 5; i++) {
    buttons[i] -> tick();
  }
  delay(10);
}

void press(void* index) {
  char indexChar = *(char*)index;
  Serial.print("Press ");
  Serial.println((int)indexChar);
  digitalWrite(Bleds[indexChar], HIGH);
  digitalWrite(leds[indexChar], HIGH);
}

void click(void* index) {
  char indexChar = *(char*)index;
  Serial.print("Click ");
  Serial.println((int)indexChar);
  digitalWrite(Bleds[indexChar], LOW);
  digitalWrite(leds[indexChar], LOW);
}

// void doubleClick(void* index) {
//   char indexChar = *(char*)index;
//   Serial.print("Double Click ");
//   Serial.println((int)indexChar);
//   // digitalWrite(Bleds[indexChar], HIGH);
//   // digitalWrite(leds[indexChar], HIGH);
// }

// void multiClick(void* index) {
//   char indexChar = *(char*)index;
//   Serial.print("Multi Click ");
//   Serial.println((int)indexChar);
//   // digitalWrite(Bleds[indexChar], LOW);
//   // digitalWrite(leds[indexChar], LOW);
// }

// void longPressStart(void* index) {
//   char indexChar = *(char*)index;
//   Serial.print("Long Press Start ");
//   Serial.println((int)indexChar);
//   // digitalWrite(Bleds[indexChar], HIGH);
//   // digitalWrite(leds[indexChar], HIGH);
// }

void longPressStop(void* index) {
  char indexChar = *(char*)index;
  Serial.print("Long Press Stop ");
  Serial.println((int)indexChar);
  digitalWrite(Bleds[indexChar], LOW);
  digitalWrite(leds[indexChar], LOW);
}

// void duringLongPress(void* index) {
//   char indexChar = *(char*)index;
//   Serial.print("During Long Press ");
//   Serial.println((int)indexChar);
//   // digitalWrite(Bleds[indexChar], HIGH);
//   // digitalWrite(leds[indexChar], HIGH);
// }

// void idle() {
//   // char indexChar = *(char*)index;
//   Serial.print("Idle ");
//   // Serial.println((int)indexChar);
//   // digitalWrite(Bleds[indexChar], LOW);
//   // digitalWrite(leds[indexChar], LOW);
// }
