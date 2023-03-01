/*
  Getting the alarm to fire a periodic interrupt on the RV-8803 Real Time Clock
  By: Andy England
  SparkFun Electronics
  Date: 3/2/2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14642

  This example shows how to generate a periodic 1s/1minute interrupt pulse

  Hardware Connections:
    Plug the RTC into the Qwiic port on your microcontroller or on your Qwiic shield/adapter.
    If you are using an adapter cable, here is the wire color scheme: 
    Black=GND, Red=3.3V, Blue=SDA, Yellow=SCL
    Open the serial monitor at 115200 baud
*/


#include <RTC/rtc.h>
#include <MyArduino/myArduino.h>
#include <mySDCard/mySD.h>

const int chipSelect=10;
MySDClass mysd(chipSelect);


const int INT_PIN=2;

const int MININTERVAL=0;
const int HOURINTERVAL=1;
const int DAYINTERVAL=0;

int loopnumber=0;

void wakeuproutine(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);  
  delay(1000);
  mysd.writeData("Loop number"+String(loopnumber*MININTERVAL));
  mysd.closeFile();

}

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  pinMode(chipSelect,OUTPUT);
  
  mysd.begin();

  rtcConnect();
  pinMode(INT_PIN, INPUT_PULLUP);
}


void loop()
{
  loopnumber+=MININTERVAL;


  setAlarmInterval(MININTERVAL,HOURINTERVAL,DAYINTERVAL);
  wakeuproutine();
  sleepmcu(INT_PIN);
  
}

