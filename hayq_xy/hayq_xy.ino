#define EN        8

//Direction pin
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7


//Step pin
#define X_STP     2
#define Y_STP     3
#define Z_STP     4


#define zProgressPin 51
#define downPin   52
#define upPin    53

#define FW   false
#define BW   true

#define pumpPinA 14
#define pumpPinB 15

#define buzzerPin 40

//DRV8825
int delayTime = 40;
bool isRun = true;

const int songLength = 160;
char notes[] = "eeeeeeegcde fffffeeeeddedg eeeeeeegcde fffffeeeggedc pedcp pedcy yedcv ggede eeeeeeegcde fffffeeeeddedg eeeeeeegcde fffffeeeggedc"; // a space represents a rest

int beats[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4};
int tempo = 300;

void cristmasSong() {
  int i, duration;
  for (i = 0; i < songLength; i++) // step through the song arrays
  { duration = beats[i] * tempo;  // length of note/rest in ms
    if (notes[i] == ' ')          // is this a rest?
    {
      delay(duration);
    }
    else                          // otherwise, play the note
    { tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo / 10);
  }
  while (true) {}
}
int frequency(char note)
{ int i;
  const int numNotes = 11;  // number of notes we're storing
  char names[] = { 'p', 'y', 'v', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {201, 222, 250, 262, 294, 330, 349, 392, 440, 494, 523};
  for (i = 0; i < numNotes; i++)
  { if (names[i] == note)
    {
      return (frequencies[i]);
    }
  }
  return (0);
}

void buzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
}

void pumpOn() {
  digitalWrite(pumpPinA, HIGH);
  digitalWrite(pumpPinB, LOW);
}


void pumpOff() {
  digitalWrite(pumpPinA, LOW);
  digitalWrite(pumpPinB, LOW);
}

//Y առանցքի շարժ
void stepY(bool dir, int cm) {
  digitalWrite(X_DIR, dir);
  digitalWrite(Y_DIR, dir);
  delay(50);
  for (int j = 0; j <= cm; j ++) {
    for (int i = 0; i < 1500; i++) {
      digitalWrite(X_STP, HIGH);
      digitalWrite(Y_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(X_STP, LOW);
      digitalWrite(Y_STP, LOW);
      delayMicroseconds(delayTime);
    }
  }

}

void stepYStop() {
  digitalWrite(X_STP, LOW);
  digitalWrite(Y_STP, LOW);
}

//x առանցքի շարժ
void stepX(bool dir, int cm) {
  digitalWrite(Z_DIR, dir);
  delay(50);
  for (int j = 0; j <= cm; j ++) {
    for (int i = 0; i < 1500; i++) {
      digitalWrite(Z_STP, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(Z_STP, LOW);
      delayMicroseconds(delayTime);
    }
  }

}


//x առանցքի շարժ
void stepXStop() {
  digitalWrite(Z_STP, LOW);
}

void runUp() {
  digitalWrite(upPin, HIGH);
  delay(100);
  digitalWrite(upPin, LOW);
  while (isZProgress()) {
    isZProgress();
  }

}

void runDown() {
  digitalWrite(downPin, HIGH);
  delay(100);
  digitalWrite(downPin, LOW);
  while (isZProgress()) {
    isZProgress();
  }

}

bool isZProgress() {
  return digitalRead(zProgressPin);
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
  pinMode(buzzerPin, OUTPUT);
  pinMode(upPin, OUTPUT);
  pinMode(downPin, OUTPUT);
  pinMode(zProgressPin, INPUT_PULLUP);
  //   pumpEmpty();
}


void pumpEmpty() {
  pumpOn();
  while (true) {}
}

void loop() {

  if (isRun) {
    for (int i = 0; i < 5; i++) {
      runDown();
      buzzer();
      delay(500);
      stepY(FW, 10);
      delay(500);
    }
    runDown();
    buzzer();
    delay(500);
    stepX(FW, 10);
    for (int i = 0; i < 5; i++) {
      runDown();
      buzzer();
      delay(500);
      stepY(BW, 10);
      delay(500);
    }
    stepX(BW, 10);
    stepY(FW, 10);
    watering();
  }

}

void watering() {
  if (isRun) {
    for (int i = 0; i < 4; i++) {
      pumpBemp();
      buzzer();
      delay(500);
      stepY(FW, 10);
      delay(500);
    }
    pumpBemp();
    buzzer();
    delay(500);
    stepX(FW, 10);
    for (int i = 0; i < 5; i++) {
      pumpBemp();
      buzzer();
      delay(500);
      stepY(BW, 10);
      delay(500);
    }
    stepX(BW, 10);
    isRun = false;
    //Finish
    cristmasSong();
  }

}

void seed() {
  stepY(FW, 10);
  delay(2000);
  runDown();
  delay(2000);
}


void pumpBemp() {
  pumpOn();
  delay(3000);
  pumpOff();
}

void test() {
  stepY(FW, 20);
  delay(1000);
  stepY(BW, 20);
  delay(1000);
  stepX(FW, 20);
  delay(1000);
  stepX(BW, 20);
  delay(1000);
}
