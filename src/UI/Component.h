typedef void(ComponentCallback)(Component *component);

class Component : public UI {
public:
  byte x = 0;
  byte y = 0;
  bool focused = false;
  ComponentCallback *onFocus = nullptr;
  ComponentCallback *onBlur = nullptr;
  Component(){};
  Component(byte x, byte y) : x(x), y(y) {}
  virtual void draw() {
    Serial1.println("Draw - C");

    lcd.setFont(u8g2_font_ncenB14_tr);
    lcd.drawStr(0, 20, "Err.");
  };
  virtual void focus();
  void blur();
};