//利用Serial.parseInt()接收多欄位int數值
int rx_buffer[3];//宣告用來接收三個欄位數值的陣列
int index=0;//接收欄位的索引值
void setup()
{
   Serial.begin(115200);
}
void loop()
{
  if(Serial.available()>0){
      for(index=0;index<3;index++)
      {
        rx_buffer[index]=Serial.parseInt(); //利用Serial.parseInt取出收到資料中的一個數值
      }
    //印出收到的數值
     for(index=0;index<3;index++)
        {
          Serial.print(rx_buffer[index]);
          Serial.print(";");
        }
     Serial.println(); 
  }
}
