#include <Helper/IncludeAll.h>

Label::Label(byte x, byte y, const char *text)
    : Component(x, y), text(text), font(u8g2_font_t0_11_me){};

Label::Label(byte x, byte y, const char *text, const uint8_t *font)
    : Component(x, y), text(text), font(font){};

void Label::draw() {
  lcd.setFont(font);
  lcd.drawUTF8(x, y, text);
}

void Label::drawSimple(byte x, byte y, const char *text, const uint8_t *font /* = u8g2_font_t0_11_me */) {
  lcd.setFont(font);
  lcd.drawUTF8(x, y, text);
}

void Label::drawSimple(byte x, byte y, int glyph, const uint8_t *font /* = u8g2_font_unifont_t_symbols */) {
  lcd.setFont(font);
  lcd.drawGlyph(x, y, glyph);
}

void Label::drawSimpleN(byte x, byte y, int value, const char *prefix /* = "" */, const char *suffix /* = "" */, byte digits /* = 1 */, const char *filler /* = "0" */, const uint8_t *font /* = u8g2_font_t0_11_me */) {
  lcd.setFont(font);

  char buf1[100];
  sprintf(buf1, "%%s%%%s%dd%%s", filler, digits);

  char buf2[100];
  sprintf(buf2, buf1, prefix, value, suffix);

  lcd.drawUTF8(x, y, buf2);
}

void Label::drawSimpleD(byte x, byte y, double value, const char *prefix /* = "" */, const char *suffix /* = "" */, byte digits /* = 1 */, byte prec /* = 0 */, const char *filler /* = "" */, const uint8_t *font /* = u8g2_font_t0_11_me */) {
  lcd.setFont(font);

  char buf1[10];
  // sprintf(buf1, "%%s%%%s%dd%%s", filler, digits);
  dtostrf(value, digits, prec, buf1);

  char buf2[100];
  sprintf(buf2, "%s%s%s", prefix, buf1, suffix);
  // dtostrf(value, digits, prec, buf2);

  lcd.drawUTF8(x, y, buf2);
}

void Label::focus() {}

// --------------------------------------

Caption::Caption(byte x, byte y, const char *text)
    : Label(x, y, text, u8g2_font_7x14B_tf){};

void Caption::drawSimple(byte x, byte y, const char *text,
                         const uint8_t *font = u8g2_font_7x14B_tf) {
  lcd.setFont(font);
  if (x == 255)
    x = 128 / 2 - lcd.getUTF8Width(text) / 2;
  
  lcd.drawUTF8(x, y, text);
}
