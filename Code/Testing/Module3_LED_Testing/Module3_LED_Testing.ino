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
