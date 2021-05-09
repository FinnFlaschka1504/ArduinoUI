class Button;

typedef void(OnClick)(Button *button);

class Button : public Component {
public:
  byte width = 0;
  byte height = 0;
  byte cornerRadius = 3;
  OnClick *onClick = nullptr;
  OnClick *onLongClick = nullptr;
  const char *label = nullptr;
  int icon = -1;
  Button(byte x, byte y, const char *label, byte width, byte height,
         OnClick *onClick, OnClick *onLongClick = nullptr)
      : Component(x, y), label(label), width(width), height(height),
        onClick(onClick), onLongClick(onLongClick){};
  Button(byte x, byte y, byte width, byte height, OnClick *onClick, OnClick *onLongClick = nullptr)
      : Component(x, y), width(width), height(height), onClick(onClick), onLongClick(onLongClick){};
  Button(byte x, byte y, const char *label, OnClick *onClick, OnClick *onLongClick = nullptr)
      : Component(x, y), label(label), onClick(onClick), onLongClick(onLongClick) {
    lcd.setFont(u8g2_font_t0_11_me);
    width = lcd.getUTF8Width(label) + 2;
    height = 14;
  };
  void draw() override;
  void focus() override;
  virtual void fireOnClick(bool longPress);
};

// -------------------------------

class ToggleButton : public Button {
public:
  bool *toggled = nullptr;
  ToggleButton(byte x, byte y, const char *label, bool *toggled,
               OnClick *onClick, OnClick *onLongClick = nullptr)
      : Button(x, y, label, onClick, onLongClick), toggled(toggled){};
  void draw() override;
  void fireOnClick(bool longPress) override;
};