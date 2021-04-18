#include "Helper/IncludeAll.h"

void Button::draw() {
  if (focused) {
    lcd.drawBox(x, y, width, height);
    lcd.setFontMode(1);
    lcd.setDrawColor(2);
  } else {
    lcd.setFontMode(1);

    // lcd.drawRFrame(x, y, width, height, cornerRadius);
    lcd.drawFrame(x, y, width, height);
  }

  if (label)
    Label::drawSimple(x + 1, y + 11, label);
};

void Button::focus() {
  Component::focus();

  InputManager::focusOnInput = [](byte pin, bool longPress, int change) {
    Button *button = (Button*) getCurrentFocus();
    switch (pin) {
    case BUTTON_U:
      button->fireOnClick();
      break;
    default:
      return false;
      break;
    }
    return true;
  };
};

void Button::fireOnClick() {
  if (onClick)
    onClick(this);
};
