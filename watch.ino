#include "config.h"
#include <soc/rtc.h>
#include <time.h>

TTGOClass *ttgo;

String hour, minute, sec, day, month;

void setup() {
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->rtc->check();
  ttgo->rtc->syncToSystem();
  ttgo->tft->setTextFont(7);
  ttgo->tft->setTextColor(0x229c, TFT_BLACK);
  ttgo->openBL();
  
}

void loop() {
  dispTime();
  delay(500);

}

void dispTime() {
  ttgo->tft->setTextSize(1);
  byte xpos = 5;
  byte ypos = 5;

  RTC_Date tnow = ttgo->rtc->getDateTime();

  uint8_t hourest = tnow.hour-4;

  month = (tnow.month < 10) ? String(0)+String(tnow.month) : String(tnow.month);;
  day = (tnow.day < 10) ? String(0)+String(tnow.day) : String(tnow.day);;
  hour = (hourest < 0) ? String(12 + hourest) : String(hourest);
  minute = (tnow.minute < 10) ? String(0)+String(tnow.minute) : String(tnow.minute);;
  sec = (tnow.second < 10) ? String(0)+String(tnow.second) : String(tnow.second);

  String time = hour + ":" + minute + ":" + sec;
  ttgo->tft->drawString(time, xpos, ypos);
}