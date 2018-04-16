int LEDpin, rx, tx;
char s[1];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LEDpin = 8;
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.readBytesUntil('\n', s, 1);
  
  if (s[0] == '1') {
    digitalWrite(LEDpin, LOW);
  } else {
    digitalWrite(LEDpin, HIGH);
  }
  Serial.println("Hello world!");
}
