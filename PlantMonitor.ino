// Second WemakeThings sample

#include <Wire.h>

void writeI2CRegister8bit(int addr, int value) {
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned int readI2CRegister16bit(int addr, int reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(20);
  Wire.requestFrom(addr, 2);
  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  return t;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  writeI2CRegister8bit(0x20, 6); //reset
}
char buff[2];
void loop() {
  unsigned int val = readI2CRegister16bit(0x20,0); // reading CHirp Capacitor sensor (water level)
  int mappedVal = map( val, 230, 510,0,9);        // mapping values to 0-9 scale
  Serial.println(val);    
  Serial.print(" mapped val is ");
  String str = String(mappedVal);                 // convert mapped value to string for brainduino
  str.toCharArray(buff,2);
  Serial.print('0');                              // Initial 0 to let brainduino know information comming from chirp
  Serial.println(buff);                             // Water level 0-9 scale
  
  if( mappedVal < 3){
    Serial.print(" Water Plant");                 // Water level low turn on faucet for a sec
    digitalWrite(10, HIGH);
    delay(1000); // leave valve open for 1 sec to prevent overflow of water
  }
  else if( mappedVal >= 2 && mappedVal <= 4){
    Serial.print(" Ideal water level");           // nothing to be done
    digitalWrite(10, LOW);
    delay(1000);
  }
  else if( mappedVal >=5 && mappedVal <=6){
    Serial.print(" OverWatered turn on light");   // a little more water than wanted
    digitalWrite(10, LOW);
    delay(1000);
  }
  else{
    Serial.print(" Might As well keep plant in a bowl of water");  
    digitalWrite(10, LOW);
    delay(1000);
  }

//  delay(1500);
//  Serial.print(readI2CRegister16bit(0x20, 5)); //temperature register
//  Serial.print(", ");
//  writeI2CRegister8bit(0x20, 3); //request light measurement 
//  Serial.println(readI2CRegister16bit(0x20, 4)); //read light register
}
