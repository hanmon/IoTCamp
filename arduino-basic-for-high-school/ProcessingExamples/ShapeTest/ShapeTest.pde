PShape bOff,bOn;
boolean bulbState=false;
void setup() {
  size(640,480);
  bOff = loadShape("bulb_off.svg");
  bOn = loadShape("bulb_on.svg");
  shapeMode(CENTER);
  background(255);
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
  bulbState=!bulbState;
}
