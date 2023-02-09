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

const int INT_PIN=2;

const int MININTERVAL=1;

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  rtcConnect();
  pinMode(INT_PIN, INPUT_PULLUP);
}


void loop()
{
  setAlarmInterval(MININTERVAL,0,0);
  blink();
  sleepmcu(INT_PIN);

}

