#include "config.h"
#include <soc/rtc.h>
#include <time.h>

TTGOClass *ttgo;

uint8_t hour, minute, sec, day, month;
byte colon = 0;

byte xpos = 80;
byte ypos = 40;

void setup() {
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->rtc->check();
  ttgo->rtc->syncToSystem();
  ttgo->tft->setTextFont(7);
  ttgo->tft->setTextColor(0x19bdbd, TFT_BLACK);
  ttgo->tft->setTextSize(1);
  ttgo->openBL();
  
}

void loop() {
  dispTime();
  delay(500);

}

void dispTime() {
  RTC_Date tnow = ttgo->rtc->getDateTime();
  hour = tnow.hour;
  minute = tnow.minute;
  sec = tnow.second;
  day = tnow.day;
  month = tnow.month;

  if(hour < 10) ttgo->tft->drawChar('0', xpos, ypos);
  ttgo->tft->drawNumber(hour, xpos+10, ypos);
  
}