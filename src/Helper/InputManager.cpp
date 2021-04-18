#include "Helper/IncludeAll.h"

OnInput *InputManager::defaultOnInput = nullptr;
OnInput *InputManager::focusOnInput = nullptr;
OnInput *InputManager::customOnInput = nullptr;
RawInput *InputManager::rawInput = nullptr;
byte InputManager::analogButtonCount = 0;
AnalogButtonHelper *InputManager::analogButtons[5] = {nullptr, nullptr, nullptr,
                                                      nullptr, nullptr};

void InputManager::addButton(byte pin) {
  switches.addSwitch(pin, [](pinid_t pin, bool heldDown) {
    if (rawInput && rawInput(pin, false, heldDown, 0))
      return;
    if (heldDown)
      InputManager::dispatchOnInput(pin, true, 0);
  });
  switches.onRelease(pin, [](pinid_t pin, bool heldDown) {
    if (rawInput && rawInput(pin, true, heldDown, 0))
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
};

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
}

// -----------------------------------------

byte RotaryHelper::pinA = 0;
byte RotaryHelper::pinB = 0;
int RotaryHelper::lastClicked = 0;

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

                    if (diff > 500) {
                      Serial1.print("Diff: ");
                      Serial1.println(diff);
                      RotaryHelper::lastClicked = mill;
                      bool left = digitalRead(RotaryHelper::pinB) == LOW;
                      byte pin = left ? RotaryHelper::pinB : RotaryHelper::pinA;
                      if (InputManager::rawInput &&
                          InputManager::rawInput(pin, true, false, 0))
                        return;

                      InputManager::dispatchOnInput(pin, false, left ? -1 : 1);

                      Serial1.println("");
                    }

                  },
                  LOW);
};

// ------------------------

AnalogButtonHelper::AnalogButtonHelper(uint8_t pin) : pin(pin) {
  pinMode(pin, INPUT_PULLUP);
};

void AnalogButtonHelper::check() {
  bool p = analogRead(pin) < 250;
  unsigned long mill = millis();
  unsigned long diff = mill - lastClicked;
  // Serial1.print("Check");
  // Serial1.println(analogRead(pin));
  if (p && !pressed && diff > 100) {
    Serial.println("Analog Pressed");
    pressed = true;
    lastClicked = mill;
    if (InputManager::rawInput && InputManager::rawInput(pin, false, false, 0))
      return;
  } else if (p && pressed && diff > 250) {
    Serial.println("Analog Long Pressed");
    if (InputManager::rawInput && InputManager::rawInput(pin, false, true, 0))
      return;
    InputManager::dispatchOnInput(pin, true, 0);
  } else if (!p && pressed && diff > 250) {
    Serial.println("Analog Long Released");
    pressed = false;
    if (InputManager::rawInput && InputManager::rawInput(pin, true, true, 0))
      return;
  } else if (!p && pressed && diff > 100) {
    Serial.println("Analog Released");
    pressed = false;
    if (InputManager::rawInput && InputManager::rawInput(pin, true, false, 0))
      return;
    InputManager::dispatchOnInput(pin, false, 0);
  }
}