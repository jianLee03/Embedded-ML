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
      Serial.println("SWITCH ON");
    }
    else{
      digitalWrite(D13, LOW);
      Serial.println("SWITCH OFF");
    }
    delay(50); 
  }
  prevSwitchState = switchState;
  Serial.println(count);
}