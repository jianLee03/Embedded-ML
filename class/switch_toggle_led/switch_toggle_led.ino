int count = 0;
int prevSwitchState = HIGH;

void setup(){
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D13, OUTPUT);
}

void loop(){
  int switchState = digitalRead(D4);
  if (prevSwitchState == HIGH && switchState == LOW){
    count = 1 - count;
    if (count == 1){
      digitalWrite(D13, HIGH);
    }
    else{
      digitalWrite(D13, LOW);
    }
    delay(50);
  }
  prevSwitchState = switchState;

  if (count == 1){
    int a = analogRead(A0);
    if(a>350){
      
      tone(D8,2000);
      Serial.println("Start!");
    }
    else{
      noTone(D8);
      Serial.println("End!");
    }
  }
}