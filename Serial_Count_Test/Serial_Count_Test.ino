void setup(){
  Serial.begin(9600);
}

void loop(){
  int count = 0;
  count = count + 1;
  Serial.println(count);
  delay(500);
}
