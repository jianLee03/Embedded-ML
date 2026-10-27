void setup() {
  Serial.begin(9600);
  pinMode(D13,OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    char c = Serial.read();
    if(c=='b'||c=='B') {
      digitalWrite(D13,HIGH);}
    if(c=='s'||c=='S') {
      digitalWrite(D13,LOW);}
  }
}
