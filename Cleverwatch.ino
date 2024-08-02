#include "config.h"
#include <soc/rtc.h>
#include <time.h>
#include <esp_wifi.h>

TTGOClass *ttgo;

String hour, minute, sec, day, month;
uint8_t lastmin;

void setup() {
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->lvgl_begin();
  ttgo->rtc->check();
  ttgo->rtc->syncToSystem();
  ttgo->tft->setTextColor(0x229c, TFT_BLACK);
  ttgo->openBL();
  lvthings();
  
}

void loop() {
  // lv_task_handler();
  dispTime();
  delay(17.5);
}

void lvthings(){
  lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_x(btn1, 30);
  lv_obj_set_y(btn1, 30);
  lv_obj_set_size(btn1, 200, 50);
}

void dispTime() {
  ttgo->tft->setTextFont(4);
  ttgo->tft->setTextSize(2);
  byte xpos = 5;
  byte ypos = 5;
  byte tzoffset = 4;

  RTC_Date tnow = ttgo->rtc->getDateTime();

  int8_t hourest = tnow.hour-tzoffset;

  month = (tnow.month < 10) ? String(0)+String(tnow.month) : String(tnow.month);
  day = (tnow.day < 10) ? String(0)+String(tnow.day) : String(tnow.day);
  hour = (hourest < 0) ? String(12 + hourest) : String(hourest);
  minute = (tnow.minute < 10) ? String(0)+String(tnow.minute) : String(tnow.minute);
  // sec = (tnow.second < 10) ? String(0)+String(tnow.second) : String(tnow.second);
  
  if(tnow.minute != lastmin){
    String time = hour + ":" + minute;
    // String date = day+"/"+month;
    ttgo->tft->drawString(time, xpos, ypos);
    // ttgo->tft->drawString(date, xpos+20, ypos);
    lastmin = tnow.minute;
  }
}