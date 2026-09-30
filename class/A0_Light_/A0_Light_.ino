void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int a = analogRead(A0);
  float v=a*3.3/1023.0;

  Serial.println(v);
  delay(100);
}
