/* 透過可變電阻中間腳讀取類比電壓，根據電壓值控制七段顯示器顯示的數值
   pin2~9為Led pin(A,B,C,D,E,F,G,Dp)，以A0 pin讀取類比電壓*/
//定義input pin腳位
const int ledPin[8]={9,8,7,6,5,4,3,2}; //排列:DpGFEDCBA
const byte digit[10]={
    //ABCDEFGp
    B11111100,//數字0
    B01100000,//數字1
    B11011010,//數字2
    B11110010,//數字3
    B01100110,//數字4
    B10110110,//數字5
    B00111110,//數字6
    B11100000,//數字7
    B11111110,//數字8
    B11100110,//數字9
};
const int varPin=0;
int num=0;
int aVal=0;
boolean isBitSet;
void setup() {      
  Serial.begin(115200);
  int i;
  for(i=0;i<8;i++)
    pinMode(ledPin[i],OUTPUT);
}
void loop() {
  aVal=analogRead(varPin);//  自varPin讀取類比電壓值（0~1023)
// 將類比電壓值對應到0~9的值，作為七段顯示器顯示參考值
    num=map(aVal,0,1023,0,9);
    Serial.println(num); //　
    setDigit(num);
    delay(1000);
}
void setDigit(int v){
     for(int i=0;i<8;i++){ //讀取數字所對應的各LED區段，並設定LED亮或滅
        isBitSet=bitRead(digit[v],i);
        digitalWrite(ledPin[i],isBitSet);
     }     
}

