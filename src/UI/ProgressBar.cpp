#include "Helper/IncludeAll.h"

void ProgressBar::draw(){

};

void ProgressBar::focus() { Component::focus(); };

void ProgressBar::drawSimple(byte x, byte y, byte width, int progress,
                             int maxProgress = 100, bool showDetail = false) {
  lcd.setFont(u8g2_font_t0_11_tf);
  lcd.drawStr(x - 1, y, "[");
  lcd.drawStr(x + width - 6, y, "]");

  lcd.drawBox(x + 3, y - 6, (width - 6) * (progress / (double)maxProgress), 4);

  if (showDetail) {
    int digits = 1;
    int tempMax = maxProgress;
    while (tempMax >= 10) {
      tempMax /= 10;
      digits++;
    }

    char buf1[100];
    sprintf(buf1, "%%0%dd/%%0%dd", digits, digits);
    char buf2[100];
    sprintf(buf2, buf1, progress, maxProgress);
    lcd.drawStr(x + width - ((digits * 2) + 1) * 6 , y + 10, buf2);
  }
}
