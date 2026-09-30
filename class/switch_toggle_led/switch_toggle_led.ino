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
      //Serial.println("SWITCH ON");
    }
    else{
      digitalWrite(D13, LOW);
      //Serial.println("SWITCH OFF");
    }
    delay(50);
  }
  prevSwitchState = switchState;

  if (count == 1){
    int a = analogRead(A0);
    //float v = a * 3.3 / 1023.0;
    //Serial.print(v);
    if(a>350){
      tone(D8,2000);
    }
    else{
      noTone(D8);
    }
  }
}