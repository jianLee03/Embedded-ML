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
}

