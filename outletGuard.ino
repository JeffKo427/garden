#include <math.h>

  int pinOut = 10; //power relay
  char message[2] ;     
  int val;  
  String str;
  String incomingByte;
  String state; 
  
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() {    
        
  val=analogRead(0);  
  int light = (val/100) - 1; //read the value between 1-9 from photoresistor   
  if (Serial.available() > 0) {//if value received from brainduino
    
    incomingByte = Serial.readString(); //integer received from brainduino
  
    if(incomingByte[0] == '1'){ //if 1 open the current flow
      digitalWrite(pinOut, HIGH);
    }
    else { //close the current flow
      digitalWrite(pinOut, LOW);
    }
  }
  else{ //else read the value from photoresistor and send it to brainduino
  if (light >= 9){ //if value of the light variable is equal or grater than 9
    str=String(9); //convert it to string
    str.toCharArray(message,2); //convert to char and insert into char array
    digitalWrite(pinOut, LOW);
    state = '1'; //state of the connection is 1 meaning its closed
  }
  else { //if value of the light variable is less than 9
    str=String(light); //convert it to string
    str.toCharArray(message,2); //convert to char and insert into char array
    digitalWrite(pinOut, HIGH);
    state = '0'; //state of the connection is 0 meaning its open
  }
  Serial.print('1'); //serial print 1 which is an arbitrary integer informing brainduino that signal comes from Oulet Guard Arduino
  Serial.print(message); //serial print value of the light
  Serial.println(state); //serial print the state of the connection
  }
  delay(500);            
}


