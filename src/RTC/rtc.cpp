#include <RTC/rtc.h>

RV8803 rtc;
const bool SETTIME=false;

void rtcConnect(){
  Serial.println("Connecting to RTC");

  if (rtc.begin() == false)
  {
    Serial.println("Device not found. Please check wiring. Freezing.");
    while(1);
  }
  Serial.println("RTC online!");
  if (SETTIME){
    if (rtc.setToCompilerTime() == false)
        Serial.println("Something went wrong setting the time");
    else
        Serial.println("New time set!");
  }

  
  rtc.disableAllInterrupts();
  rtc.clearAllInterruptFlags();
}

void setAlarmInterval(int mins=0, int hours=0, int days=0){
  rtc.disableHardwareInterrupt(ALARM_INTERRUPT);
  rtc.clearInterruptFlag(FLAG_ALARM);
  bool minute_alarm_enable=mins!=0;
  bool hour_alarm_enable=hours!=0;
  bool day_alarm_enable=days!=0;


  delay(1000);

  rtc.setItemsToMatchForAlarm(minute_alarm_enable, hour_alarm_enable, day_alarm_enable, false); //The alarm interrupt compares the alarm interrupt registers with the current time registers. We must choose which registers we want to compare by setting bits to true or false
  rtc.updateTime();
  int alarmMinute = (rtc.getMinutes() + mins) % 60;
  int alarmHour = (rtc.getHours() + hours + (rtc.getMinutes() + mins) / 60) % 24;
  int alarmDay = (rtc.getWeekday() + days + (rtc.getHours() + hours + (rtc.getMinutes() + mins) / 60) / 24) % 7;
  String dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  Serial.println("Alarm set for: " + String(alarmHour) + " hours, " + String(alarmMinute) + " minutes, on " + dayNames[alarmDay]);




  rtc.setAlarmMinutes(alarmMinute);
  rtc.setAlarmHours(alarmHour);
  rtc.setAlarmWeekday(alarmDay);
  rtc.enableHardwareInterrupt(ALARM_INTERRUPT);

}
  