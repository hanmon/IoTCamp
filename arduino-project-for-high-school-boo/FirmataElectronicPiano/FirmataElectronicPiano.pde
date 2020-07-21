/**
 * Scrollbar. 
 * 
 * Move the scrollbars left and right to change the positions of the images. 
 */
import processing.serial.*;
import cc.arduino.*;
import org.firmata.Firmata;
Arduino arduino;
Arduino.FirmataWriter writer;
Firmata firmata;

final int rgbPins[]={10, 9, 8};

color redColor=color(255, 0, 0);
color greenColor=color(0, 255, 0);
color blueColor=color(0, 0, 255);
color greyColor=color(166, 189, 216);
color yellowColor=color(255, 255, 0);
color whiteColor=color(255, 255, 255);
color blackColor=color(0, 0, 0);

void setup() {
  size(640, 360);
  noStroke();

  // Prints out the available serial ports.
  println(Arduino.list());
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  writer=arduino.new FirmataWriter();
  //firmata=new Firmata();
  rectMode(CENTER);
}

void draw() {
  background(greyColor);
  noStroke();
  for (int i=0; i<15; i++){
    noStroke();
    fill(yellowColor);
    ellipse(width*(i+1)/16, height/2, width/22, width/22);
    
    
    stroke(1);
    fill(whiteColor);
    
    rect(width*(i+1)/16,height/2,width/16,height/3);
    
  }
  for (int i=0; i<15; i++){
    if(i==3 || i==6 || i==10 || i==13 || i==14){
      continue;
    }
    fill(blackColor);
    rect(width*(i+1.5)/16,height*5/12,width/32,height/6); 
  }
  // Get the position of the img1 scrollbar
  // and convert to a value to display the img1 image 
  fill(yellowColor);
}

void mousePressed() {
  for (int i=0; i<15; i++) {
    if ((mouseX<width*(i+1)/16+width/22)&&(mouseX>width*(i+1)/16-width/22)) {
      fill(0, 0, 0);
      ellipse(width*(i+1)/16, height/2, width/22, width/22);
      fill(yellowColor);
      writer.write(i);
    }
  }
}
