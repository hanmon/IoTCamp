/*
 * Copyright (c) 2015 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Seeed
 * Modified Time: July 2015
 * Description: Connect the IR receiver pins to D2 for this demo. You can see the remote control's infrared data 
 *                that received through a serial port terminal, then write the received infrared data into send.ino 
 *                and downloaded to the board with Infrared Emitter Grove, so you can send the same data with 
 *                remote control's button.
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * 2016/04/06 refined by RTK
 */

#include <IRSendRev.h>

#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6
void setColor(int red, int green, int blue);
// Ameba need using pin that has interrupt
const int pinRecv = 3;              // ir receiver connect to D3

/*
 *  This sketch shows how to use Car2wd class to control L298N on 2WD car
 *
 **/

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

long lastValue = 0;
long resultValue = 0;
void setup()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.begin(9600);
    IR.Init(pinRecv);
    Serial.println("init over");
 
}

unsigned char dta[20];

void loop()
{
  if(IR.IsDta())                  // get IR data
    {
        IR.Recv(dta);               // receive data to dta
 
        lastValue = (dta[6]*256*256*256)+(dta[7]*256*256) +(dta[8]*256)+(dta[9]);  
        Serial.println(lastValue);
        Serial.println("+------------------------------------------------------+\r\n\r\n");
     
    if(lastValue == 8415){
        setColor(255, 0, 0); // red
    }else if(lastValue == -24481){
       setColor(0, 255, 0); // green
    }else if(lastValue == 24735){
      setColor(0, 0, 255); // blue
    }else if(lastValue == -8161){
      setColor(255, 255, 255); // White  
    }else if(lastValue == 10455){
      setColor(255, 255, 0); // yellow
    }else if(lastValue == 26775){
      setColor(255, 0, 255); // purple
    } else if(lastValue == -20401){  
      setColor(0, 255, 255); // aqua
    } else if(lastValue == 16575){  
      setColor(0, 0, 0); // Trun OFF
    }else if(lastValue == -16321){  
      setColor(255, 255, 255); // Trun Light ON
    }
  }
}

void setColor(int red, int green, int blue)
{
  
#ifdef COMMON_ANODE
red = 255 - red;
green = 255 - green;
blue = 255 - blue;
#endif

analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}


