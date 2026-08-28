#include <OneButton.h>

OneButton button1(32, true, true);
OneButton button2(35, true, false);
OneButton button3(34, true, false);
OneButton button4(39, true, false);
OneButton button5(36, true, false);

char Bled1 = 14;
char Bled2 = 27;
char Bled3 = 26;
char Bled4 = 25;
char Bled5 = 33;
char led1 = 4;
char led2 = 18;
char led3 = 19;
char led4 = 21;
char led5 = 22;
char led6 = 23;

void setup() {
  Serial.begin(115200);
  button1.attachPress(press1);
  button1.attachClick(click1);
  button2.attachPress(press2);
  button2.attachClick(click2);
  button3.attachPress(press3);
  button3.attachClick(click3);
  button4.attachPress(press4);
  button4.attachClick(click4);
  button5.attachPress(press5);
  button5.attachClick(click5);
  pinMode(Bled1, OUTPUT);
  pinMode(Bled2, OUTPUT);
  pinMode(Bled3, OUTPUT);
  pinMode(Bled4, OUTPUT);
  pinMode(Bled5, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  Serial.println("Started");
}

void loop() {
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();
  delay(10);
}

void press1() {
  Serial.println("Press 1");
  digitalWrite(Bled1, HIGH);
  digitalWrite(led1, HIGH);
}

void click1() {
  Serial.println("Click 1");
  digitalWrite(Bled1, LOW);
  digitalWrite(led1, LOW);
}

void press2() {
  Serial.println("Press 2");
  digitalWrite(Bled2, HIGH);
  digitalWrite(led2, HIGH);
}

void click2() {
  Serial.println("Click 2");
  digitalWrite(Bled2, LOW);
  digitalWrite(led2, LOW);
}

void press3() {
  Serial.println("Press 3");
  digitalWrite(Bled3, HIGH);
  digitalWrite(led3, HIGH);
}

void click3() {
  Serial.println("Click 3");
  digitalWrite(Bled3, LOW);
  digitalWrite(led3, LOW);
}

void press4() {
  Serial.println("Press 4");
  digitalWrite(Bled4, HIGH);
  digitalWrite(led4, HIGH);
}

void click4() {
  Serial.println("Click 4");
  digitalWrite(Bled4, LOW);
  digitalWrite(led4, LOW);
}

void press5() {
  Serial.println("Press 5");
  digitalWrite(Bled5, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
}

void click5() {
  Serial.println("Click 5");
  digitalWrite(Bled5, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
}