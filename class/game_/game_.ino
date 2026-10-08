enum State { WAIT, READY, GO };
State st = WAIT;

unsigned long t0, waitMs, goTime;

int stable = HIGH;
int lastRead = HIGH;

unsigned long tChange = 0;
unsigned long tDown = 0;

bool justPressed = false;
unsigned long released = 0;

unsigned long d4PressTime = 0;


void readButton() {

  justPressed = false;
  released = 0;

  int r = digitalRead(D4);

  if (r != lastRead) {
    lastRead = r;
    tChange = millis();
  }

  if (millis() - tChange > 20 && r != stable) {

    stable = r;

    if (stable == LOW) {

      justPressed = true;
      tDown = millis();

      d4PressTime = millis();
    }

    else {

      released = millis() - tDown;
    }
  }
}



int last6 = HIGH;

bool hit6 = false;

unsigned long d6PressTime = 0;

void readHit() {

  int r = digitalRead(D6);

  hit6 = false;

  if (last6 == HIGH && r == LOW) {

    hit6 = true;

    d6PressTime = millis();
  }

  last6 = r;
}

void setup() {

  Serial.begin(9600);

  pinMode(D4, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);

  pinMode(D9, OUTPUT);
  pinMode(D13, OUTPUT);

  randomSeed(analogRead(A0));

  Serial.println("D4 를 누르면 시작!");
}

void loop() {

  readButton();
  readHit();

  switch (st) {

    case WAIT:

      if (justPressed) {

        Serial.println();
        Serial.println("게임 시작");

        waitMs = random(1000, 4000);

        t0 = millis();

        digitalWrite(D13, HIGH);

        st = READY;
      }

      break;


    case READY:

      if (hit6) {

        Serial.println("D6 부정출발!");

        tone(D9, 200, 600);

        digitalWrite(D13, LOW);

        st = WAIT;
      }

      else if (millis() - t0 > waitMs) {

        tone(D9, 2000);

        goTime = millis();

        Serial.println("GO!");

        st = GO;
      }

      break;


    case GO:

      if (justPressed && hit6) {

        noTone(D9);
        digitalWrite(D13, LOW);

        if (d4PressTime < d6PressTime) {

          Serial.println("D4 버튼이 먼저 눌렸습니다!");

          Serial.print("반응시간: ");
          Serial.print(d4PressTime - goTime);
          Serial.println(" ms");
        }

        else if (d6PressTime < d4PressTime) {

          Serial.println("D6 버튼이 먼저 눌렸습니다!");

          Serial.print("반응시간: ");
          Serial.print(d6PressTime - goTime);
          Serial.println(" ms");
        }

        else {

          Serial.println("D4와 D6가 동시에 눌렸습니다!");

          Serial.print("반응시간: ");
          Serial.print(d4PressTime - goTime);
          Serial.println(" ms");
        }

        st = WAIT;
      }


      else if (justPressed) {

        noTone(D9);
        digitalWrite(D13, LOW);

        Serial.println("D4 버튼이 먼저 눌렸습니다!");

        Serial.print("반응시간: ");
        Serial.print(d4PressTime - goTime);
        Serial.println(" ms");

        st = WAIT;
      }


      else if (hit6) {

        noTone(D9);
        digitalWrite(D13, LOW);

        Serial.println("D6 버튼이 먼저 눌렸습니다!");

        Serial.print("반응시간: ");
        Serial.print(d6PressTime - goTime);
        Serial.println(" ms");

        st = WAIT;
      }

      break;
  }
}