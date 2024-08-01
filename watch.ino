#include "config.h"
#include <soc/rtc.h>
#include <time.h>
#include <string>
#include <ostream>

TTGOClass *ttgo;
String string;

uint8_t hour, minute, sec, day, month;

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
  byte xpos = 80;
  byte ypos = 40;

  RTC_Date tnow = ttgo->rtc->getDateTime();
  hour = tnow.hour;
  minute = tnow.minute;
  sec = tnow.second;
  day = tnow.day;
  month = tnow.month;
  std::ostringstream oss;
  oss << hour << ':' << minute;
  ttgo->tft->drawString(oss.str(), xpos, ypos);

  // if(hour<10) ttgo->tft->drawChar('0', xpos, ypos);
  // ttgo->tft->drawNumber(hour, xpos, ypos);
  // ttgo->tft->drawChar(':', xpos+60, ypos);
  /*
  if(minute<10) ttgo->tft->drawChar('0',xpos+25,ypos);
  ttgo->tft->drawNumber(minute,xpos+25,ypos);
  if(sec<10) ttgo->tft->drawChar('0',xpos+30,ypos);
  ttgo->tft->drawNumber(sec,xpos+30,ypos);
  */
}