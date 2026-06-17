/*
  Florida Polytechnic University
  IEEE - Computer Society
  Escape Room - Module 1
  Written by Ramiro Rojas, Aug 2025

  This is exactly what was uploaded to the Arduino UNO board.
  Due to the short amount of time spent working on this project,
  this code is not commented and needs cleaning up.
*/

const int LED1 = A5;
const int LED2 = A4;
const int LED3 = 12;
const int LED4 = 13;

const int OUT1 = 4;
const int OUT2 = 5;
const int OUT3 = 6;
const int OUT4 = 7;

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// const int RES1 = 330;
// const int RES2 = 1000;
// const int RES3 = 2000;
// const int RES4 = 5000;
const int RES1 = A3;
const int RES2 = A2;
const int RES3 = A1;
const int RES4 = A0;

const int leds[4] = {LED1, LED2, LED3, LED4};
const int outs[4] = {OUT1, OUT2, OUT3, OUT4};

// const int ins[4] = {IN1, IN2, IN3, IN4};
// const int ins[4] = {IN3, IN1, IN2, IN4};
const int ins[4] = {IN2, IN3, IN1, IN4};

const int res[4] = {RES1, RES2, RES3, RES4};

// const int vals[4] = {200, 820, 1000, 6200};
const int vals[4] = {820, 6200, 1000, 200};

bool cablesWin = false;
bool resistorsWin = false;

int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(IN3, INPUT_PULLUP);
  pinMode(IN4, INPUT_PULLUP);
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
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      // Serial.println("Test");
    }
  } else if(state == 1) {
    checkCables();
    checkResistors();
    if(cablesWin == true && resistorsWin == true) {
      state = 2;
      Serial.print(1);
    }
  } else if(state == 2) {
    ;
  }
}

void resetPins() {
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT2, HIGH);
  digitalWrite(OUT3, HIGH);
  digitalWrite(OUT4, HIGH);
}

void checkCables() {
  int count = 0;
  for(int i = 0; i < 4; i++) {
    resetPins();
    digitalWrite(outs[i], LOW);
    // Serial.print(digitalRead(ins[i]));
    // Serial.print("\t");
    if(digitalRead(ins[i]) == LOW) {
      count++;
    }
  }
  // Serial.println();
  if(count == 4 && cablesWin == false) {
    Serial.println("Cables Win");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    cablesWin = true;
  } else if(count != 4 && cablesWin == true) {
    Serial.println("Cables Reset");
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    cablesWin = false;
  }
}

void checkResistors() {
  int count = 0;
  for(int i = 0; i < 4; i++) {
    // Serial.print(analogRead(res[i]) * 5.0/1023);
    // Serial.print(isWithinRange(analogRead(res[i]) * 5.0/1023, vals[i]));
    // Serial.print(vals[i]);
    if(isWithinRange(analogRead(res[i]) * 5.0/1023, vals[i])) {
      count++;
    }
    
    // Serial.print("\t");
  }
  // Serial.println();
  if(count == 4 && resistorsWin == false) {
    Serial.println("Resistors Win");
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    resistorsWin = true;
  } else if(count != 4 && resistorsWin == true) {
    Serial.println("Resistors Reset");
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    resistorsWin = false;
  }
}

bool isWithinRange(float reading, int target) {
  float vin = 5.0;
  float r1 = 1000.0;
  float vout = (vin * target) / (r1 + target);
  return (reading >= (vout - 0.1) && reading <= (vout + 0.1));
}