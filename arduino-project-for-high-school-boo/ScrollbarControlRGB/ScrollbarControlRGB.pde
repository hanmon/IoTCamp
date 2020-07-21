/**
 * Scrollbar. 
 * 
 * Move the scrollbars left and right to change the positions of the images. 
 */
import processing.serial.*;
import cc.arduino.*;
Arduino arduino;

final int rgbPins[]={8, 9, 10};

HScrollbar hs1, hs2, hs3;  // Two scrollbars
PImage img1, img2;  // Two images to load
color redColor=color(255, 0, 0);
color greenColor=color(0, 255, 0);
color blueColor=color(0, 0, 255);
color greyColor=color(166, 189, 216);
int rgbValues[]=new int[3];

void setup() {
  size(640, 360);
  noStroke();

  // Prints out the available serial ports.
  println(Arduino.list());
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
  arduino = new Arduino(this, Arduino.list()[0], 57600);

  hs1 = new HScrollbar(0, height/4, width, 16, 16);
  hs2 = new HScrollbar(0, height*2/4, width, 16, 16);
  hs3 = new HScrollbar(0, height*3/4, width, 16, 16);

  // Load images
  img1 = loadImage("seedTop.jpg");
  img2 = loadImage("seedBottom.jpg");
}

void draw() {
  background(greyColor);

  // Get the position of the img1 scrollbar
  // and convert to a value to display the img1 image 
  float img1Pos = hs1.getPos()-width/2;
  fill(255);
  //image(img1, width/2-img1.width/2 + img1Pos*1.5, 0);

  // Get the position of the img2 scrollbar
  // and convert to a value to display the img2 image
  float img2Pos = hs2.getPos()-width/2;
  fill(255);
  //image(img2, width/2-img2.width/2 + img2Pos*1.5, height/2);

  hs1.update();
  hs2.update();
  hs3.update();
  hs1.display(redColor);
  hs2.display(greenColor);
  hs3.display(blueColor);
  int redValue=hs1.showValue();
  int greenValue=hs2.showValue();
  int blueValue=hs3.showValue();
  println("R:"+ hs1.getPos());
  println("G:"+ hs2.getPos());
  println("B:"+ hs3.getPos());
  stroke(0);
  //line(0, height/2, width, height/2);
  if(rgbValues[0]!=redValue || rgbValues[1]!=greenValue || rgbValues[2]!=blueValue){
    arduino.analogWrite(rgbPins[0], 255-redValue);
    arduino.analogWrite(rgbPins[1], 255-greenValue);
    arduino.analogWrite(rgbPins[2], 255-blueValue);
  }
    
    rgbValues[0]=redValue;
    rgbValues[1]=greenValue;
    rgbValues[2]=blueValue;
  
}


class HScrollbar {
  int swidth, sheight;    // width and height of bar
  float xpos, ypos;       // x and y position of bar
  float spos, newspos;    // x position of slider
  float sposMin, sposMax; // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;

  HScrollbar (float xp, float yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int widthtoheight = sw - sh;
    ratio = (float)sw / (float)widthtoheight;
    xpos = xp;
    ypos = yp-sheight/2;
    spos = xpos + swidth/2 - sheight/2;
    newspos = spos;
    sposMin = xpos;
    sposMax = xpos + swidth - sheight;
    loose = l;
  }

  void update() {
    if (overEvent()) {
      over = true;
    } else {
      over = false;
    }
    if (mousePressed && over) {
      locked = true;
    }
    if (!mousePressed) {
      locked = false;
    }
    if (locked) {
      newspos = constrain(mouseX-sheight/2, sposMin, sposMax);
    }
    if (abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  float constrain(float val, float minv, float maxv) {
    return min(max(val, minv), maxv);
  }

  boolean overEvent() {
    if (mouseX > xpos && mouseX < xpos+swidth &&
      mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display(color c) {
    noStroke();
    fill(c);
    rect(xpos, ypos, swidth, sheight);
    if (over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(spos, ypos, sheight, sheight);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    return spos * ratio;
  }

  int showValue() {
    textSize(22);
    int value=(int)map(this.getPos(), 0, width, 0, 256);
    text(value, width/2, ypos*0.9);
    return value;
  }
}
