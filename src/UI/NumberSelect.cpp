#include "Helper/IncludeAll.h"

void NumberSelect::draw() {
  lcd.setFont(u8g2_font_t0_11_me);

  int prefixShift = 0;
  if (prefix)
  {
    prefixShift = lcd.getUTF8Width(prefix);
    lcd.drawUTF8(x, y, prefix);
  }

  if (suffix)
  {
    lcd.drawUTF8(x + prefixShift + digits * 6, y, suffix);
  }
  
  char buf1[10];
  sprintf(buf1, "%%0%dd", digits);
  char buf2[100];
  sprintf(buf2, buf1, *value);
  lcd.drawStr(x + prefixShift, y, buf2);

  if (focused) {
    lcd.drawLine(x + prefixShift, y + 1, x + prefixShift + digits * 6 - 1, y + 1);
  }
};

void NumberSelect::focus() {
  Component::focus();

  InputManager::focusRawInput = [](byte pin, bool release, bool longPress,
                              int change) {
    NumberSelect *numberSelect = (NumberSelect *)getCurrentFocus();

    switch (pin) {
    case ROTARY_LCD_RIGHT:
    case BUTTON_U:
      if (!release && longPress) {
        numberSelect->taskId = taskManager.scheduleFixedRate(700, []() {
          ((NumberSelect *)getCurrentFocus())->countUp(true);
          UI::reRender();
        });
      }

      if (release && longPress && numberSelect->taskId != -1) {
        taskManager.cancelTask(numberSelect->taskId);
        numberSelect->taskId = -1;
      }

      if (release && !longPress) {
        numberSelect->countUp();
        UI::reRender();
      }
      break;
    case ROTARY_LCD_LEFT:
    case BUTTON_D:
      if (!release && longPress) {
        numberSelect->taskId = taskManager.scheduleFixedRate(700, []() {
          ((NumberSelect *)getCurrentFocus())->countDown(true);
          UI::reRender();
        });
      }

      if (release && longPress && numberSelect->taskId != -1) {
        taskManager.cancelTask(numberSelect->taskId);
        numberSelect->taskId = -1;
      }

      if (release && !longPress) {
        numberSelect->countDown();
        UI::reRender();
      }
      break;

    default:
      return false;
      break;
    }
    return true;
  };

  onBlur = [](Component *component){
    InputManager::focusRawInput = nullptr;
  };
};

// void NumberSelect::blur();
// {
//   Component::blur();
//   Serial1.println("Blur Number");
// }

void NumberSelect::countUp(bool bigStep = false) {
  int stepSize = bigStep ? bigStepSize : this->stepSize;
  if (hasBounds) {
    if (*value + stepSize <= maxValue)
      *value = *value + stepSize;
    else if (loop)
      *value = minValue;
  } else
    *value = *value + stepSize;
};

void NumberSelect::countDown(bool bigStep = false) {
  int stepSize = bigStep ? bigStepSize : this->stepSize;
  if (hasBounds) {
    if (*value - stepSize >= minValue)
      *value = *value - stepSize;
    else if (loop)
      *value = maxValue;
  } else if (allowNegative || *value - stepSize >= 0) {
    *value = *value - stepSize;
  }
};

void NumberSelect::setBounds(int minValue, int maxValue) {
  hasBounds = true;
  this->minValue = minValue;
  this->maxValue = maxValue;

  int digits = 1;
  int tempMax = max(abs(minValue), abs(maxValue));
  while (tempMax >= 10) {
    tempMax /= 10;
    digits++;
  }

  if (minValue < 0)
    digits++;

  this->digits = digits;
};
