#include "Helper/IncludeAll.h"

bool InputManager::rotated = false;
OnInput *InputManager::defaultOnInput = nullptr;
OnInput *InputManager::focusOnInput = nullptr;
OnInput *InputManager::customOnInput = nullptr;
RawInput *InputManager::focusRawInput = nullptr;
RawInput *InputManager::customRawInput = nullptr;
byte InputManager::analogButtonCount = 0;
AnalogButtonHelper *InputManager::analogButtons[5] = {nullptr, nullptr, nullptr,
                                                      nullptr, nullptr};

void InputManager::addButton(byte pin) {
  switches.addSwitch(pin, [](pinid_t pin, bool heldDown) {
    if (InputManager::dispatchRawInput(pin, false, heldDown, 0))
      return;
    if (heldDown)
      InputManager::dispatchOnInput(pin, true, 0);
  });
  switches.onRelease(pin, [](pinid_t pin, bool heldDown) {
    if (InputManager::dispatchRawInput(pin, true, heldDown, 0))
      return;
    if (!heldDown)
      InputManager::dispatchOnInput(pin, false, 0);
  });
}

void InputManager::addAnalogButton(uint8_t pin) {
  analogButtons[analogButtonCount] = new AnalogButtonHelper(pin);
  analogButtonCount++;
};

void InputManager::checkButtons() {

  for (byte i = 0; i < analogButtonCount; i++) {
    analogButtons[i]->check();
  }
  Serial.println();
};

bool InputManager::dispatchRawInput(byte pin, bool release, bool longPress, int change) {
  if (UI::showDialog && release)
  {
    UI::showDialog = nullptr;
    UI::reRender();
    return true;
  }
  else if (UI::showDialog)
    return true;

  if (customRawInput && customRawInput(pin, release, longPress, change))
    return true;

  return focusRawInput && focusRawInput(pin, release, longPress, change);
}

void InputManager::dispatchOnInput(byte pin, bool longPress, int change) {
  if (customOnInput) {
    if (customOnInput(pin, longPress, change)) {
      UI::reRender();
      return;
    }
  }
  if (focusOnInput) {
    if (focusOnInput(pin, longPress, change)) {
      UI::reRender();
      return;
    }
  }
  if (defaultOnInput) {
    if (defaultOnInput(pin, longPress, change)) {
      UI::reRender();
      return;
    }
  }
  Serial1.println("Click nirgendwo abgefangen");
}

// -----------------------------------------

byte RotaryHelper::pinA = 0;
byte RotaryHelper::pinB = 0;
unsigned long RotaryHelper::lastClicked = 0;

void RotaryHelper::attach(byte pinA, byte pinB) {
  RotaryHelper::pinA = pinA;
  RotaryHelper::pinB = pinB;
  RotaryHelper::lastClicked = 0;
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA),
                  []() {
                    unsigned long mill = millis();
                    unsigned long diff = mill - RotaryHelper::lastClicked;

                    if (diff > 10) {
                      RotaryHelper::lastClicked = mill;
                      bool left = digitalRead(RotaryHelper::pinB) == LOW;
                      byte pin = left ? RotaryHelper::pinB : RotaryHelper::pinA;
                      if (InputManager::dispatchRawInput(pin, true, false, 0)) {
                        return;
                      }

                      InputManager::dispatchOnInput(pin, false, left ? -1 : 1);
                    }
                  },
                  LOW);
};

// ------------------------

unsigned long AnalogButtonHelper::lastChecked = 0;

AnalogButtonHelper::AnalogButtonHelper(uint8_t pin) : pin(pin) {
  pinMode(pin, INPUT_PULLUP);
};

void AnalogButtonHelper::check() {
  bool b = digitalRead(pin) == LOW;
  Serial.println(b);
  unsigned long mill = millis();
  if (mill - lastChecked < 1)
    return;

  lastChecked = mill;
  bool p = analogRead(pin) < 50;
  // p = false;////
  // Serial.print(pin);
  // Serial.print(":");
  // Serial.println(p);
  unsigned long diff = mill - lastClicked;
  // return;
  // Serial1.print("Check");
  // Serial1.println(analogRead(pin));
  if (p && !pressed && diff > 100) {
    // Serial.println("Analog Pressed");
    pressed = true;
    lastClicked = mill;
    if (InputManager::dispatchRawInput(pin, false, false, 0))
      return;
  } else if (p && pressed && !longPressed && diff > 420) {
    // Serial.println("Analog Long Pressed");
    longPressed = true;
    if (InputManager::dispatchRawInput(pin, false, true, 0))
      return;
    InputManager::dispatchOnInput(pin, true, 0);
  } else if (!p && pressed && longPressed && diff > 420) {
    // Serial.println("Analog Long Released");
    pressed = false;
    longPressed = false;
    if (InputManager::dispatchRawInput(pin, true, true, 0))
      return;
  } else if (!p && pressed && !longPressed && diff > 100) {
    // Serial.println("Analog Released");
    pressed = false;
    Serial.println(diff);
    if (InputManager::dispatchRawInput(pin, true, false, 0))
      return;
    InputManager::dispatchOnInput(pin, false, 0);
  }
}