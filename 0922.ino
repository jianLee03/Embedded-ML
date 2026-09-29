/*void setup() {
  pinMode(D10, OUTPUT);
  analogWrite(D10, 128);
}

void loop(){
  
}

void setup()
{
  pinMode(D10, OUTPUT);
}

void loop()
{
  analogWrite(D10, 255);
  delay(100);
  analogWrite(D10, 191);
  delay(100);
  analogWrite(D10, 128);
  delay(100);
  analogWrite(D10, 64);
  delay(100);


void setup()
{
  //pinMode(D9, OUTPUT);
}

void loop()
{
  digitalWrite(D9, HIGH);
  delay(500);

  digitalWrite(D9, LOW);
  delay(500);
}*/

void setup(){
  Serial.begin(9600);
}

void loop(){
  int count = 0;
  count = count + 1;
  Serial.println(count);
  delay(500);
}
