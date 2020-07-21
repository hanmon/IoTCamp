import processing.serial.*;
import cc.arduino.*;
Arduino arduino = new Arduino(this, Arduino.list()[0], 57600);
int ledPin=13;
PShape bOff,bOn;
boolean bulbState=false;
void setup() {
  size(640,480);
  bOff = loadShape("bulb_off.svg");
  bOn = loadShape("bulb_on.svg");
  shapeMode(CENTER);
  background(255);
  //for initializing arduino
  arduino.pinMode(ledPin,Arduino.OUTPUT);
}

void draw() {
  background(255);
  if(bulbState){
    shape(bOn, width/2, height/2,width/2,width/2);
  }
  else{
    shape(bOff, width/2, height/2,width/2,width/2);
  }
}

void mousePressed(){
  //bulbState=!bulbState;
  bulbState=!bulbState;
  arduino.digitalWrite(ledPin,bulbState?Arduino.HIGH:Arduino.LOW);
}
