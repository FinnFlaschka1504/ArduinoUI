#include <Helper/IncludeAll.h>

Label::Label(byte x, byte y, const char *text)
    : Component(x, y), text(text), font(u8g2_font_t0_11_tf){};

Label::Label(byte x, byte y, const char *text, const uint8_t *font)
    : Component(x, y), text(text), font(font){};

void Label::draw() {
  lcd.setFont(font);
  lcd.drawStr(x, y, text);
}

void Label::drawSimple(byte x, byte y, const char *text,
                       const uint8_t *font = u8g2_font_t0_11_tf) {
  lcd.setFont(font);
  lcd.drawStr(x, y, text);
}

void Label::drawSimple(byte x, byte y, int value, const char *prefix = "", const char *suffix = "", byte digits = 1, const char *filler = "0", const uint8_t *font = u8g2_font_t0_11_tf) {
  lcd.setFont(font);

  char buf1[100];
  sprintf(buf1, "%%s%%%s%dd%%s", filler, digits);

  char buf2[100];
  sprintf(buf2, buf1, prefix, value, suffix);

  lcd.drawStr(x, y, buf2);
}

void Label::focus() {}

// --------------------------------------

Caption::Caption(byte x, byte y, const char *text)
    : Label(x, y, text, u8g2_font_7x14B_tf){};

void Caption::drawSimple(byte x, byte y, const char *text,
                         const uint8_t *font = u8g2_font_7x14B_tf) {
  lcd.setFont(font);
  lcd.drawStr(x, y, text);
}
