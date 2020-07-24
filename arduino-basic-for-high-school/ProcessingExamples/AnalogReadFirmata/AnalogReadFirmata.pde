import processing.serial.*;
import cc.arduino.*;
Arduino arduino = new Arduino(this, Arduino.list()[3], 57600);
int ledPin=10,sensorPin=0;
PFont myFont;
long lastTime=0;
int analogValue=0;
void setup() {
  size(640,480);
  shapeMode(CENTER);
  background(255);
  myFont=createFont("微軟正黑體",32);
  textFont(myFont, 96);
  textAlign(CENTER);
  for(int i=0;i<Arduino.list().length;i++){
    println(Arduino.list()[i]);
  }
  
}

void draw() {
  background(analogValue/4);
  fill(#5E03FF);
  text("A0數值:"+analogValue, width/2, height/2);
  if(millis()-lastTime>1000){
    lastTime=millis();
    analogValue=arduino.analogRead(sensorPin);
  }
  
  
}
