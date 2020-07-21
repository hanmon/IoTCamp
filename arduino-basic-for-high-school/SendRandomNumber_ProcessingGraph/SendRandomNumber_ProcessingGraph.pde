// Processing Sketch
import processing.serial.*;

Serial myPort;        // 宣告Serial物件，以進行Serial Port的接收
short portIndex = 0;  // 設定Com port的索引值，0為第一個Com port
char HEADER = 'S';   //起始字元為'S'
int value;         // 從Serial Port收到的位元組資料
float currentAngle=0,easing=0.05;
void setup()
{
  size(400, 250);
  textSize(100);//設定字型大小
  // Open whatever serial port is connected to Arduino.
  String portName = Serial.list()[portIndex];
  println("您的電腦目前有以下連接埠可用");
  for(String port:Serial.list()){
      println(port);
  }
  println("連接到序列埠：" + Serial.list()[portIndex]);
  myPort = new Serial(this, portName, 115200); 
}

void draw()
{
  // read the header and two binary *(16 bit) integers:
  if ( myPort.available() >= 5)  // If at least 5 bytes are available,
  {
    if( myPort.read() == HEADER) // is this the header
    {
      value = myPort.read();                 // read the least significant byte
      value =  myPort.read() * 256 + value; // add the most significant byte
      println("從Arduino接收到的數值: " + value );
    }
  }
  background(#03DBFF);             // Set background to Blue
  textAlign(CENTER,CENTER);       //設定文字定位點在正中央
  text(value, width/2,height/5);//將value值顯示並定位在畫面上
  float angle=map(value,0,65535,2*PI,PI);
  float radius=min(width/2,height/2);
  strokeWeight(20);
  translate(width/2,4*height/5);
  currentAngle+=(angle-currentAngle)*0.05;
  line(0,0,cos(currentAngle)*radius,sin(currentAngle)*radius);
  
  fill(255);                     // 設定字體填滿為白色
}
      
    
