void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop() {
  Serial.write('U');
  digitalWrite(D1,HIGH);
  digitalWrite(D8,HIGH);
  delay(100);
  digitalWrite(D1,LOW);
  digitalWrite(D8,LOW);
  delay(100);
}
