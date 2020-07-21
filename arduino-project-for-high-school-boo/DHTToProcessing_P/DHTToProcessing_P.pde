// Processing Sketch
import processing.serial.*;

Serial myPort;        // Create object from Serial class
short portIndex = 0;  // select the com port, 0 is the first port
char HEADER = 'H';
int value1;         // Data received from the serial port
float humidity=0, temperature=0;
//設定字體
PFont myFont;

//text("word", 10, 50);


void setup()
{
  size(400, 250);
  textSize(100);//設定字型大小
  // Open whatever serial port is connected to Arduino.
  String portName = Serial.list()[portIndex];
  println(Serial.list());
  println("連接到序列埠：" + Serial.list()[portIndex]);
  myPort = new Serial(this, portName, 115200); 
  //println(PFont.list());
  myFont=createFont("微軟正黑體",64);
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
        dhtArray=rxStrBuffer.split(",");
        humidity=Float.parseFloat(dhtArray[0]);
        temperature=Float.parseFloat(dhtArray[1]);
        println("Humidity:"+ humidity);
        println("Temperature:"+ temperature);
      }
    }
  }
  background(#03DBFF);             // Set background to white
  textAlign(CENTER, CENTER);
  text("濕度："+humidity, width/2, height/3);
  text("溫度："+temperature, width/2, height*2/3);//將val值顯示並定位在畫面上
  fill(0);                     // set fill to black
}
