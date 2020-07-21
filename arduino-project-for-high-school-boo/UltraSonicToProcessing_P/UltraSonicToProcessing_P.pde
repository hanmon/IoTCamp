// Processing Sketch
import processing.serial.*;

Serial myPort;        // Create object from Serial class
short portIndex = 3;  // select the com port, 0 is the first port
char HEADER = 'H';
int value1;         // Data received from the serial port
float humidity=0, temperature=0 ,distance=0, currentDiameter=0,easing=0.05;
//設定字體
PFont myFont;
PShape myCar;
//text("word", 10, 50);


void setup()
{
  size(600, 400);
  textSize(100);//設定字型大小
  // Open whatever serial port is connected to Arduino.
  String portName = Serial.list()[portIndex];
  println(Serial.list());
  println("連接到序列埠：" + Serial.list()[portIndex]);
  myPort = new Serial(this, portName, 115200); 
  //println(PFont.list());
  myFont=createFont("微軟正黑體",64);
  myCar=loadShape("mustang.svg");
  shapeMode(CENTER);
  textFont(myFont);
}

void draw()
{
  String rxStrBuffer, dhtArray[];
 
  // read the header and two binary *(16 bit) integers:
  if ( myPort.available() >=0)  // If at least 5 bytes are available,
  {
    if ( myPort.read() == HEADER) // is this the header
    {
      rxStrBuffer=myPort.readStringUntil('\n');
      if (rxStrBuffer!=null) {
        distance=Float.parseFloat(rxStrBuffer);
        println("Distance:"+  distance);
      }
    }
  }
  background(#03DBFF);             // Set background to white
  float diameter=map(distance,0,500,max(width,height),0);
  currentDiameter+=(diameter-currentDiameter)*easing;
  shape(myCar, width/2, height/2,currentDiameter,currentDiameter);
  //textAlign(CENTER CENTER);
  //text("距離："+ distance+"cm", width/2, height/2);
  //text("溫度："+temperature, width/2, height*2/3);//將val值顯示並定位在畫面上
  fill(0);                     // set fill to black
}
