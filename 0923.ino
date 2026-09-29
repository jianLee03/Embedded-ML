void setup()
{
  Serial.begin(9600);
  pinMode(D7, INPUT);
}

void loop()
{
  if (digitalRead(D7)==1)
  {
    Serial.println("DARK");
  }
  else Serial.println("LIGHT");
}
