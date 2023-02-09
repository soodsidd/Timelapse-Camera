#include <MyArduino/myArduino.h>

void wakeup(){
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(1000);
}

void sleepmcu(int interruptpin){
  sei();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(interruptpin), wakeup, LOW);
  Serial.println("Sleeping now");
  delay(100);
  sleep_cpu();
  Serial.println("I am awake");
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(interruptpin));
}

