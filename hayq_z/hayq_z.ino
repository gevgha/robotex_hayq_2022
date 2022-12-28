#define EN        8

//Direction pin
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7


//Step pin
#define X_STP     2
#define Y_STP     3
#define Z_STP     4


#define isProgressPin 51
#define downPin   52
#define upPin    53

#define UP   false
#define DOWN   true

//DRV8825
int delayTime = 40;


//Y առանցքի շարժ
void nextSeed(bool dir, int steps) {
  digitalWrite(Y_STP, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(500);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(500);
  }
}

void stopNextSeed() {
  digitalWrite(Y_STP, LOW);
}

//z առանցքի շարժ
void stepZ(bool dir, int steps) {
  digitalWrite(X_DIR, dir);
  delay(50);

  for (int i = 0; i < steps; i++) {
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(delayTime);

  }
}
  //z առանցքի շարժ
  void stopZ() {
    digitalWrite(X_DIR, LOW);
    setProgress(false);
    delay(100);
  }

  void test() {
    while (true) {
      nextSeed(true, 160);
      delay(1000);
    }
  }

  void setup() {
    Serial.begin(9600);
    pinMode(X_DIR, OUTPUT);
    pinMode(X_STP, OUTPUT);
    pinMode(Y_DIR, OUTPUT);
    pinMode(Y_STP, OUTPUT);
    pinMode(Z_DIR, OUTPUT);
    pinMode(Z_STP, OUTPUT);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);

    pinMode(upPin, INPUT_PULLUP);
    pinMode(downPin, INPUT_PULLUP);
    pinMode(isProgressPin, OUTPUT);
    setProgress(false);
    delay(1000);
    //  test();
  }

  void setProgress(bool isProgress) {
    digitalWrite(isProgressPin, isProgress);
  }

  void loop() {
    int up = digitalRead(upPin);
    int down = digitalRead(downPin);
    if (down == 1) {
      setProgress(true);
      stepZ(DOWN, 8000);
      delay(100);
      nextSeed(true, 160);
      delay(100);
      stepZ(DOWN, 2000);
      delay(100);
      stepZ(UP, 10000);
      delay(100);
      setProgress(true);
    } else if (up == 1) {
      stepZ(UP, 5);
      stopZ();
    } else {
      stopZ();
    }
  }
