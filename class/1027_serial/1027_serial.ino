Uart testSerial(PA10, PA9);

void setup() {
  testSerial.begin(9600);
}

void loop() {
  testSerial.write('Q');
  delay(50);
}
