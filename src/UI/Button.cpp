#include "Helper/IncludeAll.h"

void Button::draw()
{
  if (focused)
  {
    lcd.drawBox(x, y, width, height);
    lcd.setFontMode(1);
    lcd.setDrawColor(2);
  }
  else
  {
    lcd.setFontMode(1);
    lcd.drawFrame(x, y, width, height);
  }

  if (label)
    Label::drawSimple(x + 1, y + 11, label);
};

void Button::focus()
{
  Component::focus();

  InputManager::focusOnInput = [](byte pin, bool longPress, int change) {
    Button *button = (Button *)getCurrentFocus();
    switch (pin)
    {
    case BUTTON_R:
      if (!InputManager::rotated)
        return false;
      else
        button->fireOnClick(longPress);
      break;
    case BUTTON_U:
      if (InputManager::rotated)
        return false;
    case BUTTON_LCD_ROTARY:
      button->fireOnClick(longPress);
      break;
    default:
      return false;
      break;
    }
    return true;
  };
};

void Button::fireOnClick(bool longPress)
{
  if (onClick && (!longPress || !onLongClick))
    onClick(this);
  else if (longPress && onLongClick)
    onLongClick(this);
};

// -----------------------------------------

void ToggleButton::draw()
{
  Button::draw();
  lcd.drawFrame(x - 2, y - 2, width + 4, height + 4);
  if (!*toggled)
  {
    lcd.setDrawColor(0);
    lcd.drawVLine(x - 2, y, height);
    lcd.drawVLine(x + width + 1, y, height);
    lcd.drawHLine(x, y - 2, width);
    lcd.drawHLine(x, y + height + 1, width);
    lcd.setDrawColor(1);
  }
}

void ToggleButton::fireOnClick(bool longPress)
{
  *toggled = !*toggled;
  Button::fireOnClick(longPress);
};
