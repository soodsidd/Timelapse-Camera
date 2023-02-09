#ifndef MYARDUINO_H
#define MYARDUINO_H

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
void wakeup(void);
void sleepmcu(int interruptpin);


#endif 