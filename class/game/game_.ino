enum State { WAIT, READY, GO, FINISH };
State st = WAIT;

unsigned long t0, waitMs, goTime;


// =====================================================
// D4 버튼
// =====================================================

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


// =====================================================
// D6 버튼
// =====================================================

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


// =====================================================
// 게임 종료음
// =====================================================

void finishSound() {

  // 띠
  tone(D9, 1200);
  delay(150);

  // 로
  tone(D9, 1600);
  delay(150);

  // 리~
  tone(D9, 2000);
  delay(400);

  noTone(D9);
}


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  pinMode(D4, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);

  pinMode(D9, OUTPUT);
  pinMode(D13, OUTPUT);

  randomSeed(analogRead(A0));

  Serial.println("D4 를 누르면 시작!");
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  readButton();
  readHit();


  switch (st) {

    // =================================================
    // 게임 시작 대기
    // =================================================

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


    // =================================================
    // 부저 울리기 전
    // =================================================

    case READY:

      // D4 부정출발
      if (justPressed) {

        Serial.println("D4 부정출발!");

        tone(D9, 200, 600);

        digitalWrite(D13, LOW);

        delay(700);

        st = FINISH;
      }


      // D6 부정출발
      else if (hit6) {

        Serial.println("D6 부정출발!");

        tone(D9, 200, 600);

        digitalWrite(D13, LOW);

        delay(700);

        st = FINISH;
      }


      // 랜덤시간이 지나면 시작
      else if (millis() - t0 > waitMs) {

        tone(D9, 2000);

        goTime = millis();

        Serial.println("GO!");

        st = GO;
      }

      break;


    // =================================================
    // 반응속도 측정
    // =================================================
    case GO:

      if (justPressed && hit6) {
        // 시작 부저 먼저 완전히 끄기
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

        // 버튼 누른 후 잠시 무음
        delay(500);

        // 그 다음 종료음
        finishSound();

        st = FINISH;
      }


      else if (justPressed) {
        // 시작 부저 즉시 끄기
        noTone(D9);
        digitalWrite(D13, LOW);
        Serial.println("D4 버튼이 먼저 눌렸습니다!");
        Serial.print("반응시간: ");
        Serial.print(d4PressTime - goTime);
        Serial.println(" ms");

        // 0.5초 무음
        delay(500);
        // 종료음
        finishSound();
        st = FINISH;
      }


      else if (hit6) {

        // 시작 부저 즉시 끄기
        noTone(D9);
        digitalWrite(D13, LOW);
        Serial.println("D6 버튼이 먼저 눌렸습니다!");
        Serial.print("반응시간: ");
        Serial.print(d6PressTime - goTime);
        Serial.println(" ms");

        // 0.5초 무음
        delay(500);
        // 종료음
        finishSound();
        st = FINISH;
      }

  break;
    
    // =================================================
    // 게임 종료 후 대기
    // =================================================

    case FINISH:

      /*
        두 버튼을 모두 뗀 상태가 되어야
        다음 게임 준비 상태로 이동한다.
      */

      if (digitalRead(D4) == HIGH &&
          digitalRead(D6) == HIGH) {

        justPressed = false;
        hit6 = false;

        Serial.println();
        Serial.println("게임 종료");
        Serial.println("D4 를 누르면 다시 시작!");

        st = WAIT;
      }

      break;
  }
}