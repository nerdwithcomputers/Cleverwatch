#include "config.h"
#include <soc/rtc.h>
#include <time.h>

TTGOClass *ttgo;

uint8_t hour, minute, sec, day, month;
byte colon = 0;

byte xpos = 80;
byte ypos = 40;

void setup() {
  hour = rtc.getHours()
  minute = rtc.getMinutes();
  sec = rtc.getSeconds();
  day = rtc.getDay();
  month = rtc.getMonth();

  ttgo->tft->setTextSize(2);
}

void loop() {
  dispTime();
}

void dispTime() {
  if(hour < 10) ttgo->tft->drawChar('0', xpos, ypos);
  ttgo->tft->drawNumber(hour, xpos+10, ypos);
}