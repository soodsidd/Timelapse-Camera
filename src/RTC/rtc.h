#ifndef RTC_H
#define RTC_H

#include <SparkFun_RV8803.h> //Get the library here:http://librarymanager/All#SparkFun_RV-8803

// #define SETTIME=True

extern RV8803 rtc;
void rtcConnect();

void setAlarmInterval(int mins=0, int hours=0, int days=0);

#endif //RTC_H