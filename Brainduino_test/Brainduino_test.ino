int LEDpin, rx, tx;

void setup() {
  // put your setup code here, to run once:
  LEDpin = 8;
  rx = 0;
  tx = 1; 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(rx) == HIGH) {
    digitalWrite(LEDpin, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
  }
}
